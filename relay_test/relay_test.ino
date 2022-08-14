#define ch1 15
#define ch2 2
#define ch3 4

#include <FirebaseESP32.h>
#include  <WiFi.h>

#define WIFI_SSID "Dr Ir H Amin MT"
#define WIFI_PASSWORD "duakatahurufbesarsemua"
#define FIREBASE_HOST "electric-socket-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5rLy39hUjnJrYUOmgEiUpyM57C6ZnvGiqnMPLLs3"
FirebaseData fbdo;

void setup() {
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

void loop() {
  if (Firebase.getString(fbdo, "Relay/r1"))
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
  if (Firebase.getString(fbdo, "Relay/r2"))
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
  if (Firebase.getString(fbdo, "Relay/r3"))
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
  delay(5000);
}
