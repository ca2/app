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
class read_only_memory;
class memory;
class shared_memory;
class virtual_memory;
class memory_container;


enum enum_memory
{

   e_memory_none,
   e_memory_primitive,
   e_memory_shared,
   e_memory_virtual,

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

   enum_memory             m_ememory;

   read_only_memory *      m_preadonlymemory;
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
   virtual public ::material_object
{
public:

   typedef bstring_manager manager;

   typedef byte value_type;


   MEMORY      m_memory;

#if MEMDLEAK

   string m_strTag;

   int m_iLine;

#endif


   memory_base() { }
   memory_base(const memory_base & base) : m_memory(base.m_memory) {}
   memory_base(memory_base && base) : m_memory(base.m_memory) { __zero(base.m_memory); }
   ~memory_base() override;


   using ::material_object::clear;


   virtual string as_utf8() const;

   virtual char * c_str();

   virtual bool begins(const block& block) const;
   virtual bool begins(const char * psz, strsize iCount = -1) const;
   virtual bool begins_ci(const char * psz, strsize iCount = -1) const;
   virtual bool begins(const ::string & str, strsize iCount = -1) const;
   virtual bool begins_ci(const ::string & str, strsize iCount = -1) const;

   virtual bool ends(const block& block) const;
   virtual bool ends(const char * psz, strsize iCount = -1) const;
   virtual bool ends_ci(const char * psz, strsize iCount = -1) const;
   virtual bool ends(const ::string & str, strsize iCount = -1) const;
   virtual bool ends_ci(const ::string & str, strsize iCount = -1) const;

   virtual memory detach_as_primitive_memory();
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


   virtual void erase_offset();

   //virtual void random_bytes(::count c = -1);


   virtual ::stream & write(::stream & stream) const override;
   virtual ::stream & read(::stream & stream) override;


   virtual memsize calc_allocation(memsize size);


   virtual void transfer_to(::file::file * pfileOut, memsize uiBufferSize = 1024 * 1024) const;
   virtual void transfer_from(::file::file * pfileIn, memsize uiBufferSize = 1024 * 1024);
   virtual void transfer_from_begin(::file::file * pfileIn, memsize uiBufferSize = 1024 * 1024);


   void allocate_add_up(memsize iAddUp);


   ::element * clone() const override;


   inline byte *           internal_get_data() const;
   inline memsize          get_size() const;
   inline byte *           get_data() const;
   inline byte *           get_data();

   inline memsize          size() const;
   inline byte *           data() const;
   inline byte *           data();


   inline byte * begin() const { return get_data();  }
   inline byte * end() const { return get_data() + size(); }

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
   void from_string(const ::string & str);
   void from_string(const ::payload & payload);
   void append_from_string(const widechar * pwsz);
   void append_from_string(const char * psz);
   void append_from_string(const ::string & str);
   void append_from_string(const ::payload & payload);
   void append_byte(byte b){ append(&b, 1);}
   //void to_string(string & str, memsize iStart = 0, memsize uiSize = -1) const;
   string get_string() const override;
   string get_string(memsize iStart, memsize uiSize = -1) const;

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
   void append(const char * psz);




   void to_hex(string & str, memsize iStart = 0, memsize size = -1);
   string to_hex(memsize iStart = 0, memsize size = -1);
   strsize from_hex(const char * psz, strsize nCount = -1);

   void to_base64(string & str, memsize iStart = 0, memsize size = -1);
   string to_base64(memsize iStart = 0, memsize size = -1);
   void from_base64(const char * psz, strsize nCount = -1);

   inline void to_asc(string & str) const { str.assign((const char *) get_data(), get_size()); }
   inline string to_asc() const { string str; to_asc(str); return str; }
   inline void from_asc(const string& str) { assign(str.c_str(), str.get_length()); }

   bool operator == (const memory_base & s) const;
   bool operator == (const struct block & block) const ;


   memory_base & reverse();

   memory_base & prefix_der_uint_content();
   memory_base & prefix_der_length();
   memory_base & prefix_der_type(i32 iType);

   memory_base & prefix_der_uint();
   memory_base & prefix_der_sequence();

   memsize get_length() const;
   memsize length() const;

   inline void set_char_at_grow(strsize iChar, char ch);


   byte * find(const block& block, ::index iStart = 0) const;
   ::index find_index(const block& block, ::index iStart = 0) const;
   byte* reverse_find(const block& block, ::index iStart = 0) const;
   ::index reverse_find_index(const block& block, ::index iStart = 0) const;
   byte* reverse_find_byte_not_in_block(const block& block, ::index iStart = 0) const;
   ::index reverse_find_index_of_byte_not_in_block(const block& block, ::index iStart = 0) const;

   byte * find_line_prefix(const ::block& blockPrefix, ::index iStart = 0);
   ::index find_line_prefix_index(const ::block& blockPrefix, ::index iStart = 0);
   ::e_status patch_line_suffix(const ::block & blockPrefix, const block& blockSuffix, ::index iStart = 0);


#if defined(_UWP) && defined(__cplusplus_winrt)

   inline Array < uchar, 1U > ^ get_os_bytes(memsize pos = 0, memsize size = -1) const;
   inline ::winrt::Windows::Storage::Streams::IBuffer ^ get_os_crypt_buffer(memsize pos = 0, memsize size = -1) const;
   inline ::winrt::Windows::Storage::Streams::IBuffer ^ get_os_buffer(memsize pos = 0, memsize size = -1) const;
   inline void set_os_bytes(Array < uchar, 1U > ^ a, memsize pos = 0, memsize size = -1);
   inline void set_os_crypt_buffer(::winrt::Windows::Storage::Streams::IBuffer ^ ibuf, memsize pos = 0, memsize size = -1);
   inline void set_os_buffer(::winrt::Windows::Storage::Streams::IBuffer ^ ibuf, memsize pos = 0, memsize size = -1);

#endif
   
//#if defined(__APPLE__)
//
//   CFDataRef get_os_cf_data(memsize pos = 0, memsize size = -1) const;
//   void set_os_cf_data(CFDataRef data, memsize pos = 0, memsize size = -1);
//
//#endif



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
   minimum(memory.get_size(), iCountSrc < 0 ? memory.get_size() - iCountSrc + 1 : iCountSrc),
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



















