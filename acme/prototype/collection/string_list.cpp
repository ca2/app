#include "framework.h"
#include "acme/prototype/collection/string_list.h"


//string_list_base::string_list_base()
//{
//}
//
//
//string_list_base::~string_list_base()
//{
//}


void string_list_base::implode(string & str, const ::scoped_string & scopedstrSeparator, ::collection::index start, ::collection::count count) const
{

   str.empty();

   if(start < 0)
   {

      start += this->get_size();

   }

   ::collection::index last;

   if(count < 0)
   {

      last = this->get_size() + count;

   }
   else
   {

      last = start + count - 1;

   }

   ::collection::index i = start;

   auto p = this->begin() + start;

   for(; i <= last; i++)
   {

      if(i > start)
      {

         str += scopedstrSeparator;

      }

      str += *p;

      p++;

   }

}


string string_list_base::implode(const ::scoped_string & scopedstrSeparator, ::collection::index iStart, ::collection::index iEnd) const
{

   string str;

   implode(str, scopedstrSeparator, iStart, iEnd);

   return str;

}


void string_list_base::reverse_implode(string & str, const ::scoped_string & scopedstrSeparator, ::collection::index start, ::collection::count count) const

{

   str.empty();

   if(start < 0)
   {

      start += this->get_size();

   }

   ::collection::index last;

   if(count < 0)
   {

      last = this->get_size() + count;

   }
   else
   {

      last = start + count - 1;

   }

   ::collection::index i = last;

   auto p = this->end() - i;

   for(::collection::index i = last; i >= start; i--)
   {

      if(i < last)
      {
         
         str += scopedstrSeparator;
         
      }

      str += *p;

      p--;

   }

}


string string_list_base::reverse_implode(const ::scoped_string & scopedstrSeparator, ::collection::index iStart, ::collection::index iEnd) const
{

   string str;

   reverse_implode(str, scopedstrSeparator, iStart, iEnd);

   return str;

}


void string_list_base::explode(const ::scoped_string & scopedstrSeparator, const ::scoped_string & scopedstr)
{

   erase_all();

   add_tail_tokens(scopedstr, scopedstrSeparator, true);

}


void string_list_base::add_tail_tokens(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrSeparator, bool bAddEmpty)
{
   
   ::tokenizer tokenizer(scopedstr);

   string strToken;

   if(bAddEmpty)
   {

      while(tokenizer.get_next_token(strToken, scopedstrSeparator, false))
      {

         add_tail(strToken);

      }

   }
   else
   {
      
      while(tokenizer.get_next_token(strToken, scopedstrSeparator, false))
      {

         if (strToken.has_character())
         {

            add_tail(strToken);

         }

      }

   }

}

