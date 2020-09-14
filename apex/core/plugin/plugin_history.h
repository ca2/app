#pragma once


namespace plugin
{

   class CLASS_DECL_APEX history :
      virtual public ::apex::history
   {
   public:


      plugin * m_pplugin;


      history(::object * pobject, plugin * pplugin);


      virtual bool hist(const char *pszUrl);

   };


} // namespace plugin


