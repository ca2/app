#pragma once


#include "acme/filesystem/file/serializable.h"


template < typename N >
inline i32 msb(N n)
{

   i32 i = sizeof(N) * 8;

   do
   {
      i--;
      if(n & (numeric_info < N >::unitary () << i))
         return i;

   }
   while(i > 0);

   return -1;

}


class bstring_manager;
class memory;
class shared_memory;
class virtual_memory;
class memory_container;


enum e_memory
{

   memory_none,
   memory_primitive,
   memory_shared,
   memory_virtual,

};


__memory(MEMORY), public block
{
public:

   bool                    m_bOwn;
   byte *                  m_pbStorage;
   //byte *                  m_pdata;

   memsize                 m_iOffset;
   memsize                 m_iMaxOffset;
   memsize                 m_cbStorage;
   //memsize                 m_dwAllocation;
   double                  m_dAllocationRateUp;
   ::u32                   m_dwAllocationAddUp;

   memory_container *      m_pcontainer;

   e_memory                m_ememory;

   memory *                m_pprimitivememory;
   shared_memory *         m_psharedmemory;
   virtual_memory *        m_pvirtualmemory;

   MEMORY();
   MEMORY(const MEMORY & memory) { memcpy(this, &memory, sizeof(MEMORY)); }

   MEMORY & operator = (const MEMORY & memory) { if (this != &memory) memcpy(this, &memory, sizeof(MEMORY)); return *this; }

};


template < typename MUTABLE >
MUTABLE * __mutable(const MUTABLE * pmutable) { return (MUTABLE *)pmutable; }


class CLASS_DECL_ACME memory_base :
   virtual public ::matter
{
public:

   typedef bstring_manager manager;

   typedef byte value_type;


   MEMORY      m_memory;

#if MEMDLEAK

   string m_strTag;

   int m_iLine;

#endif




   memory_base() {}
   memory_base(const memory_base & base) : m_memory(base.m_memory) {}
   memory_base(memory_base && base) : m_memory(base.m_memory) { ·zero(base.m_memory); }
   virtual ~memory_base();


   virtual string as_utf8() const;

   virtual char * c_str();
   virtual bool begins(const char * psz, strsize iCount = -1) const;
   virtual bool begins_ci(const char * psz, strsize iCount = -1) const;
   virtual bool begins(const string & str, strsize iCount = -1) const;
   virtual bool begins_ci(const string & str, strsize iCount = -1) const;

   //virtual byte * detach_primitive_memory();
   //virtual byte * detach_virtual_memory();
   //virtual HGLOBAL detach_shared_memory();

   //bool is_enabled() const;
   //bool is_locked() const;

   inline bool defer_set_size(memsize s) { if (get_size() < s) return set_size(s); return true; }
   virtual bool set_size(memsize dwNewLength);
   virtual bool allocate_internal(memsize dwNewLength);

   inline bool truncate(memsize uTruncate) { if (uTruncate >= get_size()) return true; return set_size(uTruncate); }

   virtual byte * impl_alloc(memsize dwAllocation);
   virtual byte * impl_realloc(void * pdata,memsize dwAllocation);
   virtual void impl_free(byte * pdata);

   virtual void reserve(memsize dwNewLength);


   virtual void remove_offset();

   //virtual void random_bytes(::count c = -1);


   virtual ::stream & write(::stream & stream) const override;
   virtual ::stream & read(::stream & stream) override;


   virtual memsize calc_allocation(memsize size);


   virtual void transfer_to(::file::file * pfileOut, memsize uiBufferSize = 1024 * 1024) const;
   virtual void transfer_from(::file::file * pfileIn, memsize uiBufferSize = 1024 * 1024);
   virtual void transfer_from_begin(::file::file * pfileIn, memsize uiBufferSize = 1024 * 1024);


   void allocate_add_up(memsize iAddUp);


   virtual ::matter * clone() const override;


   inline byte *           internal_get_data() const;
   inline memsize          get_size() const;
   inline byte *           get_data() const;
   inline byte *           get_data();

   inline memsize          size() const;
   inline byte *           data() const;
   inline byte *           data();

   inline const char * c_str() const { return (char*)data(); }
   inline char * sz() { return (char*)data(); }

   inline bool has_data() const;
   inline bool is_empty() const;

   inline byte operator [] (::index i) const;
   inline byte & operator [] (::index i);

   inline operator const byte *() const;
   inline operator byte *();

   inline operator const void *() const;
   inline operator void *();

   char * get_psz(strsize & len);

   memory_base & operator = (const memory_base & s);
   memory_base & operator += (const memory_base & s);


   void from_string(const widechar * pwsz);
   void from_string(const char * psz);
   void from_string(const string & str);
   void from_string(const var & var);
   //void to_string(string & str, memsize iStart = 0, memsize uiSize = -1) const;
   virtual void to_string(const string_exchange & str) const override;
   string to_string(memsize iStart, memsize uiSize = -1) const;

   void delete_begin(memsize iSize);
   void eat_begin(void * pdata, memsize iSize);
   void set_data(void * pdata, memsize uiSize);
   void copy_from(const memory_base * pstorage);
   void copy_from(const void * pdata, memsize s);
   void copy_to(void * pdata, memsize s) const;
   void set(byte b,memsize iStart = 0,memsize uiSize = -1);
   void zero(memsize iStart = 0, memsize uiSize = -1);

   void append(const memory_base & memory, memsize iStart = 0, memsize iCount = -1);
   void append(const void * pdata, memsize iCount);
   void assign(const void * pdata, memsize iCount);
   void assign(const void * pdata, memsize iStart, memsize iCount);
   void append(memsize iCount, uchar uch);
   void assign(memsize iCount, uchar uch);
   void append(byte b);

   void clear();

   void splice(const u8 * pbMemory, memsize iCountSrc, memsize iStartDst = 0, memsize iCountDst = 0);
   void splice(const memory_base & memory, memsize iStartDst = 0, memsize iCountDst = 0, memsize iStartSrc = 0, memsize iCountSrc = -1);

   void move_and_grow(memsize offset);
   void move(memsize offset, bool bGrow = false);

   void assign(const char * psz);



   void to_hex(string & str, memsize iStart = 0, memsize size = -1);
   string to_hex(memsize iStart = 0, memsize size = -1);
   strsize from_hex(const char * psz, strsize nCount = -1);

   void to_base64(string & str, memsize iStart = 0, memsize size = -1);
   string to_base64(memsize iStart = 0, memsize size = -1);
   void from_base64(const char * psz, strsize nCount = -1);

   inline void to_asc(string & str) { str.assign((const char *) get_data(), get_size()); }
   inline string to_asc() { string str; to_asc(str); return str; }
   inline void from_asc(const string& str) { assign(str.c_str(), str.get_length()); }

   bool operator == (const memory_base & s);
   bool operator == (const struct block & block);


   memory_base & reverse();

   memory_base & prefix_der_uint_content();
   memory_base & prefix_der_length();
   memory_base & prefix_der_type(i32 iType);

   memory_base & prefix_der_uint();
   memory_base & prefix_der_sequence();

   memsize get_length() const;
   memsize length() const;

   inline void set_char_at_grow(strsize iChar, char ch);


#if defined(_UWP) && defined(__cplusplus_winrt)

   inline Array < uchar, 1U > ^ get_os_bytes(memsize pos = 0, memsize size = -1) const;
   inline ::Windows::Storage::Streams::IBuffer ^ get_os_crypt_buffer(memsize pos = 0, memsize size = -1) const;
   inline ::Windows::Storage::Streams::IBuffer ^ get_os_buffer(memsize pos = 0, memsize size = -1) const;
   inline void set_os_bytes(Array < uchar, 1U > ^ a, memsize pos = 0, memsize size = -1);
   inline void set_os_crypt_buffer(::Windows::Storage::Streams::IBuffer ^ ibuf, memsize pos = 0, memsize size = -1);
   inline void set_os_buffer(::Windows::Storage::Streams::IBuffer ^ ibuf, memsize pos = 0, memsize size = -1);

#elif defined(APPLEOS)

   CFDataRef get_os_cf_data(memsize pos = 0, memsize size = -1) const;
   void set_os_cf_data(CFDataRef data, memsize pos = 0, memsize size = -1);

#endif

#ifdef WINDOWS

   comptr < IStream > create_istream() const;

#endif


   memory_base & erase(memsize pos = 0,memsize len = -1);

   void fread(FILE * pfile);


};


