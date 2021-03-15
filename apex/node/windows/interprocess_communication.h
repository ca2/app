// created by Camilo 2021-01-31 05:26 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


namespace windows
{


   class CLASS_DECL_APEX interprocess_communication_base :
      virtual public interprocess_communication::base
   {
   public:


      HWND              m_hwnd;
      string            m_strBaseChannel;


      interprocess_communication_base();
      virtual ~interprocess_communication_base();


      HWND get_hwnd() const { return (HWND) m_hwnd; }
      void set_hwnd(HWND hwnd) { m_hwnd = hwnd; }

   };


   class CLASS_DECL_APEX interprocess_communication_tx :
      virtual public interprocess_communication_base,
      virtual public interprocess_communication::tx
   {
   public:


      interprocess_communication_tx();
      virtual ~interprocess_communication_tx();



#if defined(_UWP)
      bool open(const char * pszChannel);
#else
      bool open(const char * pszChannel, launcher * plauncher = nullptr);
#endif
      bool close();


      bool send(const char * pszMessage, duration durationTimeout);
      bool send(int message, void * pdata, int len, duration durationTimeout);


      bool is_tx_ok();

   };


   class rx_private;


   class CLASS_DECL_APEX interprocess_communication_rx :
      virtual public interprocess_communication_base,
      virtual public interprocess_communication::rx
   {
   public:


      interprocess_communication_rx();
      virtual ~interprocess_communication_rx();


      bool create(const char * pszChannel);
      bool destroy();


      virtual void * on_interprocess_receive(::interprocess_communication::rx * prx, const char * pszMessage);
      virtual void * on_interprocess_receive(::interprocess_communication::rx * prx, int message, void * pdata, memsize len);
      virtual void * on_interprocess_post(::interprocess_communication::rx * prx, i64 a, i64 b);


      virtual bool on_idle();


      LRESULT message_queue_proc(UINT message, WPARAM wparam, LPARAM lparam);


      bool is_rx_ok();


   };


//   class CLASS_DECL_APEX interprocess_communication :
//      virtual public interprocess_communication_base,
//      virtual public ::interprocess_communication::interprocess_communication
//   {
//   public:
//
//
//      interprocess_communication();
//      virtual ~interprocess_communication();
//
//
//#if defined(_UWP)
//      bool open_ab(const char * pszChannel, const char * pszModule);
//      bool open_ba(const char * pszChannel, const char * pszModule);
//#elif defined(WINDOWS)
//      bool open_ab(const char * pszChannel, const char * pszModule, launcher * plauncher = nullptr);
//      bool open_ba(const char * pszChannel, const char * pszModule, launcher * plauncher = nullptr);
//#else
//      bool open_ab(const char * pszChannel, launcher * plauncher = nullptr);
//      bool open_ba(const char * pszChannel, launcher * plauncher = nullptr);
//#endif
//
//
//      bool close();
//
//
//      virtual void restart_apex_ipc();
//
//      //bool ensure_tx(const char * pszMessage, duration durationTimeout = one_hour());
//      //bool ensure_tx(int message, void * pdata, int len, duration durationTimeout = one_hour());
//
//
//      bool is_rx_tx_ok();
//
//
//   };


   CLASS_DECL_APEX string app_install(string strPlatform = "");


} // namespace windows



