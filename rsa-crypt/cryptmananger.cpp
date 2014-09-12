#include "cryptmananger.h"

CryptMananger::CryptMananger(QObject *parent) :
    QObject(parent)
{
    //prime numbers generator
    generatePrimes(150);
    //init randomizer
    initRand();
    //create keys
    createKeys();

  //  qDebug()<<"FASAS"<<modExp(221,1134,33);

}

void CryptMananger::setSourceText(QString text)
{
    sourceText=text;
}

void CryptMananger::encryptText(){
    if(!sourceText.isEmpty())
        encryptedText=sourceText;
    else{
        encryptedText=QString("Текст отсутствует");
        return;
    }

    int encryptTextSize=encryptedText.length();
    QString tempEncryptText=encryptedText;
    int tempEncryptInt[encryptTextSize];

    encryptedText.clear();
    for(int i=0;i<encryptTextSize;i++){
        tempEncryptInt[i]=modExp(tempEncryptText[i].unicode(),e,n);
        encryptedText.append(QString::number(tempEncryptInt[i])+" ");
        qDebug()<<"Enc"<<tempEncryptText[i];
    }

}

void CryptMananger::decryptText(){
    if(!encryptedText.isEmpty())
        decryptedText=encryptedText;
    else{
        decryptedText=QString("Текст отсутствует");
        return;
    }

    QStringList tempDecryptText=decryptedText.split(" ");
    int decryptTextSize=tempDecryptText.size()-1;
    int tempDecryptInt[decryptTextSize];

    decryptedText.clear();
    for(int i=0;i<decryptTextSize;i++){
        tempDecryptInt[i]=tempDecryptText[i].toInt();
        tempDecryptInt[i]=modExp(tempDecryptInt[i],d,n);
        decryptedText.append(QChar(tempDecryptInt[i]));
        qDebug()<<"Dec"<<tempDecryptInt[i];
    }

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
    for (int i=2; i*i<=count; ++i)
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

int CryptMananger::getRand(int low, int high){
    return qrand() % ((high + 1) - low) + low;
}

void CryptMananger::createKeys(){
    int primesCount=primeNumbers.length();

    p=getRand(0,primesCount/2);
    q=getRand(primesCount/2+1,primesCount-1);

    p=primeNumbers[p];
    q=primeNumbers[q];

    n=p*q;
    f=(p-1)*(q-1);

    e=primeNumbers[getRand(0,primesCount-1)];
    while(e>=f||e==q||e==p){
        e=primeNumbers[getRand(0,primesCount-1)];
    }

    int i=0;
    bool d_found=false;
    while(!d_found)
    {
        if((f*i+1)%e==0)
            d=(f*i+1)/e;

        if(d!=e&&d!=p&&d!=q&&d!=0)
            if(calcGSD(d,f)==1)
                d_found=true;

        if((f*i+1)/e>f)
            d_found=true;

        i++;
    }

    qDebug()<<"P"<<p<<"Q"<<q<<"N"<<n<<"F"<<f<<"E"<<e<<"D"<<d;
}

int CryptMananger::calcGSD(int x,int y){
    return y ? calcGSD(y,x%y) : x;
}

int CryptMananger::modExp(long long base, long long exp, long long mod){
    if(exp==0)
        return 1;

    if(exp%2==0){
        long long res=modExp(base,exp/2,mod);
        return (res*res)%mod;
    }else{
        long long res=modExp(base,exp-1,mod);
        return ((base%mod)*res)%mod;
    }
}
