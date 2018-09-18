//Resident_Community_management Arduino code ( Node mcu esp8266)
#include "UbidotsESPMQTT.h"


#define TOKEN "A1E-y87hPiKLKfWhANuHWHUZK7t5oaV4V8" // Your Ubidots TOKEN
#define WIFINAME "abcd" //Your SSID
#define WIFIPASS "12345" // Your Wifi Pass

Ubidots client(TOKEN);

char data;
char header;
char esp_data[5];
int i=0;
int esp_mq;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void setup() {
Serial.begin(115200);
//client.setDebug(true); // Pass a true or false bool value to activate debug messages
client.wifiConnection(WIFINAME, WIFIPASS);
client.begin(callback);
}


void loop() {
  

  if(!client.connected()){
      client.reconnect();
      }
 
  if(Serial.available()){
    data = Serial.read();
 
    if(data == 'U'){
      header = data;
    }

    else if(data == 'L')
    {
      header = data;
    }

    else if(data == 'G')
    {
      header = data;
    }


    else if(data=='\0'){

      if(header =='U'){ 
      esp_mq = atoi(esp_data);
      Serial.println("ultra");
      client.add("ultrasonic",esp_mq);
      client.ubidotsPublish("basket");
      }

      if(header== 'L'){
      esp_mq = atoi(esp_data);
      Serial.println("ldr");
      client.add("ldr",esp_mq);
      client.ubidotsPublish("basket");
      
      }

      if(header== 'G'){
      esp_mq = atoi(esp_data);
      Serial.println("gas");
      client.add("gas",esp_mq);
      client.ubidotsPublish("basket");
      
      }
      memset(esp_data, 0, sizeof(esp_data));
      i=0;
    }
    
    else
    {
      esp_data[i]=data;
      //Serial.print(esp_data[i]);
      i++;
    }
  }
  client.loop();
}

