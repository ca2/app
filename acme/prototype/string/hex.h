#pragma once





CLASS_DECL_ACME bool ishexdigit(char ch);


namespace hex
{


   CLASS_DECL_ACME string to_asc(const ::string & strHex);
   CLASS_DECL_ACME string from_asc(const string& strAsc);


   CLASS_DECL_ACME huge_integer to_huge_integer(const ::scoped_string & scopedstr);

   CLASS_DECL_ACME huge_natural to_huge_natural(const string & pcsz);

   CLASS_DECL_ACME unsigned int to_unsigned_int(const ::string & str);

   inline CLASS_DECL_ACME int to_nibble(char ch)
   {

      return (ch >= '0' && ch <= '9') ? ch - '0' :
      (
         (ch >= 'a' && ch <= 'f') ? ch - 'a' + 10 :
            (
               (ch >= 'A' && ch <= 'F') ? ch - 'A' + 10 :
                  -1
            )
      );

   }


   constexpr CLASS_DECL_ACME char nibble_lower_case_from(unsigned char b)
   {

      if(b >= 10)
      {
         return b + 'a' - 10;
      }
      else
      {
         return b + '0';
      }

   }


   constexpr CLASS_DECL_ACME char nibble_upper_case_from(unsigned char b)
   {

      if(b >= 10)
      {
         return b + 'A' - 10;
      }
      else
      {
         return b + '0';
      }

   }


   constexpr CLASS_DECL_ACME void lower_case_from(char * sz, unsigned char b)
   {

      sz[0] = nibble_lower_case_from((b >> 4) & (char) 0x0f);
      sz[1] = nibble_lower_case_from(b & (char) 0x0f);

   }

   
   constexpr CLASS_DECL_ACME void upper_case_from(char * sz, unsigned char b)
   {

      sz[0] = nibble_upper_case_from((b >> 4) & (char) 0x0f);
      sz[1] = nibble_upper_case_from(b & (char) 0x0f);

   }


   // sz buffer should have twice int_size of s (p)
   constexpr CLASS_DECL_ACME void lower_case_from(char * sz, const void * p, memsize s)
   {
       const unsigned char * pb = (const unsigned char *) p;
       while(s)
       {
           lower_case_from(sz, *pb);
		      s--;
           sz+=2;
           pb++;
       }
   }

   
   constexpr CLASS_DECL_ACME void upper_case_from(char * sz, const void * p, memsize s)
   {
       const unsigned char * pb = (const unsigned char *) p;
       while(s)
       {
           upper_case_from(sz, *pb);
		     s--;
           sz+=2;
           pb++;
       }
   }


   // sz buffer should have twice int_size of s (p)
   inline string lower_case_from(const void * p, memsize s)
   {
      string str;
      lower_case_from(str.get_buffer(s * 2), p, s);
      str.release_buffer(s * 2);
      return str;
   }


   inline string upper_case_from(const void * p, memsize s)
   {
      string str;
      upper_case_from(str.get_buffer(s * 2), p, s);
      str.release_buffer(s * 2);
      return str;
   }

   
   template < primitive_integral INTEGRAL >
   constexpr auto upper_case_from(INTEGRAL i)
   {

      ::inline_number_string numberstring;

      __tosz(i, numberstring.m_end, 16, e_digit_case_upper);

      return numberstring;

   }


   template < primitive_integral INTEGRAL >
   constexpr auto lower_case_from(INTEGRAL i)
   {

      ::inline_number_string numberstring;

      __tosz(i, numberstring.m_end, 16, e_digit_case_lower);

      return numberstring;

   }


   template < character_count s_iWidth >
   inline auto padded_from(huge_natural u, enum_digit_case edigitcase)
   {

      ::inline_string < char, s_iWidth > numberstring;

      if (u != 0)
      {

         __rear_tosz(u, numberstring.m_end, 16, edigitcase);

      }

      while (numberstring.size() < s_iWidth)
      {

         *numberstring.m_end++ = '0';

      }

      reverse(numberstring.m_begin, numberstring.m_end - 1);

      *numberstring.m_end++ = '0';

      return numberstring;

   }


   template < character_count s_iWidth >
   inline auto lower_case_padded_from(huge_natural u)
   {

      return padded_from < s_iWidth >(u, e_digit_case_lower);

   }


   template < character_count s_iWidth >
   inline auto upper_case_padded_from(huge_natural u)
   {

      return padded_from < s_iWidth >(u, e_digit_case_upper);

   }


   inline void to(unsigned int & u,const ::string & str) { u = to_unsigned_int(str); }
   inline void to(huge_natural & u,const ::string & str) { u = to_huge_natural(str); }
#ifdef __APPLE__
   inline void to(unsigned long & u,const ::string & str) { u = to_huge_natural(str); }
#endif
   inline uptr to_uptr(const ::string & str) { uptr u; to(u,str); return u; }

   unsigned short parse_u16_exc(::const_ansi_range & range);


} // namespace hex




inline bool ishexdigit(char ch)
{
   return (ch >= '0' && ch <= '9')
      || (ch >= 'a' && ch <= 'f')
      || (ch >= 'A' && ch <= 'F');
      //   return true;
      //return false;
}


namespace hex
{


   CLASS_DECL_ACME string lower_case_from(const block & block);

   CLASS_DECL_ACME string upper_case_from(const block & block);


} // namespace hex

