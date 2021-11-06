#pragma once


#ifdef __APPLE__
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


      string   m_strBaseChannel;


      base();
      ~base() override;


   };


   class CLASS_DECL_APEX tx:
      virtual public  base
   {
   public:


      tx();
      ~tx() override;



      virtual bool open(const ::string & pszChannel, ::launcher * plauncher = nullptr);
      virtual bool close();


      virtual bool send(const ::string & pszMessage, duration durationTimeout);
      virtual bool send(int message,void * pdata,int len, duration durationTimeout);


      virtual bool is_tx_ok();


   };


   class rx_private;


   class CLASS_DECL_APEX rx:
      virtual public base
   {
   public:


      class CLASS_DECL_APEX dispatch_item :
         virtual public ::matter
      {
      public:


         u64         m_uData;
         string      m_strMessage;
         memory      m_memory;


         dispatch_item(::string && strMessage) : m_uData(0x80000000), m_strMessage(strMessage) {}
         dispatch_item(u64 uData, ::memory && memory) : m_uData(0x80000000), m_memory(::move(memory)) {}

         bool is_text_message() const {
            return m_uData == 0x80000000
               ;
         }

      };


      class CLASS_DECL_APEX receiver :
         virtual public ::matter
      {
      public:


         virtual void on_interprocess_receive(rx * prx, __pointer(dispatch_item) && pdispatchitem);
         virtual void on_interprocess_receive(rx * prx, ::string && strMessage);
         virtual void on_interprocess_receive(rx * prx, int message, ::memory && memory);
         virtual void on_interprocess_post(rx * prx, i64 a, i64 b);


      };


      __pointer(receiver)                 m_preceiver;
      rx_private *                        m_pp;
      __pointer_array(dispatch_item)      m_dispatchitema;
      manual_reset_event                  m_evDispatchItemNew;
      ::mutex                             m_mutexDispatch;


#ifndef WINDOWS

      bool                    m_bRunning;
      bool                    m_bRun;
      __pointer(::task)       m_pthread;

#endif


      rx();
      ~rx() override;

      
      ::e_status on_initialize_object() override;


      virtual bool create(const ::string & pszChannel);
      ::e_status destroy() override;


      virtual void on_interprocess_receive(::string && strMessage);
      virtual void on_interprocess_receive(int message, ::memory && memory);
      virtual void on_interprocess_post(i64 a, i64 b);


      virtual bool on_idle();


      virtual bool is_rx_ok();

      
      void dispatch_message(::string && strMessage);
      void dispatch_message(::u64 uData, ::memory && memory);


      void dispatch_item(__pointer(dispatch_item) && pdispatchitem);


      void task_dispatch();


   };




   class CLASS_DECL_APEX interprocess_communication:
      virtual public rx::receiver
   {
   public:


      __pointer(tx)           m_ptx;
      __pointer(rx)           m_prx;
      string                  m_strChannel;
      unsigned int            m_durationTimeout;


      interprocess_communication();
      ~interprocess_communication() override;

      virtual bool open_ab(const ::string & strChannel, launcher * plauncher = nullptr);
      virtual bool open_ba(const ::string & strChannel, launcher * plauncher = nullptr);
      virtual bool close();

      virtual void restart_apex_ipc();

      virtual bool ensure_tx(const ::string & strMessage, duration durationTimeout = hour());
      virtual bool ensure_tx(int message, void * pdata, int len, duration durationTimeout = hour());


      virtual bool is_rx_tx_ok();


   };


   CLASS_DECL_APEX string app_install(string strPlatform = "");


} // namespace interprocess_communication



