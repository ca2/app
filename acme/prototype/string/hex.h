#pragma once





CLASS_DECL_ACME bool ishexdigit(::i8 ch);


namespace hex
{


   CLASS_DECL_ACME string to_asc(const ::scoped_string & scopedstrHex);
   CLASS_DECL_ACME string from_asc(const ::scoped_string & scopedstrAsc);


   CLASS_DECL_ACME ::i64 to_i64(const ::scoped_string & scopedstr);

   CLASS_DECL_ACME ::u64 to_u64(const ::scoped_string & scopedstr);

   CLASS_DECL_ACME ::u32 to_unsigned_int(const ::scoped_string & scopedstr);

   inline CLASS_DECL_ACME ::i32 to_nibble(::i8 ch)
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


   constexpr CLASS_DECL_ACME ::i8 nibble_lower_case_from(::u8 b)
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


   constexpr CLASS_DECL_ACME ::i8 nibble_upper_case_from(::u8 b)
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


   constexpr CLASS_DECL_ACME void lower_case_from(char_pointer sz, ::u8 b)
   {

      sz[0] = nibble_lower_case_from((b >> 4) & (::i8) 0x0f);
      sz[1] = nibble_lower_case_from(b & (::i8) 0x0f);

   }

   
   constexpr CLASS_DECL_ACME void upper_case_from(char_pointer sz, ::u8 b)
   {

      sz[0] = nibble_upper_case_from((b >> 4) & (::i8) 0x0f);
      sz[1] = nibble_upper_case_from(b & (::i8) 0x0f);

   }


   // sz buffer should have twice i32_size of s (p)
   constexpr CLASS_DECL_ACME void lower_case_from(char_pointer sz, const void * p, memsize s)
   {
       const ::u8 * pb = (const ::u8 *) p;
       while(s)
       {
           lower_case_from(sz, *pb);
		      s--;
           sz+=2;
           pb++;
       }
   }

   
   constexpr CLASS_DECL_ACME void upper_case_from(char_pointer sz, const void * p, memsize s)
   {
       const ::u8 * pb = (const ::u8 *) p;
       while(s)
       {
           upper_case_from(sz, *pb);
		     s--;
           sz+=2;
           pb++;
       }
   }


   // sz buffer should have twice i32_size of s (p)
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

   
   template < prototype_integral INTEGRAL >
   constexpr auto upper_case_from(INTEGRAL i)
   {

      ::inline_number_string numberstring;

      __tosz(i, numberstring.m_end, 16, e_digit_case_upper);

      return numberstring;

   }


   template < prototype_integral INTEGRAL >
   constexpr auto lower_case_from(INTEGRAL i)
   {

      ::inline_number_string numberstring;

      __tosz(i, numberstring.m_end, 16, e_digit_case_lower);

      return numberstring;

   }


   template < character_count s_iWidth >
   inline auto padded_from(::u64 u, enum_digit_case edigitcase)
   {

      ::inline_string < ::i8, s_iWidth > numberstring;

      if (u != 0)
      {

         __rear_tosz(u, numberstring.m_end, 16, edigitcase);

      }

      while (numberstring.size() < s_iWidth)
      {

         *((char_pointer &)numberstring.m_end)++ = '0';

      }

      reverse(((char_pointer )numberstring.m_begin), ((char_pointer )(numberstring.m_end)));

      *((char_pointer &)numberstring.m_end + 1) = '\0';

      return numberstring;

   }


   template < character_count s_iWidth >
   inline auto lower_case_padded_from(::u64 u)
   {

      return padded_from < s_iWidth >(u, e_digit_case_lower);

   }


   template < character_count s_iWidth >
   inline auto upper_case_padded_from(::u64 u)
   {

      return padded_from < s_iWidth >(u, e_digit_case_upper);

   }


   inline void to(::u32 & u,const ::scoped_string & scopedstr) { u = to_unsigned_int(scopedstr); }
   inline void to(::u64 & u,const ::scoped_string & scopedstr) { u = to_u64(scopedstr); }
#ifdef __APPLE__
   inline void to(ulong & u,const ::scoped_string & scopedstr) { u = to_u64(scopedstr); }
#endif
   inline uptr to_uptr(const ::scoped_string & scopedstr) { uptr u; to(u,scopedstr); return u; }

   ::u16 parse_u16_exc(::const_ansi_range & range);


} // namespace hex




inline bool ishexdigit(::i8 ch)
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

