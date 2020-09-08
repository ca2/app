#pragma once


namespace ansios
{


   class CLASS_DECL_AQUA callstack :
      public ::callstack
   {
   public:


      callstack();
      virtual ~callstack();


      virtual const char * get_dup(const char * pszFormat, i32 iSkip, int iCount);


   };


} // namespace ansios



