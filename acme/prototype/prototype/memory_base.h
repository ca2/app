#pragma once


//#include "acme/filesystem/file/serializable.h"
//#include "acme/memory/memory.h"

//



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
   unsigned char *                  m_beginStorage;
   memsize                 m_sizeStorage;
   double                  m_dAllocationRateUp;
   unsigned int                   m_dwAllocationAddUp;

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

      memory_copy(this, &memory, sizeof(MEMORY));

   }


   void assign(const MEMORY & memory)
   {

      if (this != &memory)
      {

         _assign(memory);

      }

   }

   unsigned char * storage_begin() { return m_beginStorage; }
   const unsigned char * storage_begin() const { return m_beginStorage; }
   memsize storage_size() const { return maximum(0,m_sizeStorage); }
   unsigned char * storage_end() { return storage_begin() + storage_size(); }
   const unsigned char * storage_end() const { return storage_begin() + storage_size(); }
   memsize offset() const { return m_begin - m_beginStorage; }
   memsize max_offset() const { return storage_size(); }

};


template < typename MUTABLE >
MUTABLE * __mutable(const MUTABLE * pmutable) { return (MUTABLE *)pmutable; }


class CLASS_DECL_ACME memory_base :
   public MEMORY,
   virtual public ::subparticle
{
public:

   typedef bstring_manager manager;

   typedef unsigned char value_type;


   //MEMORY      m_memory;

#if MEMDLEAK

   string m_strTag;

   int m_iLine;

#endif


   memory_base() { }
   memory_base(const memory_base & base) : MEMORY(base) {}
   memory_base(memory_base && base) : MEMORY(::transfer(base)) {}
   ~memory_base() override;


   using ::subparticle::clear_flag;
   using MEMORY::operator();


   virtual string as_utf8() const;

   //virtual char * c_str();

   //using MEMORY::begins;
   //virtual bool begins(const ::scoped_string & scopedstr) const { return this->begins((const BLOCK &) scopedstr); }
   //virtual bool begins(const ::scoped_string & scopedstr, character_count iCount = -1) const;

   virtual bool begins_eat(const BLOCK & block);

   //virtual bool case_insensitive_begins(const ::scoped_string & scopedstr, character_count iCount = -1) const{ return ((::const_ansi_range *)this)->case_insensitive_begins(scopedstr); }
   //virtual bool begins(const ::scoped_string & scopedstr, character_count iCount = -1) const;
   //virtual bool case_insensitive_begins(const ::scoped_string & scopedstr, character_count iCount = -1) const;

   //using MEMORY::ends;
   //virtual bool ends(const ::scoped_string & scopedstr) const { return this->ends((const BLOCK &) scopedstr); }
   //virtual bool ends(const ::scoped_string & scopedstr, character_count iCount = -1) const;
   //virtual bool case_insensitive_ends(const ::scoped_string & scopedstr) const { return ((::const_ansi_range *)this)->case_insensitive_ends(scopedstr); }

   virtual bool ends_eat(const BLOCK & block);
   //virtual bool ends(const ::scoped_string & scopedstr, character_count iCount = -1) const;
   //virtual bool case_insensitive_ends(const ::scoped_string & scopedstr, character_count iCount = -1) const;

   virtual memory detach_as_primitive_memory();
   //virtual unsigned char * detach_virtual_memory();
   //virtual HGLOBAL detach_shared_memory();

   //bool is_enabled() const;
   //bool is_locked() const;

   inline void defer_set_size(memsize sizeLarger) { if (sizeLarger > size()) return set_size(sizeLarger); }
   virtual void set_size(memsize dwNewLength);
   virtual void allocate_internal(memsize dwNewLength);

   inline void truncate(memsize sizeSmaller) { if (sizeSmaller < size()) return set_size(sizeSmaller); }

   virtual unsigned char * impl_alloc(memsize dwAllocation);
   virtual unsigned char * impl_realloc(void * pdata,memsize dwAllocation);
   virtual void impl_free(unsigned char * pdata);

   virtual void reserve(memsize dwNewLength);


   virtual void erase_offset();

   //virtual void random_bytes(::collection::count c = -1);


   //virtual ::stream & write(::stream & stream) const override;
   //virtual ::stream & read(::stream & stream) override;


   virtual memsize calc_allocation(memsize size);


   //virtual void transfer_to(::file::file * pfileOut, memsize uiBufferSize = 1024 * 1024) const;
   virtual void assign_file(::file::file * pfileIn, memsize uiBufferSize = 1024 * 1024);
   virtual void assign_entire_file(::file::file * pfileIn, memsize uiBufferSize = 1024 * 1024);

   virtual void append_file(::file::file * pfileIn, memsize uiBufferSize = 1024 * 1024);
   virtual void append_entire_file(::file::file * pfileIn, memsize uiBufferSize = 1024 * 1024);


   void allocate_add_up(memsize iAddUp);


   ::subparticle_pointer clone() override;


//   inline unsigned char * storage_begin() { return m_memory.storage_begin(); }
//   inline const unsigned char * storage_begin() const { return m_memory.storage_begin(); }
//   inline unsigned char * storage_end() { return m_memory.storage_end(); }
//   inline const unsigned char * storage_end() const { return m_memory.storage_end(); }
//   inline memsize storage_size() const { return m_memory.storage_size(); }


   //inline memsize size() const { return m_memory.size(); }
   //inline const unsigned char * data() const { return m_memory.data(); }
   //inline unsigned char * data() { return m_memory.data(); }

   //inline memsize          size() const;
   //inline unsigned char *           data() const;
   //inline unsigned char *           data();

//
//   inline const unsigned char * begin() const { return data();  }
//   inline unsigned char * begin() { return data(); }
//   inline const unsigned char * end() const { return m_memory.end(); }
//   inline unsigned char * end() { return m_memory.end(); }

   //inline const_char_pointer c_str() const { return (const_char_pointer )data(); }
   //inline char * sz() { return (char*)data(); }

   ::block & block() { return *this; }
   const ::block & block() const { return *this; }

   inline bool is_set() const { return MEMORY::is_set(); }
   inline bool is_empty() const { return MEMORY::is_empty(); }
   inline bool has_data() const { return this->size() > 0; }

   inline unsigned char operator [] (::collection::index i) const { return data()[i]; }
   inline unsigned char & operator [] (::collection::index i) { return data()[i]; }

   inline operator const unsigned char * () const { return data(); }
   inline operator unsigned char * () { return data(); }

   inline operator const void * () const { return data(); }
   inline operator void * () { return data(); }


   template < primitive_character CHARACTER >
   range < CHARACTER * > get_buffer(character_count len)
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
   void append_byte(unsigned char b){ append(&b, 1);}
   //::string as_string(memsize iStart = 0, memsize uiSize = -1) const;
   virtual string get_string() const;
   virtual string get_string(memsize iStart, memsize uiSize = -1) const;

   void delete_begin(memsize iSize);
   void eat_begin(const void * pdata, memsize iSize);
   void set_data(const void * pdata, memsize uiSize);
   void set_at(::collection::index i, const void * pdata, memsize uiSize);
   void copy_from(const memory_base * pstorage);
   void copy_from(const void * pdata, memsize s);
   void copy_to(void * pdata, memsize s) const;
   void set(unsigned char b,memsize iStart = 0,memsize uiSize = -1);
   void zero(memsize iStart = 0, memsize uiSize = -1);

   
   void assign(const ::block & block);
   void assign(const void * pdata, memsize iCount);
   void assign(const void * pdata, memsize iStart, memsize iCount);
   void assign(memsize iCount, uchar uch);


   void append(const ::block & block);
   void append(const void * pdata, memsize iCount);
   void append(memsize iCount, uchar uch);
   void append(const memory_base & memory, memsize iStart = 0, memsize iCount = -1);
   void append(unsigned char b);

   void clear();

   void splice(const unsigned char * pbMemory, memsize iCountSrc, memsize iStartDst = 0, memsize iCountDst = 0);
   void splice(const memory_base & memory, memsize iStartDst = 0, memsize iCountDst = 0, memsize iStartSrc = 0, memsize iCountSrc = -1);
   ::memory slice(memsize start, memsize count);
   ::memory left(memsize count);
   ::memory right(memsize count);

   void move_and_grow(memsize offset);
   void transfer(memsize offset, bool bGrow = false);

   //void assign(const ::scoped_string & scopedstr);
   //void append(const ::scoped_string & scopedstr);

   void to_hex(string & str, memsize iStart = 0, memsize size = -1);
   string to_hex(memsize iStart = 0, memsize size = -1);
   character_count from_hex(const ::block & block);

   void to_base64(string & str, memsize iStart = 0, memsize size = -1);
   string to_base64(memsize iStart = 0, memsize size = -1);
   void from_base64(const ::scoped_string & scopedstr);

   inline void to_asc(string & str) const { str.assign((const_char_pointer )data(), size()); }
   inline string to_asc() const { string str; to_asc(str); return str; }
   inline void from_asc(const ::scoped_string & scopedstr) { assign(scopedstr.c_str(), scopedstr.size()); }

   bool operator == (const memory_base & s) const;
   bool operator == (const struct block & block) const ;


   memory_base & reverse();

   memory_base & prefix_der_uint_content();
   memory_base & prefix_der_length();
   memory_base & prefix_der_type(int iType);

   memory_base & prefix_der_uint();
   memory_base & prefix_der_sequence();

   memsize get_length() const;
   memsize length() const;

   inline void set_char_at_grow(character_count iChar, char ch);


   unsigned char * find(const ::block& block, ::collection::index iStart = 0) const;
   ::collection::index find_index(const ::block& block, ::collection::index iStart = 0) const;
   ::collection::index find_index(char ch, ::collection::index iStart = 0) const;
   unsigned char* rear_find(const ::block& block, ::collection::index iStart = 0) const;
   ::collection::index reverse_find_index(const ::block& block, ::collection::index iStart = 0) const;
   unsigned char* reverse_find_byte_not_in_block(const ::block& block, ::collection::index iStart = 0) const;
   ::collection::index reverse_find_index_of_byte_not_in_block(const ::block& block, ::collection::index iStart = 0) const;

   unsigned char * find_line_prefix(const ::block& blockPrefix, ::collection::index iStart = 0);
   ::collection::index find_line_prefix_index(const ::block& blockPrefix, ::collection::index iStart = 0);
   void patch_line_suffix(const ::block & blockPrefix, const ::block& blockSuffix, ::collection::index iStart = 0);


#if defined(UNIVERSAL_WINDOWS) && defined(__cplusplus_winrt)

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


//inline unsigned char * memory_base::internal_get_data() const
//{
//   return (unsigned char *) m_memory.begin();
//}
//inline memsize memory_base::size() const
//{
//   return size();
//}
//inline unsigned char * memory_base::data() const
//{
//   return (unsigned char*)m_memory.m_pbegin;
//}
//inline unsigned char * memory_base::data()
//{
//   return (unsigned char*)m_memory.m_pbegin;
//}
//inline unsigned char * memory_base::data() const
//{
//   return data();
//}
//inline unsigned char * memory_base::data()
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


//inline uchar memory_base::operator [] (::collection::index i) const
//{
//   return this->data()[i];
//}
//inline uchar & memory_base::operator [] (::collection::index i)
//{
//   return this->data()[i];
//}


//inline memory_base::operator const unsigned char *() const
//{
//   return this->data();
//}
//inline memory_base::operator unsigned char *()
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

