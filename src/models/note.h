#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QJsonObject>

class Note
{
public:
    Note();

    QJsonObject toJson();
    static Note* fromJson(QJsonObject o);

    QString getTitle();
    QString getContent();

    void setTitle(QString value);
    void setContent(QString value);

private:
    QString title;
    QString content;
};

#endif // NOTE_H
