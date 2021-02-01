#include "framework.h"


stringl::stringl()
{
}

stringl::~stringl()
{
}

void stringl::implode(string & str, const char * pcszSeparator, index start, ::count count) const

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

string stringl::implode(const char * pcszSeparator, index iStart, index iEnd) const

{
   string str;
   implode(str, pcszSeparator, iStart, iEnd);

   return str;
}


void stringl::reverse_implode(string & str, const char * pcszSeparator, index start, ::count count) const

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

string stringl::reverse_implode(const char * pcszSeparator, index iStart, index iEnd) const

{
   string str;
   reverse_implode(str, pcszSeparator, iStart, iEnd);

   return str;
}

void stringl::explode(const char * pcszSeparator, const char * psz)

{
   remove_all();
   add_tail_tokens(psz, pcszSeparator, true);

}


void stringl::add_tail_tokens(const char * pcsz, const char * pcszSeparator, bool bAddEmpty)

{
   ::str::tokenizer strTokenizer(pcsz);

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

