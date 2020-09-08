#pragma once



class CLASS_DECL_AQUA os_usleep
{

public:

#ifdef WINDOWS
   HANDLE m_hTimer;
   SOCKET m_socket;

#endif

   os_usleep()
   {
#ifdef WINDOWS
      m_hTimer = ::CreateWaitableTimer(NULL, TRUE, NULL);
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


CLASS_DECL_AQUA i64 __first_tick(void);
CLASS_DECL_AQUA i64 __get_tick(void);








