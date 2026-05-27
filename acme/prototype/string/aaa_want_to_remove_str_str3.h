#pragma once


namespace str
{


   CLASS_DECL_ACME void replace_tab(character_count iOffset, string & strParam, ::i32 iWidth, array < character_count * > intptra = array < character_count * >(), strsize_array * piaTab = nullptr);
   CLASS_DECL_ACME void replace_tab(character_count iOffset, string & strParam, ::i32 iWidth, strsize_array * piaTab);
   CLASS_DECL_ACME void fix_eol(string & str);



} // namespace str
