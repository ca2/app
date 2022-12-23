#include "framework.h"
#include "string_list.h"
#include "acme/primitive/string/tokenizer.h"


string_list::string_list()
{
}

string_list::~string_list()
{
}


void string_list::implode(string & str, ::const_ansi_range rangeSeparator, index start, ::count count) const
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

   auto iterator = this->begin() + start;

   for(; i <= last; i++)
   {

      if(i > start)
      {

         str += rangeSeparator;

      }

      str += iterator->element();

      iterator++;

   }

}


string string_list::implode(::const_ansi_range rangeSeparator, index iStart, index iEnd) const
{

   string str;

   implode(str, rangeSeparator, iStart, iEnd);

   return str;

}


void string_list::reverse_implode(string & str, ::const_ansi_range rangeSeparator, index start, ::count count) const

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

   auto iterator = this->end() - i;

   for(index i = last; i >= start; i--)
   {

      if(i < last)
      {
         str += rangeSeparator;
      }

      str += iterator->element();

      iterator--;

   }

}


string string_list::reverse_implode(::const_ansi_range rangeSeparator, index iStart, index iEnd) const
{

   string str;

   reverse_implode(str, rangeSeparator, iStart, iEnd);

   return str;

}


void string_list::explode(::const_ansi_range rangeSeparator, ::const_ansi_range range)
{

   erase_all();

   add_tail_tokens(range, rangeSeparator, true);

}


void string_list::add_tail_tokens(::const_ansi_range range, ::const_ansi_range rangeSeparator, bool bAddEmpty)
{
   
   ::tokenizer tokenizer(range);

   string strToken;

   if(bAddEmpty)
   {

      while(tokenizer.get_next_token(strToken, rangeSeparator, false))
      {

         add_tail(strToken);

      }

   }
   else
   {
      
      while(tokenizer.get_next_token(strToken, rangeSeparator, false))
      {

         if (strToken.has_char())
         {

            add_tail(strToken);

         }

      }

   }

}

