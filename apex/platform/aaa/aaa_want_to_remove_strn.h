#pragma once


namespace apex
{


   namespace strn
   {


      CLASS_DECL_APEX  bool           to(const ::scoped_string & scopedstr, int iLen, int & i);
      CLASS_DECL_APEX  bool           to(const ::scoped_string & scopedstr, int iLen, huge_integer & i);
      CLASS_DECL_APEX  bool           to(const ::scoped_string & scopedstr, int iLen, int & i, int iBase);
      CLASS_DECL_APEX  bool           to(const ::scoped_string & scopedstr, int iLen, huge_integer & i, int iBase);


   } // namespace strn


} // namespace apex




