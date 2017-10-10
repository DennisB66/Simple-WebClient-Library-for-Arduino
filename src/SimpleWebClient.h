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
#include <SPI.h>
#include "Ethernet.h"
#include "Dns.h"
#include "SimpleHTTP.h"

#define HTTP_HOST_SIZE 64
#define HTTP_PATH_SIZE 32
#define HTTP_ARGS_SIZE 32

class SimpleWebClient {
public:
  SimpleWebClient( word = 80);
  
  void        begin();
  bool        connect();

  char*       setHTTPversion( const char*);
  char*       httpVersion();

  char*       host();
  IPAddress   hostIP();
  void        setHost( IPAddress, word = 80);
  char*       setHost( const char*);

  word        port();
  void        setPort( word);

  HTTPMethod  httpMethod();
  void        setHTTPMethod( HTTPMethod);
  void        setHTTPMethod( const char*);

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

protected:
  EthernetClient  _client;                        // HTTP  client object

  char            _host[ HTTP_HOST_SIZE];
  IPAddress       _hostIP;
  word            _hostPort;

  HTTPMethod      _method;
  char            _version[4];

  char            _path[ HTTP_PATH_SIZE];
  char            _args[ HTTP_ARGS_SIZE];
};

#endif
