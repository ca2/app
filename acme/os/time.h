#pragma once



class CLASS_DECL_ACME os_usleep
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


CLASS_DECL_ACME i64 __first_tick(void);
CLASS_DECL_ACME i64 __get_tick(void);



class duration;


CLASS_DECL_ACME void millis_sleep(const millis & millis);



