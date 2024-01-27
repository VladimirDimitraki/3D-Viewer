#include "mainwindow.h"

#include <iostream>

#include "myopenglwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setWindowTitle("3D Viewer");
  timer = new QTimer(0);
  connect(timer, SIGNAL(timeout()), this, SLOT(createAnimation()));
}

MainWindow::~MainWindow() {
  writeSettings();
  free_mem(&ui->myGl->all_data);
  delete timer;
  delete ui;
}

void MainWindow::on_openFilePushBtn_clicked() {
  filePath = QFileDialog::getOpenFileName(this, "Выбрать файл", "/Users",
                                          "All Files (*.obj)");
  ui->vertexCount->setText("");
  ui->polygonCount->setText("");
  free_mem(&ui->myGl->all_data);

  QFileInfo check_file(filePath);

  ui->fileNameLabel->setText(check_file.fileName());
  QByteArray Len = filePath.toLocal8Bit();
  char *Str = Len.data();
  //  std::cout << Str << std::endl;
  if (check_file.exists(filePath)) {
    if (read_file(&ui->myGl->all_data, Str) == 0) {
      ui->vertexCount->setText(
          QString::number(ui->myGl->all_data.vertexes / 3));
      ui->polygonCount->setText(
          QString::number(ui->myGl->all_data.polygon / 4));
      ui->myGl->onOpenFile();
    } else {
      free_mem(&ui->myGl->all_data);
      ui->vertexCount->setText("");
      ui->polygonCount->setText("");
    }
  }
}

void MainWindow::on_setBckgColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select color:");
  ui->myGl->backroundColor = color;
  ui->myGl->update();
}

void MainWindow::on_setLinesColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select color:");
  ui->myGl->linesColor = color;
  ui->myGl->update();
}

void MainWindow::on_setVertexesColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select color:");
  ui->myGl->vertexesColor = color;
  ui->myGl->update();
}

// Clear Screen
void MainWindow::on_cleanPushButton_clicked() {
  // Очищаем виджет Open GL
  // Зануляем все настройки
  filePath = "";
  on_SetDefault_button_clicked();

  ui->fileNameLabel->setText("");
  ui->polygonCount->setText("");
  ui->vertexCount->setText("");
  ui->myGl->clearOpenGlWidget();
  free_mem(&ui->myGl->all_data);
}

void MainWindow::on_SetDefault_button_clicked() {
  ui->myGl->backroundColor = QColor(Qt::black);
  ui->myGl->linesColor = QColor(Qt::white);
  ui->myGl->vertexesColor = QColor(Qt::white);
  ui->myGl->lineWidth = 1;
  ui->lineSizeEditer->setValue(1);
  ui->myGl->vertexSize = 1;
  ui->vertexSizeEditer->setValue(0);
  ui->projectionType->setCurrentIndex(0);
  ui->vertexesType->setCurrentIndex(0);
  ui->linesType->setCurrentIndex(0);
  ui->myGl->projection = MyOpenGLWidget::CENTRAL;
  ui->myGl->lineType = MyOpenGLWidget::SOLID;
  ui->myGl->vertexType = MyOpenGLWidget::NONE;
  ui->myGl->xRot = 0;
  ui->myGl->yRot = 0;
  ui->myGl->zRot = 0;

  // Ставим на изначальное положение объект
  if (ui->myGl->all_data.polygons_value != NULL &&
      ui->myGl->all_data.vertex_value != NULL) {
    set_center(&ui->myGl->all_data, 0, 0, 0, 0);
  }

  ui->ROTATE_X_VALUE->setValue(0);
  ui->ROTATE_Y_VALUE->setValue(0);
  ui->ROTATE_Z_VALUE->setValue(0);

  // Clean Move
  ui->doubleSpinBox_X_MOVE->setValue(0);
  ui->doubleSpinBox_Y_MOVE->setValue(0);
  ui->doubleSpinBox_MOVE_Z->setValue(0);

  ui->myGl->update();
}

// BONUS PART 1

void MainWindow::on_linesType_activated(int index) {
  if (index == 0) {
    ui->myGl->lineType = MyOpenGLWidget::SOLID;
  } else if (index == 1) {
    ui->myGl->lineType = MyOpenGLWidget::DASHED;
  }
  ui->myGl->update();
}

void MainWindow::on_lineSizeEditer_valueChanged(int value) {
  ui->myGl->lineWidth = value;
  ui->myGl->update();
}

void MainWindow::on_vertexesType_activated(int index) {
  if (index == 0) {
    ui->myGl->vertexType = MyOpenGLWidget::NONE;
  } else if (index == 1) {
    ui->myGl->vertexType = MyOpenGLWidget::CIRCLE;
  } else if (index == 2) {
    ui->myGl->vertexType = MyOpenGLWidget::SQUARE;
  }
  ui->myGl->update();
}

