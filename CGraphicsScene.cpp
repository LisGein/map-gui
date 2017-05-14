#include "CGraphicsScene.h"


CGraphicsScene::CGraphicsScene(QWidget *parent)
{
    setBackgroundBrush(QBrush(Qt::white));
}


CGraphicsScene::~CGraphicsScene()
{

}

void CGraphicsScene::updatePoints(const std::vector<mrpt::math::TPoint2D> &points)
{
    for (std::vector< mrpt::math::TPoint2D >::const_iterator it = points.begin(); it != points.end(); ++it)
    {
        double part_size = 3;
        QRectF r(QPointF(it->x, -it->y) * 20, QSize(part_size, part_size));
        addRect(r, QPen(), QBrush(Qt::red));
    }

    update();
}

