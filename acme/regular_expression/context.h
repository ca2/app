//
// Recreated by camilo on 5/6/21 22:51 <3ThomasBS_!!
//
#pragma once


#include "acme/platform/department.h"


namespace regular_expression
{


   class CLASS_DECL_ACME context :
      virtual public ::platform::department
   {
   public:


      void *         m_pContext;


      context();
      virtual ~context();


      virtual ::regular_expression_pointer compile(const ::scoped_string & scopedstr);



   };


} // namespace regular_expression



