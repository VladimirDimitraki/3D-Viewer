#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qgifimage.h>

#include <QColorDialog>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QPainter>
#include <QSettings>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  QString filePath;

  QString gifName;
  QGifImage *gifFrame;
  int screenCounter = 0;
  QTimer *timer;

  int rotatedX = 0;
  int rotatedY = 0;
  int rotatedZ = 0;

  // QSettings
  void writeSettings();
  void readSettings();

 private slots:
  void on_openFilePushBtn_clicked();

  void on_setBckgColor_clicked();
  void on_setLinesColor_clicked();
  void on_setVertexesColor_clicked();

  void on_linesType_activated(int index);
  void on_lineSizeEditer_valueChanged(int value);
  void on_vertexesType_activated(int index);
  void on_vertexSizeEditer_valueChanged(int value);
  void on_projectionType_activated(int index);

  // Affine_Transformations
  // Move
  void on_B_PLUS_MOVE_Z_clicked();
  void on_B_MINUS_MOVE_Z_clicked();
  void on_B_PLUS_MOVE_Y_clicked();
  void on_B_MINUS_MOVE_Y_clicked();
  void on_B_PLUS_MOVE_X_clicked();
  void on_B_MINUS_MOVE_X_clicked();

  // Size
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();

  // Rotate
  void on_ROTATE_X_PLUS_clicked();
  void on_ROTATE_X_MINUS_clicked();
  void on_ROTATE_Y_PLUS_clicked();
  void on_ROTATE_Y_MINUS_clicked();
  void on_ROTATE_Z_PLUS_clicked();
  void on_ROTATE_Z_MINUS_clicked();

  // SetDefault
  void on_SetDefault_button_clicked();
  void on_cleanPushButton_clicked();

  // Print screen & Create gif
  void on_createScreenPshBtn_clicked();
  void on_createGifPshBtn_clicked();
  void createAnimation();

 private:
  Ui::MainWindow *ui;
  int rotationPostition_;
};
#endif  // MAINWINDOW_H
