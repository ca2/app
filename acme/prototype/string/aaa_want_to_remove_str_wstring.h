#pragma once


#include "acme/prototype/prototype/memory_c.h"



CLASS_DECL_ACME wstring operator + (const wstring & wstr1, const wstring & wstr2);
CLASS_DECL_ACME wstring operator + (const wstring & str, const wide_character * psz);
CLASS_DECL_ACME wstring operator + (const wide_character * psz, const wstring & str);


CLASS_DECL_ACME wstring gen_utf8_to_16(const ::scoped_string & scopedstr);


//class CLASS_DECL_ACME wstring_data
//{
//protected:
//
//
//   friend class wstring;
//   friend class wstring_adaptor;
//
//
//   static wide_character * get_nil();
//
//
//public:
//
//
//   ::collection::count m_iAllocation; // in chars "with nullptr characters"
//   ::collection::count m_iLength; // in chars without nullptr character
//   unichar        m_wchFirst;
//
//
//   // nil constructor
//   inline wstring_data()
//   {
//      m_iAllocation  = 0;
//      m_iLength      = 0;
//      m_wchFirst     = L'\0';
//   }
//
//   inline wstring_data * clone() const
//   {
//      wstring_data * pdata = (wstring_data *)aligned_memory_allocate(((m_iAllocation + 1) * sizeof(unichar)) + sizeof(count) + sizeof(count) + sizeof(unichar));
//      memory_copy(pdata, this, ((m_iAllocation + 1) * sizeof(unichar)) + sizeof(count) + sizeof(count) + sizeof(unichar));
//      return pdata;
//   }
//
//
//   inline static wide_character * alloc(::collection::count iCount)
//   {
//
//      wstring_data * pdata = (wstring_data *) aligned_memory_allocate(((iCount + 1) * sizeof(unichar)) + sizeof(count) + sizeof(count) + sizeof(unichar));
//      pdata->m_iAllocation = iCount;
//      pdata->m_iLength = 0;
//      pdata->m_wchFirst = L'\0';
//      return &pdata->m_wchFirst;
//
//   }
//
//   inline static void _free(wide_character * pwsz)
//   {
//      if(pwsz == nullptr)
//         return;
//      if (pwsz == get_nil())
//         return;
//      wstring_data * pdata = (wstring_data *) (((::u8 *) pwsz) - sizeof(count) - sizeof(count));
//      if(pdata->m_iAllocation <= 0)
//         return;
//      ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pdata);
//
//   }
//
//
//   inline operator const wide_character * () const { return &m_wchFirst; }
//   inline operator wide_character * () { return &m_wchFirst; }
//
//
//};


class wstring_manager;

#ifdef WINDOWS
#define unilen wcslen
#else
#define unilen wide_length
#endif

