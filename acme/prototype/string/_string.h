#pragma once


//#include "acme/prototype/collection/array.h"


CLASS_DECL_ACME void replace_tab(character_count iOffset, string & strParam, int iWidth, strsize_array * piaTab = nullptr, array < character_count * > intptra = nullptr);


CLASS_DECL_ACME void replace_tab(character_count iOffset, string & strParam, int iWidth, array < character_count * > intptra);


CLASS_DECL_ACME string _002Underscore(const ::scoped_string & scopedstr);


CLASS_DECL_ACME void erase_sharp_comment(::string& str);