#pragma once
#include <QGraphicsScene>
#include <mrpt/maps/CSimpleMap.h>
#include <mrpt/maps/CMultiMetricMap.h>


class CGraphicsScene:  public QGraphicsScene
{
	Q_OBJECT

public:
	CGraphicsScene(QObject *parent = 0);
	virtual ~CGraphicsScene();

	void loadFile(const QString& file_name, const QString& config);
	void saveGridMap(const QString& file_name);


private:
	void loadMap(const std::string& file_name);
	void loadConfig(const std::string& file_name);
	void drawMap();


	mrpt::maps::CSimpleMap simplemap_;
	mrpt::maps::CMultiMetricMap metricmap_;
};
