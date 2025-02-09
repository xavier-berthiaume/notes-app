#include "notemodel.h"

#include <QStandardPaths>
#include <QDir>
#include <QFile>

NoteModel::NoteModel(QObject *parent)
    : QAbstractListModel{parent},
      m_db(QSqlDatabase::addDatabase("QSQLITE"))
{
    // QString appName = "quick-notes"; // Replace with your application's name
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

    QDir dir(dataDir);
    if (!dir.exists()) {
        dir.mkpath(dataDir);
    }

    initializeDatabase(dataDir + "/notes.db");
    loadNotes();
}

bool NoteModel::initializeDatabase(const QString &dbFilePath)
{
    if (!QFile::exists(dbFilePath)) {
        qDebug() << "Database file doesn't exist. Create a new one.";

        m_db.setDatabaseName(dbFilePath);

        if (!m_db.open()) {
            qCritical() << "Failed to create database: " << m_db.lastError().text();
            return false;
        }

        QSqlQuery query;
        QString createTableQuery = R"(
            CREATE TABLE Notes (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL,
                body TEXT NOT NULL
            )
        )";

        if (!query.exec(createTableQuery)) {
            qCritical() << "Failed to create the Notes table: " << m_db.lastError().text();
            return false;
        }

        qDebug() << "Database and table created successfully.";
    } else {
        qDebug() << "Database file exists. Opening the existing database.";

        m_db.setDatabaseName(dbFilePath);
        if (!m_db.open()) {
            qCritical() << "Failed to open existing database: " << m_db.lastError().text();
            return false;
        }
    }

    return true;
}

bool NoteModel::loadNotes()
{
    QSqlQuery query("SELECT id, title, body FROM Notes");
    if (!query.exec()) {
        qWarning() << "Failed to fetch notes from the database: " << query.lastError().text();
        return false;
    }

    beginResetModel();
    m_notes.clear();
    while (query.next()) {
        uint32_t id = query.value(0).toUInt();
        QString title = query.value(1).toString();
        QString body = query.value(2).toString();
        m_notes.append({id, title.toStdString(), body.toStdString()});
    }
    endResetModel();

    return true;
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
    QSqlQuery query;
    query.prepare("INSERT INTO Notes (title, body) VALUES (:title, :body)");
    query.bindValue(":title", QString::fromStdString(note.getTitle()));
    query.bindValue(":body", QString::fromStdString(note.getBody()));

    if (!query.exec()) {
        qWarning() << "Failed to insert note: " << query.lastError().text();
        return;
    }

    uint32_t id = query.lastInsertId().toUInt();
    Note newNote = note;
    newNote.setId(id);

    beginInsertRows(QModelIndex(), m_notes.size(), m_notes.size());
    m_notes.push_back(newNote);
    endInsertRows();
}

void NoteModel::modifyNote(const QModelIndex &index, const QString &title, const QString &body)
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_notes.size()) {
        qWarning() << "Invalid index passed to modifyNote";
        return;
    }

    Note &note = m_notes[index.row()];
    QSqlQuery query;
    query.prepare("UPDATE Notes SET title = :title, body = :body WHERE id = :id");
    query.bindValue(":title", title);
    query.bindValue(":body", body);
    query.bindValue(":id", note.getId());

    if (!query.exec()) {
        qWarning() << "Failed to update note: " << query.lastError().text();
        return;
    }

    note.setTitle(title.toStdString());
    note.setBody(body.toStdString());

    emit dataChanged(index, index, {TitleRole, BodyRole});
}

void NoteModel::removeNote(int row)
{
    if (row < 0 || row >= m_notes.size())
        return;

    Note &note = m_notes[row];
    QSqlQuery query;
    query.prepare("DELETE FROM Notes WHERE id = :id");
    query.bindValue(":id", note.getId());

    if (!query.exec()) {
        qWarning() << "Failed to delete note: " << query.lastError().text();
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    m_notes.removeAt(row);
    endRemoveRows();
}
