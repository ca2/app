//
// Recreated by camilo on 2021-05-05 22:52 <3ThomasBS_!!
//
#pragma once



//#include "acme/prototype/prototype/pointer.h"


namespace regular_expression
{


   class result;


   class CLASS_DECL_ACME regular_expression :
      virtual public particle
   {
   public:


      void *                                       m_pRegularExpression;

      ::pointer<::regular_expression::context>     m_papplication;

      string                                       m_str;

      int                                          m_iRangeCount;


      regular_expression();
      ~regular_expression() override;


      virtual void compile(const ::scoped_string & scopedstr);

      virtual ::pointer<result>run(const ::scoped_string & scopedstr);

      virtual bool replace(string & strFind, const ::scoped_string & scopedstrReplace, string & strResult);


   };


} // namespace regular_expression



