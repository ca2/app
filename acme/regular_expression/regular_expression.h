//
// Recreated by camilo on 2021-05-05 22:52 <3ThomasBS_!!
//
#pragma once


namespace regular_expression
{


   class CLASS_DECL_ACME regular_expression :
      virtual public matter
   {
   public:


      void *                     m_pRegularExpression;

      __pointer(context)         m_pcontext;

      string                     m_str;

      int                        m_iRangeCount;


      regular_expression();
      ~regular_expression() override;


      virtual void compile(const string& str);

      virtual __pointer(result) run(const ::string & str);

      virtual bool replace(string & strFind, const ::string & strReplace, string & strResult);


   };


} // namespace regular_expression



