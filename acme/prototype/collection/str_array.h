// Created by camilo on 2022-11-04 04:20 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME string_array stringa_from_strdupa(::ansi_character ** ppParam);


CLASS_DECL_ACME char ** strdupa_from_stringa(const ::string_array & stra);


CLASS_DECL_ACME ::collection::count explode_command_line(string_array & stra, const ::string & str, address_array < char * > * argv);


CLASS_DECL_ACME string_array & csstidy_explode_ws(string_array & str, char sep, const ::string & psz);



