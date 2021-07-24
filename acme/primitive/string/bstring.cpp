#include "framework.h"


//class bstring_empty_data :
//   public bstring_data
//{
//public:
//
//   char ch;
//
//   bstring_empty_data()
//   {
//      m_len = 1;
//      m_alloc = 1;
//      ch = '\0';
//
//   }
//
//};
//
//static bstring_empty_data bstring_empty;
//
//
//bstring bstring::s_nil(&bstring_empty);
//
//
//bstring::bstring()
//{
//
//   set_bstring_data(&bstring_empty);
//
//}
//
//
//bstring::bstring(bstring_data * pdata)
//{
//
//   set_bstring_data(pdata);
//
//}
//
//
//bstring::bstring(const bstring & bstr)
//{
//   set_bstring_data(&bstring_empty);
//   allocate(bstr.get_size());
//   ::memcpy_dup(get_data(), bstr.get_data(), get_size());
//
//}
//
//bstring::bstring(bstring && bstr)
//{
//
//   m_puchData = bstr.m_puchData;
//
//   bstr.set_bstring_data(&bstring_empty);
//
//}
//
////bstring::bstring(const bstring & bstr)
////{
////
////   allocate(bstr.get_size());
////   ::memcpy_dup(get_data(), bstr.get_data(), get_size());
////
////}
//
//bstring::bstring(strsize s, char ch)
//{
//   set_bstring_data(&bstring_empty);
//   allocate(s + 1);
//   __memset(get_data(), ch, s);
//   get_data()[s] = '\0';
//
//}
//
//
//bstring::bstring(const bstring& str, strsize pos, strsize len)
//{
//
//   if (pos <= 0)
//   {
//
//      len += pos;
//      pos = 0;
//
//   }
//   set_bstring_data(&bstring_empty);
//   allocate(minimum(len+1, (str.get_allocation_size() - pos)));
//
//   ::memcpy_dup(m_puchData, &str.m_puchData[pos], get_allocation_size());
//
//}
//
//
//bstring::bstring(const char * psz)
//{
//   set_bstring_data(&bstring_empty);
//   if (psz != nullptr && *psz != '\0')
//   {
//
//      assign(psz, strlen(psz) + 1);
//
//   }
//
//}
//
//
//bstring::bstring(const void * p, strsize start, strsize end)
//{
//   set_bstring_data(&bstring_empty);
//   assign(p, start, end);
//   append((const void *) "", 1);
//
//}
//
//bstring::bstring(const void * p, strsize c)
//{
//   set_bstring_data(&bstring_empty);
//   assign(p, c);
//   append((const void *) "", 1);
//
//}
//
//bstring::~bstring()
//{
//
//   free();
//
//}
//
//
//void bstring::allocate(strsize s)
//{
//
//   if (get_bstring_data() == &bstring_empty)
//   {
//
//      if (s > 1)
//      {
//
//         strsize sAlloc = s + minimum(maximum(s, 16), 1024);
//
//         bstring_data * pdata = (bstring_data *)memory_allocate(sizeof(bstring_data) + sAlloc);
//
//         if (pdata == nullptr)
//         {
//
//            __throw(error_no_memory);
//
//         }
//
//         set_bstring_data(pdata);
//
//         get_bstring_data()->m_len = s;
//
//         get_bstring_data()->m_alloc = sAlloc;
//
//      }
//
//   }
//   else
//   {
//
//      if (s <= 1)
//      {
//
//         free();
//
//      }
//      else
//      {
//
//         if (s > get_bstring_data()->m_alloc)
//         {
//
//            strsize sAlloc = s + minimum(maximum(s, 16), 1024);
//
//            bstring_data * pdata = (bstring_data *)memory_reallocate(get_bstring_data(), sizeof(bstring_data) + sAlloc);
//
//            if (pdata == nullptr)
//            {
//
//               __throw(error_no_memory);
//
//            }
//
//            set_bstring_data(pdata);
//
//            get_bstring_data()->m_alloc = sAlloc;
//
//         }
//
//         get_bstring_data()->m_len = s;
//
//      }
//
//   }
//
//}
//
//
//void bstring::allocate_add_up(strsize s)
//{
//
//   strsize sPrevious = get_size();
//
//   allocate(sPrevious + s);
//
//}
//
//
//void bstring::free()
//{
//
//   if (get_bstring_data() != &bstring_empty)
//   {
//
//      memory_free(get_bstring_data());
//
//      set_bstring_data(&bstring_empty);
//
//   }
//
//}
//
//
//void bstring::assign(const void * p, strsize s)
//{
//   allocate(s);
//   ::memcpy_dup(m_puchData, p, s);
//}
//
//void bstring::assign(const void * p, strsize s, strsize c)
//{
//
//   allocate(c);
//   ::memcpy_dup(m_puchData, &((byte*)p)[s], c);
//
//}
//
//
//bstring & bstring::assign(const bstring & str, strsize pos, strsize len)
//{
//
//   if (len < 0)
//   {
//
//      len = str.length() - pos;
//
//      if (len < 0)
//      {
//
//         clear();
//
//         return *this;
//
//      }
//
//   }
//
//   if (pos <= 0)
//   {
//
//      len += pos;
//
//      pos = 0;
//
//   }
//
//   if (len < 0 || len >(str.length() - pos))
//   {
//
//      len = str.length() - pos;
//
//   }
//
//   allocate(len + 1);
//
//   ::memcpy_dup(m_puchData, &str.m_puchData[pos], len);
//
//   m_puchData[len] = '\0';
//
//   return *this;
//
//}
//
//
//bstring & bstring::assign(strsize s, char c)
//{
//
//   if (s <= 0)
//   {
//
//      clear();
//
//   }
//   else
//   {
//
//      allocate(s + 1);
//
//      __memset(m_puchData, c, s);
//
//      m_puchData[s] = '\0';
//
//   }
//
//   return *this;
//
//}
//
//bstring & bstring::append(strsize s, char c)
//{
//
//   if (s > 0)
//   {
//
//      strsize sPrevious = length();
//
//      allocate_add_up(s);
//
//      __memset(&m_puchData[sPrevious], c, s);
//
//      m_puchData[length()] = '\0';
//
//   }
//
//   return *this;
//
//}
//
//
//
//bstring & bstring::erase(strsize s, strsize len)
//{
//
//   if (s <= 0 && (len < 0 || (s + len) >= length()))
//   {
//
//      clear();
//
//   }
//   else
//   {
//
//      __memmov(&m_puchData[s], &m_puchData[s + len], length() - s - len);
//
//      allocate(length() - len);
//
//   }
//
//   return *this;
//
//}
//
//
//void bstring::clear()
//{
//
//   free();
//
//}
//
//
//void bstring::append(const void * p, strsize s)
//{
//
//   strsize sPrevious = get_allocation_size();
//
//   allocate(sPrevious + s);
//
//   ::memcpy_dup(&m_puchData[sPrevious - 1], p, s);
//
//   m_puchData[length()] = '\0';
//
//}
//
//
//bstring & bstring::operator = (const bstring & bstr)
//{
//
//   if (&bstr != this)
//   {
//
//      allocate(bstr.get_size());
//
//      ::memcpy_dup(get_data(), bstr.get_data(), bstr.get_size());
//
//   }
//
//   return *this;
//
//}
//
//
//bstring bstring::operator + (char ch) const
//{
//
//   bstring bstr(*this);
//
//   bstr.allocate(get_length()+1);
//
//   bstr[bstr.get_size() - 2] = ch;
//
//   bstr[bstr.get_size() - 1] = '\0';
//
//   return bstr;
//
//}
//
//
//bstring bstring::operator + (const char * psz) const
//{
//
//   bstring bstr(*this);
//
//   if (psz != nullptr)
//   {
//
//      bstr.allocate(bstr.get_length() + strlen(psz));
//      ::memcpy_dup(&bstr[bstr.get_size() - 1 - strlen(psz)], psz, strlen(psz));
//      bstr[bstr.get_size() - 1] = '\0';
//
//      //bstr.append(psz, strlen(psz));
//
//   }
//   return bstr;
//
//}
//
//bstring bstring::operator + (const bstring & bstr2) const
//{
//
//   bstring bstr(*this);
//
//   if (bstr2.length() > 0)
//   {
//
//      bstr.allocate(bstr.get_length() + bstr2.length());
//      ::memcpy_dup(&bstr[bstr.get_size() - 1 - bstr2.length()], bstr2.data(), bstr2.length());
//      bstr[bstr.get_size() - 1] = '\0';
//
//      //bstr.append(psz, strlen(psz));
//
//   }
//   return bstr;
//}
//
//bstring & bstring::operator += (char ch)
//{
//
//   allocate_add_up(1);
//   m_puchData[get_size() - 2] = ch;
//   m_puchData[get_size() - 1] = '\0';
//
//   return *this;
//
//}
//
//bstring & bstring::operator += (const char * psz)
//{
//
//   if (psz != nullptr)
//   {
//
//      allocate_add_up(strlen(psz));
//      ::memcpy_dup(&m_puchData[get_size() - 1 - strlen(psz)], psz, strlen(psz));
//      m_puchData[get_size() - 1] = '\0';
//
//   }
//
//   return *this;
//
//}
//
//bstring & bstring::operator += (const string & str)
//{
//
//   allocate_add_up(str.length());
//   ::memcpy_dup(&m_puchData[get_size() - 1 - str.length()], str, str.length());
//   m_puchData[get_size() - 1] = '\0';
//
//   return *this;
//
//}
//
//bstring & bstring::operator += (const bstring & bstr)
//{
//
//   allocate(get_size() - 1);
//   append(bstr.get_data(), bstr.get_length());
//
//   return *this;
//
//}
//
//const WCHAR * bstring::c_str() const
//{
//
//   return (const WCHAR *)get_data();
//
//}
//
//char & bstring::operator [](strsize i)
//{
//
//   return (char &)get_data()[i];
//
//}
//
//const char & bstring::operator [](strsize i) const
//{
//
//   return *((const char *)&get_data()[i]);
//
//}
//
//char * bstring::get_string_buffer(strsize s)
//{
//
//   allocate(s + 1);
//
//   return (char *)get_data();
//
//}
//
//void bstring::release_string_buffer(strsize s)
//{
//
//   ReleaseBuffer(s);
//
//}
//
//void bstring::ReleaseBuffer(strsize s)
//{
//
//   if (s < 0)
//   {
//
//      allocate(safe_strlen(get_data(), get_size()) + 1);
//
//   }
//   else
//   {
//
//      allocate(s + 1);
//
//   }
//
//   if (s > 1)
//   {
//
//      m_puchData[length()] = '\0';
//
//   }
//
//}
//
//u8 * bstring::data()
//{
//
//   return (u8 *)get_data();
//
//}
//
//const u8 * bstring::data() const
//{
//
//   return (const u8 *)get_data();
//
//}
//
//bool bstring::empty() const
//{
//
//   return get_size() <= 0;
//
//}
//
//
//int bstring::compare(const char * psz) const
//{
//
//   if (psz == nullptr)
//   {
//
//      if (get_data() == nullptr)
//      {
//
//         return 0;
//
//      }
//      else
//      {
//
//         return get_data()[0] == '\0' ? 0 : -1;
//
//      }
//
//   }
//   else if (get_data() == nullptr)
//   {
//
//      return *psz == '\0' ? 0 : 1;
//
//   }
//
//   return ansi_count_compare((const char *)get_data(), psz, get_size());
//
//}
//
//bool bstring::operator == (const char * psz) const
//{
//
//   return compare(psz) == 0;
//
//}
//
//bool bstring::operator != (const char * psz) const
//{
//
//   return compare(psz) != 0;
//
//}
//
//bool bstring::operator <= (const char * psz) const
//{
//
//   return compare(psz) <= 0;
//
//}
//
//bool bstring::operator < (const char * psz) const
//{
//
//   return compare(psz) < 0;
//
//}
//
//bool bstring::operator >= (const char * psz) const
//{
//
//   return compare(psz) >= 0;
//
//}
//
//bool bstring::operator > (const char * psz) const
//{
//
//   return compare(psz) > 0;
//
//}
//
//
//int bstring::compare(const bstring & bstr) const
//{
//
//   if (bstr.get_data() == nullptr)
//   {
//
//      if (get_data() == nullptr)
//      {
//
//         return 0;
//
//      }
//      else
//      {
//
//         return bstr.get_data()[0] == '\0' ? 0 : -1;
//
//      }
//
//   }
//   else if (get_data() == nullptr)
//   {
//
//      return bstr.get_data()[0] == '\0' ? 0 : 1;
//
//   }
//
//   int iCmp = __memcmp(get_data(), bstr.get_data(), minimum(get_size(), bstr.get_size()));
//
//   if (iCmp == 0)
//   {
//
//      iCmp = (int)(get_size() - bstr.get_size());
//
//   }
//
//   return iCmp;
//
//}
//
//bool bstring::operator != (const bstring & bstr) const
//{
//
//   return compare(bstr) != 0;
//
//}
//
//
//bool bstring::operator == (const bstring & bstr) const
//{
//
//   return compare(bstr) == 0;
//
//}
//
//bool bstring::operator <= (const bstring & bstr) const
//{
//
//   return compare(bstr) <= 0;
//
//}
//
//bool bstring::operator < (const bstring & bstr) const
//{
//
//   return compare(bstr) < 0;
//
//}
//
//bool bstring::operator >= (const bstring & bstr) const
//{
//
//   return compare(bstr) >= 0;
//
//}
//
//bool bstring::operator > (const bstring & bstr) const
//{
//
//   return compare(bstr) > 0;
//
//}
//
//
//
//
//void bstring::append(const char * psz)
//{
//
//   allocate(get_length() - 1);
//
//   append(psz, strlen(psz) + 1);
//
//}
//
//
//void bstring::append(const bstring & bstr)
//{
//
//   allocate(get_length() - 1);
//
//   append(bstr.m_puchData, bstr.get_allocation_size());
//
//}
//
//void bstring::assign(const bstring & bstr)
//{
//
//   allocate(bstr.get_allocation_size());
//
//   ::memcpy_dup(m_puchData, bstr.m_puchData, get_allocation_size());
//
//}
//
//
//void bstring::reserve(strsize s)
//{
//
//
//}
//
//
//strsize bstring::copy(value_type * s, strsize len, strsize pos) const
//{
//
//   if (len < 0)
//   {
//
//      len = length() - pos;
//
//      if (len < 0)
//      {
//
//         return 0;
//
//      }
//
//   }
//
//   if (pos <= 0)
//   {
//
//      len += pos;
//
//      pos = 0;
//
//   }
//
//   if (len < 0 || len > (length() - pos))
//   {
//
//      len = length() - pos;
//
//   }
//
//   ::memcpy_dup(s, &m_puchData[pos], len);
//
//   return len;
//
//}
//


