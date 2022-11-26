#pragma once


class CLASS_DECL_ACME nanosecond_timer
{
public:


#ifdef WINDOWS

   windows_handle      m_hTimer;

#endif


   nanosecond_timer();
   ~nanosecond_timer();


   void wait(const class time & time);


   void close_timer();


};





