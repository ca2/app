#include "framework.h"


namespace plugin
{

   history::history(::element * pobject, plugin * pplugin) :
      ::element(pobject),
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



