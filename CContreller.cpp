#include "CContreller.h"

#include <mrpt/utils/CFileGZOutputStream.h>
#include <mrpt/utils/CFileGZInputStream.h>
#include <mrpt/utils/CConfigFile.h>
#include <mrpt/maps/TMetricMapInitializer.h>


std::string METRIC_MAP_CONFIG_SECTION  =  "MappingApplication";

CController::CController(CGLWidget& gl, CGraphicsScene& scene)
    : m_gl(gl)
    , m_scene(scene)

{

}

CController::~CController()
{
}

void CController::loadFile(const QString &file_name, const QString &config)
{
    m_simplemap = mrpt::maps::CSimpleMap();
    mrpt::utils::CFileGZInputStream file( file_name.toStdString().c_str());

    file >> m_simplemap;

    m_metricmap = mrpt::maps::CMultiMetricMap();

    mrpt::maps::TSetOfMetricMapInitializers		mapCfg;
    mapCfg.loadFromConfigFile( mrpt::utils::CConfigFile(config.toStdString()), METRIC_MAP_CONFIG_SECTION);

    m_metricmap.setListOfMaps( &mapCfg );
    m_metricmap.loadFromProbabilisticPosesAndObservations(m_simplemap);


    updateViewport();

}

void CController::updateViewport()
{
    mrpt::maps::CSimplePointsMapPtr prt = m_metricmap.getMapByClass<mrpt::maps::CSimplePointsMap>();
    prt->getAs3DObject(m_gl.getOfObject());
    m_gl.update();


    std::vector< mrpt::math::TPoint2D > ps;
    prt->getAllPoints(ps);

    m_scene.updatePoints(ps);
}

void CController::saveGridMap(const QString &file_name)
{
    std::string outprefix = file_name.toStdString();
    m_metricmap.saveMetricMapRepresentationToFile( outprefix );


    for (size_t i = 0; i < m_metricmap.m_gridMaps.size(); ++i)
    {
        std::string str = mrpt::format( "%s_gridmap_no%02u.gridmap", outprefix.c_str(), (unsigned)i );

        mrpt::utils::CFileGZOutputStream f(str);
        f << *m_metricmap.m_gridMaps[i];
    }
}
