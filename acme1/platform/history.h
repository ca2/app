#pragma once


namespace acme
{


   class CLASS_DECL_ACME history :
      virtual public ::generic
   {
   public:


      __pointer(history)    m_phistory;


      history();
         
   
      virtual bool hist(const char *psz);

   };


} // namespace acme


