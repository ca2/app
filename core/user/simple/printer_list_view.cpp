#include "framework.h"
#include "core/user/simple/_simple.h"
#include "aura/graphics/draw2d/printer.h"
#include "base/user/user/print_task.h"
//#ifdef WINDOWS_DESKTOP
//#include <winspool.h>
//#endif


simple_printer_list_view::simple_printer_list_view()
{

}


simple_printer_list_view::~simple_printer_list_view()
{

}


void simple_printer_list_view::install_message_routing(::channel * pchannel)
{

   simple_list_view::install_message_routing(pchannel);
   MESSAGE_LINK(e_message_create, pchannel, this, &simple_printer_list_view::on_message_create);

}


void simple_printer_list_view::on_message_create(::message::message * pmessage)
{
//   __pointer(::message::create) pcreate(pmessage);

   pmessage->previous();

#ifdef WINDOWS_DESKTOP

   //DWORD cbNeeded = 0;

   //DWORD cbReturned = 0;

   //::EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, nullptr, 1, nullptr, 0, &cbNeeded, &cbReturned);

   //if(cbNeeded <= 0)
   //   return;

#else

   //__throw(todo);

#endif

//#ifdef WINDOWS_DESKTOP
//   PRINTER_INFO_1  * infoa = (PRINTER_INFO_1 * ) malloc(cbNeeded);
//   ::EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, nullptr, 1, (byte *) infoa, cbNeeded, &cbNeeded, &cbReturned);
//
//   string_array stra;
//
//   for(u32 i = 0; i < cbReturned; i++)
//   {
//
//      stra.add(string(infoa[i].pName));
//   }
//
//   m_psimplelistdata->set_data(this, stra);
//
//   free(infoa);
//#else
//   //__throw(todo);
//#endif


   auto pcolumn = new_list_column();
   pcolumn->m_iWidth = 500;
   pcolumn->m_iSubItem = 0;

   

}


bool simple_printer_list_view::on_click(const ::user::item & itemClick)
{

   if (!itemClick.is_set())
   {

      return false;

   }
   ::user::list_item item(this);
   item.m_plist = this;
   item.m_iItem = itemClick.m_iItem;
   item.m_iSubItem = 0;
   item.m_iListItem = -1;
   m_psimplemeshdata->_001GetItemText(&item);
   __pointer(::user::print_task) pprinttask;
   pprinttask.create(this);
   pprinttask->add_ref(OBJ_REF_DBG_THIS);

   auto papplication = get_application();

   pprinttask->m_pprinter = papplication->get_printer(item.m_strText);
   pprinttask->m_pinteraction = m_pview;

   pprinttask->branch();
   
   return true;

}

