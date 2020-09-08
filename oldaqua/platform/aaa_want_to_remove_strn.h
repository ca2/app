#pragma once


namespace aqua
{


   namespace strn
   {


      CLASS_DECL_AQUA  bool           to(const char * psz, i32 iLen, i32 & i);
      CLASS_DECL_AQUA  bool           to(const char * psz, i32 iLen, i64 & i);
      CLASS_DECL_AQUA  bool           to(const char * psz, i32 iLen, i32 & i, i32 iBase);
      CLASS_DECL_AQUA  bool           to(const char * psz, i32 iLen, i64 & i, i32 iBase);


   } // namespace strn


} // namespace aqua




