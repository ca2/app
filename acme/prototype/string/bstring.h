#pragma once


//class CLASS_DECL_ACME bstring_data
//{
//public:
//
//
//   character_count m_len;
//   character_count m_alloc;
//
//
//};
//
//
//// binary string (may contain nulls)
//class CLASS_DECL_ACME bstring
//{
//public:
//
//   typedef ::u8 value_type;
//
//   value_type * m_puchData;
//
//
//   static bstring s_nil;
//
//
//   bstring();
//
//
//   bstring(bstring_data * pdata);
//
//
//   bstring(const bstring & bstr);
//
//
//   bstring(bstring && bstr);
//
//
//   bstring(character_count s, ::i8 ch);
//
//
//   bstring(const bstring& str, character_count pos, character_count len = -1);
//
//
//   bstring(const ::scoped_string & scopedstr);
//
//
//   bstring(const void * p, character_count start, character_count end);
//
//
//   bstring(const void * p, character_count c);
//
//
//   ~bstring();
//
//
//   character_count get_allocation_size() const
//   {
//
//      return get_bstring_data()->m_len;
//
//   }
//
//   void set_allocation_size(character_count s)
//   {
//
//      get_bstring_data()->m_len = s;
//
//   }
//
//
//   character_count length() const
//   {
//
//      return get_bstring_data()->m_len - 1;
//
//   }
//
//   character_count size() const
//   {
//
//      return length();
//
//   }
//
//   character_count get_length() const
//   {
//
//      return length();
//
//   }
//
//   character_count get_size() const
//   {
//
//      return get_allocation_size();
//
//   }
//
//   void allocate(character_count s);
//   void allocate_add_up(character_count s);
//   void free();
//
//   void append(const ::scoped_string & scopedstr);
//
//   void append(const bstring & bstr);
//
//   void assign(const bstring & bstr);
//
//   void assign(const ::scoped_string & scopedstr)
//   {
//
//      assign(scopedstr, strlen(scopedstr) + 1);
//
//   }
//
//   void reserve(character_count s);
//
//   void assign(const void * p, character_count s, character_count c);
//
//   bstring & assign(const bstring& str, character_count subpos, character_count sublen);
//
//   void assign(const void * p, character_count s);
//
//   bstring & assign(character_count s, ::i8 c);
//
//   bstring & append(character_count s, ::i8 c);
//
//   bstring & erase(character_count s = 0, character_count len = -1);
//
//   void clear();
//
//   void append(const void * p, character_count s);
//
//   character_count copy(value_type * s, character_count len, character_count pos = 0) const;
//
//   bool is_empty() const
//   {
//      return length() <= 0;
//
//   }
//
//
//   bool is_null() const
//   {
//      return length() <= 0;
//
//   }
//
//
//   ::u8 * get_data() const
//   {
//
//      return m_puchData;
//
//   }
//
//
//   bstring_data * get_bstring_data() const
//   {
//
//      return &((bstring_data*)m_puchData)[-1];
//
//   }
//
//
//   void set_bstring_data(bstring_data * pdata)
//   {
//
//      m_puchData = (::u8 *) &pdata[1];
//
//   }
//
//
//   bstring & operator = (const bstring & bstr);
//
//
//   bstring operator + (::i8 ch) const;
//
//
//   bstring operator + (const ::scoped_string & scopedstr) const;
//
//
//   bstring operator + (const bstring & bstr) const;
//
//
//   bstring & operator += (::i8 ch);
//
//
//   bstring & operator += (const ::scoped_string & scopedstr);
//
//
//   bstring & operator += (const ::scoped_string & scopedstr);
//
//
//   bstring & operator += (const bstring & bstr);
//
//
//   const_char_pointer c_str() const;
//
//
//   ::i8 & operator [](character_count i);
//
//
//   const ::i8 & operator [](character_count i) const;
//
//
//   char_pointer get_buffer(character_count s);
//
//
//   void release_buffer(character_count s = -1);
//
//
//   void ReleaseBuffer(character_count s = -1);
//
//
//   ::u8 * data();
//
//
//   const ::u8 * data() const;
//
//
//   bool empty() const;
//
//
//   ::i32 compare(const ::scoped_string & scopedstr) const;
//
//
//   bool operator == (const ::scoped_string & scopedstr) const;
//
//
//   bool operator != (const ::scoped_string & scopedstr) const;
//
//
//   bool operator <= (const ::scoped_string & scopedstr) const;
//
//
//   bool operator < (const ::scoped_string & scopedstr) const;
//
//
//   bool operator >= (const ::scoped_string & scopedstr) const;
//
//
//   bool operator > (const ::scoped_string & scopedstr) const;
//
//
//   ::i32 compare(const bstring & bstr) const;
//
//
//   bool operator != (const bstring & bstr) const;
//
//
//   bool operator == (const bstring & bstr) const;
//
//
//   bool operator <= (const bstring & bstr) const;
//
//
//   bool operator < (const bstring & bstr) const;
//
//
//   bool operator >= (const bstring & bstr) const;
//
//
//   bool operator > (const bstring & bstr) const;
//
//
//};




