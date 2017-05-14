#pragma once
#include <mrpt/maps/CSimpleMap.h>
#include <mrpt/maps/CMultiMetricMap.h>

#include "CGlWidget.h"
#include "CGraphicsScene.h"


class CController
{
public:
    CController(CGLWidget &gl, CGraphicsScene &scene);
    ~CController();
    void loadFile(const QString& file_name, const QString& config);

    void updateViewport();
    void saveGridMap(const QString& file_name);


private:
    CGLWidget& m_gl;
    CGraphicsScene& m_scene;

    mrpt::maps::CSimpleMap m_simplemap;
    mrpt::maps::CMultiMetricMap m_metricmap;

};
