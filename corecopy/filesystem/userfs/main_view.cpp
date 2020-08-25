#include "framework.h"
#include "_data.h"
#include "_userfs.h"
#include "core/user/user/_tree.h"


namespace userfs
{


   main_view::main_view()
   {

   }


   void main_view::install_message_routing(::channel * pchannel)
   {
      ::user::split_view::install_message_routing(pchannel);
      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &main_view::_001OnCreate);
   }

   void main_view::_001OnCreate(::message::message * pmessage)
   {
      pmessage->previous();
      if(pmessage->m_bRet)
         return;

//      __pointer(application) papp =  (get_object());
      //papp->m_pmainview = this;
      
      SetPaneCount(2);
      
      SetSplitOrientation(orientation_vertical);
      
      set_position_rate(0, 0.2);
      
      initialize_split_layout();
      
      __pointer(::create) cc(e_create);

//      cc->m_usercreatecontext.m_pCurrentDoc = get_document();
  //    cc->m_usercreatecontext.m_typeNewView = __type(tree);
      __pointer(::user::interaction) pwnd = create_view(__type(tree),get_document(),get_pane_holder(0),100);
      SetPane(0, pwnd, false);
//      __pointer(tree) ptree =  (pwnd);


//      cc->m_usercreatecontext.m_pCurrentDoc = get_document();
  //    cc->m_usercreatecontext.m_typeNewView = __type(list);
      pwnd = create_view(__type(list),get_document(), get_pane_holder(1),101);
//      list * plist = dynamic_cast < list * > (pwnd);
      SetPane(1, pwnd, false);
      set_need_layout();


   }

   
   void main_view::_001OnTimer(::timer * ptimer)
   {

      ::user::split_view::_001OnTimer(ptimer);

   }


   ::user::document * main_view::get_document()
   {
      return  ::user::split_view::get_document();
   }


} // namespace userfs






