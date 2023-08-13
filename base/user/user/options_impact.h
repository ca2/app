// From app_simple_form/form_001.h by camilo on 2023-06-28 05:02 <3ThomasBorregaardSorensen!!
#pragma once


#include "impact.h"


namespace user
{

   class line_layout;

}


namespace user
{


   class CLASS_DECL_BASE options_impact :
      virtual public ::user::impact
   {
   public:


      //::pointer<::user::still>             m_pstill;
      //::pointer<::user::plain_edit>        m_pedit;
      //::pointer<::user::button>            m_pbuttonClear;
      //::pointer<::user::button>            m_pbuttonSend;
      //::pointer<::user::still>             m_pstillReceiver;


      options_impact();
      ~options_impact() override;


      //      // void assert_ok() const override;
      //      // void dump(dump_context & dumpcontext) const override;


#ifdef _DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif

      void install_message_routing(::channel * psender) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);


      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;
      
      bool on_perform_layout(::draw2d::graphics_pointer & pgraphics) override;

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::context * pcontext) override;



   };


} // namespace user


