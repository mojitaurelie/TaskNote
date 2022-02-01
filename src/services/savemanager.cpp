#include "savemanager.h"

SaveManager::SaveManager()
{
    openSave();
}

SaveManager::~SaveManager()
{
    flushSave();
}

void SaveManager::flushSave()
{
    QJsonArray json_notes;

    foreach (Note *n, notes)
    {
        json_notes.append(n->toJson());
    }

    QJsonObject obj
    {
        {"notes", json_notes},
    };

    QJsonDocument doc(obj);
    QFile *f = new QFile(getSaveFilePath());
    if (f->open(QIODevice::WriteOnly))
    {
        f->write(doc.toJson());
        f->close();
    }
    delete f;
}

QVector<Note *> SaveManager::getNotes()
{
    return notes;
}

void SaveManager::addNote(Note *n)
{
    this->notes.append(n);
    flushSave();
}

bool SaveManager::removeNoteByIndex(int i)
{
    if ((i < 0) || (i >= this->notes.length()))
    {
        return false;
    }
    Note *n = this->notes[i];
    this->notes.removeAt(i);
    delete n;
    flushSave();
    return true;
}

Note *SaveManager::getNoteByIndex(int i)
{
    if ((i < 0) || (i >= this->notes.length()))
    {
        return nullptr;
    }
    return this->notes[i];
}

QString SaveManager::getSaveFilePath() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!QDir(path).exists())
    {
        QDir().mkpath(path);
    }

    path += "/data/";
    if (!QDir(path).exists())
    {
        QDir().mkpath(path);
    }
    path += SAVE_FILENAME;
    return QDir::cleanPath(path);
}

void SaveManager::openSave() {
    QFile* file = new QFile(getSaveFilePath());
    file->open(QIODevice::ReadOnly);
    auto json = QString(file->readAll());
    file->close();
    delete file;

    QJsonObject obj = QJsonDocument::fromJson(json.toUtf8()).object();
    QJsonArray arr = obj["notes"].toArray();
    for (int i = 0; i < arr.size(); i++)
    {
        this->notes.append(Note::fromJson(arr[i].toObject()));
    }
}
