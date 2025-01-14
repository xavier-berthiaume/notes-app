#ifndef NOTEDELEGATE_H
#define NOTEDELEGATE_H

#include <QStyledItemDelegate>

class NoteDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    NoteDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // NOTEDELEGATE_H
