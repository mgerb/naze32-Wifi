/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include "index.h"
#include <DNSServer.h>

IPAddress apIP(192, 168, 1, 1);
IPAddress netMsk(255, 255, 255, 0);
const byte DNS_PORT = 53;
DNSServer dnsServer;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */

void handleRoot(){
  server.send(200, "text/html", page_index);
}

void handleAPIConfigurations() {
  int counter = 0;
  boolean error = false;
  Serial.flush();
  
  Serial.print("\r\n");
  delay(10);
  Serial.print("#\r\n");
  delay(10);
  Serial.print("dump\r\n");
  delay(10);
  Serial.print("exit\r\n");

  while(!Serial.available()){
    delay(1);
    counter++;

    if(counter == 5000){
      error = true;
      break;
    }
  }
  
  if (Serial.available() && error == false){ 
    String input = Serial.readString();
    
    int looptime_Index = input.indexOf("looptime");
    
    int p_pitch_Index = input.indexOf(" p_pitch ");
    int i_pitch_Index = input.indexOf(" i_pitch ");
    int d_pitch_Index = input.indexOf(" d_pitch ");

    int p_roll_Index = input.indexOf(" p_roll ");
    int i_roll_Index = input.indexOf(" i_roll ");
    int d_roll_Index = input.indexOf(" d_roll ");

    int p_yaw_Index = input.indexOf(" p_yaw ");
    int i_yaw_Index = input.indexOf(" i_yaw ");
    int d_yaw_Index = input.indexOf(" d_yaw ");
    
    String looptime = input.substring(input.indexOf("=",looptime_Index) + 1, input.indexOf("\n", looptime_Index) - 1);
    
    String p_pitch = input.substring(input.indexOf("=",p_pitch_Index) + 1, input.indexOf("\n", p_pitch_Index) - 1);
    String i_pitch = input.substring(input.indexOf("=",i_pitch_Index) + 1, input.indexOf("\n", i_pitch_Index) - 1);
    String d_pitch = input.substring(input.indexOf("=",d_pitch_Index) + 1, input.indexOf("\n", d_pitch_Index) - 1);

    String p_roll = input.substring(input.indexOf("=",p_roll_Index) + 1, input.indexOf("\n", p_roll_Index) - 1);
    String i_roll = input.substring(input.indexOf("=",i_roll_Index) + 1, input.indexOf("\n", i_roll_Index) - 1);
    String d_roll = input.substring(input.indexOf("=",d_roll_Index) + 1, input.indexOf("\n", d_roll_Index) - 1);

    String p_yaw = input.substring(input.indexOf("=",p_yaw_Index) + 1, input.indexOf("\n", p_yaw_Index) - 1);
    String i_yaw = input.substring(input.indexOf("=",i_yaw_Index) + 1, input.indexOf("\n", i_yaw_Index) - 1);
    String d_yaw = input.substring(input.indexOf("=",d_yaw_Index) + 1, input.indexOf("\n", d_yaw_Index) - 1);
    
    String response = "{\"looptime\" : " + looptime + ",\n"
                        "\"p_pitch\" : " + p_pitch + ",\n"
                        "\"i_pitch\" : " + i_pitch + ",\n"
                        "\"d_pitch\" : " + d_pitch + ",\n"
                        "\"p_roll\" : " + p_roll + ",\n"
                        "\"i_roll\" : " + i_roll + ",\n"
                        "\"d_roll\" : " + d_roll + ",\n"
                        "\"p_yaw\" : " + p_yaw + ",\n"
                        "\"i_yaw\" : " + i_yaw + ",\n"
                        "\"d_yaw\" : " + d_yaw + "}";
    
    server.send(200, "application/json", response);
  }
  else {
     server.send(200, "application/json", "{message : \"error reading Naze32\"");
  }
  
}

//handle main save functionality
void handleSave(){

  if(server.args() > 0){
    Serial.print("\r\n");
    delay(10);
    Serial.print("#\r\n");
    delay(10);
    
    for(uint8_t i=0; i < server.args(); i++){
      Serial.print("set " + server.argName(i) + " = " + server.arg(i) + "\r\n");
      delay(10);
    }
  
    Serial.print("save\r\n");
    delay(1000);
  }

  server.send(200, "text/html", "<script>window.location.replace(\"/\");</script>");
  
}

//handle manual input by user
void handleManualConfig(){

  if (server.arg("command") != ""){
    int counter = 0;
    
    Serial.print("\r\n");
    delay(10);
    Serial.print("#\r\n");
    delay(10);
    Serial.print(server.arg("command") + "\r\n");
    delay(10);
    Serial.print("save\r\n");
    delay(2000);
    Serial.flush();
    
    server.send(200, "text/html", "<script>window.location.replace(\"/\");</script>");
      
  }
  else {
    server.send(200, "text/html", page_index);
  }
  
}

void handleDump(){
  int counter = 0;
  boolean error = false;
  Serial.flush();
  
  Serial.print("\r\n");
  delay(10);
  Serial.print("#\r\n");
  delay(10);
  Serial.print("dump\r\n");
  delay(10);
  Serial.print("exit\r\n");

  while(!Serial.available()){
    delay(1);
    counter++;

    if(counter == 5000){
      error = true;
      break;
    }
  }
  
  if (Serial.available() && error == false){
    
    server.send(200, "text/plain", Serial.readString());
  }
  else {
     server.send(200, "text/html", "Error reading from Naze32 - Please reboot");
  }
}
void setup() {
	delay(1000);
	Serial.begin(115200);
	/* You can remove the password parameter if you want the AP to be open. */
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, netMsk);
	WiFi.softAP("Drone Configuration", "thereisnospoon");
  dnsServer.start(DNS_PORT, "*", apIP);
  
  server.on("/", handleRoot);
	server.on("/api/configurations", handleAPIConfigurations);
  server.on("/save", handleSave);
  server.on("/dump", handleDump);
  server.on("/manualconfig", handleManualConfig);
  
	server.begin();
}

void loop() {
  dnsServer.processNextRequest();
	server.handleClient();
}
