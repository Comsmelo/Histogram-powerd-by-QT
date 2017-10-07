#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSplitter>
#include <QMenu>
#include <QMenuBar>
#include <QTableView>
#include <QString>
#include <QFileDialog>
#include <QDebug>
#include "QSplitter"
#include "QFile"
#include "QtCore"
#include "QMessageBox"

#include "histogramview.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
  //设置模型
  void setupModel();
  //设置显示视图
  void setupView();

protected:
  void timerEvent(QTimerEvent *event);//定时器事件

private:
  QStandardItemModel *model;      //界面模型
  QStandardItem *data1;
  QStandardItem *data2;//小球数据存放
  QTableView *table;    //表格视图
  QSplitter *splitter;      //界面的分割布局
  QSplitter *splitter1;
//  QString fileName;//读取数据文件名
  int theTimerId;


  HistogramView *histogram;

private slots:
  void timerUpDate();

};

#endif // MAINWINDOW_H
