#pragma once


namespace os
{

   
   class CLASS_DECL_ACME microsecond_sleep
   {
   public:


#ifdef WINDOWS

      HANDLE m_hTimer;
      SOCKET m_socket;

#endif

      microsecond_sleep()
      {

#ifdef WINDOWS

         m_hTimer = ::CreateWaitableTimer(NULL, true, NULL);

#endif

      }


      ~microsecond_sleep()
      {

#ifdef WINDOWS

         CloseHandle(m_hTimer);

#endif

      }


      bool sleep(unsigned long usec);


   };


} // namespace os



