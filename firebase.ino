/*
  Project: Send Data to Firebase Using Arduino Uno WiFi Rev2
  Board: Arduino Uno WiFi Rev2

  External libraries:
  – Arduino_LSM6DS3 by Arduino V1.0.0
  – Firebase Arduino based on WiFiNINA by Mobizt V1.1.4
*/

#include <Arduino_LSM6DS3.h>
#include <Firebase_Arduino_WiFiNINA.h>

#define FIREBASE_HOST "apsc200-p2-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "knB35lHBrbWsqSAWYUaceUNPggbtoNLpKvtT0qlu"
#define WIFI_SSID "laptop"
#define WIFI_PASSWORD "aaaaaaaa"

FirebaseData firebaseData;

String path = "INPUT";
String jsonStr;
int pirPin = 2;
int pressurePin = A0;
int voltage = 0;
int limit = 100;
int pressState = 0;
int pirStat = digitalRead(pirPin);

void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println();

  Serial.print("Connecting to WiFi…");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }
  Serial.print(" IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  pirStat = digitalRead(pirPin);
  pressState = detectPress();

  // Send data to firebase with path
  if (Firebase.setBool(firebaseData, path + "/setMotion", pirStat))
  {
    Serial.println(firebaseData.dataPath() + " = " + pirStat);
  }
  if (Firebase.setBool(firebaseData, path + "/setPressure", pressState))
  {
    Serial.println(firebaseData.dataPath() + " = " + pressState);
  }
  
  delay(1000);
}

int detectPress() {
  voltage = map(analogRead(pressurePin), 0, 1023, 0, 5000);
  Serial.println(voltage);
  if (voltage > limit)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
