#include "CGlWidget.h"

#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>


CGLWidget::CGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_axis(mrpt::opengl::CAxis::Create(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f))
    , m_obj(mrpt::opengl::CSetOfObjects::Create())
{

}

CGLWidget::~CGLWidget()
{
}

QSize CGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize CGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

mrpt::opengl::CSetOfObjectsPtr &CGLWidget::getOfObject()
{
    return m_obj;
}

void CGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 0);
}

void CGLWidget::paintGL()
{
    if (m_obj.pointer())
    {
        m_axis->render();
        m_obj->render();
    }
}

void CGLWidget::resizeGL(int w, int h)
{
}
