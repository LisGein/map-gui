#include "CMainWindow.h"
#include "CGraphicsView.h"

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QGraphicsView>
#include <QVBoxLayout>



CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_gl(new CGLWidget(this))
    , m_scene(new CGraphicsScene(this))
    , m_controller(*m_gl, *m_scene)
{
    initMenu();

    QWidget* w = new QWidget(this);
    w->setLayout(new QVBoxLayout);
    w->layout()->addWidget(m_gl);

    QGraphicsView * g_view = new CGraphicsView(m_scene, this);
    w->layout()->addWidget(g_view);

    QMainWindow::setCentralWidget(w);
}

CMainWindow::~CMainWindow()
{

}

void CMainWindow::initMenu()
{
    setMenuBar(new QMenuBar(this));
    QMenu* file_menu = menuBar()->addMenu(QObject::tr("File"));
    QAction* new_file  = new QAction(tr("New"), this);
    file_menu->addAction(new_file);

    QAction* load_file  = new QAction(tr("Load"), this);
    file_menu->addAction(load_file);
    QObject::connect(load_file, SIGNAL(triggered(bool)), SLOT(openMap()));
}

void CMainWindow::openMap()
{
    QString file_name = "/home/lisgein/Downloads/localization_demo.simplemap";//QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.simplemap)"));
    QString config_name = "/home/lisgein/Downloads/empty.ini";//QFileDialog::getOpenFileName(this, tr("Open Config File"), "", tr("Files (*.ini)"));
    m_controller.loadFile(file_name, config_name);
}
