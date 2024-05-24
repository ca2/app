#pragma once


namespace acid
{


   class CLASS_DECL_ACID history :
      virtual public ::matter
   {
   public:


      ::pointer<history>    m_phistory;


      history();
         
   
      virtual bool hist(const char *psz);

   };


} // namespace acid


