#include "notemodel.h"

NoteModel::NoteModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int NoteModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_notes.size();
}

QVariant NoteModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_notes.size())
        return QVariant();

    const Note& note = m_notes.at(index.row());
    switch (role) {

    case IdRole: return note.getId();
    case TitleRole: return QString::fromStdString(note.getTitle());
    case BodyRole: return QString::fromStdString(note.getBody());
    case Qt::DisplayRole: return QString::fromStdString(note.getTitle());  // Default display shows the title

    }
    return QVariant();
}

QHash<int, QByteArray> NoteModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[TitleRole] = "title";
    roles[BodyRole] = "body";
    return roles;
}

void NoteModel::addNote(const Note& note)
{
    beginInsertRows(QModelIndex(), m_notes.size(), m_notes.size());
    m_notes.push_back(note);
    endInsertRows();
}

void NoteModel::modifyNote(const QModelIndex &index, const QString &title, const QString &body)
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_notes.size()) {
        qWarning() << "Invalid index passed to modifyNote";
        return;
    }

    Note &note = m_notes[index.row()];
    note.setTitle(title.toStdString());
    note.setBody(body.toStdString());

    emit dataChanged(index, index, {TitleRole, BodyRole});
}

void NoteModel::removeNote(int row)
{
    if (row < 0 || row >= m_notes.size())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_notes.removeAt(row);
    endRemoveRows();
}
