#include "notedelegate.h"
#include "notemodel.h"

#include <QPainter>

NoteDelegate::NoteDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void NoteDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString title = index.data(NoteModel::TitleRole).toString();
    QString body = index.data(NoteModel::BodyRole).toString();

    if (body.length() > 61) {
        body = body.left(61) + "...";
    }

    painter->save();

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
        painter->setPen(option.palette.highlightedText().color());
    } else {
        painter->setPen(option.palette.text().color());
    }

    QRect titleRect = option.rect.adjusted(5, 5, -5, -option.rect.height() / 2);
    QRect bodyRect = option.rect.adjusted(5, option.rect.height() / 2, -5, 5);

    QFont titleFont = option.font;
    titleFont.setBold(true);
    painter->setFont(titleFont);
    painter->drawText(titleRect, Qt::AlignLeft | Qt::AlignVCenter, title);

    QFont bodyFont = option.font;
    bodyFont.setBold(false);
    painter->setFont(bodyFont);
    painter->drawText(bodyRect, Qt::AlignLeft | Qt::AlignVCenter, body);

    painter->restore();
}

QSize NoteDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 50);
}
