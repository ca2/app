#pragma once


namespace str
{


   CLASS_DECL_AQUA void replace_tab(strsize iOffset, string & strParam, int iWidth, array < strsize * > intptra = array < strsize * >(), strsize_array * piaTab = nullptr);
   CLASS_DECL_AQUA void replace_tab(strsize iOffset, string & strParam, int iWidth, strsize_array * piaTab);
   CLASS_DECL_AQUA void fix_eol(string & str);



} // namespace str
