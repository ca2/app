#include "framework.h"
#include "string_list.h"


string_list::string_list()
{
}


string_list::~string_list()
{
}


void string_list::implode(string & str, const ::scoped_string & scopedstrSeparator, index start, ::count count) const
{

   str.empty();

   if(start < 0)
   {

      start += this->get_size();

   }

   index last;

   if(count < 0)
   {

      last = this->get_size() + count;

   }
   else
   {

      last = start + count - 1;

   }

   index i = start;

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


string string_list::implode(const ::scoped_string & scopedstrSeparator, index iStart, index iEnd) const
{

   string str;

   implode(str, scopedstrSeparator, iStart, iEnd);

   return str;

}


void string_list::reverse_implode(string & str, const ::scoped_string & scopedstrSeparator, index start, ::count count) const

{

   str.empty();

   if(start < 0)
   {

      start += this->get_size();

   }

   index last;

   if(count < 0)
   {

      last = this->get_size() + count;

   }
   else
   {

      last = start + count - 1;

   }

   index i = last;

   auto p = this->end() - i;

   for(index i = last; i >= start; i--)
   {

      if(i < last)
      {
         
         str += scopedstrSeparator;
         
      }

      str += *p;

      p--;

   }

}


string string_list::reverse_implode(const ::scoped_string & scopedstrSeparator, index iStart, index iEnd) const
{

   string str;

   reverse_implode(str, scopedstrSeparator, iStart, iEnd);

   return str;

}


void string_list::explode(const ::scoped_string & scopedstrSeparator, const ::scoped_string & scopedstr)
{

   erase_all();

   add_tail_tokens(scopedstr, scopedstrSeparator, true);

}


void string_list::add_tail_tokens(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrSeparator, bool bAddEmpty)
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

         if (strToken.has_char())
         {

            add_tail(strToken);

         }

      }

   }

}

