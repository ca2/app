#include "framework.h"
#include "acme/exception/exception.h"
#include "acme/filesystem/file/file.h"
#include "acme/primitive/primitive/memory.h"
#include "acme/primitive/primitive/payload.h"
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

   m_bOwn = false;
   m_pbStorage = nullptr;
   m_pdata = nullptr;

   m_cbStorage = 0;
   m_iSize = 0;
   m_dwAllocationAddUp = 4096;
   m_dAllocationRateUp = (double)(1.0 - ((double)m_dwAllocationAddUp / 2.0) * log((double)m_dwAllocationAddUp - 1.0)) / (1 - log((double)m_dwAllocationAddUp - 1.0));
   m_iOffset = 0;
   m_iMaxOffset = 16 * 1024;
   m_pcontainer = nullptr;
   m_pprimitivememory = nullptr;
   m_psharedmemory = nullptr;
   m_pvirtualmemory = nullptr;

}


memory_base::~memory_base()
{

   m_memory.m_cbStorage          = 0;
   m_memory.m_iSize       =  0;
   m_memory.m_pbStorage          = nullptr;
   m_memory.m_pdata         = nullptr;
   m_memory.m_iOffset            = 0;

}


memory_base & memory_base::prefix_der_length()
{
   i32 msb = ::msb(get_size());
   if(msb < 7)
   {
      move_and_grow(1);
      get_data()[0] = (byte)(get_size() - 1);
   }
   else
   {
      i32 iLen = (msb + 8) / 8;
      move_and_grow(1 + iLen);
      get_data()[0] = 0x80 | iLen;
      auto s = get_size() - 1 - iLen;
      u8 * p = (u8 *)&s;
      for(i32 i = 1; i <= iLen; i++)
      {
         get_data()[i] = p[iLen - i];
      }
   }
   return *this;
}


memory_base & memory_base::prefix_der_uint_content()
{
   if(get_size() > 0)
   {
      if(get_data()[0] & 0x80)
      {
         move_and_grow(1);
         get_data()[0] = 0;
      }
   }
   return *this;
}

memory_base & memory_base::prefix_der_type(i32 iType)
{

   move_and_grow(1);

   get_data()[0] = iType;

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

   if (m_memory.m_ememory == e_memory_primitive && m_memory.m_pprimitivememory)
   {

      return ::move(*m_memory.m_pprimitivememory);

   }

   return { get_data(), get_size() };

}


