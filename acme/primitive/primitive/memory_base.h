#pragma once


//#include "acme/filesystem/file/serializable.h"
//#include "acme/memory/memory.h"
#include "acme/primitive/primitive/particle.h"
//// #include "acme/primitive/string/string.h"


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
class paged_memory;
class memory_container;


enum enum_memory
{

   e_memory_none,
   e_memory_primitive,
   e_memory_shared,
   e_memory_virtual,

};


class CLASS_DECL_ACME MEMORY :
   public block
{
public:


   bool                    m_bOwner;
   bool                    m_bReadOnly;
   byte *                  m_beginStorage;
   memsize                 m_sizeStorage;
   double                  m_dAllocationRateUp;
   ::u32                   m_dwAllocationAddUp;

   memory_container *      m_pcontainer;

   enum_memory             m_ememory;

   read_only_memory *      m_preadonlymemory;
   memory *                m_pprimitivememory;
   shared_memory *         m_psharedmemory;
   paged_memory *        m_pvirtualmemory;

   MEMORY();
   MEMORY(const MEMORY & memory) { _assign(memory); }
   MEMORY(MEMORY && memory) { _assign(memory); zero(memory); }

   MEMORY & operator = (const MEMORY & memory) { assign(memory); return *this; }

   void _assign(const MEMORY & memory)
   {

      memcpy(this, &memory, sizeof(MEMORY));

   }


   void assign(const MEMORY & memory)
   {

      if (this != &memory)
      {

         _assign(memory);

      }

   }

   ::byte * storage_begin() { return m_beginStorage; }
   const ::byte * storage_begin() const { return m_beginStorage; }
   memsize storage_size() const { return maximum(0,m_sizeStorage); }
   ::byte * storage_end() { return storage_begin() + storage_size(); }
   const ::byte * storage_end() const { return storage_begin() + storage_size(); }
   memsize offset() const { return m_begin - m_beginStorage; }
   memsize max_offset() const { return storage_size(); }

};


template < typename MUTABLE >
MUTABLE * __mutable(const MUTABLE * pmutable) { return (MUTABLE *)pmutable; }


