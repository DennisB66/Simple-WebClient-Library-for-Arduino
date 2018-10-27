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

#define VERBOSE_MODE

#define CLIENT_NAME "CLIENT-01"                       // host name
#define CLIENT_PORT 80                                      // host port

const char* ssid     = "Kajtus06";                          // repce with proper ssid
const char* password = "Polska06";                          // repce with proper password

byte client_mac[]     = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte client_ip4[]     = { 192, 168, 1, 67 };                // lan ip (e.g. "192.168.1.60")
byte client_gateway[] = { 192, 168, 1, 1 };                 // router gateway
byte client_subnet[]  = { 255, 255, 255, 0 };               // subnet mask

IPAddress DNS( 8, 8, 8, 8);                                 // DNS server (Google)

SimpleWebClient client( 80);                               // server object (to respond on API calls)

void setup()
{
  BEGIN( 115200) LF;                                        // Serial at 115200

  #ifdef VERBOSE_MODE
  PRINT( F( "# --------------------------------------")) LF;           // show header
	PRINT( F( "# -  WebClient www.google.com example  -")) LF;
  PRINT( F( "# -  V0.1                 (DennisB66)  -")) LF;
  PRINT( F( "# --------------------------------------")) LF;
  PRINT( F( "#")) LF;
  #endif

#if defined(ESP8266)                                        // ESP8266 = connect via WiFi
  WiFi.hostname( CLIENT_NAME);                              // set host name
  WiFi.config( client_ip4, client_gateway, client_subnet);  // set fixed IP address
//WiFi.begin();                                             // open WiFi connection (ssid/pw from EEPROM)
  WiFi.begin( ssid, password);                              // open WiFi connection
  while ( WiFi.status() != WL_CONNECTED) delay(500);        // wait for  connection

  LABEL( F( "# connected to"), ssid);
  LABEL( F( " / IP ="), WiFi.localIP()) LF;
#else                                                       // Arduino = connect via Ethernet
//Ethernet.hostName( SERVER_NAME);                          // not supported (yet)
  ETHERNET_RESET( 11U);                                     // Leonardo ETH reset
  Ethernet.begin( client_mac, client_ip4, client_gateway, client_subnet);
                                                            // open ethernet connection
  LABEL( F( "# connected to "), Ethernet.localIP()) LF;
#endif

  PRINT( F("# Ready")) LF;                                   // show debug info
}

void loop()
{
  client.setHost( "www.google.com");
  client.setPath( "/");
  client.setArgs( "q", "arduino");
  //client.connect();
  client.request(); //yield();
  delay(100);
  client.receive();
  client.stop() LF;

  delay(2000) LF;
}
