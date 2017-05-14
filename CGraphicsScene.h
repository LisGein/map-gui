#pragma once
#include <QGraphicsScene>
#include <mrpt/maps/CSimpleMap.h>
#include <mrpt/maps/CMultiMetricMap.h>

class CGLWidget;

class CGraphicsScene : public QGraphicsScene
{
public:
    CGraphicsScene(QWidget *parent = 0);
    virtual ~CGraphicsScene();

    void updatePoints(const std::vector< mrpt::math::TPoint2D >& points);
};
