#include "framework.h"
#include "acme/primitive/collection/_sort.h"
#include "acme/primitive/data/listener.h"
#include "core/user/simple/list_control.h"
#include "core/user/simple/list_data.h"


simple_list_control::simple_list_control()
{

}


simple_list_control::~simple_list_control()
{

}


::pointer<::user::interaction>simple_list_control::OnDrawInterfaceGetWnd()
{

   return this;

}


bool simple_list_control::pre_create_window(::user::system * pusersystem)
{

#ifdef WINDOWS_DESKTOP



#endif

   return ::user::interaction::pre_create_window(pusersystem);

}


void simple_list_control::set_data(string_array &stra)
{
   
   m_psimplelistdata->set_data(this, stra);

}


void simple_list_control::get_data(string_array &stra)
{

   m_psimplelistdata->get_data(stra);

}


void simple_list_control::pre_subclass_window()
{
   PreSubClassWindow();

   if(!CreateHeaderCtrl())
   {
      return;
   }


   ::user::interaction::pre_subclass_window();


}


bool simple_list_control::erase_item(i32 iItem)
{
   
   if (!m_psimplelistdata->erase_item(iItem))
   {

      return false;

   }

   update_impact();

   return true;

}


bool simple_list_control::erase_item(::user::item_range & range)
{
   
   //bool bOk = true;
   
   for(::collection::index iItem = range.get_upper_bound(); iItem >= range.get_lower_bound(); iItem++)
   {

      if(!m_psimplelistdata->erase_item(iItem))
      {

//         bOk = false;

      }

   }

   update_impact();

   return true;

}


bool simple_list_control::erase_item(::user::range & range)
{
   bool bOk = true;
   index_array iaRemove;
   for(::collection::index iRange = 0; iRange < range.get_item_count(); iRange++)
   {
      auto & itemrange = range.ItemAt(iRange);
      for(::collection::index iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
      {
         iaRemove.add_unique(iItem);
      }
   }
   ::sort::QuickSortDesc(iaRemove);
   for(::collection::index i = 0; i < iaRemove.get_size(); i++)
   {
      if(!m_psimplelistdata->erase_item(iaRemove[i]))
         bOk = false;
   }
   
   update_impact();

   return bOk;

}


void simple_list_control::install_message_routing(::channel * pchannel)
{
   __UNREFERENCED_PARAMETER(pchannel);
   ::user::list::install_message_routing(pchannel);
}

