#pragma once


class CLASS_DECL_ACME nano_timer
{
public:


#ifdef WINDOWS

   HANDLE      m_hTimer;

#endif


   nano_timer();
   ~nano_timer();


   void wait(u64 uWait);


   void close_timer();


};



