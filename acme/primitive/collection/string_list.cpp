#include "framework.h"
#include "string_list.h"
#include "acme/primitive/string/tokenizer.h"


string_list::string_list()
{
}

string_list::~string_list()
{
}

void string_list::implode(string & str, const char * pcszSeparator, index start, ::count count) const

{
   str.Empty();
   string strSeparator(pcszSeparator);

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

   auto pos = index_iterator(i);

   for(; i <= last; i++)
   {

      if(i > start)
      {
         str += strSeparator;
      }

      str += *pos;

      pos++;

   }

}

string string_list::implode(const char * pcszSeparator, index iStart, index iEnd) const

{
   string str;
   implode(str, pcszSeparator, iStart, iEnd);

   return str;
}


void string_list::reverse_implode(string & str, const char * pcszSeparator, index start, ::count count) const

{
   str.Empty();
   string strSeparator(pcszSeparator);

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

   auto pos = reverse_index_iterator(i);

   for(index i = last; i >= start; i--)
   {

      if(i < last)
      {
         str += strSeparator;
      }

      str += *pos;

      pos--;

   }

}

string string_list::reverse_implode(const char * pcszSeparator, index iStart, index iEnd) const

{
   string str;
   reverse_implode(str, pcszSeparator, iStart, iEnd);

   return str;
}

void string_list::explode(const char * pcszSeparator, const char * psz)

{
   erase_all();
   add_tail_tokens(psz, pcszSeparator, true);

}


void string_list::add_tail_tokens(const char * pcsz, const char * pcszSeparator, bool bAddEmpty)

{
   ::tokenizer strTokenizer(pcsz);

   string strToken;
   if(bAddEmpty)
   {
      while(strTokenizer.GetNextToken(strToken, pcszSeparator, false))

      {
         add_tail(strToken);
      }
   }
   else
   {
      while(strTokenizer.GetNextToken(strToken, pcszSeparator, false))

      {
         if(strToken.has_char())
            add_tail(strToken);
      }
   }
}

