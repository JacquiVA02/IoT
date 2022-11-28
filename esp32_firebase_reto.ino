
#include <esp_wpa2.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include "Arduino.h"
#include "addons/RTDBHelper.h"

//LIBRERÍAS SENSOR DE HUMEDAD Y TEMPERATURA
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11   // DHT 11
//**********************************

//LIBRERÍAS SENSOR DE ACELERACIÓN****
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
//**********************************


const char* ssid = "Tec";
#define EAP_IDENTITY "a017XXXXX@tec.mx"
#define EAP_PASSWORD "Contraseña*"

// Firebase insert auth
#define USER_EMAIL "a017XXXXX@tec.mx"
#define USER_PASSWORD "Contraseña"




// Insertar clave de API del proyecto de Firebase
#define API_KEY "AIzaSyBxszYcMxp-EjlOPwmHEWgSj8CH4vrTslQ"

// Insertar URL de URLefine la URL de RTDB
#define DATABASE_URL "https://proyectoprueba-8b57d-default-rtdb.firebaseio.com/"

// Definir objeto de datos de Firebase
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int intValue;
float floatValue;
String sValue;

bool signupOK = false;
int count = 0;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    delay(10);
    Serial.println(F("DHTxx test!"));

    dht.begin();

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    // WPA2 enterprise magic starts here
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);   //init wifi mode
  //esp_wifi_set_mac(ESP_IF_WIFI_STA, &masterCustomMac[0]);
  Serial.print("MAC >> ");
  Serial.println(WiFi.macAddress());
  Serial.printf("Connecting to WiFi: %s ", ssid);
  //esp_wifi_sta_wpa2_ent_set_ca_cert((uint8_t *)incommon_ca, strlen(incommon_ca) + 1);
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  //esp_wpa2_config_t configW = WPA2_CONFIG_INIT_DEFAULT();
  //esp_wifi_sta_wpa2_ent_enable(&configW);
  esp_wifi_sta_wpa2_ent_enable();
    // WPA2 enterprise magic ends here


    WiFi.begin(ssid);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

///* Asigne la Api Key (obligatorio) */
  config.api_key = API_KEY;

  /* Asigne el RTDB URL (obligatorio) */
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


// SENSOR DE ACELERACION******
if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  delay(100);
//****************************
}

/*
 *  Todo debajo de esto, en loop(), es solo una solicitud estándar a un servidor web
 *
 */

int value = 0;

void loop() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

// SENSOR DE GAS *************
  int pin_mq = 135;
       Serial.begin(115200);
       pinMode(pin_mq, INPUT);
       boolean mq_estado = digitalRead(pin_mq);//Leemos el sensor
//**********************

// SENSOR DE DISTANCIA *********
  const int trigPin = 5;
  const int echoPin = 18;

  //define sound speed in cm/uS
  #define SOUND_SPEED 0.034
  #define CM_TO_INCH 0.393701

  long duration;
  float distanceCm;

  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
//************************

//SENSOR DE SONIDO*********************
 int sound_analog = 26; //Declaración del pin de salida análoga
  int val_analog = analogRead(sound_analog);
//*************************************


///DISPLAY DE 7 SEGMENTOS***********************
//se declaran los pines a usar
int LEDs[] = {14,23,33,25,19,32,12};    // for ESP32 microcontroller
//se declaran los arreglos que forman los dígitos
int zero[] = {1, 1, 1, 1, 1, 1, 0};   // cero
int one[] = {0, 0, 0, 0, 1, 1, 0};   // uno
int two[] = {1, 1, 0, 1, 1, 0, 1};   // dos
int three[] = {1, 1, 1, 1, 0, 0, 1};   // tres
int four[] = {0, 1, 1, 0, 0, 1, 1};   // cuatro 
int five[] = {1, 0, 1, 1, 0, 1, 1};   // cinco
int six[] = {1, 0, 1, 1, 1, 1, 1};   // seis
int seven[] = {1, 1, 1, 0, 0, 0, 0};   // siete
int eight[] = {1, 1, 1, 1, 1, 1, 1}; // ocho
int nine[] = {1, 1, 1, 1, 0, 1, 1};   // nueve
int ten[] = {0, 0, 0, 0, 0, 0, 1};   // guion
//****************************************


    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
   // Write an Int number on the database path test/int
    //HUMEDAD*********************
    if (Firebase.RTDB.setFloat(&fbdo, "test/Humedad", h)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    //count++;

    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "test/TemperaturaC",hic )){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    //////////////
    if (Firebase.RTDB.setFloat(&fbdo, "test/TemperaturaF", hif)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    //*******************************
    //GAS
    if (Firebase.RTDB.setFloat(&fbdo, "test/Gas", mq_estado)){
      Serial.println("PASSED");
            if(mq_estado){  //si la salida del sensor es 1
              Serial.println("Sin presencia de gas");
            }
            else{  //si la salida del sensor es 0
              Serial.println("Gas detectado");
            }
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    //*******************************
    // DISTANCIA
    if (Firebase.RTDB.setFloat(&fbdo, "test/DistanciaCm", distanceCm)){
      Serial.println("PASSED");
      Serial.print("Distance (cm): ");
      Serial.println(distanceCm);
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    //*******************************
    
    // ACELERACIÓN
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    if (Firebase.RTDB.setFloat(&fbdo, "test/AceleracionX", a.acceleration.x)){
       /* Get new sensor events with the readings */
      Serial.println("PASSED");
      Serial.print("Aceleracion en X: ");
      Serial.println(a.acceleration.x);
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    
    // LEER FIREBASE EN ESP32*****************
    if (Firebase.RTDB.getString(&fbdo, "/test/numero")){
      if (fbdo.dataType() == "string"){
        sValue = fbdo.stringData(); 
      }
    value = sValue.toInt();
    switch(value)
    {
        case 0:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], zero[i]);
                    break;
        case 1:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], one[i]);
                    break;
        case 2:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], two[i]);
                    break;
        case 3:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], three[i]);
                    break;
        case 4:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], four[i]);
                    break;
        case 5:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], five[i]);
                    break;
        case 6:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], six[i]);
                    break;
        case 7:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], seven[i]);
                    break;
        case 8:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], eight[i]);
                    break;
        case 9:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], nine[i]);
                    break;
        case 10:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], ten[i]);
                    break;
        default:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], ten[i]);
                    break;          
       }
     }
    //****************************************
  }
  for (int i = 0; i<7; i++) pinMode(LEDs[i], OUTPUT);
}
