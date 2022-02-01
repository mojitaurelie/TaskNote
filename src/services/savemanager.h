#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#define SAVE_FILENAME "data.json"

#include <QStandardPaths>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

#include "../models/note.h"

class SaveManager
{
public:
    SaveManager();
    ~SaveManager();

    void flushSave();

    QVector<Note*> getNotes();

    void addNote(Note *n);
    bool removeNoteByIndex(int i);
    Note *getNoteByIndex(int i);
private:
    QString getSaveFilePath();
    void openSave();

    QVector<Note*> notes;
};

#endif // SAVEMANAGER_H
