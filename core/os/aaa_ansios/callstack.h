#pragma once


namespace ansios
{


   class CLASS_DECL_CORE callstack :
      public ::callstack
   {
   public:


      callstack();
      virtual ~callstack();


      virtual const char * get_dup(const ::string & pszFormat, i32 iSkip, int iCount);


   };


} // namespace ansios



