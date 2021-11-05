#pragma once


namespace apex
{


   class CLASS_DECL_APEX history :
      virtual public ::object
   {
   public:


      __composite(history)    m_phistory;


      history();
         
   
      virtual bool hist(const char *psz);

   };


} // namespace apex


