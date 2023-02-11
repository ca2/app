#include "framework.h"
#include "main_impact.h"
#include "list.h"
#include "tree.h"
#include "acme/constant/message.h"
#include "acme/handler/item.h"
#include "acme/primitive/data/listener.h"
#include "acme/handler/request.h"
#include "core/user/user/tree.h"


namespace userfs
{


   main_impact::main_impact()
   {

   }


   void main_impact::install_message_routing(::channel * pchannel)
   {
      ::user::split_impact::install_message_routing(pchannel);
      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &main_impact::on_message_create);
   }

   void main_impact::on_message_create(::message::message * pmessage)
   {
      pmessage->previous();
      if(pmessage->m_bRet)
         return;

//      ::pointer<application>papp =  (this);
      //papp->m_pmainimpact = this;
      
      SetPaneCount(2);
      
      SetSplitOrientation(e_orientation_vertical);
      
      set_position_rate(0, 0.2);
      
      initialize_split_layout();
      
      ::pointer<::request>prequest(e_create, this);

//      prequest->m_usercreatecontext.m_pCurrentDoc = get_document();
  //    prequest->m_usercreatecontext.m_typeNewImpact = __type(tree);
      ::pointer<::user::interaction>puserinteraction = create_impact(__type(tree),get_document(),get_pane_holder(0),100);
      SetPane(0, puserinteraction, false);
//      ::pointer<tree>ptree =  (puserinteraction);


//      cc->m_usercreatecontext.m_pCurrentDoc = get_document();
  //    cc->m_usercreatecontext.m_typeNewImpact = __type(list);
      puserinteraction = create_impact(__type(list),get_document(), get_pane_holder(1),101);
//      list * plist = dynamic_cast < list * > (puserinteraction);
      SetPane(1, puserinteraction, false);
      set_need_layout();


   }

   
   void main_impact::_001OnTimer(::timer * ptimer)
   {

      ::user::split_impact::_001OnTimer(ptimer);

   }


   ::user::document * main_impact::get_document()
   {
      return  ::user::split_impact::get_document();
   }


} // namespace userfs






