#ifndef __CC3200R1M1RGC__
#endif
#include <WiFi.h>
#include <WiFiClient.h>
#include <Temboo.h>
#include "temboo_header.h" // Contains Temboo account information
#include "LiquidCrystal.h"
 

#include <Ultrasonic.h>

Ultrasonic ultrasonicfirst(28,8);// (Trig PIN,Echo PIN)
Ultrasonic ultrasonicsecond(23,24);
int keyIndex = 0;

WiFiServer server(80); 


WiFiClient client;
#define trig1 28             
#define echo1 8
#define trig2 27             
#define echo2 7

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 11;   // Maximum number of times the Choreo should be executed
int buttonState = 0;
LiquidCrystal lcd(19,17,5,4,3,2);
long Distance1, Distance2;

void setup() {
    Serial.begin(9600);
   pinMode(trig1, OUTPUT);
   pinMode(echo1, INPUT);
    pinMode(trig2, OUTPUT);
   pinMode(echo2, INPUT);
   pinMode(PUSH2, INPUT);
   pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
   
   lcd.begin(16,2);
   
  int wifiStatus = WL_IDLE_STATUS;
  Serial.print("\n\nShield:");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("FAIL");
    while(true);
  }
  Serial.println("OK");
  while(wifiStatus != WL_CONNECTED) {
    Serial.print("WiFi:");
    wifiStatus = WiFi.begin(WIFI_SSID,WIFI_PASSWORD);

    if (wifiStatus == WL_CONNECTED){ 
      Serial.println("OK");
    } else {
      Serial.println("FAIL");
    }
    delay(5000);
  }

  Serial.println("Setup complete.\n");
   
   }

void loop() {
  buttonState = digitalRead(PUSH2);
  if(buttonState == HIGH)
  {

    Serial.println("Running MakeCall - Run #" + String(calls++));
    String choice = "";

    TembooChoreo MakeCallChoreo(client);

    // Invoke the Temboo client
    MakeCallChoreo.begin();

    // Set Temboo account credentials
    MakeCallChoreo.setAccountName(TEMBOO_ACCOUNT);
    MakeCallChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    MakeCallChoreo.setAppKey(TEMBOO_APP_KEY);

    // Set Choreo inputs
   String AuthTokenValue = "b440f544e70e2aaffb45f690ff5caeb2";
    MakeCallChoreo.addInput("AuthToken", AuthTokenValue);
    String ToValue = "+919736893596";
    MakeCallChoreo.addInput("To", ToValue);
    String FromValue = "+16413246427";
    MakeCallChoreo.addInput("From", FromValue);
   String AnswerURLValue = "https://handler.twilio.com/twiml/EH1b0c31ee2367d0b88c5c0eead2d114a3";
   MakeCallChoreo.addInput("AnswerURL",AnswerURLValue);
   String GoodbyeURLValue = "https://handler.twilio.com/twiml/EHe0529e34868dba21506db0ce2393fa3c"; 
    MakeCallChoreo.addInput("GoodbyeURL",GoodbyeURLValue);
    String AccountSIDValue = "AC5884ce63c47e4c8ae693f0f97a58ca6e";

   MakeCallChoreo.addInput("AccountSID", AccountSIDValue);

    // Identify the Choreo to run from the temboo Library
    MakeCallChoreo.setChoreo("/Library/Twilio/Calls/CaptureKeyPadEntry"); 
// use an output filter to filter the required output
MakeCallChoreo.addOutputFilter("choice", "", "Digits");

  // run Choreo
 MakeCallChoreo.run(901,USE_SSL);
 //delay(15000);
  // parse the results
  while(MakeCallChoreo.available()) {
    // read the name of the next output item
    String name = MakeCallChoreo.readStringUntil('\x1F');
    name.trim(); // use “trim” to get rid of newlines
   Serial.println(name);
   // Serial.println("hi");
    // read the value of the next output item
    String data = MakeCallChoreo.readStringUntil('\x1E');
    data.trim(); // use “trim” to get rid of newlines
  Serial.println(data);
    // parse the user's choice out of the response data
    if (name == "choice") 
     {  Serial.println(" fetch");
      choice = data;
    } 
  }
  // close the Choreo 
 MakeCallChoreo.close();

  // return the choice that the user made 
  if (choice == "1")
  {
      Serial.println("The user pressed 1.\n");
      lcd.print("Pls. come later!");
  }   

     else if (choice == "2")
  {
      Serial.println("The user pressed 2.\n");
      lcd.print("Wait a sec!");
  }     


    
}


    Distance1 = ultrasonicfirst.Ranging(CM);
  Serial.print(Distance1); // CM or INC
  Serial.println(" cm" ); 
  
 
  
   delay(1000);   
  if(Distance1 <50){
  
    digitalWrite(GREEN_LED, HIGH);

  
  
    Serial.println("Running MakeCall - Run #" + String(calls++));
    String choice = "";

    TembooChoreo MakeCallChoreo(client);

    // Invoke the Temboo client
    MakeCallChoreo.begin();

    // Set Temboo account credentials
    MakeCallChoreo.setAccountName(TEMBOO_ACCOUNT);
    MakeCallChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    MakeCallChoreo.setAppKey(TEMBOO_APP_KEY);

    // Set Choreo inputs
    String AuthTokenValue = "b440f544e70e2aaffb45f690ff5caeb2";
    MakeCallChoreo.addInput("AuthToken", AuthTokenValue);
    String ToValue = "+919736893596";
    MakeCallChoreo.addInput("To", ToValue);
    String FromValue = "+16413246427";
    MakeCallChoreo.addInput("From", FromValue);
   String AnswerURLValue = "https://handler.twilio.com/twiml/EHb5d9fe93271e0f04dbaf4165de350247";
   MakeCallChoreo.addInput("AnswerURL",AnswerURLValue);
   String GoodbyeURLValue = ""; 
    MakeCallChoreo.addInput("GoodbyeURL",GoodbyeURLValue);
    String AccountSIDValue = "AC5884ce63c47e4c8ae693f0f97a58ca6e";

   MakeCallChoreo.addInput("AccountSID", AccountSIDValue);

    // Identify the Choreo to run from the temboo Library
    MakeCallChoreo.setChoreo("/Library/Twilio/Calls/CaptureKeyPadEntry"); 
// use an output filter to filter the required output
// MakeCallChoreo.addOutputFilter("choice", "", "Digits");

  // run Choreo
 MakeCallChoreo.run(901,USE_SSL);
 delay(15000);

  }
    
} 











