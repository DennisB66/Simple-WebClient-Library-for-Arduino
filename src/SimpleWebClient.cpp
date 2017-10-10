// Copyright  : Dennis Buis (2017)
// License    : MIT
// Platform   : Arduino
// Library    : Simple Web client Library for Arduino
// File       : SimpleWebClient.h
// Purpose    : Arduino library to create a simple webclient requesting API calls
// Repository : https://github.com/DennisB66/Simple-WebClient-Library-for-Arduino

#include "SimpleWebClient.h"
#include "SimplePrint.h"

#define SIMPLE_WEBCLIENT_DEBUG

SimpleWebClient::SimpleWebClient( word port)
{
  setPort( port);

  setHTTPMethod ( HTTP_GET);
  setHTTPversion( "1.1");
}

void  SimpleWebClient::begin()
{
  delay( 10);
}

bool SimpleWebClient::connect()
{

  // if ( strlen( _host) > 0) {                               // if host Found
  //   DNSClient dns;                                        // initialize DNS object
  //   dns.begin( Ethernet.dnsServerIP());                   // attach default DNS server
  //   dns.getHostByName( _host, _hostIP);                     // search for host IP
  // }
  //
  // #ifdef SIMPLE_WEBCLIENT_DEBUG                       // print debug info
  // ADDR_( Serial, F( " / "), _hostIP);
  // ATTR ( Serial, F( ":")  , _hostPort);
  // #endif
  //
  // if ( _client.connect( _host, _hostPort)) {
  //   LINE(Serial, "# connected");
  // }

  if ( strlen( _host) > 0) {
    _client.connect( _host  , _hostPort);

    #ifdef SIMPLE_WEBCLIENT_DEBUG                       // print debug info
    ATTR_( Serial, F( "# host = "), _host  ); ATTR( Serial, ":", _hostPort);
    #endif
  } else {
    _client.connect( _hostIP, _hostPort);

    #ifdef SIMPLE_WEBCLIENT_DEBUG                       // print debug info
    ADDR_( Serial, F( "# host = "), _hostIP); ATTR( Serial, ":", _hostPort);
    #endif
  }

  return _client.connected();
}

void  SimpleWebClient::request()
{
  if ( _client.connected()) {
    LINE_( _client, HTTP_Method( _method));
    ATTR_( _client, " ",         _path);
    LINE_( _client,              _args);
    ATTR ( _client, " HTTP/",    _version);

    if ( strlen( _host) > 0) {
      ATTR ( _client, "Host: ", _host);
    } else {
      ATTR_( _client, "Host: ", _hostIP);
      ATTR ( _client, ":"     , _hostPort);
    }

    LINE ( _client, "Connection: close");
    LINE ( _client, "");

    // _client.println("GET /search?q=arduino HTTP/1.1");
    // _client.println("Host: github.com");
    // _client.println("Connection: close");
    // _client.println();

    #ifdef SIMPLE_WEBCLIENT_DEBUG                       // print debug info
    LINE_( Serial, HTTP_Method(  _method));
    ATTR_( Serial, F( " ")     , _path);
    LINE_( Serial,               _args);
    ATTR ( Serial, F( " HTTP/"), _version);

    ATTR ( Serial, F( "Host: "), _host);
    // ATTR_( Serial, F( "Host: "), _hostIP);
    // ATTR ( Serial, F( ":"     ), _hostPort);

    LINE ( Serial, F( "Connection: close"));
    LINE ( Serial, F( ""));
    #endif
  }
}

void  SimpleWebClient::receive()
{
  LINE( Serial, "# response");
  while( _client.connected()) {
    if ( _client.available()) {
      char c = _client.read();
      LINE_( Serial, c);
    }
  }
  LINE( Serial, "# response done");
}

void  SimpleWebClient::stop()
{
  if ( _client.connected()) {
    _client.stop();
  }
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
  //memcpy( _hostIP, ip, sizeof( _hostIP));
  _hostIP   = ip;
  _hostPort = port;
}

char* SimpleWebClient::setHost( const char* host)
{
  int l = strlen(  host);
  int s = sizeof( _host);

  return ( l < s) ? strcpy( _host, host) : NULL;
}

word SimpleWebClient::port()
{
  return _hostPort;
}

void SimpleWebClient::setPort( word port)
{
  _hostPort = port;
}

HTTPMethod SimpleWebClient::httpMethod()
{
  return _method;
}

void  SimpleWebClient::setHTTPMethod( HTTPMethod method)
{
  _method = method;
}

void  SimpleWebClient::setHTTPMethod( const char* method)
{
  _method = HTTP_Method( method);
}

char* SimpleWebClient::setHTTPversion( const char* version)
{
  int l = strlen( version);

  return ( l < 4) ? strcpy( _version, version) : NULL;
}

char* SimpleWebClient::httpVersion()
{
  return _version;
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

    return  _args;
  } else {
    return NULL;
  }
}

char* SimpleWebClient::args()
{
  return _args;
}
