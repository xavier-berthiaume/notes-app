#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QVector>
#include <cctype>

#include "note.h"

class NoteModel : public QAbstractListModel
{
    Q_OBJECT

    QVector<Note> m_notes;

public:
    enum NoteRoles {
        IdRole = Qt::UserRole + 1,  // Custom roles start from Qt::UserRole
        TitleRole,
        BodyRole
    };

    explicit NoteModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addNote(const Note& note);

    void modifyNote(const QModelIndex &index, const QString &title, const QString &body);

    void removeNote(int row);
};

#endif // NOTEMODEL_H
