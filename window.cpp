#include <QtWidgets>
#include <QFile>
#include <QDir>

#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent): QWidget(parent), ui(new Ui::Window), metro(new Metro), flag(true) {

    ui->setupUi(this);
    setupModel();

    ui->result->setNum(0);
    ui->beginLineComboBox->setModel(lineModel);
    ui->endLineComboBox->setModel(lineModel);
    ui->beginStationComboBox->setModel(allStations[0]);
    ui->endStationComboBox->setModel(allStations[0]);
    ui->getResultButton->setText("查找");
    ui->getShortestPath->setText("最短路径");
    ui->getLeastExchange->setText("最小换乘");
    connect(ui->beginLineComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStation()));
    connect(ui->endLineComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStation()));
    connect(ui->getShortestPath, SIGNAL(toggled(bool)), this, SLOT(updateFlag()));
    connect(ui->getLeastExchange, SIGNAL(toggled(bool)), this, SLOT(updateFlag()));
    connect(ui->getResultButton, SIGNAL(clicked(bool)), this, SLOT(updateResult()));

    setWindowTitle("广州地铁");
}

Window::~Window() {
    delete ui;
}

void Window::updateStation() {
    ui->beginStationComboBox->setModel(allStations[ui->beginLineComboBox->currentIndex()]);
    ui->endStationComboBox->setModel(allStations[ui->endLineComboBox->currentIndex()]);
}

void Window::updateFlag() {
    if ( ui->getShortestPath->isChecked() ) {
        flag = true;
    }
    else {
        flag = false;
    }
}

void Window::updateResult() {
    if (flag) {
        ui->result->setNum(metro->getShortestPath(ui->beginLineComboBox->currentIndex(), ui->beginStationComboBox->currentIndex(), ui->endLineComboBox->currentIndex(), ui->endStationComboBox->currentIndex()));
    }
    else {
        ui->result->setNum(metro->getLeastExchange(ui->beginLineComboBox->currentIndex(), ui->endLineComboBox->currentIndex()));
    }
}

void Window::setupModel() {
    QDir dir;
    QString path = dir.currentPath();
    path.append("/gzmetro.txt");
    QFile file(path);
    QStringList items;
    QStringListModel* anonymous;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            items << line;
            allStations.push_back(anonymous);
            QStringList stationList;
            line = in.readLine();
            while (line != "0") {
                stationList << line;
                line = in.readLine();
            }
            allStations.back() = new QStringListModel(stationList, this);
        }
    }
    lineModel = new QStringListModel(items, this);
}
