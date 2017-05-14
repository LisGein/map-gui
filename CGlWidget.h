#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <mrpt/opengl/CAxis.h>
#include <mrpt/opengl/CSetOfObjects.h>


class CGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    CGLWidget(QWidget *parent = 0);
    ~CGLWidget();
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    mrpt::opengl::CSetOfObjectsPtr &getOfObject();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    mrpt::opengl::CAxisPtr m_axis;
    mrpt::opengl::CSetOfObjectsPtr m_obj;
};

