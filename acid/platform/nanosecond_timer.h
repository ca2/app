#pragma once


#ifdef WINDOWS


#include "acid/_operating_system.h"


#endif


class CLASS_DECL_ACID nanosecond_timer
{
public:


#ifdef WINDOWS

   ::windows::handle       m_handleTimer;

#endif


   nanosecond_timer();
   ~nanosecond_timer();


   void wait(const class time & time);


   void close_timer();


};





