//
// Recreated by camilo on 5/6/21 22:51 <3ThomasBS_!!
//
#pragma once


#include "acid/platform/department.h"


namespace regular_expression
{


   class CLASS_DECL_ACID context :
      virtual public ::acid::department
   {
   public:


      void *         m_pContext;


      context();
      virtual ~context();


      virtual ::regular_expression_pointer compile(const ::string & str);



   };


} // namespace regular_expression



