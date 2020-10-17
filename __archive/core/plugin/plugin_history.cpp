#include "framework.h"


namespace plugin
{

   history::history(::matter * pobject, plugin * pplugin) :
      ::matter(pobject),
      ::acme::history(pobject),
      m_pplugin(pplugin)
   {
   }


   bool history::hist(const char * pszUrl)
   {
      if(m_pplugin != nullptr)
      {
         m_pplugin->open_link(pszUrl, "");
         return true;
      }
      return false;
   }


} // namespace plugin



