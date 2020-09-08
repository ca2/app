#pragma once


namespace str
{


   CLASS_DECL_APEX bool x_contains(string str, string strFind);
   CLASS_DECL_APEX bool x_find(string_array & stra, string str);
   CLASS_DECL_APEX void x_left_remove(string & str, string strFind);

   extern CLASS_DECL_APEX const char g_trailingBytesForUTF8[256];


} // namespace str





