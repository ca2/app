#pragma once


namespace plugin
{

   class CLASS_DECL_ACME history :
      virtual public ::acme::history
   {
   public:


      plugin * m_pplugin;


      history(::matter * pobject, plugin * pplugin);


      virtual bool hist(const char *pszUrl);

   };


} // namespace plugin


