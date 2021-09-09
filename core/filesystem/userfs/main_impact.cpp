#include "framework.h"
#include "_data.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_userfs.h"
#endif

#include "core/user/user/_tree.h"


namespace userfs
{


   main_impact::main_impact()
   {

   }


   void main_impact::install_message_routing(::channel * pchannel)
   {
      ::user::split_view::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &main_impact::on_message_create);
   }

   void main_impact::on_message_create(::message::message * pmessage)
   {
      pmessage->previous();
      if(pmessage->m_bRet)
         return;

//      __pointer(application) papp =  (this);
      //papp->m_pmainimpact = this;
      
      SetPaneCount(2);
      
      SetSplitOrientation(e_orientation_vertical);
      
      set_position_rate(0, 0.2);
      
      initialize_split_layout();
      
      __pointer(::create) cc(e_create);

//      cc->m_usercreatecontext.m_pCurrentDoc = get_document();
  //    cc->m_usercreatecontext.m_typeNewView = __type(tree);
      __pointer(::user::interaction) puserinteraction = create_view(__type(tree),get_document(),get_pane_holder(0),100);
      SetPane(0, puserinteraction, false);
//      __pointer(tree) ptree =  (puserinteraction);


//      cc->m_usercreatecontext.m_pCurrentDoc = get_document();
  //    cc->m_usercreatecontext.m_typeNewView = __type(list);
      puserinteraction = create_view(__type(list),get_document(), get_pane_holder(1),101);
//      list * plist = dynamic_cast < list * > (puserinteraction);
      SetPane(1, puserinteraction, false);
      set_need_layout();


   }

   
   void main_impact::_001OnTimer(::timer * ptimer)
   {

      ::user::split_view::_001OnTimer(ptimer);

   }


   ::user::document * main_impact::get_document()
   {
      return  ::user::split_view::get_document();
   }


} // namespace userfs






