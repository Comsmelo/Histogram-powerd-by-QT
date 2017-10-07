#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)   //构造函数
  : QMainWindow(parent)
{

  theTimerId = startTimer(500);
//    QTimer *timer = new QTimer(this);
//    connect(timer,SIGNAL(timerout()),this,SLOT(timeUpDate()));
//    timer->start(1000);
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
void MainWindow::timerEvent(QTimerEvent *event)
{

    if(event->timerId() == theTimerId)
    {
//        QMessageBox box;
//        box.setWindowTitle(tr("鍙嶉"));
//        box.setText(tr("鍥句功")+tr("娣诲姞鎴愬姛"));
//        QPushButton *yesbtn = box.addButton(tr("鏄?&Y)"), QMessageBox::YesRole);
//        box.exec();
        setupModel();
        setupView();    //显示视图
    }
}
void MainWindow::timerUpDate(){
    setupModel();
}

void MainWindow::setupModel()
{
//    QMessageBox box;
//    box.setWindowTitle(tr("鍙嶉"));
//    box.setText(tr("鍥句功")+tr("娣诲姞鎴愬姛"));
//    QPushButton *yesbtn = box.addButton(tr("鏄?&Y)"), QMessageBox::YesRole);
//    box.exec();

  model = new QStandardItemModel(10, 2, this);   //在当前的窗口中创建一个10行1列的标准模型
  model->setHeaderData(0, Qt::Horizontal, tr("槽口"));
  model->setHeaderData(1, Qt::Horizontal, tr("小球数量"));
  for(int i=0; i<10; i++)
  {
      data1 = new QStandardItem(tr("入口")+QString::number(i+1,10));
      model->setItem(i, 0, data1);
  }

  int count = 0;
  QString  fileName = tr("data.txt");
  QFile file(fileName);
  if(file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
//      QMessageBox box;
//      box.setWindowTitle(tr("鍙嶉"));
//      box.setText(tr("鍥句功")+tr("娣诲姞鎴愬姛"));
//      QPushButton *yesbtn = box.addButton(tr("鏄?&Y)"), QMessageBox::YesRole);
//      box.exec();
      while(!file.atEnd())
      {
          /*QByteArray line*/ QString str = file.readLine();
          //QString str(line);
          data2 = new QStandardItem(str);
          model->setItem(count,1,data2);
//          if(count == 2)
//          {
//              QMessageBox box;
//              box.setWindowTitle(tr("鍙嶉"));
//              box.setText(str);
//              QPushButton *yesbtn = box.addButton(tr("鏄?&Y)"), QMessageBox::YesRole);
//              box.exec();
//          }
          count++;
      }
      file.close();

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
