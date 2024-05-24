// Created by camilo on 2022-11-07 21:43 <3ThomasBorregaardSorensen!!
#pragma once


#ifdef WINDOWS
CLASS_DECL_ACID ::string call_stack_default_format();
#else
::string call_stack_default_format();
#endif


//CLASS_DECL_ACID ::string get_call_stack_trace(void ** stack, int c, const char* pszFormat = nullptr);



