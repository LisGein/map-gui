#include "g_scene.h"
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

GScene::GScene(QObject *parent)
   : QGraphicsScene(parent)
{
   setBackgroundBrush(QBrush(Qt::white));

   string inputFile = "/home/fedor/gsoc/gsoc/localization_demo.simplemap";
   mrpt::maps::CSimpleMap simplemap;
   CFileGZInputStream f( inputFile.c_str() );
   f >> simplemap;
   qDebug() << "done: " << simplemap.size() << " observations.";

   string configFile = "/home/fedor/gsoc/gsoc/empty.ini";
   TSetOfMetricMapInitializers		mapCfg;
   mapCfg.loadFromConfigFile( CConfigFile( configFile ), METRIC_MAP_CONFIG_SECTION );

   CMultiMetricMap		metricMap;
   metricMap.setListOfMaps( &mapCfg );

   qDebug() << "Building metric maps...";
   metricMap.loadFromProbabilisticPosesAndObservations( simplemap );

   qDebug() << "done." ;


   QPointF min, max;

   QVector<QPointF> poly;
   for (auto it = simplemap.begin(); it != simplemap.end(); ++it)
   {
      mrpt::poses::CPose3D point = it->first->getMeanVal();
      if (it == simplemap.begin())
      {
         min = QPointF(point.x(), point.y());
         max = QPointF(point.x(), point.y());
      }
      else
      {
         if (min.x() > point.x())
            min.rx() = point.x();

         if (max.x() < point.x())
            max.rx() = point.x();


         if (min.y() > point.y())
            min.ry() = point.y();

         if (max.y() < point.y())
            max.ry() = point.y();
      }
      double part_size = 3;
      QRectF r(QPointF(point.x(), point.y()) * 20, QSize(part_size, part_size));
      qDebug() << point.x() << point.y() << point.z();
      addRect(r, QPen(), QBrush(Qt::red));
      poly.append(QPointF(point.x(), point.y()) * 20);

   }
   //setSceneRect(min.x(), min.y(), min.x() + max.x(), min.y() + max.y());

   addPolygon(poly, QPen(), QBrush());


   update();

}


GScene::~GScene()
{

}
