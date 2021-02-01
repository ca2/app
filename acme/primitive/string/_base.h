#pragma once

template < typename CHAR_TYPE >
class string_iterator
{
public:

   const CHAR_TYPE *         m_psz;

   string_iterator(const CHAR_TYPE * psz) : m_psz(psz) { }
   string_iterator(const CHAR_TYPE * psz, strsize size) : m_psz(psz + size) { }

   ::i32 operator *(){return ::str::ch::uni_index(m_psz); }

   string_iterator & operator ++()
   {

      m_psz = ::str::char_next(m_psz);

      return *this;

   }

   string_iterator operator ++(int)
   {

      auto psz = m_psz;

      m_psz = ::str::char_next(m_psz);

      return psz;

   }

   bool operator == (const string_iterator & it) const { return m_psz == it.m_psz;}

   bool operator != (const string_iterator & it) const { return !operator==(it);}

};


template < typename TYPE_CHAR >
class string_base :
   public natural_pointer < string_meta_data < TYPE_CHAR > >,
   public string_type < string_base < TYPE_CHAR > >
{
public:


   using CHAR_TYPE = TYPE_CHAR;
   typedef natural_pointer < string_meta_data < TYPE_CHAR > >     POINTER;
   typedef string_array_base < string_base >                           STRINGA;


   string_base() { }
   string_base(enum_no_initialize) : POINTER(e_no_initialize) { }
   string_base(nullptr_t) { }
   string_base(for_moving) { }
   string_base(e_get_buffer, strsize len) { get_string_buffer(len); }
   string_base(string_base && s) : string_base(e_no_initialize) { this->m_pdata = s.m_pdata; s.m_pdata = nullptr; }

   template < has_to_string HAS_TO_STRING >
   string_base(const HAS_TO_STRING & has_to_string) : string_base(has_to_string.to_string()) { }
   //template < has_to_string HAS_TO_STRING >
   //string_base(HAS_TO_STRING& has_to_string) : string_base(has_to_string.to_string()) { }

   string_base(const ansichar * pansichar);
   string_base(const ansichar * pansichar, strsize len);
   string_base(const ansichar * pansichar, strsize len, strsize pos) : string_base(pansichar + pos, len) { }
   string_base(const block & block);
   string_base(const wd16char * pwd16char);
   string_base(const wd16char * pwd16char, strsize len);
   string_base(const wd16char * pwd16char, strsize len, strsize pos) : string_base(pwd16char + pos, len) { }
   string_base(const wd32char * pwd32char);
   string_base(const wd32char * pwd32char, strsize len);
   string_base(const wd32char * pwd32char, strsize len, strsize pos) : string_base(pwd32char + pos, len) { }
#ifdef WINDOWS
   explicit string_base(const USHORT * pszSrc) : string_base((const wd16char * )pszSrc) {}
#endif
   string_base(const ansistring & wd32str);
   string_base(const wd16string & wd16str);
   string_base(const wd32string & wd32str);
   string_base(const natural_ansistring& ansistr);
   string_base(const natural_wd16string& wd16str);
   string_base(const natural_wd32string& wd32str);
   string_base(ansichar ansich, strsize repeat = 1);
   string_base(wd16char wd16ch, strsize repeat = 1);
   string_base(wd32char wd32ch, strsize repeat = 1);
   
#ifdef _UWP
   string_base(Array <byte > ^ a);
   string_base(Object ^ o);
#endif

   //string_base(const ::payload & payload);
   //string_base(const property & property);
   //string_base(const id & id);
   //string_base(::payload & payload);
   //string_base(property & property);
   //string_base(id & id);


   inline const string_base & to_string() const { return *this; }

   inline CHAR_TYPE * data() { return this->m_pdata; }

   inline const CHAR_TYPE * data() const { return this->m_pdata; }

   inline const CHAR_TYPE * c_str() const { return this->m_pdata; }

   inline operator const CHAR_TYPE * () const { return this->m_pdata; }

   inline operator CHAR_TYPE * () { return this->m_pdata; }

   inline const CHAR_TYPE * ptr_at(::index i) { return this->m_pdata + i; }
   inline const CHAR_TYPE * ptr_at(::index i) const { return this->m_pdata + i; }

   inline const CHAR_TYPE * reverse_ptr(::index i) { return this->m_pdata + length() + i; }
   inline const CHAR_TYPE * reverse_ptr(::index i) const { return this->m_pdata + length() + i; }

   inline const CHAR_TYPE & operator [](index i) const { return this->m_pdata[i]; }

#if OSBIT == 64
   inline const CHAR_TYPE & operator [](int i) const { return this->m_pdata[i]; }
#endif

   inline CHAR_TYPE get_at(strsize i) const { return this->m_pdata[i]; }

   //inline operator const CHAR_TYPE* () const noexcept { return this->m_pdata; }

#if defined(_UWP) 
   inline operator String ^ () const { return ref new String(wd16string(*this)); }
#endif

   auto to_string_base() const { return *this; }
   const auto & to_string_base() { return *this; }

   string_base & operator = (const ansichar * pansichar);
   string_base & operator = (const wd16char * pwd16char);
   string_base & operator = (const wd32char * pwd32char);
   string_base & operator = (const natural_ansistring & ansistr);
   string_base & operator = (const natural_wd16string & wd16str);
   string_base & operator = (const natural_wd32string & wd32str);
   string_base & operator = (const ansistring & ansistr);
   string_base & operator = (const wd16string & wd16str);
   string_base & operator = (const wd32string & wd32str);
   string_base & operator = (ansichar ansich);
   string_base & operator = (wd16char wd16ch);
   string_base & operator = (wd32char wd32ch);
#ifdef WINDOWS
   string_base & operator = (const USHORT * pshSrc) { return operator=((const wd16char *)pshSrc); }
#endif
#ifdef _UWP
   string_base& operator = (String^& str) { return operator=(str->Begin()); }
#endif

   template < int t_nSize >
   inline string_base & operator=(const static_string<CHAR_TYPE, t_nSize > & ansistrSrc);

   template < typename TYPE >
   inline string_base & operator=(const TYPE & t);


   string_base & operator += (const ansichar * pszSrc);
   string_base & operator += (const wd16char * pszSrc);
   string_base & operator += (const wd32char * pszSrc);
   string_base & operator += (const ansistring & ansistr);
   string_base & operator += (const wd16string & wd16str);
   string_base & operator += (const wd32string & wd32str);
   string_base & operator += (ansichar ansich);
   string_base & operator += (wd16char wd16ch);
   string_base & operator += (wd32char wd32ch);
#ifdef WINDOWS
   string_base & operator += (const USHORT * pshSrc) { return operator=((const wd16char *)pshSrc); }
#endif

   template < int t_nSize >
   inline string_base & operator +=(const static_string<CHAR_TYPE, t_nSize > & ansistrSrc);

   template < typename TYPE >
   inline string_base & operator +=(const TYPE & t);


   string_base operator + (const ansichar * pszSrc) const;
   string_base operator + (const wd16char * pszSrc) const;
   string_base operator + (const wd32char * pszSrc) const;
   string_base operator + (const ansistring & ansistr) const;
   string_base operator + (const wd16string & wd16str)  const;
   string_base operator + (const wd32string & wd32str)  const;
   string_base operator + (ansichar ansich)  const;
   string_base operator + (wd16char wd16ch)  const;
   string_base operator + (wd32char wd32ch)  const;
#ifdef WINDOWS
   string_base operator + (const USHORT * pshSrc) const { return operator +((const wd16char *)pshSrc); }
#endif

   //template < typename TYPE >
   //inline string_base operator +(const TYPE & t) const;

   template < typename TYPE >
   inline string_base & operator /=(const TYPE & t)
   {

      string_base strRight(t);

      trim_right("\\/");

      strRight.trim_left("\\/");

      return this->operator += ("/" + strRight);

   }


   template < typename TYPE >
   inline string_base operator /(const TYPE & t) const
   {

      string str(*this);

      str /= t;

      return str;

   }


   inline string_base & assign(const ansistring & ansistr);
   inline string_base & assign(const ansistring & ansistr, strsize pos, strsize n);
   inline string_base & assign(const wd16string & wd16str);
   inline string_base & assign(const wd16string & wd16str, strsize pos, strsize n);
   inline string_base & assign(const wd32string & wd32str);
   inline string_base & assign(const wd32string & wd32str, strsize pos, strsize n);
   inline string_base & assign(const ansichar * pansiszSrc);
   inline string_base & assign(const ansichar * pansiszSrc, strsize len);
   inline string_base & assign(const wd16char * pwd16szSrc);
   inline string_base & assign(const wd16char * pwd16szSrc, strsize len);
   inline string_base & assign(const wd32char * pwd32szSrc);
   inline string_base & assign(const wd32char * pwd32szSrc, strsize len);
   inline string_base & assign(ansichar ansich);
   inline string_base & assign(wd16char wd16ch);
   inline string_base & assign(wd32char wd32ch);
   inline string_base & assign(ansichar ansich, strsize repeat);
   inline string_base & assign(wd16char wd16ch, strsize repeat);
   inline string_base & assign(wd32char wd32ch, strsize repeat);

   template <class InputIterator>
   inline string_base & assign(InputIterator first, InputIterator last);

   template < int t_nSize >
   inline string_base & assign(const static_string<CHAR_TYPE, t_nSize > & ansistrSrc);

   inline string_base & append(strsize len, CHAR_TYPE ch);


   inline string_base & append(ansichar ch);
   inline string_base & append(const ansichar * pszSrc);
   inline string_base & append(const ansichar * pszSrc, strsize nLength);
   inline string_base & append(const ansistring & ansistrSrc);

   inline string_base & append(wd16char wch);
   inline string_base & append(const wd16char * pszSrc);
   inline string_base & append(const wd16char * pszSrc, strsize nLength);
   inline string_base & append(const wd16string & ansistrSrc);

   inline string_base & append(wd32char wch);
   inline string_base & append(const wd32char * pszSrc);
   inline string_base & append(const wd32char * pszSrc, strsize nLength);
   inline string_base & append(const wd32string & ansistrSrc);

   template < typename STATIC_TYPE_CHAR, int t_nSize >
   inline string_base& append(const static_string<STATIC_TYPE_CHAR, t_nSize > & ansistrSrc);



   inline void Empty() noexcept
   {

      if (this->has_char())
      {

         this->natural_release();

      }

   }


   CHAR_TYPE* get_string_buffer()
   {

      auto p = this->metadata();

      if (p->natural_is_shared())
      {

         fork_string(p->length());

      }

      return this->m_pdata;

   }


   CHAR_TYPE * get_string_buffer(strsize size)
   {

      auto p = this->metadata();

      if (::is_null(p) || p->natural_is_shared() || size > p->length())
      {

         fork_string(size);

      }

      this->metadata()->set_length(size);

      return this->m_pdata;

   }


   CHAR_TYPE* defer_get_string_buffer(strsize size, const CHAR_TYPE * psz)
   {

      auto p = this->metadata();

      if (::is_null(p) || p->natural_is_shared() || size > p->length() || p->contains_data(psz))
      {

         fork_string(size);

      }

      this->metadata()->set_length(size);

      return this->m_pdata;

   }


   inline strsize get_upper_bound(strsize i = -1) const noexcept { return this->get_length() + i; }

   inline void get_string(CHAR_TYPE* psz) const noexcept { ::str::copy_chars(psz, this->m_pdata, length()); }

   inline const CHAR_TYPE* get_string() const noexcept { return this->m_pdata; }

   inline bool is_empty() const noexcept { return *this->m_pdata == '\0'; }

   template < typename TYPE >
   inline bool is_empty(const TYPE& t)
   {
      if (!is_empty()) return false;
      operator =(t);
      return true;
   }

   inline static string_base empty_string() { return string_base(); }

   inline bool empty() const noexcept  { return this->is_empty(); }

   inline bool has_char() const noexcept { return !this->is_empty(); }

   string_base & release_string_buffer(strsize nNewLength = -1)
   {

      if (nNewLength == -1)
      {

         nNewLength = ::str::string_safe_length(this->m_pdata);

      }

      this->metadata()->set_length(nNewLength);

      return *this;

   }

//   inline void release_string_buffer(strsize nNewLength);
   inline void truncate(strsize nNewLength);
   inline void set_at(strsize iChar, CHAR_TYPE ch);

   CHAR_TYPE * fork_string(strsize strsize)
   {

      auto memsize = ::str::char_length_to_byte_length(this->m_pdata, strsize + 1);

      auto pNew = this->create_meta_data(memsize);

      auto pOld = this->metadata();

      if (::is_set(pOld))
      {

         auto memsizeOld = pOld->memsize();

         if (memsizeOld > 0)
         {

            auto memsizeCopy = min(memsizeOld, memsize);

            memcpy_dup(pNew->get_data(), pOld->get_data(), memsizeCopy);

         }

      }

      pNew->set_length(strsize);

      this->assign_natural_meta_data(pNew);

      pNew->natural_dec_ref();

      return pNew->get_data();

   }


   void prepare_write(strsize nLength)
   {

      auto p = this->metadata();

      if (p->natural_is_shared() || nLength >= this->get_storage_length())
      {

         fork_string(nLength);

      }

   }

   string_base if_empty(string_base ansistr) { return is_empty() ? ansistr : *this; }


//#if defined(_UWP) && defined(__cplusplus_winrt)
//   inline operator String ^ () const;
//   inline operator String ^ ();
//#endif
//

   void construct() noexcept;


   void push_back(CHAR_TYPE ch);



   i32 compare(const CHAR_TYPE * psz) const noexcept;
   i32 compare_ci(const CHAR_TYPE * psz) const noexcept;
   i32 collate(const CHAR_TYPE * psz) const noexcept;
   i32 collate_ci(const CHAR_TYPE * psz) const noexcept;

   i32 compare(const CHAR_TYPE * psz, strsize n) const noexcept;
   i32 compare_ci(const CHAR_TYPE * psz, strsize n) const noexcept;
   i32 collate(const CHAR_TYPE * psz, strsize n) const noexcept;
   i32 collate_ci(const CHAR_TYPE * psz, strsize n) const noexcept;

   i32 compare(strsize iStart, strsize iCount, const CHAR_TYPE * psz) const noexcept;
   i32 compare_ci(strsize iStart, strsize iCount, const CHAR_TYPE * psz) const noexcept;
   i32 collate(strsize iStart, strsize iCount, const CHAR_TYPE * psz) const noexcept;
   i32 collate_ci(strsize iStart, strsize iCount, const CHAR_TYPE * psz) const noexcept;

   i32 compare(strsize iStart, strsize iCount, const CHAR_TYPE * psz, strsize iStart2, strsize iCount2) const noexcept;
   i32 compare_ci(strsize iStart, strsize iCount, const CHAR_TYPE * psz, strsize iStart2, strsize iCount2) const noexcept;
   i32 collate(strsize iStart, strsize iCount, const CHAR_TYPE * psz, strsize iStart2, strsize iCount2) const noexcept;
   i32 collate_ci(strsize iStart, strsize iCount, const CHAR_TYPE * psz, strsize iStart2, strsize iCount2) const noexcept;


   inline bool operator==(const string_base & ansistr) const { return compare(ansistr) == 0; }
   inline bool operator>(const string_base & ansistr) const { return compare(ansistr) > 0; }
   inline bool operator<(const string_base & ansistr) const { return compare(ansistr) < 0; }
   inline bool operator!=(const string_base & ansistr) const { return !operator ==(ansistr); }
   inline bool operator>=(const string_base & ansistr) const { return !operator <(ansistr); }
   inline bool operator<=(const string_base & ansistr) const { return !operator >(ansistr); }


   inline bool contains(CHAR_TYPE ch, strsize start = 0, strsize count = -1) const;
   inline bool contains(const CHAR_TYPE* psz, strsize start = 0, strsize count = -1) const;
   inline bool contains(const string_base& ansistr, strsize start = 0, strsize count = -1) const;
   inline bool contains(CHAR_TYPE ch, strsize start, strsize count, const CHAR_TYPE ** ppszBeg) const;
   inline bool contains(const CHAR_TYPE * psz, strsize start, strsize count, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd = nullptr) const;
   inline bool contains(const string_base & ansistr, strsize start, strsize count, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd = nullptr) const;
   inline bool contains_any(const STRINGA & stra) const;
   inline bool contains_all(const STRINGA & stra) const;

   inline bool contains_ci(CHAR_TYPE ch, strsize start = 0, strsize count = -1) const;
   inline bool contains_ci(const CHAR_TYPE * psz, strsize start = 0, strsize count = -1) const;
   inline bool contains_ci(const string_base & ansistr, strsize start = 0, strsize count = -1) const;
   inline bool contains_ci(CHAR_TYPE ch, strsize start, strsize count, const CHAR_TYPE ** ppszBeg) const;
   inline bool contains_ci(const CHAR_TYPE* psz, strsize start, strsize count, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd = nullptr) const;
   inline bool contains_ci(const string_base& ansistr, strsize start, strsize count, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd = nullptr) const;
   inline bool contains_any_ci(const STRINGA & stra) const;
   inline bool contains_all_ci(const STRINGA& stra) const;


   //inline bool contains_wci(CHAR_TYPE ch, strsize start = 0, strsize count = -1) const;
   inline bool contains_wci(const CHAR_TYPE * psz, strsize start = 0, strsize count = -1) const;
   inline bool contains_wci(const string_base & ansistr, strsize start = 0, strsize count = -1) const;
   //inline bool contains_wci(CHAR_TYPE ch, strsize start, strsize count, const CHAR_TYPE ** ppszBeg) const;
   inline bool contains_wci(const CHAR_TYPE* psz, strsize start, strsize count, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd = nullptr) const;
   inline bool contains_wci(const string_base& ansistr, strsize start, strsize count, const CHAR_TYPE ** ppszBeg, const CHAR_TYPE ** ppszEnd = nullptr) const;
   inline bool contains_any_wci(const STRINGA & stra) const;
   inline bool contains_all_wci(const STRINGA & stra) const;


   void reserve(strsize res_arg = 0);

   // Delete 'nCount' characters, starting at index 'iIndex'
   strsize Delete(strsize iIndex, strsize nCount = 1);
   strsize remove(strsize iIndex, strsize nCount = 1);

   string_base& erase(strsize start = 0, strsize count = -1);


   template < typename PRED >
   bool is_every_char(PRED pred)
   {

      for (index i = 0; i < this->length(); i++)
      {

         if (!pred(this->operator[](i)))
         {

            return false;

         }

      }

      return true;

   }


   template < typename NUMBER >
   NUMBER& translate_index(NUMBER& number)
   {

      if (number < 0)
      {

         number += this->get_length() + 1;

         if (number < 0)
         {

            number = 0;

         }

      }
      else if (number > this->get_length())
      {

         number = this->get_length();

      }

      return number;

   }

   // Insert character 'ch' before index 'iIndex'
   strsize Insert(strsize iIndex, CHAR_TYPE ch);

   // Insert string_base 'psz' before index 'iIndex'
   strsize Insert(strsize iIndex, const CHAR_TYPE* psz);

   // replace all occurrences of character 'chOld' with character 'chNew'
   strsize replace(CHAR_TYPE chOld, CHAR_TYPE chNew, strsize iStart = 0);

   // replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
   template < pointer_castable < TYPE_CHAR > PCHAR1, pointer_castable < TYPE_CHAR > PCHAR2 >
   strsize replace(PCHAR1 pchar1, PCHAR2 pchar2, strsize iStart = 0);

   template < pointer_castable < TYPE_CHAR > PCHAR1, pointer_castable < TYPE_CHAR > PCHAR2 >
   strsize replace_ci(PCHAR1 pchar1, PCHAR2 pchar2, strsize iStart = 0);

   // replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
   template < pointer_castable < TYPE_CHAR > PCHAR1, pointer_castable < TYPE_CHAR > PCHAR2 >
   ::count replace_count(PCHAR1 pchar1, PCHAR2 pchar2, strsize iStart = 0);

   template < pointer_castable < TYPE_CHAR > PCHAR1, pointer_castable < TYPE_CHAR > PCHAR2 >
   ::count replace_ci_count(PCHAR1 pchar1, PCHAR2 pchar2, strsize iStart = 0);

   //::count utf8_replace(const CHAR_TYPE* pszOld, const CHAR_TYPE* pszNew, strsize iStart = 0);

   string_base& replace(strsize iStart, strsize nCount, const CHAR_TYPE* psz);
   string_base& replace(strsize iStart, strsize nCount, const CHAR_TYPE* psz, strsize nLen);

   // remove all occurrences of character 'chRemove'
   strsize remove(CHAR_TYPE chRemove);

   template < pointer_castable < TYPE_CHAR > PCHAR >
   string_base Tokenize(PCHAR pszTokens, strsize& iStart) const;
   // find routines

   // find the first occurrence of character 'ch', starting at index 'iStart'
   strsize find(CHAR_TYPE ch) const RELEASENOTHROW;
   strsize find(CHAR_TYPE ch, strsize start) const RELEASENOTHROW;
   strsize find(CHAR_TYPE ch, strsize start, strsize count) const RELEASENOTHROW;
   strsize find_ci(CHAR_TYPE ch, strsize start = 0, strsize count = -1) const RELEASENOTHROW;

   strsize find_skip_or_length(CHAR_TYPE ch, strsize start = 0) const RELEASENOTHROW
   {

      while (true)
      {

         if (this->m_pdata[start] == '\0')
         {

            return start;

         }

         if (this->m_pdata[start] == ch)
         {

            start++;

            return start;

         }

         start++;

      }

   }

   strsize find_whitespace_or_length(strsize start = 0) const RELEASENOTHROW;

   // look for a specific sub-string_base

   // find the first occurrence of string_base 'pszSub', starting at index 'iStart'
   strsize find(const CHAR_TYPE* pszSub, strsize start = 0, strsize count = -1, const CHAR_TYPE** pszTail = nullptr) const RELEASENOTHROW;
   strsize find_w(const CHAR_TYPE* pszSub, strsize start = 0, strsize count = -1, const CHAR_TYPE** pszTail = nullptr) const RELEASENOTHROW;
   strsize find_ci(const CHAR_TYPE* pszSub, strsize start = 0, strsize count = -1, const CHAR_TYPE** pszTail = nullptr) const RELEASENOTHROW;
   strsize find_wci(const CHAR_TYPE* pszSub, strsize start = 0, strsize count = -1, const CHAR_TYPE** pszTail = nullptr) const RELEASENOTHROW;

   // find the first occurrence of string_base 'pszSub', starting at index 'iStart', if found returns the index of first character after the end of the found string_base
   strsize find_tail(const CHAR_TYPE* pszSub, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize find_w_tail(const CHAR_TYPE* pszSub, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize find_ci_tail(const CHAR_TYPE* pszSub, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize find_wci_tail(const CHAR_TYPE* pszSub, strsize start = 0, strsize count = -1) const RELEASENOTHROW;

   // find the first occurrence of any of the characters in string_base 'pszCharSet'
   strsize FindOneOf(const CHAR_TYPE* pszCharSet, strsize iStart = 0, strsize n = -1) const RELEASENOTHROW;

   strsize find_first_in(const string_base& ansistr, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_in(const CHAR_TYPE* s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_first_in(const CHAR_TYPE* s, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_in(CHAR_TYPE ca, strsize pos = 0) const RELEASENOTHROW;

   strsize find_first_not_in(const string_base& ansistr, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_not_in(const CHAR_TYPE* s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_first_not_in(const CHAR_TYPE* s, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_not_in(CHAR_TYPE ca, strsize pos = 0) const RELEASENOTHROW;

   strsize find_last_not_in(const string_base& ansistr, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_not_in(const CHAR_TYPE* s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_last_not_in(const CHAR_TYPE* s, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_not_in(CHAR_TYPE ca, strsize pos = -1) const RELEASENOTHROW;

   strsize find_last_in(const string_base& ansistr, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_in(const CHAR_TYPE* s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_last_in(const CHAR_TYPE* s, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_in(CHAR_TYPE ca, strsize pos = -1) const RELEASENOTHROW;

   strsize find_first_of(const string_base& ansistr, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_of(const CHAR_TYPE* s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_first_of(const CHAR_TYPE* s, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_of(CHAR_TYPE ca, strsize pos = 0) const RELEASENOTHROW;

   strsize find_first_not_of(const string_base& ansistr, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_not_of(const CHAR_TYPE* s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_first_not_of(const CHAR_TYPE* s, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_not_of(CHAR_TYPE ca, strsize pos = 0) const RELEASENOTHROW;

   strsize find_last_not_of(const string_base& ansistr, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_not_of(const CHAR_TYPE* s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_last_not_of(const CHAR_TYPE* s, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_not_of(CHAR_TYPE ca, strsize pos = -1) const RELEASENOTHROW;

   strsize find_last_of(const string_base& ansistr, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_of(const CHAR_TYPE* s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_last_of(const CHAR_TYPE* s, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_of(CHAR_TYPE ca, strsize pos = -1) const RELEASENOTHROW;

   // find the last occurrence of character 'ch'
   strsize reverse_find(CHAR_TYPE ch, strsize iStart = -1) const RELEASENOTHROW;

   // find the last occurrence of string_base 'sz'
   strsize reverse_find(const CHAR_TYPE* sz, strsize iStart = -1) const RELEASENOTHROW;

   strsize rfind(CHAR_TYPE ch, strsize iStart = -1) const RELEASENOTHROW
   {
      return reverse_find(ch, iStart);
   };
   strsize rfind(const CHAR_TYPE* sz, strsize iStart = -1) const RELEASENOTHROW
   {
      return reverse_find(sz, iStart);
   };

   string_base intersection(const string_base & find) const;


   string_base ansistr() const
   {
      return *this;
   }


   string_iterator < CHAR_TYPE > begin() const
   {

      return string_iterator < CHAR_TYPE >(c_str());

   }


   string_iterator < CHAR_TYPE > end() const
   {

      return string_iterator < CHAR_TYPE >(c_str(), get_length());

   }


   inline bool begins(const string_base& ansistr) const;
   inline bool ends(const string_base& ansistr) const;

   inline bool begins_ci(const string_base& ansistr) const;
   inline bool ends_ci(const string_base& ansistr) const;

   inline bool begins_eat(const string_base& ansistr);
   inline bool ends_eat(const string_base& ansistr);

   inline bool begins_eat_ci(const string_base& ansistr);
   inline bool ends_eat_ci(const string_base& ansistr);

   inline string_base& ensure_begins(const string_base& strPrefix);
   inline string_base& ensure_begins_ci(const string_base& strPrefix);

   inline string_base& ensure_ends(const string_base& strSuffix);
   inline string_base& ensure_ends_ci(const string_base& strSuffix);

   bool eat_before(string_base& strBefore, string_base strSeparator, bool bEatEverythingIfNotFound = false);
   bool eat_before_let_separator(string_base& strBefore, string_base strSeparator, bool bEatEverythingIfNotFound = false);

   CHAR_TYPE last_char(strsize count = -1) const;

   // manipulation

   // Convert the string_base to uppercase
   string_base& make_upper();

   // Convert the string_base to lowercase
   string_base& make_lower();

   // Reverse the string_base
   string_base& MakeReverse();

   string_base lower() const;

   string_base upper() const;


   // Convert the string_base to uppercase
   string_base uppered() const;

   // Convert the string_base to lowercase
   string_base lowered() const;

   // Convert the string_base to lowercase
   string_base reversed() const;

   // trimming

   // remove all trailing whitespace
   string_base& trim_right();

   // remove all leading whitespace
   string_base& trim_left();

   // remove all leading and trailing whitespace
   string_base& trim();

   // remove all leading and trailing occurrences of character 'chTarget'
   string_base& trim(CHAR_TYPE chTarget);

   // remove all leading and trailing occurrences of any of the characters in the string_base 'pszTargets'
   template < pointer_castable < TYPE_CHAR > PCHAR >
   string_base & trim(PCHAR pcharTargets);

   // trimming anything (either side)

   // remove all trailing occurrences of character 'chTarget'
   string_base& trim_right(CHAR_TYPE chTarget);

   // remove all trailing occurrences of any of the characters in string_base 'pszTargets'
   template < pointer_castable < TYPE_CHAR > PCHAR >
   string_base & trim_right(PCHAR pcharTargets);

   // remove all leading occurrences of character 'chTarget'
   string_base& trim_left(CHAR_TYPE chTarget);

   // remove all leading occurrences of any of the characters in string_base 'pszTargets'
   template < pointer_castable < TYPE_CHAR > PCHAR >
   string_base& trim_left(PCHAR pchTargets);


   // remove all trailing whitespace
   string_base right_trimmed() const;

   // remove all leading whitespace
   string_base left_trimmed() const;

   // remove all leading and trailing whitespace
   string_base trimmed() const;

   // remove all leading and trailing occurrences of character 'chTarget'
   string_base trimmed(CHAR_TYPE chTarget) const;

   // remove all leading and trailing occurrences of any of the characters in the string_base 'pszTargets'
   string_base trimmed(const CHAR_TYPE* pszTargets) const;

   // trimming anything (either side)

   // remove all trailing occurrences of character 'chTarget'
   string_base right_trimmed(CHAR_TYPE chTarget) const;

   // remove all trailing occurrences of any of the characters in string_base 'pszTargets'
   string_base right_trimmed(const CHAR_TYPE* pszTargets) const;

   // remove all leading occurrences of character 'chTarget'
   string_base left_trimmed(CHAR_TYPE chTarget) const;

   // remove all leading occurrences of any of the characters in string_base 'pszTargets'
   string_base left_trimmed(const CHAR_TYPE* pszTargets) const;


   // Convert the string_base to the OEM character set
   void AnsiToOem();

   // Convert the string_base to the ANSI character set
   void OemToAnsi();

   // Very simple sub-string_base extraction

   // Return the substring starting at index 'iFirst'
   string_base Mid(strsize iFirst) const;

   string_base substr(strsize iFirst) const;

   // Return the substring starting at index 'iFirst', with length 'nCount'
   string_base Mid(strsize iFirst, strsize nCount) const;


   string_base substr(strsize iFirst, strsize nCount) const;


   inline memsize get_storage_size_in_bytes() { return this->metadata()->memsize(); }
   inline strsize get_storage_length() { return (::strsize) ::str::byte_length_to_char_length(this->m_pdata, this->get_storage_size_in_bytes()); }


   inline strsize get_length() const { return (::strsize) this->metadata()->m_datasize; }
   inline memsize get_length_in_bytes() const { return ::str::char_length_to_byte_length(this->m_pdata, (strsize) (this->metadata()->m_datasize)); }
   inline memsize get_length_in_bytes_with_null_terminator() const { return ::str::char_length_to_byte_length(this->m_pdata, (strsize) (this->metadata()->m_datasize + 1)); }
   inline strsize length() const { return this->get_length(); }
   inline strsize size() const { return this->length(); }

   // Return the substring consisting of the rightmost 'nCount' characters
   string_base Right(strsize nCount) const;

   // Return the substring consisting of the leftmost 'nCount' characters
   string_base Left(strsize nCount) const;

   // Return the substring consisting of the leftmost characters in the set 'pszCharSet'
   string_base span_including(const CHAR_TYPE* pszCharSet) const;

   // Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
   string_base span_excluding(const CHAR_TYPE* pszCharSet) const;

   void Format(const CHAR_TYPE* pszFormat, ...);

   void FormatV(const CHAR_TYPE * pszFormat, va_list args);

   void AppendFormat(const CHAR_TYPE* pszFormat, ...);

   void AppendFormatV(const CHAR_TYPE* pszFormat, va_list args);

   //void FormatMessage(const CHAR_TYPE* pszFormat, ...);




   // set the string_base to the value of environment ::payload 'pszVar'
   bool get_environment_variable(const CHAR_TYPE* pszVar);

   // set the string_base to the value of environment ::payload 'pszVar'
   bool getenv(const CHAR_TYPE* pszVar);

   // Load the string_base from resource 'nID'
   //bool load_string(::matter* pobject, id id);

   // Load the string_base from resource 'nID' in module 'hInstance'
   /*    bool load_string(HINSTANCE hInstance,strsize nID )
   {
   const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID );
   if( pImage == nullptr )
   {
   return( false );
   }

   strsize nLength = str_traits::GetcharLength( pImage->achString, pImage->nLength );
   CHAR_TYPE * pszBuffer = GetBuffer( nLength );
   str_traits::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
   release_string_buffer( nLength );

   return( true );
   }*/

   // Load the string_base from resource 'nID' in module 'hInstance', using language 'wLanguageID'
   /*bool load_string(HINSTANCE hInstance,strsize nID,::u16 wLanguageID )
   {
   const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID, wLanguageID );
   if( pImage == nullptr )
   {
   return( false );
   }

   strsize nLength = str_traits::GetcharLength( pImage->achString, pImage->nLength );
   CHAR_TYPE * pszBuffer = GetBuffer( nLength );
   str_traits::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
   release_string_buffer( nLength );

   return( true );
   }*/

   void resize(strsize n)
   {
      resize(n, '\0');
   }

   void resize(strsize n, CHAR_TYPE c)
   {

      strsize nOldSize = length();

      if (n < nOldSize)
      {

         this->truncate(n);

      }
      else
      {

         auto psz = this->get_string_buffer(n);

         ::str::flood_characters(psz + nOldSize, c, n - nOldSize);

         this->release_string_buffer(n);

      }

   }



   inline strsize unichar_count() const;
   inline memsize char_type_count(strsize iChar) const;


   string_base unichar_substr(strsize iFirst) const;
   string_base unichar_substr(strsize iFirst, strsize nCount) const;
   string_base unichar_left(strsize nCount) const;
   string_base unichar_mid(strsize iFirst) const;
   string_base unichar_mid(strsize iFirst, strsize nCount) const;


   //strsize char_get_count(strsize iCharCount) const;
   //ansistring char_left(strsize nCount) const;
   //ansistring char_mid(strsize iFirst) const;
   //ansistring char_mid(strsize iFirst, strsize nCount) const;

   void clear();




   bool equals(const CHAR_TYPE * psz) const;
   bool equals_ci(const CHAR_TYPE * psz) const;

   bool operator==(const CHAR_TYPE * psz2) const;
   bool operator==(CHAR_TYPE ch) const;

   bool operator>(const CHAR_TYPE * psz2) const;
   bool operator>(CHAR_TYPE ch) const;

   bool operator<(const CHAR_TYPE * psz2) const;
   bool operator<(CHAR_TYPE ch) const;

   inline bool operator!=(const CHAR_TYPE * psz) const { return !operator ==(psz); }
   inline bool operator!=(CHAR_TYPE ch) const { return !operator ==(ch); }

   inline bool operator>=(const CHAR_TYPE * psz) const { return !operator <(psz); }
   inline bool operator>=(CHAR_TYPE ch) const { return !operator <(ch); }

   inline bool operator<=(const CHAR_TYPE * psz) const { return !operator >(psz); }
   inline bool operator<=(CHAR_TYPE ch) const { return !operator >(ch); }


   typedef strsize size_type;


};



inline string CLASS_DECL_ACME operator + (const char * psz, const ::string & str);
inline string CLASS_DECL_ACME operator + (ansichar ansich, const ::string & str);
inline string CLASS_DECL_ACME operator + (wd16char wd16ch, const ::string & str);
inline string CLASS_DECL_ACME operator + (wd16char wd32ch, const ::string & str);

inline const ansichar* __c_str(const string& str) { return str.c_str(); }