class CLASS_DECL_ACME wstring :
   public wstring
{
public:

   static const ::i32 npos;
   typedef wstring_manager manager;
   typedef unichar value_type;
   typedef wstring_data data_type;



//
//   friend class wstring_adaptor;
//
//   // it is and should be really a pointer to the m_pwsz of a wstring_data alloced in heap
//   // better always use wstring_data::alloc and wstring_data::free
//   wide_character * m_pwsz;
//
//   inline wstring_data * get_data()
//   {
//      return (wstring_data *)(((::u8 *) m_pwsz) - sizeof(count) - sizeof(count));
//   }
//
//   inline const wstring_data * get_data() const
//   {
//      return (wstring_data *)(((::u8 *) m_pwsz) - sizeof(count) - sizeof(count));
//   }
//
//public:

   wstring();
   wstring(for_moving) {};
   wstring(manager * pstringmanager);
   void construct(manager * pstringmanager = nullptr);
   wstring(const wstring & strSrc,manager * pstringmanager = nullptr);
   wstring(const ::scoped_string & scopedstrSrc,manager * pstringmanager = nullptr);
   wstring(const ::u8 * pszSrc,manager * pstringmanager = nullptr);
   wstring(const ::u8 * pszSrc, character_count nLength, manager * pstringmanager = nullptr);
   wstring(const wide_character * pchSrc, manager * pstringmanager = nullptr);
   wstring(const wide_character * pchSrc, character_count nLength,manager * pstringmanager = nullptr);
   inline wstring(const wstring_data * pdata,manager * pstringmanager = nullptr)
   {
      __UNREFERENCED_PARAMETER(pstringmanager);
      m_pwsz = (wide_character * ) &pdata->m_wchFirst;
   }
   ~wstring();


   inline void attach(wstring_data * pdata)
   {
      if(m_pwsz != nullptr)
      {
         wstring_data::_free(m_pwsz);
      }
      m_pwsz = &pdata->m_wchFirst;
   }

   inline wstring_data * detach()
   {
      wstring_data * pdata = get_data();
      m_pwsz = wstring_data::get_nil();
      return pdata;
   }


   void reserve(character_count n) { __UNREFERENCED_PARAMETER(n); } // wstring does not prereserve

   wstring & operator = (const wstring & wstr);
   wstring & operator = (const wide_character * pwsz);
   wstring & operator = (const ::scoped_string & scopedstr);


   inline operator const wide_character * () const { return get_data()->m_iAllocation <= 0 ? wstring_data::get_nil() : m_pwsz; }
   inline operator const wide_character * () { return get_data()->m_iAllocation <= 0 ? wstring_data::get_nil() : m_pwsz; }

   inline operator wide_character * () const { return get_data()->m_iAllocation <= 0 ? wstring_data::get_nil() : m_pwsz; }
   inline operator wide_character * () { return get_data()->m_iAllocation <= 0 ? wstring_data::get_nil() : m_pwsz; }


   inline const wide_character * c_str() const { return this->operator const wide_character * ();  }

#if defined(UNIVERSAL_WINDOWS) && defined(__cplusplus_winrt)
   inline operator String ^ () const { return ref aaa_primitive_new String(operator const wide_character * ()); }
   inline operator String ^ () { return ref aaa_primitive_new String(operator const wide_character * ()); }
#endif

   inline wstring & operator += (unichar wch) { append(wch); return *this; }
   inline wstring & operator += (const wide_character * pwsz) { append(pwsz); return *this; }



   inline unichar operator [] (::collection::index iIndex) const
   {
      return m_pwsz[iIndex];
   }

   inline unichar & operator [] (::collection::index iIndex)
   {
      return m_pwsz[iIndex];
   }

   wide_character * alloc(::collection::count iCount);

   inline ::collection::count get_length() const
   {
      return get_data()->m_iLength;
   }

   inline ::collection::count length() const
   {
      return get_data()->m_iLength;
   }

   inline ::collection::count size() const
   {
      return get_data()->m_iLength;
   }

   inline ::collection::count storage_size() const
   {
      return get_data()->m_iAllocation;
   }

   inline ::collection::count allocation_size() const
   {
      return get_data()->m_iAllocation;
   }

   inline ::collection::count get_storage_size() const
   {
      return get_data()->m_iAllocation;
   }

   inline ::collection::count get_allocation_size() const
   {
      return get_data()->m_iAllocation;
   }

   inline bool operator == (const wide_character * pwsz) const
   {
      return Compare(pwsz) == 0;
   }

   inline bool operator == (const wstring & wstr) const;

   inline ::i32 Compare(const wide_character * psz) const
   {
      return wide_compare(m_pwsz, psz);
   }

   inline ::i32 Compare(const wstring &str) const
   {
      return wide_compare(m_pwsz, str);
   }

   inline ::i32 CompareNoCase(const wide_character * psz) const
   {
      return wide_compare_case_insensitive(m_pwsz, psz);
   }

   inline ::i32 CompareNoCase(const wstring &str) const
   {
      return wide_compare_case_insensitive(m_pwsz, str);
   }


   inline bool is_empty() const
   {
      return get_data()->m_iLength <= 0 || *m_pwsz == L'\0';
   }


   inline void set_length(::collection::count iLength)
   {

      if(iLength <= get_data()->m_iAllocation)
      {
         get_data()->m_iLength = iLength;
      }
      else
      {
         get_data()->m_iLength = 0;
      }
      m_pwsz[iLength] = L'\0';
   }

   inline void release_buffer()
   {

      set_length(wide_length(m_pwsz));

   }


   inline static wstring empty_string()
   {
      unichar push[]= {0};
      return push;
   }

   inline wstring & append(unichar wch)
   {

      unichar wsz[2];

      wsz[0] = wch;

      wsz[1] = L'\0';

      return *this = (*this + wsz);

   }

   inline wstring & append(unichar wch, ::collection::count c)
   {

      while(c > 0)
      {

         append(wch);

         c--;

      }

      return *this;

   }

   inline wstring & append(const wide_character * pwsz) { assign(*this + pwsz); return *this; }

   wstring substr(::collection::index iStart, ::collection::count c = -1);
   wstring & replace(::collection::index iStart,::collection::count c, const wide_character * psz);


   wstring & operator = (const ::scoped_string & scopedstr);

   void assign(const wide_character * pwsz);
   void assign(const ::scoped_string & scopedstr);


   character_count find(unichar ch,character_count start = 0,character_count count = -1) const RELEASENOTHROW;
   character_count find(const wide_character * pszSub,character_count start = 0,character_count count = -1,const wide_character * * pszTail = nullptr) const RELEASENOTHROW;

   bool empty() const { return is_empty();  }


};



