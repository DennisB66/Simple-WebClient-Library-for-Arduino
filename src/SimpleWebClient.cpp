// Copyright  : Dennis Buis (2017)
// License    : MIT
// Platform   : Arduino
// Library    : Simple Web client Library for Arduino
// File       : SimpleWebClient.h
// Purpose    : Arduino library to create a simple webclient requesting API calls
// Repository : https://github.com/DennisB66/Simple-WebClient-Library-for-Arduino

#include "SimpleWebClient.h"
#include "SimpleUtils.h"
#include "SimplePrint.h"
#include "SimpleDebug.h"

#ifdef SIMPLE_WEBCLIENT_DEBUG
#define CPRINT(S) _client->print(S); PRINT(S)
#else
#define CPRINT(S) _client->print(S)
#endif

#define BUFFER_SIZE 2000

SimpleWebClient::SimpleWebClient( word port)
{
#if   defined(ESP8266)
  _client = new WiFiClient;
#elif defined(__AVR__)
  _client = new EthernetClient;
#endif

  _buffer = new SimpleBuffer( BUFFER_SIZE);

  setMethod ( HTTP_GET);
  setVersion( "1.1");
  setPath( "/");
  setPort( port);
}

//
SimpleWebClient::~SimpleWebClient()
{
  delete _buffer;
  delete _client;
}

void  SimpleWebClient::begin()
{
  delay( 10);
}

bool SimpleWebClient::connect()
{
  if ( strlen( _host)) {
    connect( _host  , _port);
  } else {
    connect( _hostIP, _port);
  }

  return _client->connected();
}

bool SimpleWebClient::connect( IPAddress hostIP, word port)
{
  _client->connect( _hostIP = hostIP, _port = port);

  return _client->connected();
}

bool SimpleWebClient::connect( const char* host, word port)
{
  strCpy( _host, host, HTTP_HOST_SIZE);

  _client->connect( _host, _port = port);

  return _client->connected();
}

bool SimpleWebClient::connected()
{
  return _client->connected();
}

void SimpleWebClient::request()
{
  if ( !_client->connected()) connect();

  if (  _client->connected()) {
    char buff[256];

    strcpy( buff, HTTP_Method(_method)); strcat( buff, " ");
    strcat( buff, _path);    strcat( buff, _args);
    strcat( buff, " HTTP/"); strcat( buff, _version);
    strcat( buff, "\r\n");
    strcat( buff, "User-Agent: Arduino\r\n");
    strcat( buff, "Accept: *.*\r\n");
    strcat( buff, "Content-length: 0\r\n");
    strcat( buff, "Connection: keep-alive\r\n");
    strcat( buff, "\r\n");
    _client->write( buff, strlen( buff));
  }

  _buffer->clr();
}

void SimpleWebClient::receive()
{
  //if ( _client->connected()) {
    while ( _client->available()) {
      _buffer->put( _client->read());
    }
  //}
}

void SimpleWebClient::print()
{
  size_t leng = _buffer->available(); if ( leng == 0) return;

  while ( leng--) {
    char c = _buffer->get();
    PRINT(( c == 0) ? ' ' : c);
  } LF;
}

void  SimpleWebClient::stop()
{
  if ( _client->connected()) _client->stop();
}

char* SimpleWebClient::host()
{
  return _host;
}

IPAddress SimpleWebClient::hostIP()
{
  return _hostIP;
}

void  SimpleWebClient::setHost( IPAddress ip, word port)
{
  _hostIP = ip;
  _port   = port;
}

char* SimpleWebClient::setHost( const char* host)
{
  int l = strlen(  host);
  int s = sizeof( _host);

  return ( l < s) ? strcpy( _host, host) : NULL;
}

word SimpleWebClient::port()
{
  return _port;
}

void SimpleWebClient::setPort( word port)
{
  _port = port;
}

char* SimpleWebClient::version()
{
  return _version;
}

char* SimpleWebClient::setVersion( const char* version)
{
  int l = strlen( version);

  return ( l < 4) ? strcpy( _version, version) : NULL;
}

HTTPMethod SimpleWebClient::method()
{
  return _method;
}

void  SimpleWebClient::setMethod( HTTPMethod method)
{
  _method = method;
}

void  SimpleWebClient::setMethod( const char* method)
{
  _method = HTTP_Method( method);
}

void SimpleWebClient::clrPath()
{
  _path[0] = 0;
}

char* SimpleWebClient::setPath( const char* path)
{
  clrPath();
  return addPath( path);
}

char* SimpleWebClient::addPath( const char* path)
{
  if (( path) && ( path[0] == '/')) {
    int p = strlen( _path);
    int n = strlen(  path);
    int s = sizeof( _path);

    return ( p + n < s) ? strcat( _path, path) : NULL;
  } else {
    return NULL;
  }
}

char* SimpleWebClient::path()
{
  return _path;
}

void SimpleWebClient::clrArgs()
{
  _args[0] = 0;
}

char* SimpleWebClient::setArgs( const char* param)
{
  clrArgs();
  return addArgs( param);
}

char* SimpleWebClient::setArgs( const char* param, const char* value)
{
  clrArgs();
  return addArgs( param, value);
}

char* SimpleWebClient::addArgs( const char* param)
{
  int p = param ? strlen( param) : 0;
  int l = strlen( _args);

  if (( p) && ( l + p + 1 < (int) sizeof( _args))) {
    strcat( _args, l ? "&" : "?");
    strcat( _args, param);

    VALUE( _args) LF;

    return  _args;
  } else {
    return NULL;
  }
}

char* SimpleWebClient::addArgs( const char* param, const char* value)
{
  int p = param ? strlen( param) : 0;
  int v = value ? strlen( value) : 0;
  int l = strlen( _args);

  if (( v) && ( l + p + v + 2 < (int) sizeof( _args))) {
    strcat( _args, l ? "&" : "?");
    strcat( _args, param);

    strcat( _args, "=");
    strcat( _args, value);

    VALUE( _args) LF;

    return  _args;
  } else {
    return NULL;
  }
}

char* SimpleWebClient::args()
{
  return _args;
}
