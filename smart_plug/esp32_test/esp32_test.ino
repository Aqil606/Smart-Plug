#include <FirebaseESP32.h>
#include  <WiFi.h>


#define WIFI_SSID "Dr Ir H Amin MT"
#define WIFI_PASSWORD "duakatahurufbesarsemua"
#define FIREBASE_HOST "electric-socket-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5rLy39hUjnJrYUOmgEiUpyM57C6ZnvGiqnMPLLs3"
FirebaseData fbdo;

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
}

void loop()
{
  bool relay1 = Firebase.getBool(fbdo, "/Relay/r1");
  Serial.print(relay1);
}
