#ifndef CRYPTMANANGER_H
#define CRYPTMANANGER_H

#include <QObject>
#include <QDebug>

#include <QTime>
#include <cmath>

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
    Q_INVOKABLE QString generateLog();
    Q_INVOKABLE void createKeys();
    Q_INVOKABLE QString getEncryptLog();
    Q_INVOKABLE QString getDecryptLog();
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
    //create keys
    int p,q,n,f,e,d;
    int calcGSD(int x,int y);
    int modExp(long long base, long long exp, long long mod);
    //log
    QString encryptLog;
    QString decryptLog;
};

#endif // CRYPTMANANGER_H
