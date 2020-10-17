/*
 Copyright (ca) 2001 - 2002
 Author: Konstantin Boukreev
 E-mail: konstantin@mail.primorye.ru
 Created: 25.12.2001 19:41:00
 Version: 1.0.2

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

 sym_engine class incapsulate Symbol Handler and Debugging Service API

 the list of used API:
   SymInitialize, SymCleanup, SymGetLineFromAddr, SymGetModuleBase,
   SymGetSymbolInfo, SymGetSymFromAddr, SymGetSymFromName, SymGetSymNext,
   SymLoadModule, SymSetOptions
   StackWalk

 based on code\ideas from John Robbins's book "Debugging application"
 http://www.wintellect.com/robbins
*/
#pragma once


class os_engine;


class CLASS_DECL_ACME exception_engine :
   virtual public matter
{
public:


   critical_section     m_cs;


   exception_engine();
   virtual ~exception_engine();


   static const char * default_format() { return "%f(%l) : %s\n"; }


   virtual void reset();


};


CLASS_DECL_ACME ::exception_engine & engine();



