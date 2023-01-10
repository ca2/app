#include "framework.h"
#include "acme/exception/no_memory.h"
#include "acme/filesystem/file/file.h"
//#include "acme/memory/_memory.h"
#include "acme/primitive/primitive/memory.h"
//#include "acme/primitive/primitive/payload.h"
#include "acme/primitive/string/base64.h"
#include "acme/primitive/string/hex.h"
#include "acme/primitive/string/international.h"
#include "acme/_operating_system.h"


#ifdef WINDOWS
#include <Shcore.h>
#endif


MEMORY::MEMORY()
{

#if MEMDLEAK

   m_iLine = 0;

#endif

   m_bOwner = false;
   m_bReadOnly = true;
   m_beginStorage = nullptr;
   m_begin = nullptr;

   m_sizeStorage = 0;
   m_end = 0;
   m_dwAllocationAddUp = 4096;
   m_dAllocationRateUp = (double)(1.0 - ((double)m_dwAllocationAddUp / 2.0) * log((double)m_dwAllocationAddUp - 1.0)) / (1 - log((double)m_dwAllocationAddUp - 1.0));
   m_pcontainer = nullptr;
   m_pprimitivememory = nullptr;
   m_psharedmemory = nullptr;
   m_pvirtualmemory = nullptr;

}


memory_base::~memory_base()
{

   this->m_sizeStorage          = 0;
   this->m_end      =  nullptr;
   this->m_beginStorage          = nullptr;
   this->m_begin         = nullptr;

}


memory_base & memory_base::prefix_der_length()
{
   i32 msb = ::msb(size());
   if(msb < 7)
   {
      move_and_grow(1);
      data()[0] = (byte)(size() - 1);
   }
   else
   {
      i32 iLen = (msb + 8) / 8;
      move_and_grow(1 + iLen);
      data()[0] = 0x80 | iLen;
      auto s = size() - 1 - iLen;
      u8 * p = (u8 *)&s;
      for(i32 i = 1; i <= iLen; i++)
      {
         data()[i] = p[iLen - i];
      }
   }
   return *this;
}


memory_base & memory_base::prefix_der_uint_content()
{
   if(size() > 0)
   {
      if(data()[0] & 0x80)
      {
         move_and_grow(1);
         data()[0] = 0;
      }
   }
   return *this;
}

memory_base & memory_base::prefix_der_type(i32 iType)
{

   move_and_grow(1);

   data()[0] = iType;

   return *this;

}

memory_base & memory_base::prefix_der_uint()
{
   return prefix_der_uint_content().prefix_der_length().prefix_der_type(2); // 2 - integer
}

memory_base & memory_base::prefix_der_sequence()
{
   return prefix_der_length().prefix_der_type(0x30); // 0x30 - universal sequence
}


memory memory_base::detach_as_primitive_memory()
{

   if (this->m_ememory == e_memory_primitive && this->m_pprimitivememory)
   {

      return ::transfer(*this->m_pprimitivememory);

   }

   return { data(), size() };

}


void memory_base::set_size(memsize dwNewLength)
{


   if(dwNewLength <= 0)
   {
      
      this->m_begin = this->m_beginStorage;
      
      this->m_end = this->m_begin;

      return;

   }

   if ((this->offset() + dwNewLength) <= this->storage_size())
   {

      this->m_end = this->m_begin + dwNewLength;

      return;

   }

   erase_offset();

   if(dwNewLength > this->storage_size())
   {

      allocate_internal(dwNewLength);

   }

   this->m_end = this->m_begin + dwNewLength;

}


byte * memory_base::impl_alloc(memsize dwAllocation)
{

   return nullptr;

}

byte * memory_base::impl_realloc(void * pdata, memsize dwAllocation)
{

   return nullptr;

}

void memory_base::impl_free(byte * pdata)
{

}


void memory_base::allocate_internal(memsize sizeNew)
{

   if(sizeNew < 0)
   {

      throw ::exception(error_invalid_parameter);

   }
   else if(sizeNew == 0)
   {

      return;

   }

   erase_offset();

   memsize sizeNewStorage = calc_allocation(sizeNew);

   if(sizeNewStorage < sizeNew)
   {

      throw ::exception(error_wrong_state);

   }

   byte * pOldStorage = this->storage_begin();

   byte * pNewStorage = nullptr;

   memsize sizeOld = this->size();

   memsize sizeOldStorage = this->storage_size();

   if(::is_null(pOldStorage) || !this->m_bOwner || this->m_bReadOnly)
   {

      pNewStorage = (byte *) impl_alloc(sizeNewStorage);

      if (pOldStorage && (!this->m_bOwner || this->m_bReadOnly))
      {

         ::memcpy_dup(pNewStorage, pOldStorage, (memsize) minimum(sizeOld, sizeNewStorage));

      }

      this->m_bOwner = true;

      this->m_bReadOnly = false;

   }
   else if(sizeNew > sizeOldStorage)
   {

      pNewStorage = impl_realloc(pOldStorage, (size_t)sizeNewStorage);

      if(::is_null(pNewStorage))
      {

         pNewStorage = impl_alloc((size_t)sizeNewStorage);

         ::memcpy_dup(pNewStorage, pOldStorage, sizeOld);

         impl_free(pOldStorage);

      }

   }

   if (pNewStorage)
   {

      this->m_beginStorage = pNewStorage;

      this->m_sizeStorage = sizeNewStorage;

      this->m_begin = pNewStorage;

   }

   this->m_end = this->m_begin + sizeNew;

}


