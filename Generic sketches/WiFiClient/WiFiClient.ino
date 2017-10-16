/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>  //  UDP library - http://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/udp-examples.html
#include <PubSubClient.h>    //MQTT library

const char* ssid     = "XXX";  // Wifi network name
const char* password = "XXXXXX";   // wifi network password


WiFiClient espClient;
PubSubClient client(espClient);
WiFiUDP Udp;


unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacekt[] = "Hi there! Got the message :-)";  // a reply string to send back


void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   // Done connecting to wifi network


  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  client.setServer("XXXXXX",XXXXX);
}

void loop() {
  delay(500);

  client.connect("myid", "XXXXXX", "XXXXXXX");
  
  client.publish("room", "DOES IT WORK");

  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
  }

  //send a random number
  int  randNumber = random(1000);   // create a random number between 0 and 999
  char buf[4];  // buffer to contain the number as chars 
  sprintf (buf, "%03d", randNumber);   // create a string 3 digits with leading zero if needed
 
  Udp.beginPacket("192.168.43.247", 10119);  // send udp message to IP address 192.168.43.247, port 10119
  Udp.write(buf);
  Udp.endPacket();  
}

