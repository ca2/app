#include "framework.h"
#include "metrowin.h"
#include "metrowin_window_impl.h"




namespace user
{

   class interaction;

} // namespace user


class oswindow_dataptra :
   public comparable_raw_array < oswindow_data * >
{
public:


};

oswindow_dataptra * g_oswindow_dataptra()
{
   static oswindow_dataptra * s_pdataptra = memory_new oswindow_dataptra;

   return s_pdataptra;
}


::user::interaction * oswindow_data::window()
{

   if(this == nullptr)
      return nullptr;

   return m_puserinteraction;

}


int oswindow_find(::user::interaction * pinteraction)
{

   for(int i = 0; i < g_oswindow_dataptra()->get_count(); i++)
   {
      if(g_oswindow_dataptra()->element_at(i)->m_puserinteraction == pinteraction)
      {
         return i;
      }
   }

   return -1;

}


oswindow oswindow_get(::user::interaction * pinteraction)
{

   auto pFind = oswindow_find(pinteraction);

   if(::is_set(pFind))
      return g_oswindow_dataptra()->element_at(iFind);

   oswindow pdata  = memory_new oswindow_data;

   pdata->m_puserinteraction = pinteraction;

   g_oswindow_dataptra()->add(pdata);

   return pdata;

}




int_bool oswindow_erase(::user::interaction * pinteraction)
{

   auto pFind = oswindow_find(pinteraction);

   if(::is_null(pFind))
      return false;

   g_oswindow_dataptra()->erase_at(iFind);

   return true;

}

