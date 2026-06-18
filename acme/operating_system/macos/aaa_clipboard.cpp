#include "framework.h"



long mm_clipboard_get_file_count();

char_pointer * mm_clipboard_get_filea(long * pc);

void mm_clipboard_set_filea(const_char_pointer * psza, long c);

char_pointer mm_clipboard_get_plain_text();

void mm_clipboard_set_plain_text(const ::scoped_string & scopedstr);


long macos_clipboard_get_file_count()
{
   
   return mm_clipboard_get_file_count();
   
}


void macos_clipboard_get_filea(::file::path_array & patha)
{
   
   long c = 0;
   
   try
   {
  
      char_pointer * psza = mm_clipboard_get_filea(&c);
      
      patha.c_add(scopedstra, c, false);
      
   }
   catch (...)
   {
      
   }
   
}


void macos_clipboard_set_filea(const ::file::path_array & patha)
{
   
   auto psza = patha.c_ansi_get();
   
   mm_clipboard_set_filea(scopedstra.get_data(), psza.get_count());
   
}


string macos_clipboard_get_plain_text()
{

   return ::string_from_strdup(mm_clipboard_get_plain_text());
   
}


void macos_clipboard_set_plain_text(const ::scoped_string & scopedstrPlainText)
{
   
   mm_clipboard_set_plain_text(scopedstrPlainText);
   
}














