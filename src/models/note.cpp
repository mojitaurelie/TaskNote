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
    o["encrypted"] = this->encrypted;
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

QString Note::getEncryptedContent(QString passwd)
{
    if (this->encrypted)
    {
        using namespace CryptoPP;
        std::string password = passwd.toStdString();
        QString bytes = QByteArray::fromBase64(QByteArray::fromStdString(this->content.toStdString()));
        std::string encoded = bytes.toStdString();
        std::string iv = encoded.substr(0, TAG_SIZE);
        std::string cipher = encoded.substr(TAG_SIZE + 1, encoded.length());
        std::string recovered;

        try {
          GCM< AES >::Decryption d;
          d.SetKeyWithIV((const unsigned char*)password.c_str(), sizeof(password.c_str()), (const unsigned char*)iv.c_str(), sizeof(iv.c_str()));

          AuthenticatedDecryptionFilter df( d,
              new StringSink(recovered),
              AuthenticatedDecryptionFilter::DEFAULT_FLAGS, TAG_SIZE
          );
          StringSource ss2(cipher, true,
              new Redirector(df)
          );
          return QString::fromStdString(recovered);
        }  catch (CryptoPP::Exception& e) {
          std::cout << e.GetWhat() << "\n";
        }
    }
    return "";
}

bool Note::isEncrypted()
{
  return this->encrypted;
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

// TODO encrypt avec le mot de passe
bool Note::setEncryptedContent(QString value, QString passwd)
{
  if (this->encrypted) {
    using namespace CryptoPP;
    AutoSeededRandomPool prng;
    std::string password = passwd.toStdString();
    std::string pdata = value.toStdString();
    std::string cipher, encoded;

    SecByteBlock key(AES::MAX_KEYLENGTH + AES::BLOCKSIZE);
    SecByteBlock iv(AES::BLOCKSIZE);
    prng.GenerateBlock(iv, iv.size());
    try
    {
      GCM<AES>::Encryption e;
      e.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));

      StringSource ss1(pdata, true,
          new AuthenticatedEncryptionFilter(e,
              new StringSink(cipher), false, TAG_SIZE
          )
      );
      std::string s(reinterpret_cast< char const* >(iv.data())) ;
      encoded = s + cipher;
      auto bytes = QByteArray::fromStdString(encoded);
      this->content = bytes.toBase64();
      return true;
    }
    catch(CryptoPP::Exception& e)
    {
      std::cout << e.GetWhat() << "\n";
      return false;
    }
  }
  return false;
}

void Note::encrypt(QString password)
{
  if (!this->encrypted && (password.length() >= 6)) {
    this->encrypted = true;
    if (!setEncryptedContent(this->content, password))
    {
        this->encrypted = false;
    }
  }
}