void memory_base::reserve(memsize dwNewLength)
{

   if (dwNewLength <= this->size())
   {

      return;

   }

   allocate_internal(dwNewLength);

}


void memory_base::erase_offset()
{

   if (this->m_beginStorage == nullptr || this->m_begin == nullptr || this->offset() <= 0)
   {

      return;

   }

   auto size = this->size();

   __memmov(this->m_beginStorage,this->m_begin,size);

   this->m_begin = this->m_beginStorage;

   this->m_end = this->m_begin + size;

}

//void memory_base::random_bytes(::count c)
//{
//
//   if (c >= 0)
//   {
//
//      set_size(c);
//
//   }
//
//   if (size() > 0)
//   {
//
//      acmesystem()->math().random_bytes(data(), size());
//
//   }
//
//}


memsize memory_base::calc_allocation(memsize size)
{

   return (memsize) (size + this->m_dwAllocationAddUp);

}


//stream & memory_base::write(::stream & stream) const
//{
//
//   __mutable(this)->exchange(stream);
//
//   return stream;
//
//}
//
//
//stream & memory_base::read(::stream & stream)
//{
//
//   exchange(stream);
//
//   return stream;
//
//}


void memory_base::delete_begin(memsize iSize)
{

   if (iSize < 0)
   {

      throw ::exception(error_bad_argument);

   }
   else if (iSize > this->size())
   {

      throw ::exception(error_bad_argument);

   }
   else if (iSize == 0)
   {

      return;

   }

   this->m_begin += iSize;

}


