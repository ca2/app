#pragma once


class CLASS_DECL_ACME nanosecond_timer
{
public:


#ifdef WINDOWS

   windows_handle      m_hTimer;

#endif


   nanosecond_timer();
   ~nanosecond_timer();


   void wait(const ::duration & duration);


   void close_timer();


};





