//
//  host_interaction.cpp
//  aura
//
//  Copied from node/ios by Camilo Sasuke Thomas Borregaard Soerensen on 20/06/05.
//  (with refactorization: ui_interaction -> host_interaction to
//  match OPERATING_SYSTEM_NAMESPACE::create_*host*_window() naming.)
// as acme::sandbox_windowing on 2024-11-25 23:25 by
// camilo <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_sandbox.h"
#include "acme/platform/application.h"
#include "acme/user/micro/button.h"
#include "acme/user/micro/popup_button.h"
#include "acme/user/user/activation_token.h"
#include "acme/user/user/mouse.h"


namespace acme
{


namespace sandbox_windowing
{


host_interaction::host_interaction()
{
   
   
   
}


host_interaction::~host_interaction()
{
   
   
}


::acme::sandbox_windowing::windowing* host_interaction::windowing()
{
   
   auto pwindowing = system()->acme_windowing();
   
   auto pwindowingHere = dynamic_cast <::acme::sandbox_windowing::windowing*>(pwindowing);
   
   return pwindowingHere;
   
}





void host_interaction::create_context_button()
{

   if(__defer_construct_new(m_pbuttonContext))
   {
      
      auto r = get_rectangle();
      
      r.left() = r.right() - 32;
      r.top() = r.bottom() - 32;
      
      m_pbuttonContext->id() = id_context_button;

      m_pbuttonContext->set_rectangle(r);

      add_child(m_pbuttonContext);
      
   }

}


void host_interaction::on_click(const ::payload & payload, ::user::mouse * pmouse)
{
 
   if(payload.as_atom() == id_context_button)
   {
      
      auto ppopupbutton = __create_new<::micro::popup_button>();

      //auto pwindowParent = this->acme_windowing_window();

      ::int_rectangle rectanglePointTo;

      rectanglePointTo.left() = 0;
      rectanglePointTo.top() = 0;
      rectanglePointTo.right() = rectanglePointTo.left() + 200;
      rectanglePointTo.bottom() = rectanglePointTo.top() + 2;

      ppopupbutton->acme_windowing_window()->m_rectanglePointingTo = rectanglePointTo;

      ppopupbutton->initialize_popup_button(
         "About...",
         pmouse->m_pointAbsolute.x(), pmouse->m_pointAbsolute.y(),
         this);

      auto puseractivationtoken = ::as_pointer(pmouse->user_activation_token());

      ppopupbutton->main_async()
         << [this, ppopupbutton, puseractivationtoken]()
         {
            
            application()->show_about_box(puseractivationtoken);

//            auto result = ppopupbutton->m_payloadPopupButtonResult;
//
//            if (result == e_dialog_result_yes)
//            {
//
//               display_temporary_file_with_text(
//                  m_prealizable->m_strMessage + "\n\n"
//                  + m_prealizable->m_strDetails);
//
//            }

         };
      
      pmouse->m_bRet = true;
      
      return;

   }
   
   //return false;
   
}






//
//void host_interaction::install_message_routing(::channel* pchannel)
//{
//   
//   ::user::interaction::install_message_routing(pchannel);
//   
//   MESSAGE_LINK(e_message_create, pchannel, this, &host_interaction::on_message_create);
//   
//}
//
//
//void host_interaction::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
//{
//   
//   
//}
//
//
//void host_interaction::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
//{
//   
//   ::user::interaction::_001DrawChildren(pgraphics);
//   
//}
//
//
//void host_interaction::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
//{
//   
//   ::user::interaction::_000OnDraw(pgraphics);
//   
//}
//
//
//void host_interaction::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
//{
//   
//   
//}
//
//
//void host_interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
//{
//   
//   ::user::interaction::_001OnDraw(pgraphics);
//   
//}


void host_interaction::post_redraw(bool bAscendants)
{
   
   ::acme::user::interaction::post_redraw(bAscendants);
   
}


//void host_interaction::on_message_create(::message::message* pmessage)
//{
//   
//   pmessage->previous();
//   
//   auto pwindowing = windowing();
//   
//   auto pwindow = window();
//   
//   pwindowing->m_pwindowApplicationHost = pwindow;
//   
//   window()->show_window();
//   
//}
//
//
//void host_interaction::on_layout(::draw2d::graphics_pointer& pgraphics)
//{
//   
//   ::int_rectangle r;
//   
//   r = this->rectangle();
//   
//   if (r.is_empty())
//   {
//      
//      return;
//      
//   }
//   
//   ::pointer<::user::interaction>pinteraction;
//   
//   get_child(pinteraction);
//   
//   if (::is_null(pinteraction))
//   {
//      
//      return;
//      
//   }
//   
//   pinteraction->place(r);
//   
//}


void host_interaction::handle(::topic * ptopic, ::context * pcontext)
{
   
   ::micro::main_window::handle(ptopic, pcontext);
   
}


} // namespace sandbox_windowing



} // namespace acme



