#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif


namespace userex
{


   message_box::message_box()
   {
      
   }

   
   void message_box::on_show(const char * pszMatter)
   {
      
      //auto pformpropertyset = get_form_property_set();
      //
      //auto & set = pformpropertyset->propset();

      //auto 
      //
      //if(!set.has_property("application_name"))
      //{
      // 
      //   set["application_name"] = Application.get_title();
      //   
      //}
         
//      if(set.has_property("message_box_timeout_ms"))
      {
         
  //       m_millisDelay = set["message_box_timeout_ms"].i64();
         
      }

      m_millisDelay = *fetch_property("message_box_timeout_ms");
      
      wait_message_dialog::on_show(pszMatter);
      
   }
   

   bool message_box::on_timeout()
   {
      m_id = "ok";
      return wait_message_dialog::on_timeout();
   }


   void message_box::on_timer_soft_reload(millis tickTimeout)
   {
      
      wait_message_dialog::on_timer_soft_reload(tickTimeout);
      
   }


} // namespace userex


//namespace aura
//{
//
//   
//   string application::dialog_box(const char * pszMatter, property_set & propertyset)
//   {
//      
//      auto pbox = __create_new <::userex::message_box >();
//      
//      //box.form_callback_as_property_set();
//      
//      pbox->get_property_set().merge(propertyset);
//      
//      pbox->show(pszMatter);
//      
//      return pbox->m_idResponse;
//      
//   }
//
//
//} // namespace aura
