// From definition.h by camilo on 2022-09-06 17:19 <3ThomasBorregaardSorensen!!
#pragma once


////#include "acme/exception/exception.h"


namespace database
{


   class CLASS_DECL_AXIS exception :
      public ::exception
   {
   public:


      exception();
      exception(const scoped_string & strFormat, ...);


   };


} // namespace database



