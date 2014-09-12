#include "cryptmananger.h"

CryptMananger::CryptMananger(QObject *parent) :
    QObject(parent)
{
    //prime numbers generator
    generatePrimes(150);
    //init randomizer
    initRand();
}

void CryptMananger::setSourceText(QString text)
{
    sourceText=text;
}

void CryptMananger::encryptText(){
    encryptLog.clear();
    encryptLog.append(generateLog()+"\n");
    encryptLog.append("Кодировка\n");
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
        encryptLog.append("{ "+tempEncryptText[i]+"="+QString::number(tempEncryptText[i].unicode())+";  "+
                          QString::number(tempEncryptText[i].unicode())+" ^ "+QString::number(e)+
                          " mod "+QString::number(n)+"="+encryptedText[i]+" }\t");
    }

}

void CryptMananger::decryptText(){
    decryptLog.clear();
    decryptLog.append(generateLog()+"\n");
    decryptLog.append("Раскодировка\n");
    if(!encryptedText.isEmpty())
        decryptedText=encryptedText;
    else{
        decryptedText=QString("Текст отсутствует");
        return;
    }

    QStringList tempDecryptText=decryptedText.split(" ");
    int decryptTextSize=tempDecryptText.size()-1;
    int tempDecryptInt[decryptTextSize];
    qDebug()<<decryptedText;
    decryptedText.clear();
    for(int i=0;i<decryptTextSize;i++){
        tempDecryptInt[i]=tempDecryptText[i].toInt();
        tempDecryptInt[i]=modExp(tempDecryptInt[i],d,n);
        decryptedText.append(QChar(tempDecryptInt[i]));
        decryptLog.append("{ "+tempDecryptText[i]+" ^ "+QString::number(d)+
                          " mod "+QString::number(n)+"="+decryptedText[i]+" }\t");
    }

}

QString CryptMananger::getEncryptedText(){
    return encryptedText;
}

QString CryptMananger::getDecryptedText(){
    return decryptedText;
}

QString CryptMananger::generateLog()
{
    QString log;
    log+="Сгенерированы переменные P="+QString::number(p)+" Q="+QString::number(q)+"\n";
    log+="Произведение P и Q ="+QString::number(n)+"\n";
    log+="Функция Эйлера "+QString::number(f)+"\n";
    log+="Публичный ключ для кодировки "+QString::number(e)+" - "+QString::number(n)+"\n";
    log+="Секретный ключ для декодировки "+QString::number(d)+" - "+QString::number(n)+"\n";
    return log;
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
    d=0;
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

QString CryptMananger::getEncryptLog()
{
    return encryptLog;
}

QString CryptMananger::getDecryptLog()
{
    return decryptLog;
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
