#pragma once
#include <QMainWindow>
#include "CContreller.h"


class CGraphicsScene;

class CMainWindow : public QMainWindow {
	Q_OBJECT

public:
	CMainWindow(QWidget *parent = 0);
	virtual ~CMainWindow();

private slots:
	void openMap();

private:
	void initMenu();

    CGLWidget *m_gl;
    CGraphicsScene *m_scene;
    CController m_controller;
};
