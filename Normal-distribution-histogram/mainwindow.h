#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSplitter>
#include <QMenu>
#include <QMenuBar>
#include <QTableView>
#include <QString>

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

private:
  QStandardItemModel *model;      //界面模型
  QStandardItem *data1;
  QTableView *table;    //表格视图
  QSplitter *splitter;      //界面的分割布局
  QSplitter *splitter1;

  HistogramView *histogram;

};

#endif // MAINWINDOW_H
