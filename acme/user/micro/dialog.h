//
// // Created from acme/user/micro/main_window by 
//      camilo on 2024-10-07 10:17 <3ThomasBorregaardSorensen!!
// 

#pragma once


#include "acme/parallelization/manual_reset_happening.h"
#include "acme/user/interface/dialog.h"
#include "acme/user/micro/main_window.h"
#include "user/implementation/dialog_implementation.h"


namespace micro
{



   class CLASS_DECL_ACME dialog :
      virtual public ::micro::main_window,
      virtual public ::user_interface::dialog_implementation
   {
   public:


      ::collection::index                                      m_iDefaultButton = -1;
      //::function < void(::acme::user::interaction *) >       m_functionClose;
      //manual_reset_happening                                   m_manualresethappeningFinished;
      //bool                                                     m_bRunningModalLoop;
      class ::time                                             m_timeDialogTimeout;
      //::payload                                                m_payloadDialogResult;
      //::function < void(::acme::user::interaction *) >         m_functionOnDialogResult;


      dialog();
      ~dialog();


      //virtual void do_modal();

      bool on_window_create(void * pCREATESTRUCT) override;

      void run() override;
      //void complete_aggregation(::sequence * psequence) override;



      virtual void set_dialog_response(const ::payload & payloadResult) override;
      void on_dialog_response(const ::payload & payloadResult) override;
      virtual ::payload wait_for_dialog_response(const class ::time & timeTimeout = ::time::infinity()) override;

      virtual ::payload get_dialog_response() override;



      virtual ::micro::dialog * micro_dialog();

      void on_window_close() override;
      void on_dialog_finished() override;

      void display(::e_display edisplay = e_display_default, const ::user::activation & useractivation = {}) override;


   };


} // namespace micro



