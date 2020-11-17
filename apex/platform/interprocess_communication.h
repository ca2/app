#pragma once


#ifdef APPLEOS
typedef int key_t;
#elif defined(LINUX)
typedef __key_t key_t;
#elif defined(ANDROID)
#else
//#include "ca_mutex.h"
#endif

//namespace apex
//{


namespace interprocess_communication
{


   class CLASS_DECL_APEX base :
      virtual public object
   {
   public:

#ifdef _UWP

      //i32              m_iSerial;

#elif defined(WINDOWS_DESKTOP)


      oswindow             m_oswindow;


#elif defined(APPLEOS)


      CFMessagePortRef     m_port;


#elif !defined(_UWP)

      key_t                m_key;
      int                  m_iQueue;

      struct data_struct
      {


         long     mtype;
         long     request;
         int      size;
         char     data[0];


      };


#endif


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
      bool open(const char * pszChannel);
#else
      bool open(const char * pszChannel, launcher * plauncher = nullptr);
#endif
      bool close();


      bool send(const char * pszMessage, duration durationTimeout);
      bool send(int message,void * pdata,int len, duration durationTimeout);


      bool is_tx_ok();

   };


   class rx_private;


   class CLASS_DECL_APEX rx:
      virtual public base
   {
   public:


      class CLASS_DECL_APEX receiver
      {
      public:


         virtual void on_interprocess_receive(rx * prx,const char * pszMessage);
         virtual void on_interprocess_receive(rx * prx,int message,void * pdata,memsize len);
         virtual void on_interprocess_post(rx * prx, i64 a, i64 b);


      };

      receiver *           m_preceiver;
      rx_private *         m_pp;

#ifndef WINDOWS

      bool                 m_bRunning;
      bool                 m_bRun;
      thread *             m_pthread;

#endif


      rx();
      virtual ~rx();


      bool create(const char * pszChannel);
      bool destroy();


      virtual void * on_ipc_receive(rx * prx,const char * pszMessage);
      virtual void * on_ipc_receive(rx * prx,int message,void * pdata,memsize len);
      virtual void * on_ipc_post(rx * prx, i64 a, i64 b);


      virtual bool on_idle();


#ifdef WINDOWS_DESKTOP
      //ATOM register_class(HINSTANCE hInstance);
      //static LRESULT CALLBACK s_message_queue_proc(oswindow oswindow,const ::id & id,WPARAM wParam,LPARAM lParam);
      LRESULT message_queue_proc(::u32 message,WPARAM wParam,LPARAM lParam);
#else

      bool start_receiving();

      void * receive();

#endif

      bool is_rx_ok();

   };




   class CLASS_DECL_APEX interprocess_communication:
      virtual public tx,
      virtual public rx::receiver
   {
   public:


      rx                      m_rx;
      string                  m_strChannel;
      unsigned int            m_millisTimeout;


      interprocess_communication();
      virtual ~interprocess_communication();

#if defined(_UWP)
      bool open_ab(const char * pszChannel, const char * pszModule);
      bool open_ba(const char * pszChannel, const char * pszModule);
#elif defined(WINDOWS)
      bool open_ab(const char * pszChannel,const char * pszModule,launcher * plauncher = nullptr);
      bool open_ba(const char * pszChannel,const char * pszModule,launcher * plauncher = nullptr);
#else
      bool open_ab(const char * pszChannel, launcher * plauncher = nullptr);
      bool open_ba(const char * pszChannel, launcher * plauncher = nullptr);
#endif
      bool close();

      virtual void restart_apex_ipc();

      bool ensure_tx(const char * pszMessage, duration durationTimeout = one_hour());
      bool ensure_tx(int message, void * pdata, int len, duration durationTimeout = one_hour());


      bool is_rx_tx_ok();


   };


   CLASS_DECL_APEX string app_install(string strPlatform = "");


} // namespace interprocess_communication


//} // namespace apex




