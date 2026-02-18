#pragma once


namespace aura
{


   class CLASS_DECL_AURA history :
      virtual public ::object
   {
   public:


      ::pointer<history>    m_phistory;


      history();
         
   
      virtual bool hist(const ::scoped_string & scopedstr);

   };


} // namespace aura


