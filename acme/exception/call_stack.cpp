// Created by camilo on 2023-11-22 09:39 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/platform/node.h"


#ifdef WINDOWS
CLASS_DECL_ACME ::string call_stack_default_format()
#else
::string call_stack_default_format()
#endif
{

   return "%f(%l) %s\n";

}


//CLASS_DECL_ACME void get_call_stack_frames(void** stack, int & frame_count)
//{
//
//   this->::system()->node()->get_call_stack_frames(stack, frame_count);
//
//}
//
//
//CLASS_DECL_ACME ::string get_call_stack_trace(void ** stack, int c, const_char_pointer pszFormat)
//{
//
//   return this->::system()->node()->get_call_stack_trace(stack, c, pszFormat);
//
//}



