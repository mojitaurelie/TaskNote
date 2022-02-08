#ifndef NOTE_H
#define NOTE_H

#define TAG_SIZE 12

#include <iostream>
#include <string>

#include <QString>
#include <QJsonObject>
#include <QUuid>
#include <QMessageBox>

#include <crypto++/modes.h>
#include <crypto++/aes.h>
#include <crypto++/filters.h>
#include <crypto++/cryptlib.h>
#include <crypto++/sha.h>
#include <crypto++/hkdf.h>
#include <crypto++/osrng.h>
#include <crypto++/gcm.h>
#include <crypto++/rijndael.h>

class Note
{
public:
    Note();

    QJsonObject toJson();
    static Note* fromJson(QJsonObject o);

    QString getUuid();
    QString getTitle();
    QString getContent();
    QString getEncryptedContent(QString passwd);
    bool isEncrypted();

    void setTitle(QString value);
    void setContent(QString value);
    bool setEncryptedContent(QString value, QString passwd);

    void encrypt(QString password);

private:
    QString uuid;
    QString title;
    QString content;
    bool encrypted;
};

#endif // NOTE_H
