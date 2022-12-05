#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>

//String ssid = "Pak DELUCI";
//String passwd = "hallo123456";

//String ssid = "iPhone 8";
//String passwd = "321123321";

String ssid = "Indah ";
String passwd = "aldo123456";

HTTPClient http;

//String url = "http://192.168.137.152:3000/api/v1/review/now";
//String url = "http://172.20.10.2:3000/api/v1/review/now";
String url = "https://3000-fahmibahtia-arduinorevi-ep2bm3kfyxh.ws-us77.gitpod.io/api/v1/review/now";

void connectWifi();
void postPuas();
void postBiasa();
void postTidakPuas();
//void scrollText();

#define PIN_PUAS 2
#define PIN_BIASA 16
#define PIN_TIDAK_PUAS 18
#define PIN_LED 15

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

//String messageStatic = "ARDUINO";
String messageToScroll = "INI TEXT JALAN";

void setup() {

  Serial.begin(115200);

  pinMode(PIN_PUAS, INPUT_PULLUP);
  pinMode(PIN_BIASA, INPUT_PULLUP);
  pinMode(PIN_TIDAK_PUAS, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);

  connectWifi();
  
//  lcd.init();
//  lcd.backlight();

  int puasValue = getPuas();
  int biasaValue = getBiasa();
  int tidakPuasValue = getTidakPuas();

  String strPuasValue;
  strPuasValue += puasValue;

  Serial.println(strPuasValue);

//  Serial.println(puasValue);

//  Serial.println(puasValue);
//  Serial.println(biasaValue);
//  Serial.println(tidakPuasValue);
 
}

void loop() {

  while (digitalRead(PIN_PUAS) != LOW && digitalRead(PIN_BIASA) != LOW && digitalRead(PIN_TIDAK_PUAS) != LOW) {
//    scrollText(1, messageToScroll, 100, lcdColumns);
    digitalWrite(PIN_LED, 1);
  }
  
  if (digitalRead(PIN_PUAS) == LOW) {
    
    postPuas();
    
  }

  if (digitalRead(PIN_BIASA) == LOW) {
    
    postBiasa();

  }

  if (digitalRead(PIN_TIDAK_PUAS) == LOW) {
    
    postTidakPuas();
    
  }

  delay(100);
  
}

void connectWifi() {
  
  Serial.println("Connecting to WiFi...");
  
  WiFi.begin(ssid.c_str(),passwd.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    
    delay(5000);
    Serial.println("Connecting to WiFi...");
  }

  if (WiFi.status() == WL_CONNECTED) {
    
    delay(3000);
    Serial.print("Connected to ");
    Serial.println(ssid);
    
    delay(1000);
    Serial.println("Ready to go");
    Serial.println(" ");
  }
  
}

void postPuas() {

  Serial.println("Posting...");
  
  HTTPClient http;
  String response;
  
  StaticJsonDocument<256> root;
  String jsonParams;
  
  root["puas"] = 1;
  root["tidakPuas"] = 0;
  root["biasa"] = 0;

  serializeJson(root, jsonParams);

  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int statusCode = http.POST(jsonParams);

  response = http.getString();

  if (statusCode == 201) {
    
    Serial.println("Post Puas Success");
    Serial.println(" ");

    digitalWrite(PIN_LED, 1);
    delay(100);
    digitalWrite(PIN_LED, 0);
    delay(300);
    digitalWrite(PIN_LED, 1);
    delay(100);
    digitalWrite(PIN_LED, 0);
    delay(300);
    digitalWrite(PIN_LED, 1);
    delay(100);
    digitalWrite(PIN_LED, 0);
    delay(300);
    
  } else {
    
    Serial.println("Post Puas Failed");
    Serial.println(" ");
    
  }
}

  void postBiasa() {

  Serial.println("Posting...");

  HTTPClient http;
  String response;
  
  StaticJsonDocument<256> root;
  String jsonParams;
  
  root["puas"] = 0;
  root["tidakPuas"] = 0;
  root["biasa"] = 1;

  serializeJson(root, jsonParams);

  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int statusCode = http.POST(jsonParams);

  response = http.getString();

//  Serial.println(statusCode);

  if (statusCode == 201) {
    
    Serial.println("Post Biasa Success");
    Serial.println(" ");

    digitalWrite(PIN_LED, 1);
    delay(100);
    digitalWrite(PIN_LED, 0);
    delay(300);
    digitalWrite(PIN_LED, 1);
    delay(100);
    digitalWrite(PIN_LED, 0);
    delay(300);
    
  } else {
    
    Serial.println("Post Biasa Failed");
    Serial.println(" ");
    
  }
}

void postTidakPuas() {

  Serial.println("Posting...");
  
  HTTPClient http;
  String response;
  
  StaticJsonDocument<256> root;
  String jsonParams;
  
  root["puas"] = 0;
  root["tidakPuas"] = 1;
  root["biasa"] = 0;

  serializeJson(root, jsonParams);

  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int statusCode = http.POST(jsonParams);

  response = http.getString();

  if (statusCode == 201) {
    
    Serial.println("Post Tidak Puas Success");
    Serial.println(" ");

    digitalWrite(PIN_LED, 1);
    delay(100);
    digitalWrite(PIN_LED, 0);
    delay(300);
    
  } else {
    
    Serial.println("Post Tidak Puas Failed");
    Serial.println(" ");
    
  }
}

int getPuas() {
  
  http.begin(url);
  http.GET();

  String response = http.getString();
  
  StaticJsonDocument<256> doc;
  deserializeJson(doc, response);
  JsonObject root = doc.as<JsonObject>();

  int reviews = root["reviews"][0]["puas"];
  
  return reviews;
  
}

int getBiasa() {
  
  http.begin(url);
  http.GET();

  String response = http.getString();
  
  StaticJsonDocument<256> doc;
  deserializeJson(doc, response);
  JsonObject root = doc.as<JsonObject>();

  int reviews = root["reviews"][0]["biasa"];
  
  return reviews;
  
}

int getTidakPuas() {
  
  http.begin(url);
  http.GET();

  String response = http.getString();
  
  StaticJsonDocument<256> doc;
  deserializeJson(doc, response);
  JsonObject root = doc.as<JsonObject>();

  int reviews = root["reviews"][0]["tidakPuas"];
  
  return reviews;
  
}

//void scrollText(int row, String message, int delayTime, int lcdColumns) {
//  for (int i=0; i < lcdColumns; i++) {
//    message = " " + message;  
//  } 
//  message = message + " "; 
//  for (int pos = 0; pos < message.length(); pos++) {
//    lcd.setCursor(0, row);
//    lcd.print(message.substring(pos, pos + lcdColumns));
//    delay(delayTime);
//  }
//}
