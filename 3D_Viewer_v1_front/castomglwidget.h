#ifndef CASTOMGLWIDGET_H
#define CASTOMGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWidget>

#include "glu.h"

class casomGLWidget : public QOpenGLWidget {
  Q_OBJECT

 private:
  float xRot, yRot, zRot;
  QPoint mPos;
  void drawCube(float a);
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 public:
  casomGLWidget(QWidget *parent = nullptr);
  ~casomGLWidget();

 private:
};

#endif  // CASTOMGLWIDGET_H
