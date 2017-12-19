#include <SimpleDHT.h>
int lichtsensorWaarde = 0;
int pinDHT11 = 4;
SimpleDHT11 dht11;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //  lees_lichtsensor();
  //  lees_sht11();
  serial_python();
}

float lees_lichtsensor() {
  lichtsensorWaarde = analogRead(A2);
  Serial.println(lichtsensorWaarde);
  float x = berekenSpanning(lichtsensorWaarde);
  Serial.println("De lichtsensorwaarde is " + String (x) + " % ");
  delay(1000);
  return x;
}

float berekenSpanning (int sensorWaarde) {
  float spanning = (sensorWaarde / 400.0) * 100; //in percent
  float Gspanning = (100 - spanning);
  return Gspanning;
}


String lees_sht11() {
  byte bTemperature = 0;
  String sTemperature = "";
  byte humidity = 0;

  if (dht11.read(pinDHT11, &bTemperature, &humidity, NULL)) {
    Serial.print("Read DHT11 Failed");
    return "null";
  }
  sTemperature = String(bTemperature);
  Serial.println("De temperatuur is " + sTemperature  + "°c");
  delay (2000);
  return sTemperature;

}

void serial_python() {
  if (Serial.available() > 0) {
    String tekst = Serial.readString();
    tekst.replace("\n", "");
    tekst.replace("\r", "");

    if (tekst == "temp") {
      Serial.println(" De temperatuur is " + lees_sht11() + " °c");
    }
    else if (tekst == "licht") {
 
      Serial.println ("licht: " + String(lees_lichtsensor()) + " %");
    }
    else {
      Serial.println("\""+ tekst +"\" is geen geldig commando ontvangen, stuur temp of licht");
    }
  }
}
