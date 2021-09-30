#pragma once


class CLASS_DECL_ACME nano_timer
{
public:


#ifdef WINDOWS

   windows_handle      m_hTimer;

#endif


   nano_timer();
   ~nano_timer();


   void wait(const ::nanos & nanosWait);
   void wait_nano(::u64 u);


   void close_timer();


};





