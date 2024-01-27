#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>

#include "glu.h"

#ifdef __cplusplus

extern "C" {
#endif
#include "../3D_Viewer.h"

#ifdef __cplusplus
}
#endif

class MyOpenGLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  MyOpenGLWidget(QWidget *parent = nullptr);

  enum linesType { SOLID, DASHED };
  enum vertexesType { NONE, CIRCLE, SQUARE };
  enum projectionType { CENTRAL, PARALLEL };
  data_t all_data = {0, 0, 0, 0, 0, 0};
  float xRot, yRot, zRot;
  QPoint mPos;

  int widgetWidth = width();
  int widgetHeight = height();

  QColor backroundColor;
  QColor vertexesColor;
  QColor linesColor;

  int lineWidth;
  int vertexSize;

  linesType lineType;
  vertexesType vertexType;
  projectionType projection;

  void onOpenFile();
  void clearOpenGlWidget();
  void setProjection();
  void drawVertexes();
  void setLinesType();
  void drawLines();

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};

#endif  // MYOPENGLWIDGET_H
