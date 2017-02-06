#include "mainwindow.h"
#include <QHBoxLayout>
#include <QTextEdit>
#include "g_scene.h"

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   ,v_(new QGraphicsView(new GScene(this)))
{

   setLayout(new QVBoxLayout(this));

   layout()->addWidget(v_);


}

MainWindow::~MainWindow()
{
}
