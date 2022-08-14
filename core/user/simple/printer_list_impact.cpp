#include "framework.h"
#include "core/user/simple/_component.h"
#include "aura/graphics/draw2d/printer.h"
#include "base/user/user/print_task.h"
//#ifdef WINDOWS_DESKTOP
//#include <winspool.h>
//#endif


simple_printer_list_impact::simple_printer_list_impact()
{

}


simple_printer_list_impact::~simple_printer_list_impact()
{

}


void simple_printer_list_impact::install_message_routing(::channel * pchannel)
{

   simple_list_impact::install_message_routing(pchannel);
   MESSAGE_LINK(e_message_create, pchannel, this, &simple_printer_list_impact::on_message_create);

}


void simple_printer_list_impact::on_message_create(::message::message * pmessage)
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

   //throw ::exception(todo);

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
//   //throw ::exception(todo);
//#endif


   auto pcolumn = new_list_column();
   pcolumn->m_iWidth = 500;
   pcolumn->m_iSubItem = 0;

   

}


bool simple_printer_list_impact::on_click(::item * pitem)
{

   if (!::is_set(pitem))
   {

      return false;

   }

   auto & psubitem = get_subitem(pitem->m_iItem, 0);

   m_psimplemeshdata->_001GetSubItemText(psubitem);

   __pointer(::user::print_task) pprinttask;

   pprinttask.create(this);

   pprinttask->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   auto papp = get_app();

   pprinttask->m_pprinter = papp->get_printer(psubitem->m_strText);

   pprinttask->m_pinteraction = m_pimpact;

   pprinttask->branch();
   
   return true;

}


