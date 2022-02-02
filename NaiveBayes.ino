#include <DHT.h>
#define pinDHT D4
#define typeDHT DHT11

//normal
double mNsuhu = 29.66666667, mNkelembaban =73.66666667 ,ssNormal = 0.913600934,sKnormal =1.861898673 ;

//peringatan
double mPsuhu =33.06666667, mPkelembaban = 66.66666667,ssPeringatan = 0.398329847, sKperingatan = 1.032795559;

//bahaya
double mBsuhu = 34.96666667, mBkelembaban = 59,ssBahaya = 0.852447457, sKbahaya = 3.577708764;

double  pSuhuNormal, pKelembabanNormal, pTotalNormal;
double  pSuhuPeringatan, pKelembabanPeringatan, pTotalPeringatan;
double  pSuhuBahaya,pKelembabanBahaya,pTotalBahaya;



DHT dht (pinDHT, typeDHT);
float h,t;


void setup() {
  Serial.begin(9600);
  dht.begin();
  
}

void loop() {
    h = dht.readHumidity();
    t = dht.readTemperature();
    Serial.println(t);
    Serial.println(h);

    pSuhuNormal = (1/(sqrt(2*3.14*ssNormal)))*exp(-((pow((t-mNsuhu),2)))/(2*(pow((ssNormal),2))));
    pKelembabanNormal = (1/(sqrt(2*3.14*sKnormal)))*exp(-((pow((h-mNkelembaban),2)))/(2*(pow((sKnormal),2))));
    pTotalNormal =  pSuhuNormal+pKelembabanNormal;


    
    pSuhuPeringatan = (1/(sqrt(2*3.14*ssPeringatan)))*exp(-((pow((t-mPsuhu),2)))/(2*(pow((ssPeringatan),2))));
    pKelembabanPeringatan = (1/(sqrt(2*3.14*sKperingatan)))*exp(-((pow((h-mPkelembaban),2)))/(2*(pow((sKperingatan),2))));
    pTotalPeringatan =  pSuhuPeringatan+pKelembabanPeringatan;



    pSuhuBahaya = (1/(sqrt(2*3.14*ssBahaya)))*exp(-((pow((t- mBsuhu),2)))/(2*(pow((ssBahaya),2))));
    pKelembabanBahaya = (1/(sqrt(2*3.14*sKbahaya)))*exp(-((pow((h-mBkelembaban),2)))/(2*(pow((sKbahaya),2))));
    pTotalBahaya =  pSuhuBahaya+pKelembabanBahaya; 
 


    if(pTotalNormal > pTotalPeringatan && pTotalNormal>pTotalBahaya)
    {
      Serial.println("Kondisi Normal");
    }
    if(pTotalPeringatan > pTotalNormal && pTotalPeringatan > pTotalBahaya)
    {
      Serial.println("Kondisi Peringatan");
    }
    if( pTotalBahaya > pTotalNormal &&  pTotalBahaya > pTotalPeringatan){
      Serial.println("Kondisi Bahaya");
    }

    delay(2000);

}
