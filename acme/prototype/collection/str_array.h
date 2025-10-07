// Created by camilo on 2022-11-04 04:20 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME string_array_base stringa_from_strdupa(::ansi_character ** ppParam);


CLASS_DECL_ACME char ** strdupa_from_stringa(const ::string_array_base & stra);


CLASS_DECL_ACME ::collection::count explode_command_line(string_array_base & stra, const ::scoped_string & scopedstr, address_array_base < char * > * argv);


CLASS_DECL_ACME string_array_base & csstidy_explode_ws(string_array_base & str, char sep, const ::scoped_string & scopedstr);



