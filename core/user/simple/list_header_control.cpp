#include "framework.h"
#include "core/user/simple/list_header_control.h"
#include "core/user/user/list.h"
#include "aura/message/user.h"


const i32 simple_list_header_control::s_iDividerWidth = 4;

simple_list_header_control::simple_list_header_control()
{



}

simple_list_header_control::~simple_list_header_control()
{
}



void simple_list_header_control::install_message_routing(::channel * pchannel)
{
   ::user::list_header::install_message_routing(pchannel);
//#ifdef WINDOWS_DESKTOP
//   MESSAGE_LINK(HDN_ENDTRACK, pchannel, this, &simple_list_header_control::_001OnEndTrack);
//   MESSAGE_LINK(HDN_TRACK, pchannel, this, &simple_list_header_control::_001OnTrack);
//   MESSAGE_LINK(HDN_ENDDRAG, pchannel, this, &simple_list_header_control::_001OnEndDrag);
//#endif
   MESSAGE_LINK(e_message_create, pchannel, this, &simple_list_header_control::on_message_create);
   //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &simple_list_header_control::on_message_left_button_down);
   //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &simple_list_header_control::on_message_left_button_up);
   //MESSAGE_LINK(e_message_mouse_move, pchannel, this, &simple_list_header_control::on_message_mouse_move);
}

/*i32 simple_list_header_control::GetItemWidth(i32 iItem)
{
   HDITEM hditem;

   hditem.mask = HDI_WIDTH | HDI_TEXT;

   char pszText[1024];

   hditem.pszText = pszText;
   hditem.cchTextMax = 1024;

   get_item(iItem, &hditem);

   return hditem.cxy;

}*/

void simple_list_header_control::_001OnEndTrack(::message::message * pmessage)
{

   ::pointer<::message::notify>pnotify(pmessage);

   get_parent()->send_message(::user::list::MESSAGE_ENDCOLUMNHEADERTRACK);

   pnotify->m_bRet = false;

}


void simple_list_header_control::_001OnTrack(::message::message * pmessage)
{

   ::pointer<::message::notify>pnotify(pmessage);

   get_parent()->send_message(::user::list::MESSAGE_COLUMNHEADERTRACK);

   pnotify->m_bRet = false;

}


void simple_list_header_control::on_message_create(::message::message * pmessage)
{

   ::pointer<::message::create>pcreate(pmessage);

   pcreate->m_bRet = false;

}


void simple_list_header_control::_001OnEndDrag(::message::message * pmessage)
{

   ::pointer<::message::notify>pnotify(pmessage);

   get_parent()->send_message(::user::list::MESSAGE_ENDCOLUMNHEADERDRAG);

   pnotify->m_lresult = false;

   pnotify->m_bRet = false;

}

/*void simple_list_header_control::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
   LPNMHDDISPINFO pdi = (LPNMHDDISPINFO) pNMHDR;

   CTransparentWndInterface * ptwi = nullptr;
   CTransparentWndInterface::CGetProperty getp;
   getp.m_eproperty = CTransparentWndInterface::PropertyInterface;
   get_parent()->SendMessage(CTransparentWndInterface::MessageGetProperty, 0, (LPARAM) &getp);
   ptwi = getp.m_pinterface;
   if(ptwi != nullptr)
   {
      ::user::list * plist = dynamic_cast<::user::list *>(ptwi);
      if(plist != nullptr)
      {
         if(pdi->mask & HDI_TEXT

            && pdi->iItem >= 0 &&

            pdi->iItem < plist->_001GetColumnCount())

         {
            string & str = m_strBuffer;
            str.load_string(plist->_001GetColumnText(pdi->iItem));

            pdi->pszText = (char *) (const ::string &) str;

            pdi->cchTextMax = str.get_length();

         }*/
/*         if(pdi->mask & HDI_TEXT

            && pdi->lParam >= 0 &&

            pdi->lParam < plist->_001GetColumnCount())

         {
            string & str = m_strBuffer;
            str.load_string(plist->_001GetColumnText(pdi->lParam));

            pdi->pszText = (char *) (const ::string &) str;

            pdi->cchTextMax = str.get_length();

         }
      }
   }

}*/

/*LPARAM simple_list_header_control::GetItemLParam(i32 iItem)
{
   HDITEM hditem;

   hditem.mask = HDI_LPARAM;

   get_item(iItem, &hditem);

   return hditem.lParam;
}*/


//bool simple_list_header_control::create_window(u32 nStyle, ::user::interaction * puiParent, ::atom atom)
//{
//
//   return ::user::interaction::create_window(nullptr, nullptr, nStyle, puiParent, atom);
//
//}



