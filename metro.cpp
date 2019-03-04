#include "metro.h"

#include <iostream>
#include <fstream>

#define infinity 100000

using namespace std;

void Metro::getStationList( ifstream& in ) {
  int lineSize = 0;
  in >> lineSize;
  numOfLine = lineSize;
  stationList.reserve( lineSize );
  for ( int i = 0; i < lineSize; ++i ) {
    stationList.push_back( vector<int>() );
  }
  map<string,int> name2num;
  string name;
  int count = 0;
  for ( int i = 0; i < lineSize; ++i ) {
    int stationSize;
    in >> stationSize;
    in.get();
    stationList[i].reserve( stationSize );
    for ( int j = 0; j < stationSize; ++j ) {
      getline( in, name );
      if ( name2num.count( name ) ) {
        stationList[i].push_back( name2num[name] );
      }
      else {
        stationList[i].push_back( count );
        name2num[name] = count;
        count++;
      }
    }
  }
  numOfStation = count;
}

/*void Metro::printGraph( const vector<vector<int> >& Graph ) {
  for ( int i = 0; i < Graph.size(); ++i ) {
    for ( int j = 0; j < Graph[i].size(); ++j ) {
      cout << Graph[i][j].first << " " << Graph[i][j].second << "   ";
    }
    cout << endl;
  }
  cout << endl;
}*/

void Metro::buildStationGraph() {
    stationGraph.reserve( numOfStation );
    for ( int i = 0; i < numOfStation; ++i ) {
      stationGraph.push_back( vector<int>() );
    }
    for ( int i = 0; i < numOfLine; ++i ) {
        for ( int k = 0; k < stationList[i].size()-1; ++k ) {
            stationGraph[stationList[i][k]].push_back( stationList[i][k+1] );
            stationGraph[stationList[i][k+1]].push_back( stationList[i][k] );
        }
    }
}

void Metro::buildLineGraph( ifstream& in ) { 
  lineGraph.reserve( numOfLine );
  for ( int i = 0; i < numOfLine; ++i ) {
    lineGraph.push_back( vector<int>() );
  }
  int num, a, b;
  in >> num;
  for ( int i = 0; i < num; ++i ) {
    in >> a >> b;
    lineGraph[a].push_back( b );
    lineGraph[b].push_back( a );
  }
}

vertex Metro::findMinDist(int* dist,bool* known,int size){
    vertex ret;
    int i;
    for(i=0;known[i]&&i<size;i++);
    ret = i;
    for(;i<size;i++)
        if(!known[i] && (dist[i] < dist[ret]))
            ret = i;
    return ret;
}

int Metro::shortestpath(vertex from,vertex to, vector<vector<int> >& g){
    int dist[g.size()];
    bool known[g.size()];
    for(int i=0;i<g.size();i++)
    {
        dist[i] = infinity;
        known[i] = false;
    }
    dist[from] = 0;
    while(!known[to]){
        vertex v = findMinDist(dist,known,g.size());
        known[v] = true;
        for( int i = 0; i < g[v].size(); ++i ){
            if(!known[g[v][i]] && (dist[v] + 1 < dist[g[v][i]]))
                dist[g[v][i]] = dist[v] + 1;
        }
    }
    return dist[to];
}

Metro::Metro() {
  ifstream in( "gzmetrodata.in", ios::in );
  if ( in.is_open() ) {
    getStationList( in );
    buildLineGraph( in );
    buildStationGraph();
  }
}

int Metro::getShortestPath( int beginLine, int beginStation, int endLine, int endStation ) {
  int begin = stationList[beginLine][beginStation];
  int end = stationList[endLine][endStation];
  return shortestpath( begin, end, stationGraph );
}

int Metro::getLeastExchange( int beginLine, int endLine ) {
  return shortestpath( beginLine, endLine, lineGraph );
}
