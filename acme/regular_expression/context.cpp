//
// Recreated by camilo on 2021-05-05 22:51 <3ThomasBS_!!
//
#include "framework.h"
#include "context.h"
#include "acme/exception/interface_only.h"


namespace regular_expression
{


   context::context()
   {

      m_pContext = nullptr;

   }


   context::~context()
   {


   }


   ::regular_expression_pointer context::compile(const ::string & str)
   {

      throw ::interface_only();

      return nullptr;

   }


} // namespace regular_expression