inline byte * memory_base::internal_get_data() const
{
   return (byte *) m_memory.m_pdata;
}
inline memsize memory_base::get_size() const
{
   return m_memory.m_cbStorage;
}
inline memsize memory_base::size() const
{
   return get_size();
}
inline byte * memory_base::get_data() const
{
   return (byte*)m_memory.m_pdata;
}
inline byte * memory_base::get_data()
{
   return (byte*)m_memory.m_pdata;
}
inline byte * memory_base::data() const
{
   return get_data();
}
inline byte * memory_base::data()
{
   return get_data();
}
inline bool memory_base::has_data() const
{
   return get_size() > 0;
}
inline bool memory_base::is_empty() const
{
   return !has_data();
}


inline uchar memory_base::operator [] (::index i) const
{
   return this->get_data()[i];
}
inline uchar & memory_base::operator [] (::index i)
{
   return this->get_data()[i];
}


inline memory_base::operator const u8 *() const
{
   return this->get_data();
}
inline memory_base::operator u8 *()
{
   return this->get_data();
}
inline memory_base::operator const void *() const
{
   return this->get_data();
}
inline memory_base::operator void *()
{
   return this->get_data();
}

inline void memory_base::allocate_add_up(memsize iAddUp)
{

   if (iAddUp != 0)
   {

      set_size(get_size() + iAddUp);

   }

}

inline void memory_base::splice(const memory_base & memory, memsize iStartDst, memsize iCountDst, memsize iStartSrc, memsize iCountSrc)
{

   splice(
   &memory.get_data()[iStartSrc],
   min(memory.get_size(), iCountSrc < 0 ? memory.get_size() - iCountSrc + 1 : iCountSrc),
   iStartDst,
   iCountDst);

}


inline void memory_base::set_char_at_grow(strsize iChar, char ch)
{

   if (::comparison::ge(iChar, get_size()))
   {

      set_size(iChar + 1);

   }

   ((char*)get_data())[iChar] = ch;

}






















