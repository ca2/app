#pragma once


namespace str
{


   CLASS_DECL_AQUA bool x_contains(string str, string strFind);
   CLASS_DECL_AQUA bool x_find(string_array & stra, string str);
   CLASS_DECL_AQUA void x_left_remove(string & str, string strFind);

   extern CLASS_DECL_AQUA const char g_trailingBytesForUTF8[256];


} // namespace str