class CLASS_DECL_ACME memory_base :
   public MEMORY,
   virtual public ::particle
{
public:

   typedef bstring_manager manager;

   typedef byte value_type;


   //MEMORY      m_memory;

#if MEMDLEAK

   string m_strTag;

   int m_iLine;

#endif


   memory_base() { }
   memory_base(const memory_base & base) : MEMORY(base) {}
   memory_base(memory_base && base) : MEMORY(::transfer(base)) {}
   ~memory_base() override;


   using ::particle::clear_flag;


   virtual string as_utf8() const;

   //virtual char * c_str();

   virtual bool begins(const ::scoped_string & scopedstr) const { return ((::const_ansi_range *)this)->begins(scopedstr); }
   //virtual bool begins(const ::scoped_string & scopedstr, strsize iCount = -1) const;
   virtual bool case_insensitive_begins(const ::scoped_string & scopedstr, strsize iCount = -1) const{ return ((::const_ansi_range *)this)->case_insensitive_begins(scopedstr); }
   //virtual bool begins(const ::string & str, strsize iCount = -1) const;
   //virtual bool case_insensitive_begins(const ::string & str, strsize iCount = -1) const;

   virtual bool ends(const ::scoped_string & scopedstr) const { return ((::const_ansi_range *)this)->ends(scopedstr); }
   //virtual bool ends(const ::scoped_string & scopedstr, strsize iCount = -1) const;
   virtual bool case_insensitive_ends(const ::scoped_string & scopedstr) const { return ((::const_ansi_range *)this)->case_insensitive_ends(scopedstr); }
   //virtual bool ends(const ::string & str, strsize iCount = -1) const;
   //virtual bool case_insensitive_ends(const ::string & str, strsize iCount = -1) const;

   virtual memory detach_as_primitive_memory();
   //virtual byte * detach_virtual_memory();
   //virtual HGLOBAL detach_shared_memory();

   //bool is_enabled() const;
   //bool is_locked() const;

   inline void defer_set_size(memsize sizeLarger) { if (sizeLarger > size()) return set_size(sizeLarger); }
   virtual void set_size(memsize dwNewLength);
   virtual void allocate_internal(memsize dwNewLength);

   inline void truncate(memsize sizeSmaller) { if (sizeSmaller < size()) return set_size(sizeSmaller); }

   virtual byte * impl_alloc(memsize dwAllocation);
   virtual byte * impl_realloc(void * pdata,memsize dwAllocation);
   virtual void impl_free(byte * pdata);

   virtual void reserve(memsize dwNewLength);


   virtual void erase_offset();

   //virtual void random_bytes(::count c = -1);


   //virtual ::stream & write(::stream & stream) const override;
   //virtual ::stream & read(::stream & stream) override;


   virtual memsize calc_allocation(memsize size);


   //virtual void transfer_to(::file::file * pfileOut, memsize uiBufferSize = 1024 * 1024) const;
   virtual void assign_file(::file::file * pfileIn, memsize uiBufferSize = 1024 * 1024);
   virtual void assign_entire_file(::file::file * pfileIn, memsize uiBufferSize = 1024 * 1024);

   virtual void append_file(::file::file * pfileIn, memsize uiBufferSize = 1024 * 1024);
   virtual void append_entire_file(::file::file * pfileIn, memsize uiBufferSize = 1024 * 1024);


   void allocate_add_up(memsize iAddUp);


   ::particle * clone() const override;


//   inline byte * storage_begin() { return m_memory.storage_begin(); }
//   inline const byte * storage_begin() const { return m_memory.storage_begin(); }
//   inline byte * storage_end() { return m_memory.storage_end(); }
//   inline const byte * storage_end() const { return m_memory.storage_end(); }
//   inline memsize storage_size() const { return m_memory.storage_size(); }


   //inline memsize size() const { return m_memory.size(); }
   //inline const byte * data() const { return m_memory.data(); }
   //inline byte * data() { return m_memory.data(); }

   //inline memsize          size() const;
   //inline byte *           data() const;
   //inline byte *           data();

//
//   inline const byte * begin() const { return data();  }
//   inline byte * begin() { return data(); }
//   inline const byte * end() const { return m_memory.end(); }
//   inline byte * end() { return m_memory.end(); }

   //inline const char * c_str() const { return (const char*)data(); }
   //inline char * sz() { return (char*)data(); }

   ::block & block() { return *this; }
   const ::block & block() const { return *this; }

   inline bool is_set() const { return MEMORY::is_set(); }
   inline bool is_empty() const { return MEMORY::is_empty(); }
   inline bool has_data() const { return this->size() > 0; }

   inline byte operator [] (::index i) const { return data()[i]; }
   inline byte & operator [] (::index i) { return data()[i]; }

   inline operator const byte * () const { return data(); }
   inline operator byte * () { return data(); }

   inline operator const void * () const { return data(); }
   inline operator void * () { return data(); }


   template < primitive_character CHARACTER >
   range < CHARACTER * > get_string_buffer(strsize len)
   {

      set_size((len + 1) * sizeof(CHARACTER));

      auto p = (CHARACTER *)begin();

      p[len] = 0;

      return { p, len, true };

   }


   memory_base & operator = (const ::memory_base & memory) { assign(memory.data(), memory.size()); return *this; }
   memory_base & operator = (const ::block & block) { assign(block.data(), block.size()); return *this; }


   memory_base & operator += (const ::memory_base & memory) { append(memory.data(), memory.size()); return *this; }
   memory_base & operator += (const ::block & block) { append(block.data(), block.size()); return *this; }


   void from_string(const ::wide_character * pwsz);
   void from_string(const ::scoped_string & scopedstr);
   void from_string(const ::string & str);
   void from_string(const ::payload & payload);
   void append_from_string(const ::wide_character * pwsz);
   void append_from_string(const ::scoped_string & scopedstr);
   void append_from_string(const ::string & str);
   void append_from_string(const ::payload & payload);
   void append_byte(byte b){ append(&b, 1);}
   //::string as_string(memsize iStart = 0, memsize uiSize = -1) const;
   virtual string get_string() const;
   virtual string get_string(memsize iStart, memsize uiSize = -1) const;

   void delete_begin(memsize iSize);
   void eat_begin(void * pdata, memsize iSize);
   void set_data(void * pdata, memsize uiSize);
   void copy_from(const memory_base * pstorage);
   void copy_from(const void * pdata, memsize s);
   void copy_to(void * pdata, memsize s) const;
   void set(byte b,memsize iStart = 0,memsize uiSize = -1);
   void zero(memsize iStart = 0, memsize uiSize = -1);

   
   void assign(const ::block & block);
   void assign(const void * pdata, memsize iCount);
   void assign(const void * pdata, memsize iStart, memsize iCount);
   void assign(memsize iCount, uchar uch);


   void append(const ::block & block);
   void append(const void * pdata, memsize iCount);
   void append(memsize iCount, uchar uch);
   void append(const memory_base & memory, memsize iStart = 0, memsize iCount = -1);
   void append(byte b);

   void clear();

   void splice(const u8 * pbMemory, memsize iCountSrc, memsize iStartDst = 0, memsize iCountDst = 0);
   void splice(const memory_base & memory, memsize iStartDst = 0, memsize iCountDst = 0, memsize iStartSrc = 0, memsize iCountSrc = -1);

   void move_and_grow(memsize offset);
   void transfer(memsize offset, bool bGrow = false);

   //void assign(const ::scoped_string & scopedstr);
   //void append(const ::scoped_string & scopedstr);

   void to_hex(string & str, memsize iStart = 0, memsize size = -1);
   string to_hex(memsize iStart = 0, memsize size = -1);
   strsize from_hex(const ::scoped_string & scopedstr);

   void to_base64(string & str, memsize iStart = 0, memsize size = -1);
   string to_base64(memsize iStart = 0, memsize size = -1);
   void from_base64(const ::scoped_string & scopedstr);

   inline void to_asc(string & str) const { str.assign((const char *) data(), size()); }
   inline string to_asc() const { string str; to_asc(str); return str; }
   inline void from_asc(const ::scoped_string & scopedstr) { assign(scopedstr.c_str(), scopedstr.size()); }

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


   byte * find(const ::block& block, ::index iStart = 0) const;
   ::index find_index(const ::block& block, ::index iStart = 0) const;
   ::index find_index(char ch, ::index iStart = 0) const;
   byte* rear_find(const ::block& block, ::index iStart = 0) const;
   ::index reverse_find_index(const ::block& block, ::index iStart = 0) const;
   byte* reverse_find_byte_not_in_block(const ::block& block, ::index iStart = 0) const;
   ::index reverse_find_index_of_byte_not_in_block(const ::block& block, ::index iStart = 0) const;

   byte * find_line_prefix(const ::block& blockPrefix, ::index iStart = 0);
   ::index find_line_prefix_index(const ::block& blockPrefix, ::index iStart = 0);
   void patch_line_suffix(const ::block & blockPrefix, const ::block& blockSuffix, ::index iStart = 0);


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

   //void fread(FILE * pfile);


};


