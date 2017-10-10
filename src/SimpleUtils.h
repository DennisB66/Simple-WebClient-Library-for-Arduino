// Copyright  : Dennis Buis (2017)
// License    : MIT
// Platform   : Arduino
// Library    : Simple Utils
// File       : SimpleUtils.h
// Purpose    : provide simple macros to replace more complex expressions
// Repository : https://github.com/DennisB66/

#ifndef _SIMPLE_UTILS_H
#define _SIMPLE_UTILS_H

#include <Arduino.h>

#define minMax(A,B,C)     min(max(A,B),C)

#define strLen(A)         (strlen(A)  !=0)
#define strCmp(A,B)       (strcmp(A,B)==0)
#define strCpy(D,S,L)     strncpy(D,S,L);D[L]=0
#define strClr(D)         D[0]=0

typedef void ( *StopwatchFunc)();

class Stopwatch {
public:
  Stopwatch ( unsigned long l) { _lapse = l; _ticks = millis() + _lapse; }
  void lapse( unsigned long l) { _lapse = l; _ticks = millis() + _lapse; }
  bool check(                ) { if ( millis() > _ticks) {           _ticks = millis() + _lapse; return true; } return false; }
  bool check( StopwatchFunc f) { if ( millis() > _ticks) {  ( *f)(); _ticks = millis() + _lapse; return true; } return false; }
  void reset(                ) { _ticks = millis() + _lapse; }
private:
  unsigned long _lapse;
  unsigned long _ticks;
};

#endif
