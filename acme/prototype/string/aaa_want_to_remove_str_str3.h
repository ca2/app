#pragma once


namespace str
{


   CLASS_DECL_ACME void replace_tab(character_count iOffset, string & strParam, int iWidth, array < character_count * > intptra = array < character_count * >(), strsize_array * piaTab = nullptr);
   CLASS_DECL_ACME void replace_tab(character_count iOffset, string & strParam, int iWidth, strsize_array * piaTab);
   CLASS_DECL_ACME void fix_eol(string & str);



} // namespace str
