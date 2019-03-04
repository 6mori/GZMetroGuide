#include <vector>
#include <string>
#include <map>

using namespace std;

typedef int vertex;

class Metro {
private:
  vector<vector<int> > stationGraph;
  vector<vector<int> > lineGraph;
  vector<vector<int> > stationList;

  int numOfStation;
  int numOfLine;

  void getStationList( ifstream& in );
  /*void printGraph( const vector<vector<int> >& Graph );*/
  void buildStationGraph();
  void buildLineGraph( ifstream& in );
  vertex findMinDist(int* dist, bool* known, int size);
  int shortestpath( vertex from, vertex to, vector<vector<int> >& g);

public:
  Metro();
  int getShortestPath( int beginLine, int beginStation, int endLine, int endStation );
  int getLeastExchange( int beginLine, int endLine );
};
