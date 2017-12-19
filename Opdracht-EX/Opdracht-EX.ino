#include <SimpleDHT.h>
int lichtsensorWaarde = 0;
int pinDHT11 = 4;
SimpleDHT11 dht11;
// blabkabkabkabkarerhg

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  lees_lichtsensor();
  lees_sht11();
  serial_python();
}

float lees_lichtsensor() {
  lichtsensorWaarde = analogRead(A2);
  //Serial.println(lichtsensorWaarde);
  float x = berekenSpanning(lichtsensorWaarde);
  //Serial.println("De lichtsensorwaarde is " + String (x) + " % ");
  delay(1000);
  return x;
}

float berekenSpanning (int sensorWaarde) {
  float spanning = (sensorWaarde / 900.0) * 100; //in percent
  float Gspanning = (100 - spanning);
  return Gspanning;
}


byte lees_sht11() {
  byte temperature = 0;
  byte humidity = 0;

  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 Filed");
    temperature = &temperature;
    return temperature;
  }
  //Serial.println("De temperatuur is " + String(temperature) + "°c");
  delay (2000);

}

void serial_python() {
  if (Serial.available() > 0) {

    byte lees = Serial.read();
    byte temperature = 0;
    String tekst = Serial.readString();
    //cr lf verwijderen
    tekst.replace("\n", "");
    tekst.replace("\r", "");
    //Serial.println("hallo + tekst");
    if (tekst == "temp") {
      Serial.println("De temperatuur is" + String(temperature) + " °c");
    }
    else if (tekst == "licht") {
      Serial.println ("De lichtwaarde is" + String (lees_lichtsensor()) + " %");
    }
    else {
      Serial.println("haen geldig commando ontvangen, stuur temp of licht");

    }
  }
  serial_python();
}

