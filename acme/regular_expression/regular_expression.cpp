//
// Recreated by camilo on 2021-05-05 22:52 <3ThomasBS_!!
//
#include "framework.h"
#include "regular_expression.h"
////#include "acme/exception/exception.h"


namespace regular_expression
{


   regular_expression::regular_expression()
   {

      m_pRegularExpression = nullptr;
      m_iRangeCount = 0;

   }


   regular_expression::~regular_expression()
   {


   }


   void regular_expression::compile(const ::scoped_string & scopedstr)
   {

      m_str = scopedstr;

   }


   ::pointer<result>regular_expression::run(const ::scoped_string & scopedstr)
   {

      throw ::exception(error_interface_only, "missing \"" + scopedstr + "\" runned by regular expression \"" + m_str + "\"");

      return nullptr;

   }


   bool regular_expression::replace(string & strFind, const ::scoped_string & scopedstrReplace, string & strResult)
   {

      return false;

   }


} // namespace regular_expression



