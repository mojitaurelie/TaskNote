#include "note.h"

Note::Note()
{

}

QJsonObject Note::toJson()
{
    QJsonObject o;

    o["title"] = this->title;
    o["content"] = this->content;

    return o;
}

Note *Note::fromJson(QJsonObject o)
{
    Note *n = new Note();
    n->title = o["title"].toString();
    n->content = o["content"].toString();
    return n;
}

QString Note::getTitle()
{
    return title;
}

QString Note::getContent()
{
    return content;
}

void Note::setTitle(QString value)
{
    this->title = value;
}

void Note::setContent(QString value)
{
    this->content = value;
}

