#include "availabledelegate.h"

AvailableDelegate::AvailableDelegate( int column, QObject *parent ) :
    QItemDelegate(parent)
{
    this->column = column;
}

void AvailableDelegate::paint( QPainter *painter,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index ) const
{
    if( index.column() == column )
    {
        bool available = index.data().toBool();

        QString text = available ? trUtf8("disponível") : trUtf8("indisponível");

        drawDisplay( painter, option, option.rect, text );
        drawFocus( painter, option, option.rect );

    } else {
        QItemDelegate::paint(painter, option, index);
    }
}
