#pragma once


namespace dynamic_source
{


   inline property& script_interface::get(id id)
   {

      return netnodesocket()->request().form().get()[id];

   }


   inline property& script_interface::post(id id)
   {

      return netnodesocket()->request().form().post()[id];

   }


   inline http::cookie& script_interface::get_cookie(id id)
   {

      return netnodesocket()->request().cookies().cookie(id);

   }


   inline http::cookie& script_interface::set_cookie(id id)
   {

      return netnodesocket()->response().cookies().cookie(id);

   }


   inline property& script_interface::request(id id)
   {

      return netnodesocket()->request().form().request()[id];

   }


   inline property_set& script_interface::geta()
   {

      return netnodesocket()->request().form().get();

   }


   inline property_set& script_interface::posta()
   {

      return netnodesocket()->request().form().post();

   }


   inline http::cookies& script_interface::cookies()
   {

      return netnodesocket()->request().cookies();

   }


   inline property_set& script_interface::requesta()
   {

      return netnodesocket()->request().form().request();

   }


   inline property_set& script_interface::inattra()
   {

      return netnodesocket()->inattrs();

   }


   inline property& script_interface::inheader(id id)
   {

      return netnodesocket()->inheader(id);

   }


   inline property& script_interface::outheader(id id)
   {

      return netnodesocket()->outheader(id);

   }


   inline property& script_interface::inattr(id id)
   {

      return netnodesocket()->inattr(id);

   }


   inline property& script_interface::outattr(id id)
   {

      return netnodesocket()->outattr(id);

   }




   inline string& script_interface::gstr(id id)
   {

      return gprop(id).get_ref_string();

   }


   inline void script_interface::uri_set_var(string& strUrl, const char* pszUrl, const char* pszKey, payload payload)
   {

      System.url().set_key(strUrl, pszUrl, pszKey, payload);

   }


   inline void script_interface::uri_set_param(string& strUrl, const char* pszUrl, const char* pszKey, const string& strParam)
   {

      System.url().set_param(strUrl, pszUrl, pszKey, strParam);

   }


   inline string script_interface::query_get_param(const char* pszUrl, const char* pszKey)
   {

      return System.url().get_param(pszUrl, pszKey);

   }


   inline payload script_interface::query_get_var(const char* pszUrl, const char* pszKey)
   {

      return System.url().get_var(pszUrl, pszKey);

   }


   inline void script_interface::dprint(const char* psz)
   {

      if (m_pmain && m_pmain->m_iDebug > 0)
      {

         print(psz);

      }

   }


   inline void script_interface::dprint_r(payload payload)
   {

      if (m_pmain != nullptr && m_pmain->m_iDebug > 0)
      {

         print_r(payload);

      }

   }


   inline property& script_interface::gprop(id id)
   {

      auto& set = m_pmain->get_property_set();

      return set.get(id);

   }


   inline httpd_socket* script_interface::netnodesocket() 
   { 
      
      return m_pmain->m_psocket2; 
   
   }


   inline script_manager* script_interface::manager()
   { 
      
      return m_pmain->m_pmanager2; 
   
   }


} // namespace dynamic_source



