#include "mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include "QSplitter"

MainWindow::MainWindow(QWidget *parent)   //构造函数
  : QMainWindow(parent)
{
  setupModel();   //设置模型
  setupView();    //显示视图

  //设置标题和界面大小
  this->setWindowTitle(tr("高尔顿钉板"));
  this->resize(1000,600);
}

MainWindow::~MainWindow()
{

}

//设置模型
//void setupModel();
void MainWindow::setupModel()
{
  model = new QStandardItemModel(10, 2, this);   //在当前的窗口中创建一个10行1列的标准模型
  model->setHeaderData(0, Qt::Horizontal, tr("槽口"));
  model->setHeaderData(1, Qt::Horizontal, tr("小球数量"));
  for(int i=0; i<10; i++)
  {
      data1 = new QStandardItem(tr("道")+QString::number(i+1,10));
      model->setItem(i, 0, data1);
  }
}

//设置显示视图
void MainWindow::setupView()
{
  //设置好表格视图
  table = new QTableView;
  table->setModel(model);   //设置这个表格视图的模型

  QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
  table->setSelectionModel(selectionModel);

  //  histogram = new HistogramView;
    histogram = new HistogramView(splitter);

    histogram->setModel(model); //添加到这个模型中

    histogram->setSelectionModel(selectionModel);

  splitter1 = new QSplitter(Qt::Horizontal,0);
  splitter = new QSplitter(Qt::Horizontal, splitter1);

  splitter->addWidget(table);
  splitter->addWidget(histogram);

  splitter->setStretchFactor(0,3);
  splitter->setStretchFactor(1,5);
  splitter->setAutoFillBackground(true);

  this->setCentralWidget(splitter);

  connect(selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), table, SLOT(selectionChanged(QItemSelection,QItemSelection)));
  connect(selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), histogram, SLOT(selectionChanged(QItemSelection,QItemSelection)));

}
