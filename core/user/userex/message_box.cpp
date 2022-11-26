#include "framework.h"
#include "message_box.h"


namespace userex
{


   message_box::message_box()
   {
      
   }

   
   void message_box::on_show(const ::string & pszMatter)
   {
      
      //auto pformpropertyset = get_form_property_set();
      //
      //auto & set = pformpropertyset->propset();

      //auto 
      //
      //if(!set.has_property("application_name"))
      //{
      // 
      //   set["application_name"] = papp->get_title();
      //   
      //}
         
//      if(set.has_property("message_box_timeout"))
      {
         
  //       m_timeDelay = set["message_box_timeout"].i64();
         
      }

      m_timeDelay = fetch_property("message_box_timeout")->time();
      
      wait_message_dialog::on_show(pszMatter);
      
   }
   

   bool message_box::on_timeout()
   {
      m_atom = "ok";
      return wait_message_dialog::on_timeout();
   }


   void message_box::on_timer_soft_reload(const class ::time & tickTimeout)
   {
      
      wait_message_dialog::on_timer_soft_reload(tickTimeout);
      
   }


} // namespace userex


//namespace aura
//{
//
//   
//   string application::dialog_box(const ::string & pszMatter, property_set & propertyset)
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
//      return pbox->m_atomResponse;
//      
//   }
//
//
//} // namespace aura
