#include <FirebaseESP32.h>
#include <WiFi.h>
#define ch1 15
#define ch2 2
#define ch3 4



#define WIFI_SSID "Milik Rakyat"
#define WIFI_PASSWORD "66666666"
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

void data_acs1() {
  const int pinADC = 27;
  int sensitivitas = 66;
  int nilaiadc = 00;
  int teganganoffset = 2500; //
  double tegangan = 00;
  double nilaiarus = 00;

  nilaiadc = analogRead(pinADC);
  tegangan = (nilaiadc / 1024.0) * 5000;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas) / 100;

  Serial.print(" Arus = ");
  Serial.println(nilaiarus, 3);
  Firebase.setFloat(fbdo, "/Arus/AC41", nilaiarus) ? "ok" : fbdo.errorReason().c_str();
}

void data_acs2() {
  const int pinADC = 26;
  int sensitivitas = 66;
  int nilaiadc = 00;
  int teganganoffset = 2500; //
  double tegangan = 00;
  double nilaiarus = 00;

  nilaiadc = analogRead(pinADC);
  tegangan = (nilaiadc / 1024.0) * 5000;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas) / 100;

  Serial.print(" Arus = ");
  Serial.println(nilaiarus, 3);
  Firebase.setFloat(fbdo, "/Arus/ACS5", nilaiarus) ? "ok" : fbdo.errorReason().c_str();
}

void data_acs3() {
  const int pinADC = 25;
  int sensitivitas = 66;
  int nilaiadc = 00;
  int teganganoffset = 2500; //
  double tegangan = 00;
  double nilaiarus = 00;

  nilaiadc = analogRead(pinADC);
  tegangan = (nilaiadc / 1024.0) * 5000;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas) / 100;

  Serial.print(" Arus = ");
  Serial.println(nilaiarus, 3);
  Firebase.setFloat(fbdo, "/Arus/AC63", nilaiarus) ? "ok" : fbdo.errorReason().c_str();
}

void loop()
{
  //Sensor 4
  if (Firebase.getString(fbdo, "Relay/r4"))
  {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    if (fbdo.stringData() == "true")
    {
      digitalWrite(ch1, LOW);

      data_acs1();

      emon.voltage(13, vCalibration, 1.7);
      emon.calcVI(20, 2000);
      float supplyVoltage   = (emon.Vrms * 10) + 59;
      Serial.print("V1 = ");
      Serial.println(supplyVoltage);
      Firebase.setFloat(fbdo, "/Tegangan/Voltase4", supplyVoltage) ? "ok" : fbdo.errorReason().c_str();

      if (supplyVoltage == 0) {
        Firebase.setString(fbdo, "/Pesan_Error/Sensor4", "Sensor Rusak") ? "ok" : fbdo.errorReason().c_str();
      }
      else {
        Firebase.setString(fbdo, "/Pesan_Error/Sensor4", "Sensor Berfungsi") ? "ok" : fbdo.errorReason().c_str();
      }
    }
    else
    {
      digitalWrite(ch1, HIGH);
    }
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }

  //Sensor 5
  if (Firebase.getString(fbdo, "Relay/r5"))
  {
    Serial.print("Get int data B success, str = ");
    Serial.println(fbdo.stringData());
    if (fbdo.stringData() == "true")
    {
      digitalWrite(ch2, LOW);

      data_acs2();

      emon.voltage(12, vCalibration, 1.7);
      emon.calcVI(20, 2000);
      float supplyVoltage   = (emon.Vrms * 10) + 59;
      Serial.print("V2 = ");
      Serial.println(supplyVoltage);
      Firebase.setFloat(fbdo, "/Tegangan/Voltase5", supplyVoltage) ? "ok" : fbdo.errorReason().c_str();

      if (supplyVoltage == 0) {
        Firebase.setString(fbdo, "/Pesan_Error/Sensor5", "Sensor Rusak") ? "ok" : fbdo.errorReason().c_str();
      }
      else {
        Firebase.setString(fbdo, "/Pesan_Error/Sensor5", "Sensor Berfungsi") ? "ok" : fbdo.errorReason().c_str();
      }
    }
    else
    {
      digitalWrite(ch2, HIGH);
    }
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }

  //Sensor 6
  if (Firebase.getString(fbdo, "Relay/r6"))
  {
    Serial.print("Get int data C success, str = ");
    Serial.println(fbdo.stringData());
    if (fbdo.stringData() == "true")
    {
      digitalWrite(ch3, LOW);

      data_acs3();

      emon.voltage(14, vCalibration, 1.7);
      emon.calcVI(20, 2000);
      float supplyVoltage   = (emon.Vrms * 10) + 59;
      Serial.print("V3 = ");
      Serial.println(supplyVoltage);
      Firebase.setFloat(fbdo, "/Tegangan/Voltase6", supplyVoltage) ? "ok" : fbdo.errorReason().c_str();

      if (supplyVoltage == 0) {
        Firebase.setString(fbdo, "/Pesan_Error/Sensor6", "Sensor Rusak") ? "ok" : fbdo.errorReason().c_str();
      }
      else {
        Firebase.setString(fbdo, "/Pesan_Error/Sensor6", "Sensor Berfungsi") ? "ok" : fbdo.errorReason().c_str();
      }
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
