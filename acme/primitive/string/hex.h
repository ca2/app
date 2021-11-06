#pragma once



CLASS_DECL_ACME bool ishexdigit(char ch);


namespace hex
{

   CLASS_DECL_ACME string to_asc(const ::string & strHex);
   CLASS_DECL_ACME string from_asc(const string& strAsc);


   CLASS_DECL_ACME i64 to_i64(const char * pcsz);

   CLASS_DECL_ACME u64 to_u64(const string & pcsz);

   CLASS_DECL_ACME u32 to_u32(const ::string & str);

   inline CLASS_DECL_ACME i32 to(char ch);


   inline CLASS_DECL_ACME char nibble_lower_from(byte b)
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


   inline CLASS_DECL_ACME char nibble_upper_from(byte b)
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


   inline CLASS_DECL_ACME void lower_from(char * sz, byte b)
   {

      sz[0] = nibble_lower_from((b >> 4) & (char) 0x0f);
      sz[1] = nibble_lower_from(b & (char) 0x0f);

   }

   inline CLASS_DECL_ACME void upper_from(char * sz, byte b)
   {

      sz[0] = nibble_upper_from((b >> 4) & (char) 0x0f);
      sz[1] = nibble_upper_from(b & (char) 0x0f);

   }


   // sz buffer should have twice size_i32 of s (p)
   inline CLASS_DECL_ACME void lower_from(char * sz, const void * p, memsize s)
   {
       const u8 * pb = (const u8 *) p;
       while(s)
       {
           lower_from(sz, *pb);
		      s--;
           sz+=2;
           pb++;
       }
   }

   inline CLASS_DECL_ACME void upper_from(char * sz, const void * p, memsize s)
   {
       const u8 * pb = (const u8 *) p;
       while(s)
       {
           upper_from(sz, *pb);
		     s--;
           sz+=2;
           pb++;
       }
   }

   // sz buffer should have twice size_i32 of s (p)
   inline CLASS_DECL_ACME string lower_from(const void * p, memsize s)
   {
      string str;
      lower_from(str.get_string_buffer(s * 2), p, s);
      str.release_string_buffer(s * 2);
      return str;
   }


   inline CLASS_DECL_ACME string upper_from(const void * p, memsize s)
   {
      string str;
      upper_from(str.get_string_buffer(s * 2), p, s);
      str.release_string_buffer(s * 2);
      return str;
   }

   inline string upper_from(::i64 i)
   {

      char sz[64];

      __u64toansi((::u64)i, sz, 16);

      ansi_upr(sz);

      return sz;

   }


   inline string lower_from(::i64 i)
   {

      char sz[64];

      __u64toansi((::u64)i, sz, 16);

      ansi_lwr(sz);

      return sz;

   }


   template < typename INTEGER >
   inline string lower_pad_from(INTEGER iValue,int iWidth)
   {
      string str = lower_from(iValue);
      while(str.get_length() < iWidth)
      {
         str = "0" + str;
      }
      return str;
   }

   template < typename INTEGER >
   inline string upper_pad_from(INTEGER iValue,int iWidth)
   {
      string str = upper_from(iValue);
      while(str.get_length() < iWidth)
      {
         str = "0" + str;
      }
      return str;
   }


   inline void to(u32 & u,const ::string & str) { u = to_u32(str); }
   inline void to(u64 & u,const ::string & str) { u = to_u64(str); }
#ifdef __APPLE__
   inline void to(unsigned long & u,const ::string & str) { u = to_u64(str); }
#endif
   inline uptr to_uptr(const ::string & str) { uptr u; to(u,str); return u; }

} // namespace hex