//inline byte * memory_base::internal_get_data() const
//{
//   return (byte *) m_memory.begin();
//}
//inline memsize memory_base::size() const
//{
//   return size();
//}
//inline byte * memory_base::data() const
//{
//   return (byte*)m_memory.m_pbegin;
//}
//inline byte * memory_base::data()
//{
//   return (byte*)m_memory.m_pbegin;
//}
//inline byte * memory_base::data() const
//{
//   return data();
//}
//inline byte * memory_base::data()
//{
//   return data();
//}
//inline bool memory_base::has_data() const
//{
//   return size() > 0;
//}
//inline bool memory_base::is_empty() const
//{
//   return !has_data();
//}


//inline uchar memory_base::operator [] (::index i) const
//{
//   return this->data()[i];
//}
//inline uchar & memory_base::operator [] (::index i)
//{
//   return this->data()[i];
//}


//inline memory_base::operator const u8 *() const
//{
//   return this->data();
//}
//inline memory_base::operator u8 *()
//{
//   return this->data();
//}
//inline memory_base::operator const void *() const
//{
//   return this->data();
//}
//inline memory_base::operator void *()
//{
//   return this->data();
//}

inline void memory_base::allocate_add_up(memsize iAddUp)
{

   if (iAddUp != 0)
   {

      set_size(size() + iAddUp);

   }

}

inline void memory_base::splice(const memory_base & memory, memsize iStartDst, memsize iCountDst, memsize iStartSrc, memsize iCountSrc)
{

   splice(
   &memory.data()[iStartSrc],
   minimum(memory.size(), iCountSrc < 0 ? memory.size() - iCountSrc + 1 : iCountSrc),
   iStartDst,
   iCountDst);

}


inline void memory_base::set_char_at_grow(strsize iChar, char ch)
{

   if (::comparison::ge(iChar, size()))
   {

      set_size(iChar + 1);

   }

   ((char*)data())[iChar] = ch;

}

