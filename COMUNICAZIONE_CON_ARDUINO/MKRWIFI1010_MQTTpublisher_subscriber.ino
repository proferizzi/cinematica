// MQTT PUBLISHER con MKR WiFi-1010

//#include "secrets.h"  // inserire un nuovo file nella stessa cartella del filo *.ino con i dati ID e PW della rete       
#include <WiFiNINA.h>
#include <PubSubClient.h>

//const char WIFI_SSID[] = "ReteRizzi";  // commentare queste due righe se si usa "secrets.h"
//const char WIFI_PASS[] = "";

WiFiClient wifi;
int status = WL_IDLE_STATUS;

IPAddress server(192, 168, 178, 130);
PubSubClient client(wifi);

unsigned long t1, dt;
int stato = 0;


void setup() {
  while(!Serial){ ; }   // Attendo che sia pronta la Seriale
  Serial.begin(9600);   // La configuro 
  Serial.print("Connessione");
  while(status != WL_CONNECTED){
    status = WiFi.begin(WIFI_SSID, WIFI_PASS); Serial.print("."); delay(1000);
  }
  Serial.println("Connesso al WiFi!\n");
  
  client.setServer(server, 1883);   // Settaggio e collegamento col server MQTT
  if(client.connect("arduinopub")){      
    Serial.println("MQTT connesso");
    client.subscribe("/dati");  
  }else{
    Serial.println("MQTT non connesso"); 
    Serial.print("rc = "); Serial.println(client.state());  
  }
  t1 = millis();
}


void loop() {
  dt = millis() - t1;
  if(dt > 2000){
    if((stato%2) == 0){  // Divide per due e controlla il resto
      client.publish("/prova", "on"); Serial.println("on");
    }else{
      client.publish("/prova", "off"); Serial.println("off");
    }
    
    stato++;
    t1 = millis();
    
  }
}



// Fonte Aliverti https://www.youtube.com/watch?v=cLRuWwKkSp4
//                e per secrets.h https://www.youtube.com/watch?v=k5HJ6G0YeWw
// MKR1010 Hardware https://www.mischianti.org/it/2021/06/14/arduino-mkr-wifi-1010-piedinatura-ad-alta-risoluzione-e-specifiche/








/*

// MQTT SUBSCRIBER con MKR WiFi-1010


#include "secrets.h"
#include <WiFiNINA.h>
#include <PubSubClient.h>

WiFiClient wifi;
int status = WL_IDLE_STATUS;

IPAddress server(192, 168, 178, 130);
PubSubClient client(wifi);


void setup() {
  pinMode(13, OUTPUT);
  while(!Serial){ ; } Serial.begin(9600); Serial.println("Ok");
  Serial.print("Connessione");
  while(status != WL_CONNECTED){
    status = WiFi.begin(WIFI_SSID, WIFI_PASS); Serial.print("."); delay(1000);
  }
  Serial.println("Connesso al WiFi!\n");
  client.setServer(server, 1883);
  client.setCallback(callback);
  if(client.connect("arduinosub")){
    Serial.println("MQTT connesso");
    client.subscribe("/prova");  
  }else{
    Serial.println("MQTT non connesso"); 
    Serial.print("rc = "); Serial.println(client.state());  
  }
}


void loop() {
  client.loop();
}


void callback(char* topic, byte* payload, unsigned int length){
  String msg;
  for(int i = 0; i < length; i++){
    msg += (char)payload[i];
  }
  if(strcmp(topic, "/prova") == 0){
    if(msg == "on"){
      digitalWrite(13, HIGH); Serial.println("on");    
    }else{
      digitalWrite(13, LOW); Serial.println("off");
    }
  }
}



// Fonte https://www.youtube.com/watch?v=k5HJ6G0YeWw


*/





