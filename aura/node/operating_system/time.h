#pragma once



class CLASS_DECL_AURA os_usleep
{

public:

#ifdef WINDOWS
   HANDLE m_hTimer;
   SOCKET m_socket;

#endif

   os_usleep()
   {
#ifdef WINDOWS
      m_hTimer = ::CreateWaitableTimer(NULL, true, NULL);
#endif
   }
   ~os_usleep()
   {
#ifdef WINDOWS
      CloseHandle(m_hTimer);

#endif

   }

   bool sleep(unsigned long usec);


};


CLASS_DECL_AURA i64 __first_tick(void);
CLASS_DECL_AURA i64 __get_tick(void);








