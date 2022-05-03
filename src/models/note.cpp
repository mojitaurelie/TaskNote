#include "note.h"

Note::Note()
{
    QUuid uid = QUuid::createUuid();
    this->uuid = uid.toString(QUuid::StringFormat::WithoutBraces);
}

QJsonObject Note::toJson()
{
    QJsonObject o;
    o["uuid"] = this->uuid;
    o["title"] = this->title;
    o["content"] = this->content;
    return o;
}

Note *Note::fromJson(QJsonObject o)
{
    Note *n = new Note();
    n->uuid = o["uuid"].toString(n->uuid);
    n->title = o["title"].toString();
    n->content = o["content"].toString();
    n->encrypted = o["encrypted"].toBool(false);
    return n;
}

QString Note::getUuid()
{
    return uuid;
}

QString Note::getTitle()
{
    return title;
}

QString Note::getContent()
{
    if (!this->encrypted)
    {
        return content;
    }
    return "";
}
void Note::setTitle(QString value)
{
    this->title = value;
}

void Note::setContent(QString value)
{
  if (!this->encrypted) {
    this->content = value;
  }
}
