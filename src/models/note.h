#ifndef NOTE_H
#define NOTE_H

#define TAG_SIZE 12

#include <iostream>
#include <string>

#include <QString>
#include <QJsonObject>
#include <QUuid>
#include <QMessageBox>

class Note
{
public:
    Note();

    QJsonObject toJson();
    static Note* fromJson(QJsonObject o);

    QString getUuid();
    QString getTitle();
    QString getContent();

    void setTitle(QString value);
    void setContent(QString value);
private:
    QString uuid;
    QString title;
    QString content;
    bool encrypted;
};

#endif // NOTE_H
