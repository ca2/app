#pragma once


#ifdef APPLEOS
typedef int key_t;
#elif defined(LINUX)
typedef __key_t key_t;
#elif defined(ANDROID)
#else
//#include "ca_mutex.h"
#endif


namespace interprocess_communication
{


   class CLASS_DECL_APEX base :
      virtual public object
   {
   public:

//#ifdef _UWP
//
//      //i32              m_iSerial;
//
//#elif defined(WINDOWS_DESKTOP)
//
//
//      HWND              m_hwnd;
//
//
//#elif defined(APPLEOS)
//
//
//      CFMessagePortRef     m_port;
//
//
//#elif !defined(_UWP)
//
//      key_t                m_key;
//      int                  m_iQueue;
//
//      struct data_struct
//      {
//
//
//         long     mtype;
//         long     request;
//         int      size;
//         char     data[0];
//
//
//      };
//
//
//#endif


      string   m_strBaseChannel;


      base();
      virtual ~base();


   };




   class CLASS_DECL_APEX tx:
      virtual public  base
   {
   public:


      tx();
      virtual ~tx();



#if defined(_UWP)
      virtual bool open(const char * pszChannel);
#else
      virtual bool open(const char * pszChannel, launcher * plauncher = nullptr);
#endif
      virtual bool close();


      virtual bool send(const char * pszMessage, duration durationTimeout);
      virtual bool send(int message,void * pdata,int len, duration durationTimeout);


      virtual bool is_tx_ok();

   };


   class rx_private;


   class CLASS_DECL_APEX rx:
      virtual public base
   {
   public:


      class CLASS_DECL_APEX receiver :
         virtual public ::matter
      {
      public:


         virtual void on_interprocess_receive(rx * prx,const char * pszMessage);
         virtual void on_interprocess_receive(rx * prx,int message,void * pdata,memsize len);
         virtual void on_interprocess_post(rx * prx, i64 a, i64 b);


      };


      __pointer(receiver)     m_preceiver;
      rx_private *            m_pp;


#ifndef WINDOWS

      bool                    m_bRunning;
      bool                    m_bRun;
      thread *                m_pthread;

#endif


      rx();
      virtual ~rx();


      virtual bool create(const char * pszChannel);
      virtual bool destroy();


      virtual void * on_interprocess_receive(rx * prx,const char * pszMessage);
      virtual void * on_interprocess_receive(rx * prx,int message,void * pdata,memsize len);
      virtual void * on_interprocess_post(rx * prx, i64 a, i64 b);


      virtual bool on_idle();

//ifndef WINDOWS
//
//      bool start_receiving();
//
//      void * receive();
//
//#endif

      virtual bool is_rx_ok();

   };




   class CLASS_DECL_APEX interprocess_communication:
      virtual public rx::receiver
   {
   public:


      __pointer(tx)           m_ptx;
      __pointer(rx)           m_prx;
      string                  m_strChannel;
      unsigned int            m_millisTimeout;


      interprocess_communication();
      virtual ~interprocess_communication();

#if defined(_UWP)
      virtual bool open_ab(const char * pszChannel, const char * pszModule);
      virtual bool open_ba(const char * pszChannel, const char * pszModule);
#elif defined(WINDOWS)
      virtual bool open_ab(const char * pszChannel,const char * pszModule,launcher * plauncher = nullptr);
      virtual bool open_ba(const char * pszChannel,const char * pszModule,launcher * plauncher = nullptr);
#else
      virtual bool open_ab(const char * pszChannel, launcher * plauncher = nullptr);
      virtual bool open_ba(const char * pszChannel, launcher * plauncher = nullptr);
#endif
      virtual bool close();

      virtual void restart_apex_ipc();

      virtual bool ensure_tx(const char * pszMessage, duration durationTimeout = one_hour());
      virtual bool ensure_tx(int message, void * pdata, int len, duration durationTimeout = one_hour());


      virtual bool is_rx_tx_ok();


   };


   CLASS_DECL_APEX string app_install(string strPlatform = "");


} // namespace interprocess_communication