bool memory_base::set_size(memsize dwNewLength)
{

   //if(!is_enabled())
   //{
   //   ASSERT(false);
   //   return false;
   //}

   if((m_memory.m_iOffset + dwNewLength) <= 0)
   {
      m_memory.m_pdata   =m_memory. m_pbStorage + m_memory.m_iOffset;
      m_memory.m_iOffset = 0;
      m_memory.m_cbStorage = 0;
      return true;
   }

   if((m_memory.m_iOffset + dwNewLength) > m_memory.m_iSize)
   {

      if (!allocate_internal(m_memory.m_iOffset + dwNewLength))
      {

         return false;

      }

   }

   if((m_memory.m_iOffset + dwNewLength) > m_memory.m_iSize)
      return false;

   m_memory.m_cbStorage    = dwNewLength;

   m_memory.m_pdata   = m_memory.m_pbStorage + m_memory.m_iOffset;

   return true;

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


bool memory_base::allocate_internal(memsize dwNewLength)
{

   //if(!is_enabled())
   //{
   //   ASSERT(false);
   //   return false;
   //}

   if(dwNewLength < 0)
   {

      throw ::exception(error_invalid_parameter);

   }
   else if(dwNewLength == 0)
   {

      return true;

   }

   erase_offset();

   memsize dwAllocation = calc_allocation(dwNewLength);

   if(dwAllocation < 0)
   {


      printf("Negative amount of memory to allocate");

   }

   byte * pb;

   if(m_memory.m_pbStorage == nullptr || !m_memory.m_bOwn)
   {

      pb = (byte *) impl_alloc(dwAllocation);

      if(pb == nullptr)

      {

         return false;

      }

      if (!m_memory.m_bOwn)
      {

         ::memcpy_dup(pb, m_memory.m_pbStorage, (memsize) minimum(m_memory.m_iSize, dwAllocation));


      }

   }
   else
   {

      if(dwNewLength < m_memory.m_iSize)
      {

         return true;

      }

      if (m_memory.m_bOwn)
      {

         pb = impl_realloc(m_memory.m_pbStorage, (size_t)dwAllocation);


      }
      else
      {

         pb = nullptr;


      }

      if(pb == nullptr)

      {

         pb = impl_alloc((size_t) dwAllocation);


         if(pb == nullptr)

         {

            return false;

         }

         ::memcpy_dup(pb,m_memory.m_pbStorage,m_memory.m_cbStorage);


         if (!m_memory.m_bOwn)
         {

            impl_free(m_memory.m_pbStorage);

         }

      }

      memsize iOffset = pb - m_memory.m_pbStorage;


      //if(m_pcontainer != nullptr)
      //{

      //   m_pcontainer->offset_kept_pointers(iOffset);

      //}

   }

   m_memory.m_iSize    = dwAllocation;

   m_memory.m_pbStorage       = pb;


   m_memory.m_pdata      = m_memory.m_pbStorage;

   m_memory.m_bOwn            = true;

   return true;

}


void memory_base::reserve(memsize dwNewLength)
{

   if(dwNewLength <= m_memory.m_iSize)
      return;

   if(!allocate_internal(dwNewLength))
      throw ::exception(error_no_memory);

}


void memory_base::erase_offset()
{

   if(m_memory.m_pbStorage == nullptr || m_memory.m_pdata == nullptr || m_memory.m_iOffset <= 0)
      return;

   __memmov(m_memory.m_pbStorage,m_memory.m_pdata,m_memory.m_cbStorage);

   m_memory.m_iOffset      = 0;

   m_memory.m_pdata   = m_memory.m_pbStorage;

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
//   if (get_size() > 0)
//   {
//
//      get_system()->math().random_bytes(get_data(), get_size());
//
//   }
//
//}


memsize memory_base::calc_allocation(memsize size)
{

   return (memsize) (((size + m_memory.m_dwAllocationAddUp) ) / m_memory.m_dwAllocationAddUp * m_memory.m_dwAllocationAddUp);

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

   iSize = maximum(0,minimum(get_size(),iSize));

   m_memory.m_iOffset += iSize;

   //if(m_pcontainer != nullptr)
   //{

   //   m_pcontainer->offset_kept_pointers((memsize) iSize);

   //}

   m_memory.m_cbStorage -= iSize;

   m_memory.m_pdata += iSize;

   if(m_memory.m_iOffset >= m_memory.m_iMaxOffset || (memsize)m_memory.m_iOffset >= m_memory.m_iSize)
   {

      erase_offset();

   }

}


void memory_base::transfer_to(::file::file * pfileOut, memsize uiBufferSize) const
{

   if(get_data() == nullptr || get_size() <= 0)
      return;

   if(pfileOut->increase_internal_data_size(get_size()) && pfileOut->get_internal_data() != nullptr)
   {

      if(pfileOut->get_internal_data() == get_data())
         return;

      __memmov(((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position() + get_size(),((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position(),pfileOut->get_internal_data_size() - get_size());
      ::memcpy_dup(((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position(),get_data(),get_size());

      pfileOut->position() += get_size();

   }
   else
   {

      pfileOut->write(get_data(),get_size());

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

      ::filesize filesize = pfileIn->get_size();

      if (filesize >= 0)
      {

         if (filesize > ::numeric_info < memsize> ::maximum())
         {

            throw ::exception(error_no_memory);

         }

         set_size((::memsize) filesize);

         memsize uRead = pfileIn->read(get_data(), (memsize) get_size());

         set_size(uRead);

      }
      else
      {

         memsize uRead;

         memsize uiSize = 0;

         while (true)
         {

            set_size(uiSize + uiBufferSize);

            uRead = pfileIn->read(&get_data()[uiSize], uiBufferSize);

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

      pos = get_size() + pos;

   }

   if(len < 0)
   {

      len = get_size() - pos + len + 1;

   }

   if(pos < 0)
   {

      pos = 0;

   }

   len = minimum(len,get_size() - pos);

   if(len <= 0)
   {

      return *this;

   }

   if(pos >= get_size())
   {

      return *this;

   }

   __memmov(m_memory.m_pbStorage + pos,m_memory.m_pbStorage + pos + len,get_size() - (pos + len));

   set_size(get_size() - len);

   return *this;

}

#ifdef WINDOWS_DESKTOP

//
//comptr < IStream > memory_base::create_istream() const
//{
//
//   if (get_data() == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   return ::SHCreateMemStream(get_data(),(::u32)get_size());
//
//}


//#elif defined(_UWP)
//
//comptr < IStream > memory_base::create_istream() const
//{
//
//   if (get_data() == nullptr)
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


char * memory_base::get_psz(strsize & len)
{

   if(get_size() >= 2 && get_data()[0] == 255 && get_data()[1] == 60)
   {

      memory mem;

      mem = *this;

      set_size(utf_to_utf_length((char *) get_data(),(const wd16char *)&get_data()[2],get_size() - 2));

      utf_to_utf((char *) get_data(),(const widechar *)&mem.get_data()[2],(i32)(mem.get_size() - 2));

      len = get_size();

      return (char *) get_data();

   }
   else if(get_size() >= 3 && get_data()[0] == 255 && get_data()[1] == 254 && get_data()[2] == 0x73)
   {

      memory mem;

      mem = *this;

      set_size(utf_to_utf_length((char *) get_data(),(const wd16char *)&get_data()[3],get_size() - 3));

      utf_to_utf((char *)get_data(),(const wd16char *)&mem.get_data()[3],(i32)(mem.get_size() - 3));

      len = get_size();

      return (char *)get_data();

   }
   else if(get_size() >= 3 && get_data()[0] == 0xef && get_data()[1] == 0xbb && get_data()[2] == 0xbf)
   {

      len = get_size() - 3;

      return (char *)&get_data()[3];

   }
   else
   {

      len = get_size();

      return (char *)get_data();

   }

}


string memory_base::as_utf8() const
{

   string strResult;

   if (get_size() >= 2
         && get_data()[0] == 255
         && get_data()[1] == 60)
   {

      utf_to_utf(strResult, (wd16char *)&get_data()[2], (i32)(get_size() - 2));

   }
   else if (get_size() >= 2
            && get_data()[0] == 255
            && get_data()[1] == 254)
   {

#ifdef ANDROID
      //for (index i = 2; i < storage.get_size(); i += 2)
      //{
      //   byte b = storage.get_data()[i];
      //   storage.get_data()[i] = storage.get_data()[i + 1];
      //   storage.get_data()[i + 1] = b;
      //}
#endif
      utf_to_utf(strResult, (const wd16char *)&get_data()[2], (i32)(get_size() - 2));

   }
   else if (get_size() >= 3
            && get_data()[0] == 0xef
            && get_data()[1] == 0xbb
            && get_data()[2] == 0xbf)
   {

      strResult = string((const char *)&get_data()[3], (i32)(get_size() - 3));

   }
   else
   {

      strResult = string((const char *)get_data(), (i32)get_size());

   }

   return strResult;

}


char * memory_base::c_str()
{

   if (get_size() <= 0)
   {

      return nullptr;

   }

   if (get_data()[get_size() - 1] != '\0')
   {

      allocate_add_up(1);

      get_data()[get_size() - 1] = '\0';

   }

   return (char *)get_data();

}


bool memory_base::begins(const char * psz, strsize iCount) const
{

   if (iCount < 0)
   {

      iCount += strlen(psz) + 1;

   }

   if (get_size() < iCount)
   {

      return false;

   }

   return !__memcmp(get_data(), psz, iCount);

}


bool memory_base::begins_ci(const char * psz, strsize iCount) const
{

   if (::is_null(psz) || *psz == '\0')
   {

      return true;

   }

   const char * pszThis = (const char *)get_data();

   if (::is_null(pszThis))
   {

      return false;

   }

   if (iCount < 0)
   {

      iCount += strlen(psz) + 1;

   }

   if (get_size() < iCount)
   {

      return false;

   }

   return !ansi_count_compare_ci(pszThis, psz, (size_t) iCount);

}


bool memory_base::begins(const ::string & str, strsize iCount) const
{

   if (iCount < 0)
   {

      iCount += str.get_length() + 1;

   }

   if (get_size() < iCount)
   {

      return false;

   }

   return !__memcmp(get_data(), str.c_str(), iCount);

}


bool memory_base::begins_ci(const ::string & str, strsize iCount) const
{

   if (iCount < 0)
   {

      iCount += str.get_length() + 1;

   }

   if (get_size() < iCount)
   {

      return false;

   }

   return !ansi_count_compare_ci((const char*) get_data(), str.c_str(), iCount);

}


bool memory_base::ends(const char * psz, strsize iCount) const
{

   if (iCount < 0)
   {

      iCount += strlen(psz) + 1;

   }

   if (get_size() < iCount)
   {

      return false;

   }

   return !__memcmp(get_data() + get_size() - iCount, psz, iCount);

}


bool memory_base::ends_ci(const char * psz, strsize iCount) const
{

   if (::is_null(psz) || *psz == '\0')
   {

      return true;

   }

   const char * pszThis = (const char *)get_data();

   if (::is_null(pszThis))
   {

      return false;

   }

   if (iCount < 0)
   {

      iCount += strlen(psz) + 1;

   }

   if (get_size() < iCount)
   {

      return false;

   }

   return !ansi_count_compare_ci(pszThis + get_size() - iCount, psz, (size_t) iCount);

}


bool memory_base::ends(const ::string & str, strsize iCount) const
{

   if (iCount < 0)
   {

      iCount += str.get_length() + 1;

   }

   if (get_size() < iCount)
   {

      return false;

   }

   return !__memcmp(get_data() + get_size() - iCount, str.c_str(), iCount);

}


bool memory_base::ends_ci(const ::string & str, strsize iCount) const
{

   if (iCount < 0)
   {

      iCount += str.get_length() + 1;

   }

   if (get_size() < iCount)
   {

      return false;

   }

   return !ansi_count_compare_ci((const char*) get_data() + get_size() - iCount, str.c_str(), iCount);

}


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

   bool b = false;

   //single_lock synchronouslock(m_spmutex);

   //synchronouslock.lock();

   if (this->get_size() == s.get_size())
      b = __memcmp(get_data(), s.get_data(), (size_t) this->get_size()) == 0;

   //synchronouslock.unlock();

   return b;

}

bool memory_base::operator == (const struct block & s) const
{

   bool b = false;

   //single_lock synchronouslock(m_spmutex);

   //synchronouslock.lock();

   if (this->get_size() == s.get_size())
      b = __memcmp(get_data(), s.get_data(), (size_t)this->get_size()) == 0;

   //synchronouslock.unlock();

   return b;

}


void memory_base::copy_from(const memory_base *pstorage)
{

   ASSERT(pstorage != nullptr);

   set_size(pstorage->get_size());

   ::memcpy_dup(get_data(), pstorage->get_data(), (size_t) this->get_size());

}

void memory_base::copy_from(const void * pdata, memsize s)
{

   defer_set_size(s);

   ::memcpy_dup(get_data(), pdata, (size_t)minimum(this->get_size(), s));

}


void memory_base::copy_to(void * pdata, memsize s) const
{

   if (is_empty())
   {

      return;

   }

   ::memcpy_dup(pdata, get_data(), (size_t)minimum(this->get_size(), s));

}


void memory_base::set_data(void *pdata, memsize uiSize)
{

   set_size(uiSize);

   ::memcpy_dup(get_data(), pdata, (size_t)uiSize);

}


void memory_base::set(byte b, memsize iStart, memsize uiSize)
{

   if (uiSize + iStart > get_size())
      uiSize = get_size() - iStart;

   __memset(get_data() + iStart, b, (size_t)uiSize);

}


void memory_base::zero(memsize iStart, memsize uiSize)
{

   set(0, iStart, uiSize);

}


void memory_base::eat_begin(void * pdata, memsize iSize)
{

   ASSERT(iSize <= this->get_size());

   if (iSize <= this->get_size())
   {

      delete_begin(iSize);

   }

}


memory_base & memory_base::operator = (const memory_base & s)
{

   if (this != &s)
   {

      copy_from(&s);

   }

   return *this;

}


memory_base & memory_base::operator += (const block & block)
{

   append(block);

   return *this;

}


memory_base & memory_base::operator += (const memory_base & s)
{

   append(s);

   return *this;

}


void memory_base::to_hex(string & str, memsize pos, memsize size)
{

   if (pos > this->get_size())
   {

      throw ::exception(error_bad_argument);

   }

   if (size < 0)
   {

      size += this->get_size() - pos + 1;

   }

   if (pos + size > get_size())
   {

      size = get_size() - pos;

   }

   char * pchSrc = (char *)get_data();

   char * pchDst = str.get_string_buffer(size * 2);

   u64 tickEnd = pos + size;

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


strsize memory_base::from_hex(const char * psz, strsize nCount)
{

   char ch;

   bool bOdd = false;

   strsize iLen = nCount < 0 ? strlen(psz) + nCount + 1 : nCount;

   bOdd = (iLen % 2) != 0;

   if (bOdd)
   {

      iLen++;

   }

   set_size(iLen / 2);

   char * pch = (char *)get_data();

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


void memory_base::to_base64(string & str, memsize pos, memsize size)
{

   if (get_data() == nullptr)
   {

      return;

   }

   ::base64 base64;

   str = base64.encode({&get_data()[pos], minimum(get_size() - pos, size)});

}


string memory_base::to_base64(memsize pos, memsize size)
{

   string str;

   to_base64(str, pos, size);

   return str;

}

void memory_base::from_base64(const char * psz, strsize nCount)
{

   ::base64 base64;

   base64.decode(*this, psz, nCount);

}


//void memory_base::to_asc(string & str)
//{
//
//   str.assign(get_data(), get_size());
//
//}
//
//
//bool memory_base::from_asc(const char * psz)
//{
//
//
//}


void memory_base::from_string(const widechar * pwsz)
{

   from_string(unicode_to_utf8(pwsz));

}


void memory_base::from_string(const char * psz)
{

   set_size(strlen(psz));

   ::memcpy_dup(get_data(), psz, this->get_size());

}


void memory_base::from_string(const ::string & str)
{

   set_size(str.length());

   ::memcpy_dup(get_data(), str, this->get_size());

}


void memory_base::from_string(const ::payload & payload)
{

   from_string((const string &)payload.string());

}


void memory_base::append_from_string(const widechar * pwsz)
{

   append_from_string(unicode_to_utf8(pwsz));

}


void memory_base::append_from_string(const char * psz)
{

   auto sizeOld = get_size();

   auto lenExtra = strlen(psz);

   allocate_add_up(lenExtra);

   ::memcpy_dup(get_data() + sizeOld, psz, lenExtra);

}


void memory_base::append_from_string(const ::string & str)
{


   auto sizeOld = get_size();

   auto lenExtra = str.get_length();

   allocate_add_up(lenExtra);

   ::memcpy_dup(get_data() + sizeOld, str.c_str(), lenExtra);
   
}


void memory_base::append_from_string(const ::payload & payload)
{

   append_from_string((const string &)payload.string());

}


string memory_base::as_string() const
{

   return as_string(0);

}


string memory_base::as_string(memsize iStart, memsize iCount) const
{

   string str;

   if ((memsize)iStart < 0)
   {

      *((memsize*)iStart) += this->get_size();

   }

   if (iStart > this->get_size())
   {

      return str;

   }

   if (iCount < 0)
   {

      iCount += this->get_size() - iStart + 1;

   }

   if (iStart + iCount > this->get_size())
   {

      iCount = this->get_size() - iStart - iCount;

   }

   if (iCount <= 0)
   {

      return str;

   }

   if (get_data() == nullptr)
   {

      return str;

   }

   char * psz = str.get_string_buffer(iCount + 1);

   ::memcpy_dup(psz, &get_data()[iStart], iCount);

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

   move(offset, true);

}


void memory_base::move(memsize offset, bool bGrow)
{

   if (offset > 0)
   {

      if (bGrow)
      {

         this->allocate_add_up(offset);

      }

      if ((memsize)offset > this->get_size())
      {

         return;

      }

      __memmov(&this->get_data()[offset], this->get_data(), this->get_size() - offset);

   }
   else if (offset < 0)
   {

      offset = -offset;

      if (bGrow)
      {

         this->allocate_add_up(offset);

      }

      if ((memsize)offset > this->get_size())
      {

         return;

      }

      __memmov(this->get_data(), &this->get_data()[offset], this->get_size() - offset);

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

      *((memsize*)iStart) += mem.get_size();

   }

   if (iStart > mem.get_size())
   {

      return;

   }

   if (iStart + iCount > mem.get_size())
   {

      iCount = mem.get_size() - iStart;

   }

   if (iCount <= 0)
   {

      return;

   }

   allocate_add_up(iCount);

   ::memcpy_dup(&get_data()[this->get_size() - iCount], &mem.get_data()[iStart], (size_t)iCount);

}


void memory_base::append(const void * pdata, memsize iCount)
{

   if (iCount <= 0)
   {

      return;

   }

   memsize iOldSize = get_size();

   allocate_add_up(iCount);

   ::memcpy_dup(&get_data()[iOldSize], pdata, (size_t)iCount);

}


void memory_base::assign(const void * pdata, memsize iCount)
{

   set_size(iCount);

   ::memcpy_dup(get_data(), pdata, (size_t)iCount);

}


void memory_base::assign(const void * pdata, memsize iStart, memsize iCount)
{

   set_size(iCount);

   ::memcpy_dup(get_data(), &((byte *)pdata)[iStart], (size_t)iCount);

}


void memory_base::append(memsize iCount, uchar uch)
{

   allocate_add_up(iCount);

   memsize iStart = this->get_size() - iCount;

   memsize iEnd = iStart + iCount - 1;

   for (memsize i = iStart; i <= iEnd; i++)
   {

      get_data()[i] = uch;

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

      iCountDst = get_size();

   }

   if(iCountSrc >= iCountDst)
   {

      //_____________dddddddddddddddd
      //aaaaaaaaaaaaabbbcccccccccccccccccccccccc

      memsize iSize = get_size();

      memsize iMove = iSize - minimum(iSize, iStartDst + iCountDst);

      allocate_add_up(iCountSrc - iCountDst);

      ::__memmov(&get_data()[iStartDst + iCountSrc], &get_data()[iStartDst + iCountDst], iMove);

   }
   else if (iCountSrc < iCountDst)
   {

      //_____________ddd
      //aaaaaaaaaaaaabbbbbbbbbbbbbbbbcccccccccccccccccccccccc

      memsize iSize = get_size();

      memsize iMove = iSize - minimum(iSize, iStartDst + iCountDst);

      ::__memmov(&get_data()[iStartDst + iCountSrc], &get_data()[iStartDst + iCountDst], iMove);

      allocate_add_up(iCountSrc - iCountDst);

   }

   if (iCountSrc > 0)
   {

      ::memcpy_dup(&get_data()[iStartDst], pbMemory, iCountSrc);

   }

}


void memory_base::assign(memsize iCount, uchar uch)
{

   set_size(iCount);

   memsize iEnd = iCount - 1;

   for (memsize i = 0; i <= iEnd; i++)
   {

      this->get_data()[i] = uch;

   }

}



//void memory_base::assign(const char * psz)
//{
//
//   return from_string(psz);
//
//}
//
//
//void memory_base::append(const char * psz)
//{
//
//   return append_from_string(psz);
//
//}


#if defined(_UWP) && defined(__cplusplus_winrt)


Array < uchar, 1U > ^ memory_base::get_os_bytes(memsize pos, memsize size) const
{

   if (pos > get_size())
   {

      throw ::exception(error_bad_argument);

   }

   if (size < 0 || pos + size > get_size())
   {

      size = get_size() - pos;

   }

   return ref memory_new Array < uchar, 1U >((uchar *)&get_data()[pos], size);

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

   ::memcpy_dup(get_data(), &a->Data[pos], size);

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
   if (this->get_data() != nullptr)
   {
      ::reverse_memory(this->get_data(), this->get_size());
   }
   return *this;
}


memsize memory_base::get_length() const
{

   return get_size();

}


memsize memory_base::length() const
{

   return get_size();

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

   return get_data() + iFind;

}


::index memory_base::find_line_prefix_index(const ::block& blockPrefix, ::index iStart)
{

   if (is_empty())
   {

      return -1;

   }

   ::index iFind;

   ::count cFindLength;

   if (memcmp(get_data() + iStart, blockPrefix.get_data(), blockPrefix.get_size()) == 0)
   {

      iFind = iStart;

      cFindLength = blockPrefix.get_size();

   }
   else
   {

      memory memoryFind;

      memoryFind.set_size(blockPrefix.get_size() + 1);

      memoryFind[0] = '\n';

      memcpy(memoryFind.get_data() + 1, blockPrefix.get_data(), blockPrefix.get_size());

      iFind = find_index(memoryFind, iStart + 1);

      if (iFind < 0)
      {

         return -1;

      }

      cFindLength = memoryFind.get_length();

   }

   return iFind + cFindLength;

}


void memory_base::patch_line_suffix(const ::block& blockPrefix, const block& blockSuffix, ::index iStart )
{

   iStart = find_line_prefix_index(blockPrefix, iStart);

   if (iStart < 0)
   {

      throw ::exception(error_not_found);

   }

   auto iFindEol = find_index(memory_block('\n'), iStart);

   if (iFindEol < 0)
   {

      iFindEol = get_size();

   }

   auto iOldLen = iFindEol - iStart;

   auto iNewLen = blockSuffix.get_size();

   auto iOldSize = get_size();

   auto iNewSize = iOldSize - iOldLen + iNewLen;

   set_size(iNewSize);

   auto pdata = (byte*)get_data();

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

      auto psource = (const char *) blockSuffix.get_data();

      auto c = blockSuffix.get_size();

      memcpy(ptarget, psource, c);

      output_debug_string(" ");

   }

   //return ::success;

}


bool memory_base::begins(const block& block) const
{

   if(get_size() < block.get_size())
   {

      return false;

   }

   int iMemcmp = memcmp(get_data(), block.get_data(), block.get_size());

   return iMemcmp == 0;

}


bool memory_base::ends(const block& block) const
{

   if(get_size() < block.get_size())
   {

      return false;

   }

   int iMemcmp = memcmp(get_data() + get_size() - block.get_size(), block.get_data(), block.get_size());

   return iMemcmp == 0;

}



byte * memory_base::find(const ::block & block, ::index iStart) const
{

   return (byte *)memmem(get_data() + iStart, get_size() - iStart, (byte *)block.get_data(), block.get_size());

}


::index memory_base::find_index(const ::block & block, ::index iStart) const
{

   auto p = find(block, iStart);

   if (!p)
   {

      return -1;

   }

   return ((byte *)p) - get_data();

}


byte * memory_base::reverse_find(const ::block & block, ::index iStart) const
{

   return (byte *)reverse_memmem(get_data() + iStart, get_size() - iStart, (byte *)block.get_data(), block.get_size());

}


::index memory_base::reverse_find_index(const ::block & block, ::index iStart) const
{

   auto p = reverse_find(block, iStart);

   if (!p)
   {

      return -1;

   }

   return ((byte *)p) - get_data();

}


byte * memory_base::reverse_find_byte_not_in_block(const ::block & block, ::index iStart) const
{

   return (byte *)reverse_byte_not_in_block(get_data() + iStart, get_size() - iStart, (byte *)block.get_data(), block.get_size());

}


::index memory_base::reverse_find_index_of_byte_not_in_block(const ::block & block, ::index iStart) const
{

   auto p = reverse_find_byte_not_in_block(block, iStart);

   if (!p)
   {

      return -1;

   }

   return ((byte *)p) - get_data();

}


namespace acme
{



   CLASS_DECL_ACME void transfer_to(::file::file * pfileOut, memory_base & mem, memsize uiBufferSize)
   {

      if (mem.get_data() == nullptr || mem.get_size() <= 0)
         return;

      if (pfileOut->increase_internal_data_size(mem.get_size()) && pfileOut->get_internal_data() != nullptr)
      {

         if (pfileOut->get_internal_data() == mem.get_data())
            return;

         __memmov(((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position() + mem.get_size(), ((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position(), pfileOut->get_internal_data_size() - mem.get_size());

         ::memcpy_dup(((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position(), mem.get_data(), mem.get_size());

         pfileOut->position() += mem.get_size();

      }
      else
      {

         pfileOut->write(mem.get_data(), mem.get_size());

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

            uRead = pfileIn->read(&mem.get_data()[uiSize], uiBufferSize);

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





memory_base & memory_base::operator = (const block & block)
{

   assign(block);

   return *this;

}


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

   assign(block.get_data(), block.get_size());

}


void memory_base::append(const ::block & block)
{

   append(block.get_data(), block.get_size());

}




