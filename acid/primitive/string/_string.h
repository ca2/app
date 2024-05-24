#pragma once


//#include "acid/primitive/collection/array.h"


CLASS_DECL_ACID void replace_tab(strsize iOffset, string & strParam, int iWidth, strsize_array * piaTab = nullptr, array < strsize * > intptra = nullptr);


CLASS_DECL_ACID void replace_tab(strsize iOffset, string & strParam, int iWidth, array < strsize * > intptra);


CLASS_DECL_ACID string _002Underscore(string str);


CLASS_DECL_ACID void erase_sharp_comment(::string& str);