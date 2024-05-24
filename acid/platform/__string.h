// Created by camilo on 2022-11-07 09:43 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACID string as_string(enum_display edisplay);
CLASS_DECL_ACID string as_string(const ::e_display & edisplay);


#ifdef MEMDLEAK

CLASS_DECL_ACID string get_mem_info_report1();
CLASS_DECL_ACID::collection::count get_mem_info(i32 ** ppiUse, const char *** ppszFile, const char *** pszCallStack, u32 ** ppuiLine, size_t ** ppsize);


#endif

