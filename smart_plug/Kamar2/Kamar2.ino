#include <FirebaseESP32.h>
#include  <WiFi.h>
#define ch1 15
#define ch2 2
#define ch3 4

#define WIFI_SSID "Dr Ir H Amin MT"
#define WIFI_PASSWORD "duakatahurufbesarsemua"
#define FIREBASE_HOST "electric-socket-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5rLy39hUjnJrYUOmgEiUpyM57C6ZnvGiqnMPLLs3"
FirebaseData fbdo;

#include "EmonLib.h"
EnergyMonitor emon;
#define vCalibration 83.

void setup()
{
  pinMode(ch1, OUTPUT);
  pinMode(ch2, OUTPUT);
  pinMode(ch3, OUTPUT);
  digitalWrite(ch1, 1);
  digitalWrite(ch2, 1);
  digitalWrite(ch3, 1);

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
  Firebase.setFloat(fbdo, "/Tegangan/Voltase4", supplyVoltage) ? "ok" : fbdo.errorReason().c_str();

  emon.voltage(12, vCalibration, 1.7);
  emon.calcVI(20, 2000);
  supplyVoltage   = emon.Vrms * 10;
  Serial.print("V2 = ");
  Serial.println(supplyVoltage);
  Firebase.setFloat(fbdo, "/Tegangan/Voltase5", supplyVoltage) ? "ok" : fbdo.errorReason().c_str();
  
  emon.voltage(14, vCalibration, 1.7);
  emon.calcVI(20, 2000);
  supplyVoltage   = emon.Vrms * 10;
  Serial.print("V3 = ");
  Serial.println(supplyVoltage);
  Firebase.setFloat(fbdo, "/Tegangan/Voltase6", supplyVoltage) ? "ok" : fbdo.errorReason().c_str();

  if (Firebase.getString(fbdo, "Relay/r4"))
  {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    if (fbdo.stringData() == "true")
    {
      digitalWrite(ch1, LOW);
    }
    else
    {
      digitalWrite(ch1, HIGH);
    }
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
  if (Firebase.getString(fbdo, "Relay/r5"))
  {
    Serial.print("Get int data B success, str = ");
    Serial.println(fbdo.stringData());
    if (fbdo.stringData() == "true")
    {
      digitalWrite(ch2, LOW);
    }
    else
    {
      digitalWrite(ch2, HIGH);
    }
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
  if (Firebase.getString(fbdo, "Relay/r6"))
  {
    Serial.print("Get int data C success, str = ");
    Serial.println(fbdo.stringData());
    if (fbdo.stringData() == "true")
    {
      digitalWrite(ch3, LOW);
    }
    else
    {
      digitalWrite(ch3, HIGH);
    }
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
}
