#pragma once
#include <QGraphicsView>


class CGraphicsView:  public QGraphicsView
{
	Q_OBJECT

public:
	CGraphicsView(QGraphicsScene *scene, QWidget* parent = 0);
	virtual ~CGraphicsView();

protected:
	virtual void wheelEvent(QWheelEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);



private:
	bool m_pan_;

	QPoint m_pan_start_;


};
