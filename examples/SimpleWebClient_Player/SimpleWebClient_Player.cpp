// Copyright  : Dennis Buis (2017, 2018)
// License    : MIT
// Platform   : Arduino
// Library    : Simple WebRadio Library for Arduino & ESP8266
// File       : SimpleWebClient_GET.cpp
// Purpose    : Arduino / ESP8266 library to create a simple webclient requesting API calls
// Repository : https://github.com/DennisB66/Simple-WebClient-Library-for-Arduino

#include <Arduino.h>
#include "SimpleWebClient.h"
#include "SimpleUtils.h"

#define CLIENT_NAME "CLIENT-01"                             // host name
#define CLIENT_PORT 80                                      // host port

#include "MySecrets.h"                                      // Wifi Settings (change in MySecrets.h)
const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;

byte client_mac[]     = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte client_ip4[]     = { 192, 168,   1,  68 };             // lan ip (e.g. "192.168.1.60")
byte client_gateway[] = { 192, 168,   1,   1 };             // router gateway
byte client_subnet[]  = { 255, 255, 255,   0 };             // subnet mask

SimpleWebClient client( 80);                                // server object (to respond on API calls)

void setup()
{
  BEGIN( 115200) LF;                                        // Serial at 115200

  PRINT( F( "# ---------------------------")) LF;           // show header
	PRINT( F( "# -  WebClient GET example  -")) LF;
  PRINT( F( "# -  V0.1      (DennisB66)  -")) LF;
  PRINT( F( "# ---------------------------")) LF;
  PRINT( F( "#")) LF;

#if defined(ESP8266)                                        // ESP8266 = connect via WiFi
  WiFi.hostname( CLIENT_NAME);                              // set host name
  WiFi.config( client_ip4, client_gateway, client_subnet);  // set fixed IP address
//WiFi.begin();                                             // open WiFi connection (ssid/pw from EEPROM)
  WiFi.begin( ssid, pass);                                  // open WiFi connection
  while ( WiFi.status() != WL_CONNECTED) delay(500);        // wait for  connection

  LABEL( F( "# client available at "), WiFi.localIP()) LF;
#else                                                       // Arduino = connect via Ethernet
//Ethernet.hostName( SERVER_NAME);                          // not supported (yet)
  ETHERNET_RESET( 11U);                                     // Leonardo ETH reset
  Ethernet.begin( client_mac, client_ip4, client_gateway, client_subnet);
                                                            // open ethernet connection
  LABEL( F( "# client available at "), Ethernet.localIP()) LF;
#endif

  client.connect( "djxmmx.net", 17);

  LABEL( F( "# client connected to "), client.host());
  LABEL( F( ":")                     , client.port());
  PRINT( F( " > "));
  while( !client.connected()) client.connect();
  PRINT(  client.connected() ? F("success!") : F("failure!")) LF;

  client.setMethod( HTTP_GET);
  client.setPath( "/quote");

  PRINT( F("# Ready")) LF;
}

void loop()
{
   for ( int i = 0; i < 8; i++) {
    //char path[32] = "/station/"; strcat ( path, dec( i, 1));

    client.connect();
    client.request(); //yield();
    delay(1000);
    client.receive();
    client.stop();

    client.print();

    delay(9000);
  }
}
