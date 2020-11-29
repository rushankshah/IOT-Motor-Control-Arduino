#include <ArduinoJson.h>
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>
#define FIREBASE_HOST "your-firebase-app.firebaseio.com"  
#define FIREBASE_AUTH "your-secret-key"  
#define WIFI_SSID "WifiName"  
#define WIFI_PASSWORD "password" 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  // connect to wifi.  
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
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);  
}
int n = 0;  
void loop() {
  n=Firebase.getInt("Direction"); 
  Serial.println(n);
  if (n==1) {  
      Serial.print("Move Forward");  
      digitalWrite(D2,HIGH);
      digitalWrite(D4,HIGH);  
      Serial.println(Firebase.error());   
  }  
 else if (n==0){  
   Serial.print("Stop");  
   digitalWrite(D1,LOW);
   digitalWrite(D2,LOW);
   digitalWrite(D3,LOW);
   digitalWrite(D4,LOW);  
   Serial.println(Firebase.error()); 
 }  
 else if(n==2){
  Serial.print("Move right");
  digitalWrite(D1,HIGH);
  digitalWrite(D4,HIGH);
 }
 else if(n==3){
  Serial.print("Move backwards");
  digitalWrite(D1,HIGH);
  digitalWrite(D3,HIGH);
 }
 else if(n==4){
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
 }
 else{
    Serial.println("error");
}
}
