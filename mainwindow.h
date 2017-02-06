#pragma once

#include <QMainWindow>
#include <QScopedPointer>
#include <QGraphicsView>
#include <QGraphicsScene>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:

    QGraphicsView *v_;
};
