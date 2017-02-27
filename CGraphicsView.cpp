#include "CGraphicsView.h"
#include <QScrollBar>
#include <QWheelEvent>
#include <QDebug>


CGraphicsView::CGraphicsView(QGraphicsScene* scene, QWidget* parent)
	: QGraphicsView(scene, parent)
	, m_pan_(false)
	, m_pan_start_(QPoint(-1, -1))
{
	setScene(scene);
	setHorizontalScrollBar(new QScrollBar(Qt::Horizontal, this));
	setVerticalScrollBar(new QScrollBar(Qt::Vertical, this));

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

CGraphicsView::~CGraphicsView()
{

}

void CGraphicsView::wheelEvent(QWheelEvent* event)
{
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	double scaleFactor = (event->delta() <= 0.) ? 1.0/1.15  : 1.15;

	scale(scaleFactor, scaleFactor);
}

void CGraphicsView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_pan_ = true;

		m_pan_start_ = event->pos();
		setCursor(Qt::ClosedHandCursor);
		event->accept();
	}
	else
		event->ignore();
}

void CGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	if (m_pan_)
	{
		horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - m_pan_start_.x()));
		verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - m_pan_start_.y()));

		m_pan_start_ = event->pos();
		event->accept();
	}
	else
		event->ignore();
}

void CGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
	m_pan_ = false;
	if (event->button() == Qt::LeftButton)
	{

		qDebug() << 3;
		setCursor(Qt::ArrowCursor);
		event->accept();
	}
	else
		event->ignore();
}

