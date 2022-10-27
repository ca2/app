// Created by camilo on 2022-10-11 00:00 <3ThomasBorregaardSorensen!! (Thomas Likes Number 5!!)
// Thomas handlers are key!!
#pragma once


#include "base.h"


namespace interprocess
{


   class CLASS_DECL_APEX target :
      virtual public base
   {
   public:


      //class CLASS_DECL_APEX dispatch_item :
      //   virtual public ::matter
      //{
      //public:


      //   u64         m_uData;
      //   string      m_strMessage;
      //   memory      m_memory;


      //   dispatch_item(::string && strMessage) : m_uData(0x80000000), m_strMessage(strMessage) {}
      //   dispatch_item(u64 uData, ::memory && memory) : m_uData(0x80000000), m_memory(::move(memory)) {}

      //   bool is_text_message() const {
      //      return m_uData == 0x80000000
      //         ;
      //   }

      //};



      ::pointer_array<::handler>             m_handlera;
      //rx_private *                         m_pp;
      //pointer_array < dispatch_item >      m_dispatchitema;
      //manual_reset_event                   m_evDispatchItemNew;
      //::pointer < ::mutex >                              m_pmutexDispatch;


//#ifndef WINDOWS

      bool                                   m_bRunning;
      bool                                   m_bRun;
      ::pointer<::task>                      m_pthread;

//#endif


      target();
      ~target() override;


      void on_initialize_particle() override;


      virtual void create(const ::string & strChannel);
      void destroy() override;


      bool _handle_uri(const block & blockUri) override;
      //virtual bool on_interprocess_receive(int message, ::memory && memory);
      //virtual void on_interprocess_post(i64 a, i64 b);



      virtual void add_handler(::handler * phandler);

      virtual bool on_idle();


      virtual bool is_target_ok();


      //bool dispatch_message(::string && strMessage);
      //bool dispatch_message(::u64 uData, ::memory && memory);


      //void dispatch_item(::pointer<dispatch_item>&& pdispatchitem);


      //void task_dispatch();


   };


} // namespace interprocess



