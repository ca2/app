//
// // Created from acme/user/micro/main_window by 
//      camilo on 2024-10-07 10:17 <3ThomasBorregaardSorensen!!
// 

#pragma once


#include "acme/user/micro/main_window.h"
#include "acme/parallelization/manual_reset_happening.h"


namespace micro
{



   class CLASS_DECL_ACME dialog :
      virtual public ::micro::main_window
   {
   public:


      ::collection::index                       m_iDefaultButton = -1;
      //::function < void(::acme::user::interaction *) >        m_functionClose;
      manual_reset_happening                        m_manualreseteventFinished;
      bool                                      m_bRunningModalLoop;
      class ::time                              m_timeDialogTimeout;


      dialog();
      ~dialog();


      //virtual void do_modal();


      void run() override;
      //void complete_aggregation(::sequence * psequence) override;

      virtual bool is_waiting_for_dialog_result() override;
      virtual void set_dialog_result(const ::payload & payloadResult) override;
      virtual void on_dialog_result_set();
      virtual ::payload wait_for_dialog_result(const class ::time & timeTimeout = ::time::infinity()) override;

      virtual ::payload get_dialog_result() override;

      virtual ::micro::dialog * micro_dialog();

      void on_window_close() override;



   };


} // namespace micro



