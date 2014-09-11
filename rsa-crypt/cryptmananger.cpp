#include "cryptmananger.h"

CryptMananger::CryptMananger(QObject *parent) :
    QObject(parent)
{
    //prime numbers generator
    generatePrimes(100);
    //init randomizer
    initRand();
}

void CryptMananger::setSourceText(QString text)
{
    sourceText=text;

    //qDebug()<<(int)sourceText.toUtf8().data()[0];
}

void CryptMananger::encryptText(){
    encryptedText=!sourceText.isEmpty()?sourceText:QString("Текст отсутствует");
}

void CryptMananger::decryptText(){
    decryptedText=!sourceText.isEmpty()?sourceText:QString("Текст отсутствует");
}

QString CryptMananger::getEncryptedText(){
    return encryptedText;
}

QString CryptMananger::getDecryptedText(){
    return decryptedText;
}

void CryptMananger::generatePrimes(int count){

    std::vector<bool> primeVector (count+1, true);
    primeVector[0] = primeVector[1] = false;
    for (int i=2; i*i<=count; ++i)   // valid for n < 46340^2 = 2147395600
        if (primeVector[i])
            for (int j=i*i; j<=count; j+=i)
                primeVector[j] = false;


    for(int i=0;i<count;i++)
        if(primeVector[i])
            primeNumbers.append(i);

    qDebug()<<primeNumbers;
}

 void CryptMananger::initRand(){
     QTime time = QTime::currentTime();
     qsrand((uint)time.msec());
 }

 int CryptMananger::getRand(int high, int low){
     return qrand() % ((high + 1) - low) + low;
 }

