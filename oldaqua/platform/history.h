#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA history :
      virtual public ::object
   {
   public:


      __composite(history)    m_phistory;


      history();
         
   
      virtual bool hist(const char *psz);

   };


} // namespace aqua


