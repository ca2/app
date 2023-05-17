#pragma once


class CLASS_DECL_ACME tokenizer :
   public ::ansi_range
{
public:


   using RANGE = ::ansi_range;
   using const_iterator = RANGE::const_iterator;


   const_iterator      m_iterator;


   tokenizer():m_iterator(nullptr) {}
   tokenizer(const tokenizer & range) : ansi_range(range) {}
   tokenizer(tokenizer && range) : ansi_range(::transfer(range)) { }
   tokenizer(const ::const_ansi_range & range) :
      RANGE(range), m_iterator(range.begin())
   {}
   ~tokenizer() {}


   tokenizer & operator = (const tokenizer & tokenizer)
   {
      
      ::ansi_range::operator=(tokenizer);
      
      return *this;
      
   }
   
   
   tokenizer & operator = (tokenizer && tokenizer)
   {
      
      ::ansi_range::operator=(::transfer(tokenizer));
      
      return *this;
      
   }


   const_iterator find(const ::scoped_string & scopedstrSeparator) const
   { 
      
      auto iterator = (*this)(m_iterator).find(scopedstrSeparator, ::comparison::comparison < ::ansi_character >());
   
      return iterator;
      
   }

   
   ::string & substring(::string & str, strsize count)
   {

      str.assign(m_iterator, count);

      return str;

   }


   ::string & substring(::string & str, const_iterator iterator)
   {

      str.assign(m_iterator, iterator);

      return str;

   }


   ::string & substring(::string & str)
   {

      str.assign(m_iterator, m_end - m_iterator);

      return str;

   }


   template < primitive_range RANGE >
   RANGE & substring(RANGE & range, strsize count)
   {

      range.begin() = m_iterator;
      
      range.end() = range.begin() + count;

      return range;

   }

   
   template < primitive_range RANGE >
   RANGE & substring(RANGE & range, const_iterator iterator)
   {

      range.begin() = m_iterator;
      
      range.end() = iterator;

      return range;

   }

   
   template < primitive_range RANGE >
   RANGE & substring(RANGE & range)
   {

      range.begin() = m_iterator;
      
      range.end() = this->end();

      return range;

   }


   bool ReadLine(::string & str, bool bWithSeparator = false);
   bool _01Read(i32 & i);
   bool _01Read(::u32 & user);
   bool _01ReadHex(i32 & i);
   bool _01ReadHex(::u32 & user);

   bool _01Read(::string & str);
   bool ExtractFolderPath(const ::scoped_string & scopedstrFilePath);

   void reset() { m_iterator = this->begin(); }
   
   void reset(const ::ansi_range & range) { RANGE::operator = (range); reset(); }
   
   bool get_next_token(::string & strToken, const ::scoped_string & scopedstrSeparator, bool bWithSeparator = false);

   bool get_next_smallest_token(::string & strToken, const ::string_array & straSeparator, bool bWithSeparator = false);

   bool get_next_token_ex(::string & strToken, const ::scoped_string & scopedstrSeparator, bool bWithSeparator = false, bool bSkipAdjacent = false);

   bool _001GetNextToken(::string & strToken);

   bool get_next_word(::string * pstrToken = nullptr);

   strsize read(void* p, strsize s)
   {

      auto iRead = minimum(s, this->m_end - m_iterator);

      ::memcpy(p, m_iterator, iRead);

      m_iterator += iRead;

      return iRead;

   }


   template < primitive_range RANGE >
   bool get_line(RANGE & rangeLine)
   {

      if (::is_end(m_iterator, this->end()))
      {

         return false;

      }

      const_iterator iteratorR = find("\r");

      const_iterator iteratorN = find("\n");

      if (::is_ok(iteratorR, this->end()))
      {

         if (::is_ok(iteratorN, this->end()))
         {

            if (iteratorR < iteratorN)
            {

               if (iteratorR + 1 == iteratorN)
               {

                  substring(rangeLine, iteratorR);

                  m_iterator = iteratorN + 1;

               }
               else
               {

                  substring(rangeLine, iteratorR);

                  m_iterator = iteratorR + 1;

               }

            }
            else
            {

               // '\n' < '\r'

               substring(rangeLine, iteratorN);

               m_iterator = iteratorN + 1;

            }

         }
         else
         {

            substring(rangeLine, iteratorR);

            m_iterator = iteratorR + 1;

         }

      }
      else if (::is_ok(iteratorN, this->end()))
      {

         substring(rangeLine, iteratorN);

         m_iterator = iteratorN + 1;

      }
      else
      {

         substring(rangeLine);

         m_iterator = end();

      }

      return true;

   }

   ::count skip_word(::count c);
      
   ::string get_word();
   

};


