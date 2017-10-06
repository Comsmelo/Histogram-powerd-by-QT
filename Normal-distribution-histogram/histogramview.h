#ifndef HISTOGRAMVIEW_H
#define HISTOGRAMVIEW_H

#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QRegion>
#include <QMouseEvent>

class HistogramView : public QAbstractItemView
{
  Q_OBJECT
public:
  explicit HistogramView(QWidget *parent = 0);
  QRect visualRect(const QModelIndex &index) const;
  void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible);
  QModelIndex indexAt(const QPoint &point) const;

  //绘制柱形图的函数
  void paintEvent(QPaintEvent *);
  //为selections赋初值
  void setSelectionModel(QItemSelectionModel *selectionModel);
  //当鼠标在按下的时候调用setSelection函数，确定鼠标点击点所在的区域，设置选择项
  void mousePressEvent(QMouseEvent *event);
  //选中区域是属于什么
  QRegion itemRegion(QModelIndex index);


signals:

public slots:

protected slots:
  void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
  void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

protected:
    QModelIndex moveCursor(CursorAction cursorAction,
                                   Qt::KeyboardModifiers modifiers);

    int horizontalOffset() const;
    int verticalOffset() const;

    bool isIndexHidden(const QModelIndex &index) const;

    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command);
    QRegion visualRegionForSelection(const QItemSelection &selection) const;

private:
  QItemSelectionModel *selections;
  QList<QRegion> MRegionList;

};

#endif // HISTOGRAMVIEW_H
