#pragma once


////#include "acme/primitive/primitive/object.h"


namespace apex
{


   class CLASS_DECL_APEX history :
      virtual public ::object
   {
   public:


      ::pointer<history>    m_phistory;


      history();
         
   
      virtual bool hist(const ::scoped_string & scopedstr);

   };


} // namespace apex


