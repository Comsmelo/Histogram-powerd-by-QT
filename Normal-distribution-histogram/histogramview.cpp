#include "histogramview.h"

#include <QPainter>   //绘画工具
#include <QDebug>

HistogramView::HistogramView(QWidget *parent) :
  QAbstractItemView(parent)
{
}

//绘制柱形图的函数
void HistogramView::paintEvent(QPaintEvent *)
{
  QPainter painter(viewport());   //这个就是在这个viewport范围内建立一个绘画对象，这个viewport就是给定的范围，大小暂时不知,反正就是一个地方
  painter.setPen(Qt::black);

  int x0 = 60;
  int y0 = 500;     //坐标原点

  //y坐标轴
  painter.drawLine(x0,y0,60,100);
  painter.drawLine(55,105,60,100);
  painter.drawLine(60,100,65,105);
  painter.drawText(20,80,tr("小球数量"));   //坐标轴后面的给个文字

  for(int i=1; i<8; i++)      //y坐标的刻度
    {
        painter.setPen(Qt::black);
        painter.drawLine(x0, i*50+100, 80, i*50+100);
        painter.drawText(30, (8-i)*50+100, tr("%1").arg(i*5));
    }

  //x 坐标轴
  painter.setPen(Qt::black);
  painter.drawLine(x0,y0,580,500);
  painter.drawLine(575,495,580,500);
  painter.drawLine(580,500,575,505);
  painter.drawText(590,520,tr("槽口"));

  //横坐标名称
  int posD = x0 + 20;
  int row;    //标记写到了第几行
  for(row = 0; row < model()->rowCount(this->rootIndex()); ++row)   //model() 返回已经呈现的视图
    {
      QModelIndex index = model()->index(row, 0, rootIndex());    //得到第row行，第1列，第0个的索引
      QString dep = model()->data(index).toString();    //得到这个索引的数据

      painter.drawText(posD, y0 + 20, dep);   //dep就是刚得到的部门信息
      posD += 50;   //下一个

    }

  int posM=x0+15;
  for(row=0; row<model()->rowCount(rootIndex()); ++row)
  {
      QModelIndex index=model()->index(row,1,rootIndex());    //第二列
      int numbers=model()->data(index).toDouble();   //数值转化

      int width=30;   //柱形图柱子的宽度
      if(selections->isSelected(index))
        {
          painter.setBrush(QBrush(Qt::black,Qt::Dense3Pattern));   //设置画刷
        }
      else
        {
          painter.setBrush(Qt::blue);
        }
      painter.drawRect(QRect(posM,y0-numbers*10,width,numbers*10));   //画柱子，宽度已设置为10

      QRegion regionM(posM,y0-numbers*10,width,numbers*10);   //剪裁一个区域的大小记录下来
      MRegionList<<regionM;   //把占据的区域保存下来给后面使用

      posM+=50;
  }

}

//当模型的数据改变的时候，调用绘图设备的update函数更新
void HistogramView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
  QAbstractItemView::dataChanged(topLeft, bottomRight);
  this->viewport()->update();   //在这个基础上改变更新
}

//设置selections的初值
void HistogramView::setSelectionModel(QItemSelectionModel *selectionModel)
{
  selections = selectionModel;
}

QRect HistogramView::visualRect(const QModelIndex &index)const
{
  QRect *p = new QRect();
  return *p;
}

void HistogramView::scrollTo(const QModelIndex &index,ScrollHint){}

QModelIndex HistogramView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
  return QModelIndex();
}

int HistogramView::horizontalOffset()const
{
  return 0;
}

int HistogramView::verticalOffset()const
{
  return 0;
}

bool HistogramView::isIndexHidden(const QModelIndex &index)const
{
  return true;
}

QRegion HistogramView::visualRegionForSelection(const QItemSelection &selection)const
{
  return QRegion();
}


//选项的更新
void HistogramView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  viewport()->update();     //更新数据
}

 //当鼠标在按下的时候调用setSelection函数，确定鼠标点击点所在的区域，设置选择项
void HistogramView::mousePressEvent(QMouseEvent *event)
{
  QAbstractItemView::mousePressEvent(event);    //视图层的鼠标点击事件获取
  qDebug()<<"mouse";
  setSelection(QRect(event->pos().x(), event->pos().y(), 1, 1), QItemSelectionModel::SelectCurrent);    //获取当前选择的那个区域
}

//返回选择到的数值的区域
QRegion HistogramView::itemRegion(QModelIndex index)
{
  QRegion region;
  if(index.column() == 1)   //第二列
    {
      region = MRegionList[index.row()];
    }
  return region;
}

//设置选择的区域
void HistogramView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
    int rows = model()->rowCount(rootIndex());
    int columns = model()->columnCount(rootIndex());
    QModelIndex selectedIndex;

    for (int row=0; row<rows; ++row)
    {
        for (int column=1; column<columns; ++column)
        {
            QModelIndex index=model()->index(row, column, rootIndex());   //得到选择中的位置的索引
            QRegion region=itemRegion(index);   //得到这个区域

            if (!region.intersected(rect).isEmpty())    //没有重合的部分
                selectedIndex = index;
        }
    }

    if(selectedIndex.isValid())   //里面的数据不为空
        selections->select(selectedIndex, command);
    else
    {
        qDebug()<<"noindex";
        QModelIndex noIndex;    //空的索引
        selections->select(noIndex, command);
    }
}

QModelIndex HistogramView::indexAt(const QPoint &point)const
{
    QPoint newPoint(point.x(),point.y());
    QRegion region;
    foreach(region,MRegionList)
    {
        if (region.contains(newPoint))
        {
            int row = MRegionList.indexOf(region);
            QModelIndex index = model()->index(row,1,rootIndex());
            return index;
        }
    }
    return QModelIndex();
}
