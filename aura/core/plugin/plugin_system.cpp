#include "framework.h"


namespace plugin
{


   system::system()
   {

   }


   ::e_status system::os_native_bergedge_start()
   {

      //return m_pplugin->os_native_bergedge_start();

      return ::success;

   }


   bool system::open_link(const string & pszLink, const string & pszTarget)
   {

      UNREFERENCED_PARAMETER(pszTarget);

      m_pplugin->m_puiHost->post_message(host_interaction::message_check, 2, (LPARAM) (void *) (new string(pszLink)));

      return true;

   }


   ::e_status system::verb()
   {

      return ::aura::system::verb();

   }


   string system::get_host_location_url()
   {

      return (const string &) m_pplugin->get_host_location_url();

   }


} // namespace plugin


