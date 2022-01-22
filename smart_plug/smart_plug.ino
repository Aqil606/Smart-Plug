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

int decimalPrecision = 2;
int VoltageAnalogInputPin[3] = {13, 12, 14};
float voltageSampleRead  = 0;
float voltageLastSample  = 0;
float voltageSampleSum   = 0;
float voltageSampleCount = 0;
float voltageMean ;
float RMSVoltageMean ;
float adjustRMSVoltageMean;
float FinalRMSVoltage[3];

float voltageOffset1 = 0.00 ;
float voltageOffset2 = 0.00;

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
  for (int i = 0; i < 3; i++) {
    if (micros() >= voltageLastSample + 1000 )
    {
      voltageSampleRead = (analogRead(VoltageAnalogInputPin[i]) - 512) + voltageOffset1;
      voltageSampleSum = voltageSampleSum + sq(voltageSampleRead) ;

      voltageSampleCount = voltageSampleCount + 1;
      voltageLastSample = micros() ;
    }

    if (voltageSampleCount == 1000)
    {
      voltageMean = voltageSampleSum / voltageSampleCount;
      RMSVoltageMean = (sqrt(voltageMean)) * 1.5;
      adjustRMSVoltageMean = RMSVoltageMean + voltageOffset2;                                                                                                                                                                                                          /* square root of the average value*/
      FinalRMSVoltage[i] = (RMSVoltageMean + voltageOffset2) - 550;
      if (FinalRMSVoltage[i] <= 2.5)
      {
        FinalRMSVoltage[i] = 0;
      }
      voltageSampleSum = 0;
      voltageSampleCount = 0;
    }
  }

  Firebase.setFloat(fbdo, "/Tegangan/Voltase1", FinalRMSVoltage[0]) ? "ok" : fbdo.errorReason().c_str();
  Firebase.setFloat(fbdo, "/Tegangan/Voltase2", FinalRMSVoltage[1]) ? "ok" : fbdo.errorReason().c_str();
  Firebase.setFloat(fbdo, "/Tegangan/Voltase3", FinalRMSVoltage[2]) ? "ok" : fbdo.errorReason().c_str();

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
}
