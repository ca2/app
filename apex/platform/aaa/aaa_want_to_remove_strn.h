#pragma once


namespace apex
{


   namespace strn
   {


      CLASS_DECL_APEX  bool           to(const ::scoped_string & scopedstr, i32 iLen, i32 & i);
      CLASS_DECL_APEX  bool           to(const ::scoped_string & scopedstr, i32 iLen, i64 & i);
      CLASS_DECL_APEX  bool           to(const ::scoped_string & scopedstr, i32 iLen, i32 & i, i32 iBase);
      CLASS_DECL_APEX  bool           to(const ::scoped_string & scopedstr, i32 iLen, i64 & i, i32 iBase);


   } // namespace strn


} // namespace apex




