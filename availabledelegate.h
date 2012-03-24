#ifndef BOOLDELEGATE_H
#define BOOLDELEGATE_H

#include <QtDebug>
#include <QItemDelegate>

class AvailableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit AvailableDelegate(int column, QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

private:
    int column;

};

#endif // BOOLDELEGATE_H
