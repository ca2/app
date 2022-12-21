#pragma once


//class CLASS_DECL_ACME bstring_data
//{
//public:
//
//
//   strsize m_len;
//   strsize m_alloc;
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
//   typedef byte value_type;
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
//   bstring(strsize s, char ch);
//
//
//   bstring(const bstring& str, strsize pos, strsize len = -1);
//
//
//   bstring(const ::scoped_string & scopedstr);
//
//
//   bstring(const void * p, strsize start, strsize end);
//
//
//   bstring(const void * p, strsize c);
//
//
//   ~bstring();
//
//
//   strsize get_allocation_size() const
//   {
//
//      return get_bstring_data()->m_len;
//
//   }
//
//   void set_allocation_size(strsize s)
//   {
//
//      get_bstring_data()->m_len = s;
//
//   }
//
//
//   strsize length() const
//   {
//
//      return get_bstring_data()->m_len - 1;
//
//   }
//
//   strsize size() const
//   {
//
//      return length();
//
//   }
//
//   strsize get_length() const
//   {
//
//      return length();
//
//   }
//
//   strsize get_size() const
//   {
//
//      return get_allocation_size();
//
//   }
//
//   void allocate(strsize s);
//   void allocate_add_up(strsize s);
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
//      assign(psz, strlen(psz) + 1);
//
//   }
//
//   void reserve(strsize s);
//
//   void assign(const void * p, strsize s, strsize c);
//
//   bstring & assign(const bstring& str, strsize subpos, strsize sublen);
//
//   void assign(const void * p, strsize s);
//
//   bstring & assign(strsize s, char c);
//
//   bstring & append(strsize s, char c);
//
//   bstring & erase(strsize s = 0, strsize len = -1);
//
//   void clear();
//
//   void append(const void * p, strsize s);
//
//   strsize copy(value_type * s, strsize len, strsize pos = 0) const;
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
//   u8 * get_data() const
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
//      m_puchData = (u8 *) &pdata[1];
//
//   }
//
//
//   bstring & operator = (const bstring & bstr);
//
//
//   bstring operator + (char ch) const;
//
//
//   bstring operator + (const ::scoped_string & scopedstr) const;
//
//
//   bstring operator + (const bstring & bstr) const;
//
//
//   bstring & operator += (char ch);
//
//
//   bstring & operator += (const ::scoped_string & scopedstr);
//
//
//   bstring & operator += (const ::string & str);
//
//
//   bstring & operator += (const bstring & bstr);
//
//
//   const char * c_str() const;
//
//
//   char & operator [](strsize i);
//
//
//   const char & operator [](strsize i) const;
//
//
//   char * get_string_buffer(strsize s);
//
//
//   void release_string_buffer(strsize s = -1);
//
//
//   void ReleaseBuffer(strsize s = -1);
//
//
//   u8 * data();
//
//
//   const u8 * data() const;
//
//
//   bool empty() const;
//
//
//   int compare(const ::scoped_string & scopedstr) const;
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
//   int compare(const bstring & bstr) const;
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