void memory_base::transfer_to(::file::file * pfileOut, memsize uiBufferSize) const
{

   if (data() == nullptr || this->is_empty())
   {

      return;

   }

   if(pfileOut->increase_internal_data_size(size()) && pfileOut->get_internal_data() != nullptr)
   {

      if(pfileOut->get_internal_data() == data())
         return;

      __memmov(((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position() + size(),((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position(),pfileOut->get_internal_data_size() - size());
      ::memcpy_dup(((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position(),data(),size());

      pfileOut->position() += size();

   }
   else
   {

      pfileOut->write(data(),size());

   }

}


void memory_base::transfer_from_begin(::file::file * pfileIn,memsize uiBufferSize)
{

   pfileIn->seek_to_begin();

   transfer_from(pfileIn,uiBufferSize);

}


void memory_base::transfer_from(::file::file * pfileIn,memsize uiBufferSize)
{

   if(pfileIn->get_internal_data() != nullptr && pfileIn->get_internal_data_size() > pfileIn->get_position())
   {

      append((u8 *)pfileIn->get_internal_data() + pfileIn->get_position(),(memsize) (pfileIn->get_internal_data_size() - pfileIn->get_position()));

   }
   else
   {

      ::filesize filesize = pfileIn->size();

      if (filesize >= 0)
      {

         if (filesize > ::numeric_info < memsize> ::maximum())
         {

            throw ::exception(error_no_memory);

         }

         set_size((::memsize) filesize);

         memsize uRead = pfileIn->read(data(), (memsize) size());

         set_size(uRead);

      }
      else
      {

         memsize uRead;

         memsize uiSize = 0;

         while (true)
         {

            set_size(uiSize + uiBufferSize);

            uRead = pfileIn->read(&data()[uiSize], uiBufferSize);

            if (uRead <= 0)
            {
               break;

            }

            uiSize += uRead;

         }

         set_size(uiSize);

      }

   }

}


//void memory_base::fread(FILE * pfile)
//{
//
//   ::memory buffer;
//
//   buffer.set_size(1024 * 1024);
//
//   while(true)
//   {
//
//      memsize iRead = ::fread(buffer, 1, buffer.size(), pfile);
//
//      if(iRead > 0)
//      {
//
//         append(buffer, 0, (::memsize) iRead);
//
//      }
//
//      if(iRead <= buffer.size())
//      {
//
//         if(::feof(pfile))
//         {
//
//            break;
//
//         }
//
//         if(::ferror(pfile))
//         {
//
//            i32 iErrNo = errno;
//            
//            auto errorcode = errno_error_code(iErrNo);
//            
//            auto estatus = errno_status(iErrNo);
//            
//            throw ::file::exception(estatus, errorcode, m_path, "");
//
//         }
//
//         break;
//
//      }
//
//   }
//
//}


memory_base & memory_base::erase(memsize pos,memsize len)
{

   if(pos < 0)
   {

      pos = size() + pos;

   }

   if(len < 0)
   {

      len = size() - pos + len + 1;

   }

   if(pos < 0)
   {

      pos = 0;

   }

   len = minimum(len,size() - pos);

   if(len <= 0)
   {

      return *this;

   }

   if(pos >= size())
   {

      return *this;

   }

   __memmov(this->m_begin + pos,this->m_begin + pos + len,size() - (pos + len));

   set_size(size() - len);

   return *this;

}

#ifdef WINDOWS_DESKTOP

//
//comptr < IStream > memory_base::create_istream() const
//{
//
//   if (data() == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   return ::SHCreateMemStream(data(),(::u32)size());
//
//}


//#elif defined(_UWP)
//
//comptr < IStream > memory_base::create_istream() const
//{
//
//   if (data() == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   ::winrt::Windows::Storage::Streams::InMemoryRandomAccessStream ^ randomAccessStream = ref memory_new ::winrt::Windows::Storage::Streams::InMemoryRandomAccessStream();
//
//   ::wait(randomAccessStream->WriteAsync(get_os_buffer()));
//
//   IStream * pstream = nullptr;
//
//   ::CreateStreamOverRandomAccessStream(randomAccessStream,IID_PPV_ARGS(&pstream));
//
//   return pstream;
//
//
//}
#endif


::string memory_base::get_string() const
{

   if(size() >= 2 && data()[0] == 255 && data()[1] == 60)
   {

      memory mem;

      mem.set_size(utf_to_utf_length((char *) data(),(const ::wd16_character *)&data()[2],size() - 2));

      utf_to_utf((char *) mem.data(),(const ::wide_character *)&data()[2],(i32)(size() - 2));

      return { (const char *)mem.data(), mem.size() };

   }
   else if(size() >= 3 && data()[0] == 255 && data()[1] == 254 && data()[2] == 0x73)
   {

      memory mem;

      mem.set_size(utf_to_utf_length((char *) data(),(const ::wd16_character *)&data()[3],size() - 3));

      utf_to_utf((char *)mem.data(),(const ::wd16_character *)&data()[3],(i32)(size() - 3));

      return { (const char *)mem.data(), mem.size() };

   }
   else if(size() >= 3 && data()[0] == 0xef && data()[1] == 0xbb && data()[2] == 0xbf)
   {

      return { (const char *)data() + 3, size() - 3 };

   }
   else
   {

      return { (const char *)data(), size() };

   }

}


string memory_base::as_utf8() const
{

   string strResult;

   if (size() >= 2
         && data()[0] == 255
         && data()[1] == 60)
   {

      utf_to_utf(strResult, (::wd16_character *)&data()[2], (i32)(size() - 2));

   }
   else if (size() >= 2
            && data()[0] == 255
            && data()[1] == 254)
   {

#ifdef ANDROID
      //for (index i = 2; i < storage.size(); i += 2)
      //{
      //   byte b = storage.data()[i];
      //   storage.data()[i] = storage.data()[i + 1];
      //   storage.data()[i + 1] = b;
      //}
#endif
      utf_to_utf(strResult, (const ::wd16_character *)&data()[2], (i32)(size() - 2));

   }
   else if (size() >= 3
            && data()[0] == 0xef
            && data()[1] == 0xbb
            && data()[2] == 0xbf)
   {

      strResult = string((const char *)&data()[3], (i32)(size() - 3));

   }
   else
   {

      strResult = string((const char *)data(), (i32)size());

   }

   return strResult;

}


char * memory_base::c_str()
{

   if (size() <= 0)
   {

      return nullptr;

   }

   if (data()[size() - 1] != '\0')
   {

      allocate_add_up(1);

      data()[size() - 1] = '\0';

   }

   return (char *)data();

}


//bool memory_base::begins(const ::scoped_string & scopedstr) const
//{
//
//
//
//}
//
//
//bool memory_base::case_insensitive_begins(const ::scoped_string & scopedstr, strsize iCount) const
//{
//
//   if (::is_null(psz) || *psz == '\0')
//   {
//
//      return true;
//
//   }
//
//   const ::scoped_string & scopedstrThis = (const char *)data();
//
//   if (::is_null(pszThis))
//   {
//
//      return false;
//
//   }
//
//   if (iCount < 0)
//   {
//
//      iCount += strlen(psz) + 1;
//
//   }
//
//   if (size() < iCount)
//   {
//
//      return false;
//
//   }
//
//   return !ansi_count_compare_ci(pszThis, psz, (size_t) iCount);
//
//}
//
//
//bool memory_base::begins(const ::string & str, strsize iCount) const
//{
//
//   if (iCount < 0)
//   {
//
//      iCount += str.length() + 1;
//
//   }
//
//   if (size() < iCount)
//   {
//
//      return false;
//
//   }
//
//   return _memory_order(data(), str.c_str(), iCount) == 0;
//
//}
//
//
//bool memory_base::case_insensitive_begins(const ::string & str, strsize iCount) const
//{
//
//   if (iCount < 0)
//   {
//
//      iCount += str.length() + 1;
//
//   }
//
//   if (size() < iCount)
//   {
//
//      return false;
//
//   }
//
//   return ansi_count_compare_ci((const char*) data(), str.c_str(), iCount) == 0;
//
//}
//
//
//bool memory_base::ends(const ::scoped_string & scopedstr, strsize iCount) const
//{
//
//   if (iCount < 0)
//   {
//
//      iCount += strlen(psz) + 1;
//
//   }
//
//   if (size() < iCount)
//   {
//
//      return false;
//
//   }
//
//   return _memory_order(data() + size() - iCount, psz, iCount) == 0;
//
//}
//
//
//bool memory_base::case_insensitive_ends(const ::scoped_string & scopedstr, strsize iCount) const
//{
//
//   if (::is_null(psz) || *psz == '\0')
//   {
//
//      return true;
//
//   }
//
//   const ::scoped_string & scopedstrThis = (const char *)data();
//
//   if (::is_null(pszThis))
//   {
//
//      return false;
//
//   }
//
//   if (iCount < 0)
//   {
//
//      iCount += strlen(psz) + 1;
//
//   }
//
//   if (size() < iCount)
//   {
//
//      return false;
//
//   }
//
//   return ansi_count_compare_ci(pszThis + size() - iCount, psz, (size_t) iCount) == 0;
//
//}
//
//
//bool memory_base::ends(const ::string & str, strsize iCount) const
//{
//
//   if (iCount < 0)
//   {
//
//      iCount += str.length() + 1;
//
//   }
//
//   if (size() < iCount)
//   {
//
//      return false;
//
//   }
//
//   return _memory_order(data() + size() - iCount, str.c_str(), iCount) == 0;
//
//}
//
//
//bool memory_base::case_insensitive_ends(const ::string & str, strsize iCount) const
//{
//
//   if (iCount < 0)
//   {
//
//      iCount += str.length() + 1;
//
//   }
//
//   if (size() < iCount)
//   {
//
//      return false;
//
//   }
//
//   return ansi_count_compare_ci((const char*) data() + size() - iCount, str.c_str(), iCount) == 0;
//
//}


//bool memory_base::is_enabled() const
//{
//
//   if (m_bLockMode)
//      return is_locked();
//   else
//      return true;
//
//}


bool memory_base::operator == (const memory_base & s) const
{

   if (this->size() != s.size())
   {

      return false;

   }

   return memory_order(data(), s.data(), (size_t)this->size()) == 0;

}

bool memory_base::operator == (const struct block & s) const
{

   if (this->size() != s.size())
   {

      return false;

   }

   return memory_order(data(), s.data(), (size_t)this->size()) == 0;

}


void memory_base::copy_from(const memory_base *pstorage)
{

   ASSERT(pstorage != nullptr);

   set_size(pstorage->size());

   ::memcpy_dup(data(), pstorage->data(), (size_t) this->size());

}

void memory_base::copy_from(const void * pdata, memsize s)
{

   defer_set_size(s);

   ::memcpy_dup(data(), pdata, (size_t)minimum(this->size(), s));

}


void memory_base::copy_to(void * pdata, memsize s) const
{

   if (is_empty())
   {

      return;

   }

   ::memcpy_dup(pdata, data(), (size_t)minimum(this->size(), s));

}


void memory_base::set_data(void *pdata, memsize uiSize)
{

   set_size(uiSize);

   ::memcpy_dup(data(), pdata, (size_t)uiSize);

}


void memory_base::set(byte b, memsize iStart, memsize uiSize)
{

   if (uiSize + iStart > size())
      uiSize = size() - iStart;

   memory_set(data() + iStart, b, (size_t)uiSize);

}


void memory_base::zero(memsize iStart, memsize uiSize)
{

   set(0, iStart, uiSize);

}


void memory_base::eat_begin(void * pdata, memsize iSize)
{

   ASSERT(iSize <= this->size());

   if (iSize <= this->size())
   {

      delete_begin(iSize);

   }

}


//memory_base & memory_base::operator = (const memory_base & s)
//{
//
//   if (this != &s)
//   {
//
//      copy_from(&s);
//
//   }
//
//   return *this;
//
//}


//memory_base & memory_base::operator += (const block & block)
//{
//
//   append(block);
//
//   return *this;
//
//}
//
//
//memory_base & memory_base::operator += (const memory_base & s)
//{
//
//   append(s);
//
//   return *this;
//
//}


void memory_base::to_hex(string & str, memsize pos, memsize count)
{

   if (pos > this->size())
   {

      throw ::exception(error_bad_argument);

   }

   if (count < 0)
   {

      count += this->size() - pos + 1;

   }

   if (pos + count > this->size())
   {

      count = this->size() - pos;

   }

   char * pchSrc = (char *)data();

   char * pchDst = str.get_string_buffer(count * 2);

   u64 tickEnd = pos + count;

   for (u64 dw = pos; dw < tickEnd; dw++)
   {

      if (((pchSrc[dw] & 0xf0) >> 4) < 10)
      {

         *pchDst = (char)(((pchSrc[dw] & 0xf0) >> 4) + '0');

      }
      else
      {

         *pchDst = (char)(((pchSrc[dw] & 0xf0) >> 4) + 'A' - 10);

      }

      pchDst++;

      if (((pchSrc[dw] & 0x0f)) < 10)
      {

         *pchDst = (char)((pchSrc[dw] & 0x0f) + '0');

      }
      else
      {

         *pchDst = (char)((pchSrc[dw] & 0x0f) + 'A' - 10);

      }

      pchDst++;

   }

   str.release_string_buffer();

}


string memory_base::to_hex(memsize pos, memsize size)
{

   string str;

   to_hex(str, pos, size);

   return str;

}


strsize memory_base::from_hex(const ::scoped_string & scopedstr)
{

   char ch;

   bool bOdd = false;

   strsize iLen = scopedstr.size();

   bOdd = (iLen % 2) != 0;

   if (bOdd)
   {

      iLen++;

   }

   auto psz = scopedstr.begin();

   set_size(iLen / 2);

   char * pch = (char *)data();

   strsize i = 0;

   char ch2;

   while (i < iLen)
   {

      try
      {

         ch = ::hex::to_nibble(psz[i]);

      }
      catch (...)
      {

         break;

      }

      i++;

      if (i < iLen)
      {

         try
         {

            ch2 = ::hex::to_nibble(psz[i]);

         }
         catch (...)
         {

            *pch = ch;

            break;

         }

         ch <<= 4;

         ch |= ch2;

      }

      *pch = ch;

      pch++;

      i++;

   }

   truncate(i);

   return i;

}


void memory_base::to_base64(string & str, memsize pos, memsize count)
{

   if (data() == nullptr)
   {

      return;

   }

   ::base64 base64;

   str = base64.encode({&data()[pos], minimum(this->size() - pos, count)});

}


string memory_base::to_base64(memsize pos, memsize size)
{

   string str;

   to_base64(str, pos, size);

   return str;

}


void memory_base::from_base64(const ::scoped_string & scopedstr)
{

   ::base64 base64;

   base64.decode(*this, scopedstr);

}


//void memory_base::to_asc(string & str)
//{
//
//   str.assign(data(), size());
//
//}
//
//
//bool memory_base::from_asc(const ::scoped_string & scopedstr)
//{
//
//
//}


void memory_base::from_string(const ::wide_character * pwsz)
{

   from_string(unicode_to_utf8(pwsz));

}


void memory_base::from_string(const ::scoped_string & scopedstr)
{

   set_size(scopedstr.size());

   ::memcpy_dup(data(), scopedstr.begin(), this->size());

}


void memory_base::from_string(const ::string & str)
{

   set_size(str.length());

   ::memcpy_dup(data(), str, this->size());

}


void memory_base::from_string(const ::payload & payload)
{

   from_string((const string &)payload.get_string());

}


void memory_base::append_from_string(const ::wide_character * pwsz)
{

   append_from_string(unicode_to_utf8(pwsz));

}


void memory_base::append_from_string(const ::scoped_string & scopedstr)
{

   auto sizeOld = size();

   auto lenExtra = scopedstr.size();

   allocate_add_up(lenExtra);

   ::memcpy_dup(data() + sizeOld, scopedstr.begin(), lenExtra);

}


void memory_base::append_from_string(const ::string & str)
{


   auto sizeOld = size();

   auto lenExtra = str.length();

   allocate_add_up(lenExtra);

   ::memcpy_dup(data() + sizeOld, str.c_str(), lenExtra);
   
}


void memory_base::append_from_string(const ::payload & payload)
{

   append_from_string((const string &)payload.get_string());

}


//string memory_base::as_string() const
//{
//
//   return as_string(0);
//
//}


string memory_base::get_string(memsize iStart, memsize iCount) const
{

   string str;

   if ((memsize)iStart < 0)
   {

      *((memsize*)iStart) += this->size();

   }

   if (iStart > this->size())
   {

      return str;

   }

   if (iCount < 0)
   {

      iCount += this->size() - iStart + 1;

   }

   if (iStart + iCount > this->size())
   {

      iCount = this->size() - iStart - iCount;

   }

   if (iCount <= 0)
   {

      return str;

   }

   if (data() == nullptr)
   {

      return str;

   }

   char * psz = str.get_string_buffer(iCount + 1);

   ::memcpy_dup(psz, &data()[iStart], iCount);

   psz[iCount] = '\0';

   str.release_string_buffer();

   return str;

}


//string memory_base::to_string(memsize iStart, memsize iCount) const
//{
//
//   string str;
//
//   to_string(str, iStart, iCount);
//
//   return str;
//
//}


void memory_base::move_and_grow(memsize offset)
{

   transfer(offset, true);

}


void memory_base::transfer(memsize offset, bool bGrow)
{

   if (offset > 0)
   {

      if (bGrow)
      {

         this->allocate_add_up(offset);

      }

      if ((memsize)offset > this->size())
      {

         return;

      }

      __memmov(&this->data()[offset], this->data(), this->size() - offset);

   }
   else if (offset < 0)
   {

      offset = -offset;

      if (bGrow)
      {

         this->allocate_add_up(offset);

      }

      if ((memsize)offset > this->size())
      {

         return;

      }

      __memmov(this->data(), &this->data()[offset], this->size() - offset);

   }

}

void memory_base::append(byte b)
{

   append(&b, 1);

}


void memory_base::clear()
{

   set_size(0);

}


void memory_base::append(const memory_base & mem, memsize iStart, memsize iCount)
{

   if ((memsize)iStart < 0)
   {

      *((memsize*)iStart) += mem.size();

   }

   if (iStart > mem.size())
   {

      return;

   }

   if (iStart + iCount > mem.size())
   {

      iCount = mem.size() - iStart;

   }

   if (iCount <= 0)
   {

      return;

   }

   allocate_add_up(iCount);

   ::memcpy_dup(&data()[this->size() - iCount], &mem.data()[iStart], (size_t)iCount);

}


void memory_base::append(const void * pdata, memsize iCount)
{

   if (iCount <= 0)
   {

      return;

   }

   memsize iOldSize = size();

   allocate_add_up(iCount);

   ::memcpy_dup(&data()[iOldSize], pdata, (size_t)iCount);

}


void memory_base::assign(const void * pdata, memsize iCount)
{

   set_size(iCount);

   ::memcpy_dup(data(), pdata, (size_t)iCount);

}


void memory_base::assign(const void * pdata, memsize iStart, memsize iCount)
{

   set_size(iCount);

   ::memcpy_dup(data(), &((byte *)pdata)[iStart], (size_t)iCount);

}


void memory_base::append(memsize iCount, uchar uch)
{

   allocate_add_up(iCount);

   memsize iStart = this->size() - iCount;

   memsize iEnd = iStart + iCount - 1;

   for (memsize i = iStart; i <= iEnd; i++)
   {

      data()[i] = uch;

   }

}


void memory_base::splice(const u8 * pbMemory, memsize iCountSrc, memsize iStartDst, memsize iCountDst)
{

   if (iCountSrc <= 0)
   {

      iCountSrc = 0;

   }

   if (iCountDst < 0)
   {

      iCountDst = size();

   }

   if(iCountSrc >= iCountDst)
   {

      //_____________dddddddddddddddd
      //aaaaaaaaaaaaabbbcccccccccccccccccccccccc

      memsize iSize = size();

      memsize iMove = iSize - minimum(iSize, iStartDst + iCountDst);

      allocate_add_up(iCountSrc - iCountDst);

      ::__memmov(&data()[iStartDst + iCountSrc], &data()[iStartDst + iCountDst], iMove);

   }
   else if (iCountSrc < iCountDst)
   {

      //_____________ddd
      //aaaaaaaaaaaaabbbbbbbbbbbbbbbbcccccccccccccccccccccccc

      memsize iSize = size();

      memsize iMove = iSize - minimum(iSize, iStartDst + iCountDst);

      ::__memmov(&data()[iStartDst + iCountSrc], &data()[iStartDst + iCountDst], iMove);

      allocate_add_up(iCountSrc - iCountDst);

   }

   if (iCountSrc > 0)
   {

      ::memcpy_dup(&data()[iStartDst], pbMemory, iCountSrc);

   }

}


void memory_base::assign(memsize iCount, uchar uch)
{

   set_size(iCount);

   memsize iEnd = iCount - 1;

   for (memsize i = 0; i <= iEnd; i++)
   {

      this->data()[i] = uch;

   }

}



//void memory_base::assign(const ::scoped_string & scopedstr)
//{
//
//   return from_string(psz);
//
//}
//
//
//void memory_base::append(const ::scoped_string & scopedstr)
//{
//
//   return append_from_string(psz);
//
//}


#if defined(_UWP) && defined(__cplusplus_winrt)


Array < uchar, 1U > ^ memory_base::get_os_bytes(memsize pos, memsize size) const
{

   if (pos > size())
   {

      throw ::exception(error_bad_argument);

   }

   if (size < 0 || pos + size > size())
   {

      size = size() - pos;

   }

   return ref memory_new Array < uchar, 1U >((uchar *)&data()[pos], size);

}


::winrt::Windows::Storage::Streams::IBuffer ^ memory_base::get_os_crypt_buffer(memsize pos, memsize size) const
{

   Array < uchar, 1U >^ pbytes = get_os_bytes(pos, size);

   return ::winrt::Windows::Security::Cryptography::CryptographicBuffer::CreateFromByteArray(pbytes);

}


::winrt::Windows::Storage::Streams::IBuffer ^ memory_base::get_os_buffer(memsize pos, memsize size) const
{

   ::winrt::Windows::Storage::Streams::DataWriter ^ writer = ref memory_new ::winrt::Windows::Storage::Streams::DataWriter();

   Array < uchar, 1U >^ pbytes = get_os_bytes(pos, size);

   writer->WriteBytes(pbytes);

   return writer->DetachBuffer();

}


void memory_base::set_os_bytes(Array < uchar, 1U > ^ a, memsize pos, memsize size)
{

   if (!a)
   {

      return;

   }

   if (pos > (memsize) a->Length)
   {

      throw ::exception(error_bad_argument);

   }

   if (pos > (memsize) a->Length)
   {

      throw ::exception(error_bad_argument);

   }

   if (size < 0 || pos + size > (memsize) a->Length)
   {

      size = a->Length - pos;

   }

   set_size(size);

   ::memcpy_dup(data(), &a->Data[pos], size);

}


void memory_base::set_os_crypt_buffer(::winrt::Windows::Storage::Streams::IBuffer ^ ibuf, memsize pos, memsize size)
{

   Array < uchar, 1U > ^ a = nullptr;

   ::winrt::Windows::Security::Cryptography::CryptographicBuffer::CopyToByteArray(ibuf, &a);

   return set_os_bytes(a, pos, size);

}


void memory_base::set_os_buffer(::winrt::Windows::Storage::Streams::IBuffer ^ ibuf, memsize pos, memsize size)
{

   ::winrt::Windows::Storage::Streams::DataReader^ r = ::winrt::Windows::Storage::Streams::DataReader::FromBuffer(ibuf);

   Array<uchar, 1U>^ a = ref memory_new Array<uchar, 1U>(ibuf->Length);

   r->ReadBytes(a);

   return set_os_bytes(a, pos, size);

}


#endif


memory_base & memory_base::reverse()
{
   if (this->data() != nullptr)
   {
      ::reverse_memory(this->data(), this->size());
   }
   return *this;
}


memsize memory_base::get_length() const
{

   return size();

}


memsize memory_base::length() const
{

   return size();

}


::particle * memory_base::clone() const
{

   auto pmemory = memory_new memory();

   pmemory->copy_from(this);

   return pmemory;

}


byte* memory_base::find_line_prefix(const ::block& blockPrefix, ::index iStart)
{

   auto iFind = find_line_prefix_index(blockPrefix, iStart);

   if (iFind < 0)
   {

      return nullptr;

   }

   return data() + iFind;

}


::index memory_base::find_line_prefix_index(const ::block& blockPrefix, ::index iStart)
{

   if (is_empty())
   {

      return -1;

   }

   ::index iFind;

   ::count cFindLength;

   if (memcmp(data() + iStart, blockPrefix.data(), blockPrefix.size()) == 0)
   {

      iFind = iStart;

      cFindLength = blockPrefix.size();

   }
   else
   {

      memory memoryFind;

      memoryFind.set_size(blockPrefix.size() + 1);

      memoryFind[0] = '\n';

      memcpy(memoryFind.data() + 1, blockPrefix.data(), blockPrefix.size());

      iFind = find_index(memoryFind, iStart + 1);

      if (iFind < 0)
      {

         return -1;

      }

      cFindLength = memoryFind.get_length();

   }

   return iFind + cFindLength;

}


void memory_base::patch_line_suffix(const ::block& blockPrefix, const ::block& blockSuffix, ::index iStart )
{

   iStart = find_line_prefix_index(blockPrefix, iStart);

   if (iStart < 0)
   {

      throw ::exception(error_not_found);

   }

   auto iFindEol = find_index('\n', iStart);

   if (iFindEol < 0)
   {

      iFindEol = size();

   }

   auto iOldLen = iFindEol - iStart;

   auto iNewLen = blockSuffix.size();

   auto iOldSize = size();

   auto iNewSize = iOldSize - iOldLen + iNewLen;

   set_size(iNewSize);

   auto pdata = (byte*)data();

   if (iNewLen != iOldLen)
   {

      auto ptarget = pdata + iStart + iNewLen;

      auto psource = pdata + iStart + iOldLen;

      auto c = abs(iNewLen - iOldLen);

      memmove(ptarget, psource, iOldSize - iStart - iNewLen);

   }

   if (iNewLen > 0)
   {

      auto ptarget = pdata + iStart;

      auto psource = (const char *) blockSuffix.data();

      auto c = blockSuffix.size();

      memcpy(ptarget, psource, c);

      output_debug_string(" ");

   }

   //return ::success;

}


//bool memory_base::begins(const ::block& block) const
//{
//
//   if(size() < block.size())
//   {
//
//      return false;
//
//   }
//
//   int iMemcmp = memcmp(data(), block.data(), block.size());
//
//   return iMemcmp == 0;
//
//}
//
//
//bool memory_base::ends(const ::block& block) const
//{
//
//   if(size() < block.size())
//   {
//
//      return false;
//
//   }
//
//   int iMemcmp = memcmp(data() + size() - block.size(), block.data(), block.size());
//
//   return iMemcmp == 0;
//
//}



byte * memory_base::find(const ::block & block, ::index iStart) const
{

   return (byte *)memory_find(data() + iStart, size() - iStart, (byte *)block.data(), block.size());

}


::index memory_base::find_index(char ch, ::index iStart) const
{

   auto p = memory_find(data() + iStart, size() - iStart, (byte *)&ch, 1);

   if (!p)
   {

      return -1;

   }

   return ((byte *)p) - data();

}


::index memory_base::find_index(const ::block & block, ::index iStart) const
{

   auto p = find(block, iStart);

   if (!p)
   {

      return -1;

   }

   return ((byte *)p) - data();

}


byte * memory_base::rear_find(const ::block & block, ::index iStart) const
{

   return (byte *)reverse_memmem(data() + iStart, size() - iStart, (byte *)block.data(), block.size());

}


::index memory_base::reverse_find_index(const ::block & block, ::index iStart) const
{

   auto p = rear_find(block, iStart);

   if (!p)
   {

      return -1;

   }

   return ((byte *)p) - data();

}


byte * memory_base::reverse_find_byte_not_in_block(const ::block & block, ::index iStart) const
{

   return (byte *)reverse_byte_not_in_block(data() + iStart, size() - iStart, (byte *)block.data(), block.size());

}


::index memory_base::reverse_find_index_of_byte_not_in_block(const ::block & block, ::index iStart) const
{

   auto p = reverse_find_byte_not_in_block(block, iStart);

   if (!p)
   {

      return -1;

   }

   return ((byte *)p) - data();

}


namespace acme
{



   CLASS_DECL_ACME void transfer_to(::file::file * pfileOut, memory_base & mem, memsize uiBufferSize)
   {

      if (mem.data() == nullptr || mem.size() <= 0)
         return;

      if (pfileOut->increase_internal_data_size(mem.size()) && pfileOut->get_internal_data() != nullptr)
      {

         if (pfileOut->get_internal_data() == mem.data())
            return;

         __memmov(((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position() + mem.size(), ((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position(), pfileOut->get_internal_data_size() - mem.size());

         ::memcpy_dup(((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position(), mem.data(), mem.size());

         pfileOut->position() += mem.size();

      }
      else
      {

         pfileOut->write(mem.data(), mem.size());

      }

   }


   CLASS_DECL_ACME void transfer_from_begin(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize)
   {

      pfileIn->seek_to_begin();

      ::acme::transfer_from(pfileIn, mem, uiBufferSize);

   }


   CLASS_DECL_ACME void transfer_from(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize)
   {

      if (pfileIn->get_internal_data() != nullptr && pfileIn->get_internal_data_size() > pfileIn->get_position())
      {

         mem.append((u8 *)pfileIn->get_internal_data() + pfileIn->get_position(), (memsize)(pfileIn->get_internal_data_size() - pfileIn->get_position()));

      }
      else
      {

         memsize uRead;

         memsize uiSize = 0;

         while (true)
         {

            mem.set_size(uiSize + uiBufferSize);

            uRead = pfileIn->read(&mem.data()[uiSize], uiBufferSize);

            if (uRead <= 0)
            {
               break;

            }

            uiSize += uRead;

         }

         mem.set_size(uiSize);

      }


   }



} // namespace acme



//CLASS_DECL_ACME stream & operator << (stream & stream, memory_container & memcontainer)
//{
//
//   if (memcontainer.get_memory() == nullptr)
//   {
//
//      memcontainer.set_memory(__new(memory(&memcontainer)));
//
//   }
//
//   stream << *memcontainer.get_memory();
//
//   return stream;
//
//}
//
//
//
//CLASS_DECL_ACME stream & operator >> (stream & stream, memory_container & memcontainer)
//{
//
//   if (memcontainer.get_memory() == nullptr)
//   {
//
//      memcontainer.set_memory(__new(memory(&memcontainer)));
//
//   }
//
//   stream >> *memcontainer.get_memory();
//
//   return stream;
//
//}
//

//CLASS_DECL_ACME stream & operator << (stream & stream, memory_base & mem)
//{
//
//   ::acme::transfer_to(stream, mem);
//
//   return stream;
//
//}



//CLASS_DECL_ACME stream & operator >> (stream & stream, memory_base & mem)
//{
//
//   ::acme::transfer_from(stream, mem);
//
//   return stream;
//
//}





//const char * matter::__type_name(this) const
//{
//
//   return __type_name(this);
//
//}




//
//memory_base & memory_base::operator = (const ::block & block)
//{
//
//   assign(block);
//
//   return *this;
//
//}
//

//memory_base & memory_base::operator += (const block & block)
//{
//
//   append(block);
//
//   return *this;
//
//}


void memory_base::assign(const ::block & block)
{

   assign(block.data(), block.size());

}


void memory_base::append(const ::block & block)
{

   append(block.data(), block.size());

}




