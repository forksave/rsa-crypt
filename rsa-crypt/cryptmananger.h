#ifndef CRYPTMANANGER_H
#define CRYPTMANANGER_H

#include <QObject>
#include <QDebug>

#include <QTime>

class CryptMananger : public QObject
{
    Q_OBJECT
public:
    explicit CryptMananger(QObject *parent = 0);
    Q_INVOKABLE void setSourceText(QString text);
    Q_INVOKABLE QString getEncryptedText();
    Q_INVOKABLE QString getDecryptedText();
    Q_INVOKABLE void encryptText();
    Q_INVOKABLE void decryptText();
private:
    QString sourceText;
    QString encryptedText;
    QString decryptedText;
    //primes
    void generatePrimes(int count);
    QList<int> primeNumbers;
    //init randomizer
    void initRand();
    int getRand(int high, int low);
public slots:

};

#endif // CRYPTMANANGER_H