void MainWindow::on_vertexSizeEditer_valueChanged(int value) {
  ui->myGl->vertexSize = value;
  ui->myGl->update();
}

void MainWindow::on_projectionType_activated(int index) {
  if (index == 0) {
    ui->myGl->projection = MyOpenGLWidget::CENTRAL;
  } else if (index == 1) {
    ui->myGl->projection = MyOpenGLWidget::PARALLEL;
  }
  ui->myGl->update();
}

void MainWindow::writeSettings() {
  QString pathSettings = QCoreApplication::applicationDirPath();
  QSettings settings(pathSettings + "/settings.ini", QSettings::IniFormat);
  settings.beginGroup("settings");

  settings.setValue("filePath", filePath);

  settings.setValue("backgroundColor", ui->myGl->backroundColor);
  settings.setValue("linesColor", ui->myGl->linesColor);
  settings.setValue("vertexesColor", ui->myGl->vertexesColor);
  settings.setValue("lineSizeEditer", ui->lineSizeEditer->value());
  settings.setValue("lineWidth", ui->myGl->lineWidth);
  settings.setValue("vertexSize", ui->myGl->vertexSize);
  settings.setValue("vertexSizeEditer", ui->vertexSizeEditer->value());

  settings.setValue("vertexesType", ui->vertexesType->currentIndex());
  settings.setValue("linesType", ui->linesType->currentIndex());
  settings.setValue("projectionType", ui->projectionType->currentIndex());

  settings.setValue("lineType", ui->myGl->lineType);
  settings.setValue("vertexType", ui->myGl->vertexType);
  settings.setValue("projection", ui->myGl->projection);

  settings.setValue("xRot", ui->myGl->xRot);
  settings.setValue("yRot", ui->myGl->yRot);
  settings.setValue("zRot", ui->myGl->zRot);

  settings.endGroup();
}

void MainWindow::readSettings() {
  QString pathSettings = QCoreApplication::applicationDirPath();
  QSettings settings(pathSettings + "/settings.ini", QSettings::IniFormat);
  settings.beginGroup("settings");

  filePath = settings.value("filePath", "").toString();

  QFileInfo check_file(filePath);

  if (check_file.exists(filePath)) {
    free_mem(&ui->myGl->all_data);

    QByteArray Len = filePath.toLocal8Bit();
    char *Str = Len.data();
    ui->fileNameLabel->setText(check_file.fileName());
    if (read_file(&ui->myGl->all_data, Str) == 0) {
      ui->vertexCount->setText(
          QString::number(ui->myGl->all_data.vertexes / 3));
      ui->polygonCount->setText(
          QString::number(ui->myGl->all_data.polygon / 4));
      ui->myGl->onOpenFile();
    } else {
      free_mem(&ui->myGl->all_data);
      ui->vertexCount->setText("");
      ui->polygonCount->setText("");
    }
  }

  ui->myGl->backroundColor =
      QColor(settings.value("backgroundColor", QColor(Qt::black)).toString());
  ui->myGl->linesColor =
      QColor(settings.value("linesColor", QColor(Qt::white)).toString());
  ui->myGl->vertexesColor =
      QColor(settings.value("vertexesColor", QColor(Qt::white)).toString());

  ui->lineSizeEditer->setValue(settings.value("lineSizeEditer", 1).toInt());
  ui->myGl->lineWidth = settings.value("lineWidth", 1).toInt();

  ui->vertexSizeEditer->setValue(settings.value("vertexSizeEditer", 1).toInt());
  ui->myGl->vertexSize = settings.value("vertexSize", 1).toInt();

  ui->vertexesType->setCurrentIndex(settings.value("vertexesType", 0).toInt());
  ui->linesType->setCurrentIndex(settings.value("linesType", 0).toInt());
  ui->projectionType->setCurrentIndex(
      settings.value("projectionType", 0).toInt());

  ui->myGl->lineType = static_cast<MyOpenGLWidget::linesType>(
      settings.value("lineType", MyOpenGLWidget::SOLID).toInt());
  ui->myGl->vertexType = static_cast<MyOpenGLWidget::vertexesType>(
      settings.value("vertexType", MyOpenGLWidget::NONE).toInt());
  ui->myGl->projection = static_cast<MyOpenGLWidget::projectionType>(
      settings.value("projection", MyOpenGLWidget::CENTRAL).toInt());

  ui->myGl->xRot = settings.value("xRot", 0).toDouble();
  ui->myGl->yRot = settings.value("yRot", 0).toDouble();
  ui->myGl->zRot = settings.value("zRot", 0).toDouble();

  settings.endGroup();
}

// AFFINE_TRANSFORMATIONS

/*             MOVE                */

// Z Axis

void MainWindow::on_B_PLUS_MOVE_Z_clicked() {
  double value = ui->doubleSpinBox_MOVE_Z->value();

  move_z(&ui->myGl->all_data, value);
  ui->myGl->update();
}

