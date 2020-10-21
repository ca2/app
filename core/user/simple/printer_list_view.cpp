#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple/_simple.h"
#endif
#include "aura/graphics/draw2d/printer.h"
#include "base/user/user/print_task.h"
#ifdef WINDOWS_DESKTOP
#include <winspool.h>
#endif


simple_printer_list_view::simple_printer_list_view()
{

}


simple_printer_list_view::~simple_printer_list_view()
{

}


void simple_printer_list_view::install_message_routing(::channel * pchannel)
{

   simple_list_view::install_message_routing(pchannel);
   IGUI_MSG_LINK(WM_CREATE, pchannel, this, &simple_printer_list_view::_001OnCreate);

}


void simple_printer_list_view::_001OnCreate(::message::message * pmessage)
{
//   SCAST_PTR(::message::create, pcreate, pmessage);

   pmessage->previous();

   DWORD cbNeeded = 0;
#ifdef WINDOWS_DESKTOP
   DWORD cbReturned = 0;
   ::EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, nullptr, 1, nullptr, 0, &cbNeeded, &cbReturned);
#else
   //__throw(todo());
#endif

   if(cbNeeded <= 0)
      return;

#ifdef WINDOWS_DESKTOP
   PRINTER_INFO_1  * infoa = (PRINTER_INFO_1 * ) malloc(cbNeeded);
   ::EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, nullptr, 1, (byte *) infoa, cbNeeded, &cbNeeded, &cbReturned);

   string_array stra;

   for(u32 i = 0; i < cbReturned; i++)
   {

      stra.add(string(infoa[i].pName));
   }

   m_psimplelistdata->set_data(this, stra);

   free(infoa);
#else
   //__throw(todo());
#endif


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
   pprinttask->m_pprinter = Application.get_printer(item.m_strText);
   pprinttask->m_pinteraction = m_pview;
   ::task::start(pprinttask);
   
   return true;

}

