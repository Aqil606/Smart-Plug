#include <WiFi.h>
#include <FirebaseESP32.h>
 
#define FIREBASE_HOST "https://electric-socket-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "5rLy39hUjnJrYUOmgEiUpyM57C6ZnvGiqnMPLLs3"
#define WIFI_SSID "Milik Rakyat"
#define WIFI_PASSWORD "66666666"
FirebaseData firebaseData;
FirebaseJson json;


const int pinADC = 27;
int sensitivitas = 66;
int nilaiadc = 00;
int teganganoffset = 2500; //
double tegangan = 00;
double nilaiarus = 00;

void setup()
{
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
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  Serial.println("------------------------------------");
  Serial.println("Connected...");
  
}
 
void loop()
{
  nilaiadc = analogRead(pinADC);
  tegangan = (nilaiadc / 1024.0) * 5000;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas);

  Serial.print("Nilai ADC yang terbaca = " );
  Serial.print(nilaiadc);
  Serial.print(" tegangan (mV) = ");
  Serial.print(tegangan, 3);
  Serial.print(" Arus = ");
  Serial.println(nilaiarus, 3);
  
  json.set("/data", nilaiarus);
  Firebase.updateNode(firebaseData,"/Sensor",json);
}
