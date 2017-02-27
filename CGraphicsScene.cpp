#include "CGraphicsScene.h"
#include <mrpt/system/os.h>
#include <mrpt/maps/CSimpleMap.h>
#include <mrpt/maps/CMultiMetricMap.h>
#include <mrpt/utils/CConfigFile.h>
#include <mrpt/utils/CFileGZInputStream.h>
#include <mrpt/utils/CFileGZOutputStream.h>
#include <QDebug>


using namespace mrpt;
using namespace mrpt::maps;
using namespace mrpt::opengl;
using namespace mrpt::system;
using namespace mrpt::math;
using namespace mrpt::utils;
using namespace std;


string METRIC_MAP_CONFIG_SECTION  =  "MappingApplication";

CGraphicsScene::CGraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
{
	setBackgroundBrush(QBrush(Qt::white));

}


CGraphicsScene::~CGraphicsScene()
{

}

void CGraphicsScene::loadFile(const QString& file_name, const QString& config)
{
	loadMap(file_name.toStdString());
	loadConfig(config.toStdString());

	drawMap();
	update();
}

void CGraphicsScene::saveGridMap(const QString& file_name)
{
	string outprefix = file_name.toStdString();
	metricmap_.saveMetricMapRepresentationToFile( outprefix );


	for (size_t i = 0; i < metricmap_.m_gridMaps.size(); ++i)
	{
		std::string str = format( "%s_gridmap_no%02u.gridmap", outprefix.c_str(), (unsigned)i );

		CFileGZOutputStream f(str);
		f << *metricmap_.m_gridMaps[i];
	}
}

void CGraphicsScene::loadMap(const std::string& file_name)
{
	simplemap_ = mrpt::maps::CSimpleMap();
	CFileGZInputStream file( file_name.c_str());

	file >> simplemap_;

}

void CGraphicsScene::loadConfig(const std::string& file_name)
{
	metricmap_ = mrpt::maps::CMultiMetricMap();

	TSetOfMetricMapInitializers		mapCfg;
	mapCfg.loadFromConfigFile( CConfigFile(file_name), METRIC_MAP_CONFIG_SECTION);

	metricmap_.setListOfMaps( &mapCfg );
	metricmap_.loadFromProbabilisticPosesAndObservations(simplemap_);

}

void CGraphicsScene::drawMap()
{
	mrpt::maps::CSimplePointsMapPtr prt = metricmap_.getMapByClass<mrpt::maps::CSimplePointsMap>();
	std::vector< mrpt::math::TPoint2D > ps;
	prt->getAllPoints(ps);

	for (std::vector< mrpt::math::TPoint2D >::iterator it = ps.begin(); it != ps.end(); ++it)
	{
		double part_size = 3;
		QRectF r(QPointF(it->x, -it->y) * 20, QSize(part_size, part_size));
		addRect(r, QPen(), QBrush(Qt::red));
	}

	update();

}
