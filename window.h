#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QString>

#include "metro.h"

using std::string;

QT_BEGIN_NAMESPACE
class QComboBox;
class QDataWidgetMapper;
class QLabel;
class QLineEdit;
class QPushButton;
class QStandardItemModel;
class QStringListModel;
class QTextEdit;
QT_END_NAMESPACE

namespace Ui {
    class Window;
}

class Window : public QWidget {
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private slots:
    void updateStation();
    void updateFlag();
    void updateResult();

private:
    void setupModel();

    Ui::Window *ui;

    //QLabel *shortestPath;
    //QLabel *leastExchange;

    QStandardItemModel *model;
    QStringListModel *lineModel;
    QList<QStringListModel*> allStations;

    bool flag;
    Metro *metro;
    QString path;
};

#endif // WINDOW_H