void MainWindow::on_B_MINUS_MOVE_Z_clicked() {
  double value = ui->doubleSpinBox_MOVE_Z->value();
  value *= -1;
  move_z(&ui->myGl->all_data, value);
  ui->myGl->update();
}

// Y Axis

void MainWindow::on_B_PLUS_MOVE_Y_clicked() {
  double value = ui->doubleSpinBox_Y_MOVE->value();

  move_y(&ui->myGl->all_data, value);
  ui->myGl->update();
}

void MainWindow::on_B_MINUS_MOVE_Y_clicked() {
  double value = ui->doubleSpinBox_Y_MOVE->value();
  value *= -1;

  move_y(&ui->myGl->all_data, value);
  ui->myGl->update();
}

// X Axis

void MainWindow::on_B_PLUS_MOVE_X_clicked() {
  double value = ui->doubleSpinBox_X_MOVE->value();

  move_x(&ui->myGl->all_data, value);
  ui->myGl->update();
}

void MainWindow::on_B_MINUS_MOVE_X_clicked() {
  double value = ui->doubleSpinBox_X_MOVE->value();
  value *= -1;

  move_x(&ui->myGl->all_data, value);
  ui->myGl->update();
}

/*                SIZE                */

void MainWindow::on_pushButton_4_clicked() {
  double value = 1.1;
  size_xyz(&ui->myGl->all_data, value);
  ui->myGl->update();
}

void MainWindow::on_pushButton_5_clicked() {
  double value = 0.9;
  size_xyz(&ui->myGl->all_data, value);
  ui->myGl->update();
}

/*                ROTATE               */

// X Axis

void MainWindow::on_ROTATE_X_PLUS_clicked() {
  int value = ui->ROTATE_X_VALUE->value();
  rotation_x(&ui->myGl->all_data, value);
  ui->myGl->update();
}

void MainWindow::on_ROTATE_X_MINUS_clicked() {
  int value = ui->ROTATE_X_VALUE->value() * -1;
  rotation_x(&ui->myGl->all_data, value);
  ui->myGl->update();
}

// Y Axis

void MainWindow::on_ROTATE_Y_PLUS_clicked() {
  int value = ui->ROTATE_Y_VALUE->value();
  rotation_y(&ui->myGl->all_data, value);
  ui->myGl->update();
}

void MainWindow::on_ROTATE_Y_MINUS_clicked() {
  int value = ui->ROTATE_Y_VALUE->value() * -1;
  rotation_y(&ui->myGl->all_data, value);
  ui->myGl->update();
}

// Z Axis

void MainWindow::on_ROTATE_Z_PLUS_clicked() {
  int value = ui->ROTATE_Z_VALUE->value();
  rotation_z(&ui->myGl->all_data, value);
  ui->myGl->update();
}

void MainWindow::on_ROTATE_Z_MINUS_clicked() {
  int value = ui->ROTATE_Z_VALUE->value() * -1;
  rotation_z(&ui->myGl->all_data, value);
  ui->myGl->update();
}

/*
 *  3th Bonus part
 *  Screenshot & Gif animation
 **/

void MainWindow::on_createScreenPshBtn_clicked() {
  QString fileName =
      QFileDialog::getSaveFileName(this, "Сохранить скриншот", "/Users",
                                   "Images (*.jpeg *.bmp);;All Files (*)");
  if (!fileName.isEmpty()) {
    QImage screen = ui->myGl->grabFramebuffer();
    screen.save(fileName);
    QMessageBox successMessage;
    successMessage.setText("Printscreen saved successfully!");
    successMessage.exec();
  } else {
    QMessageBox::warning(this, "", "Printscreen creating failed!");
  }
}

void MainWindow::on_createGifPshBtn_clicked() {
  gifName = QFileDialog::getSaveFileName(this, "Save gif", "/Users",
                                         "Gif (*.gif);;All Files (*)");
  if (!gifName.isEmpty() && !screenCounter) {
    gifFrame = new QGifImage;
    gifFrame->setDefaultDelay(10);
    timer->setInterval(100);
    timer->start();
    ui->createGifPshBtn->setEnabled(false);
  } else {
    QMessageBox::warning(this, "", "Gif creating failed!");
  }
}

void MainWindow::createAnimation() {
  if (screenCounter < 50) {
    QImage screen = ui->myGl->grabFramebuffer();
    gifFrame->addFrame(screen);
    screenCounter++;
    ui->createGifPshBtn->setText(QString::number(screenCounter / 10, 10));
  } else {
    QMessageBox successMessage;
    successMessage.setText("Gif saved successfully!");
    successMessage.exec();
    timer->stop();
    screenCounter = 0;
    gifFrame->save(gifName);
    delete gifFrame;
    ui->createGifPshBtn->setText("Create gif");
    ui->createGifPshBtn->setEnabled(true);
  }
}
