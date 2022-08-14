#include <FirebaseESP32.h>
#include <WiFi.h>

#define WIFI_SSID "Dr Ir H Amin MT"
#define WIFI_PASSWORD "duakatahurufbesarsemua"
#define FIREBASE_HOST "electric-socket-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5rLy39hUjnJrYUOmgEiUpyM57C6ZnvGiqnMPLLs3"
FirebaseData fbdo;

#include "EmonLib.h"
EnergyMonitor emon;
#define vCalibration 83.3

void setup()
{
  Serial.begin(9600);

  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  emon.voltage(13, vCalibration, 1.7);
  emon.calcVI(20, 2000);
  float supplyVoltage   = emon.Vrms * 10;
  Serial.print("V1 = ");
  Serial.println(supplyVoltage);
  Firebase.setFloat(fbdo, "/Tegangan/Voltase1", supplyVoltage) ? "ok" : fbdo.errorReason().c_str();

  emon.voltage(12, vCalibration, 1.7);
  emon.calcVI(20, 2000);
  supplyVoltage   = emon.Vrms * 10;
  Serial.print("V2 = ");
  Serial.println(supplyVoltage);
  Firebase.setFloat(fbdo, "/Tegangan/Voltase2", supplyVoltage) ? "ok" : fbdo.errorReason().c_str();
  
  emon.voltage(14, vCalibration, 1.7);
  emon.calcVI(20, 2000);
  supplyVoltage   = emon.Vrms * 10;
  Serial.print("V3 = ");
  Serial.println(supplyVoltage);
  Firebase.setFloat(fbdo, "/Tegangan/Voltase3", supplyVoltage) ? "ok" : fbdo.errorReason().c_str();

  delay(1000);
}
