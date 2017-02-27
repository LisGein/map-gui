#include "CMainWindow.h"
#include "CGraphicsScene.h"
#include "CGraphicsView.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QGraphicsView>



CMainWindow::CMainWindow(QWidget *parent)
	: QMainWindow(parent)
	,m_scene_(new CGraphicsScene(this))
{
	initMenu();

	QGraphicsView * g_view = new CGraphicsView(m_scene_, this);
	QMainWindow::setCentralWidget(g_view);

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
	QString file_name = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.simplemap)"));
	QString config_name = QFileDialog::getOpenFileName(this, tr("Open Config File"), "", tr("Files (*.ini)"));
	m_scene_->loadFile(file_name, config_name);
}
