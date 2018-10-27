// Copyright  : Dennis Buis (2017)
// License    : MIT
// Platform   : Arduino
// Library    : Simple Web client Library for Arduino
// File       : SimpleWebClient.h
// Purpose    : Arduino library to create a simple webclient requesting API calls
// Repository : https://github.com/DennisB66/Simple-WebClient-Library-for-Arduino

#ifndef SIMPLE_WEB_CLIENT_H
#define SIMPLE_WEB_CLIENT_H

#include <Arduino.h>
#include "SimpleHTTP.h"
#include "SimpleBuffer.h"

#if   defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(__AVR__)
#include <SPI.h>
#include <Ethernet.h>
#endif

#define HTTP_HOST_SIZE 128
#define HTTP_PATH_SIZE 64
#define HTTP_ARGS_SIZE 64

class SimpleWebClient {
public:
  SimpleWebClient( word = 80);
 ~SimpleWebClient();

  void        begin();
  bool        connect();
  bool        connect( IPAddress  , word = 80);
  bool        connect( const char*, word = 80);
  bool        connected();

  char*       version();
  char*       setVersion( const char*);

  char*       host();
  IPAddress   hostIP();
  void        setHost( IPAddress, word = 80);
  char*       setHost( const char*);

  word        port();
  void        setPort( word);

  HTTPMethod  method();
  void        setMethod( HTTPMethod);
  void        setMethod( const char*);

  char*       path();
  void        clrPath();
  char*       setPath( const char*);
  char*       addPath( const char*);

  char*       args();
  void        clrArgs();
  char*       setArgs( const char*);
  char*       setArgs( const char*, const char*);
  char*       addArgs( const char*);
  char*       addArgs( const char*, const char*);

  void        request();
  void        receive();
  void        stop();

  void        print();

protected:
#if   defined(ESP8266)
  WiFiClient*     _client;                                  // client for ESP8266
#elif defined(__AVR__)
  EthernetClient* _client;                                  // client for Arduino
#endif
  SimpleBuffer*   _buffer;

  word            _port;
  char            _host[ HTTP_HOST_SIZE];
  IPAddress       _hostIP;

  HTTPMethod      _method;
  char            _version[4];

  char            _path[ HTTP_PATH_SIZE];
  char            _args[ HTTP_ARGS_SIZE];
};

#endif
