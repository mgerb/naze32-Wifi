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
#include "config.h"

/* Set these to your desired credentials. */
const char *ssid = "ESPap";
const char *password = "thereisnospoon";

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
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
     server.send(200, "text/html", "error reading naze32");
  }
  
}

void handleConfig(){

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
    server.send(200, "text/html", page_config);
  }
  
}

void setup() {
	delay(1000);
	Serial.begin(115200);
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	server.on("/", handleRoot);
  server.on("/config", handleConfig);
  
	server.begin();
}

void loop() {
	server.handleClient();
}
