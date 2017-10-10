// Copyright  : Dennis Buis (2017)
// License    : MIT
// Platform   : Arduino
// Library    : ...
// File       : SimpleWebClient_GET.ino
// Purpose    : Arduino library to create a simple webclient requesting API calls
// Repository : https://github.com/DennisB66/Simple-WebClient-Library-for-Arduino

#include <Arduino.h>
#include "SimpleWebClient.h"
#include "SimplePrint.h"

#define DEBUG_MODE

byte macAddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ipLocal( 192, 168,   1,  62);           // lan IP (e.g. "192.168.1.178")
IPAddress gateway( 192, 168,   1,   1);           // router gateway
IPAddress subnet ( 255, 255, 255,   0);           // subnet mask
IPAddress DNS    (   8,   8,   8,   8);           // DNS server (Google)

SimpleWebClient   myClient( 80);                  // server    object (to respond on API calls)

void setup()
{
	Serial.begin( 9600);

  #ifdef DEBUG_MODE                               // show debug info
  LINE( Serial, F( "--------------------------------"));
	LINE( Serial, F( "- Arduino WebClient GET exmple -"));
  LINE( Serial, F( "--------------------------------"));
  LINE( Serial, F("#"));
  #endif

  Ethernet.begin( macAddr, ipLocal, DNS, gateway, subnet);
  myClient.begin();                               // starting webclient
  delay(1000);
  #ifdef DEBUG_MODE                               // show debug info
  ATTR_( Serial, F( "# client communicating at "), Ethernet.localIP());
  ATTR ( Serial, F( ":")                     , myClient.port());
  #endif

  myClient.setHost( "github.com");
  myClient.connect();

  myClient.setPath( "/");
  //myClient.setArgs( "q", "arduino");

  myClient.request();
  delay(10);
  myClient.receive();
  myClient.stop();

  LINE( Serial, F("# done"));                     // show debug info
}

void loop()
{

}
