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



template < typename PRED >
inline bool pred_Sleep(int iTime, PRED pred);



///  \brief    pauses generic for specified time
///  \lparam    duration sleeping time of generic
CLASS_DECL_ACME void sleep(const duration& duration);




