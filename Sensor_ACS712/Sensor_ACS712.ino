#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "Milik Rakyat"
#define WIFI_PASSWORD "66666666"
#define FIREBASE_HOST "electric-socket-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5rLy39hUjnJrYUOmgEiUpyM57C6ZnvGiqnMPLLs3"

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void data_acs1() {
  const int pinADC = 14;
  int sensitivitas = 185;
  int nilaiadc = 00;
  int teganganoffset = 2500; //
  double tegangan = 00;
  double nilaiarus = 00;

  nilaiadc = analogRead(pinADC);
  tegangan = (nilaiadc / 1024.0) * 5000;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas);

  Serial.print("Nilai ADC yang terbaca = " );
  Serial.print(nilaiadc);
  Serial.print(" tegangan (mV) = ");
  Serial.print(tegangan, 3);
  Serial.print(" Arus = ");
  Serial.println(nilaiarus, 3);
  Firebase.setFloat("Arus/ACS1", nilaiarus);
  // handle error
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
}

void data_acs2() {
  const int pinADC = 12;
  int sensitivitas = 185;
  int nilaiadc = 00;
  int teganganoffset = 2500; //
  double tegangan = 00;
  double nilaiarus = 00;

  nilaiadc = analogRead(pinADC);
  tegangan = (nilaiadc / 1024.0) * 5000;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas);

  Serial.print("Nilai ADC yang terbaca = " );
  Serial.print(nilaiadc);
  Serial.print(" tegangan (mV) = ");
  Serial.print(tegangan, 3);
  Serial.print(" Arus = ");
  Serial.println(nilaiarus, 3);
  Firebase.setFloat("Arus/ACS2", nilaiarus);
  // handle error
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
}

void data_acs3() {
  const int pinADC = 13;
  int sensitivitas = 185;
  int nilaiadc = 00;
  int teganganoffset = 2500; //
  double tegangan = 00;
  double nilaiarus = 00;

  nilaiadc = analogRead(pinADC);
  tegangan = (nilaiadc / 1024.0) * 5000;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas);

  Serial.print("Nilai ADC yang terbaca = " );
  Serial.print(nilaiadc);
  Serial.print(" tegangan (mV) = ");
  Serial.print(tegangan, 3);
  Serial.print(" Arus = ");
  Serial.println(nilaiarus, 3);
  Firebase.setFloat("Arus/ACS3", nilaiarus);
  // handle error
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
}

void loop() {
  data_acs1();
  data_acs2();
  data_acs3();
  delay(1000);
}
