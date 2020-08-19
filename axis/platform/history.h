#pragma once


namespace aura
{


   class CLASS_DECL_AURA history :
      virtual public ::object
   {
   public:


      __composite(history)    m_phistory;


      history();
         
   
      virtual bool hist(const char *psz);

   };


} // namespace aura


