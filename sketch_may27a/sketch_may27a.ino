
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Net_551976"
#define WIFI_PASSWORD "adnan2244adnan2244"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBt3Vyfp1ze7VgCX5WGW9JAzyLrxPIGKkE"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://doorlock-ae216-default-rtdb.europe-west1.firebasedatabase.app" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;



#define BUTTON D7
#define LOCK D8
int count = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  pinMode(BUTTON, INPUT);
  pinMode(LOCK, OUTPUT);
}
bool openDoor = false;
void loop() {
  // delay(1000);
  byte buttonState = digitalRead(BUTTON);
  
  if(buttonState == HIGH){
    Firebase.RTDB.setInt(&fbdo, "doorbell", true);
  }
  else{
    Firebase.RTDB.setInt(&fbdo, "doorbell", false);
  }

  if(Firebase.RTDB.getBool(&fbdo, "openDoor")){
    openDoor = fbdo.boolData();
  }

  if(openDoor == true){
    digitalWrite(LOCK, LOW);
  }
  else{
    digitalWrite(LOCK, HIGH);

  }

  delay(500);
}
