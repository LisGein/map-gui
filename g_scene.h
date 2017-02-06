#pragma once

#include <QGraphicsScene>

class GScene:  public QGraphicsScene
{
   Q_OBJECT

public:
   GScene(QObject *parent = 0);
   virtual ~GScene();


private:
};
