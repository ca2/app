#include "framework.h"
#include "memory_base.h"
#include "acme/primitive/primitive/atom.h"
#include "acme/primitive/string/base64.h"
//#include "acme/primitive/string/hex.h"


block::block(const atom & atom) :
   ::block(atom.is_text() ? atom.m_str.begin() : nullptr, atom.is_text() ? atom.m_str.end() : 0)
{

}


//block::block(const ::string & str) :
//   ::block(str.c_str(), str.length())
//{
//
//}


//block::block(const ::string & str, ::strsize s) : 
//   ::block((const void *)str.c_str(), (::i64)(s >= 0 ? s : str.length() + s + 1))
//{
//
//
//}



//void block::to_string(string & str) const
//{
//
//   str.assign((const ::ansi_character *)data(), size());
//
//}


//#ifdef _UWP
//
//
//::winrt::Windows::Storage::Streams::IBuffer^ block::get_os_buffer(memsize pos, memsize size) const
//{
//
//   ::winrt::Windows::Storage::Streams::DataWriter^ writer = ref memory_new ::winrt::Windows::Storage::Streams::DataWriter();
//
//   Array < uchar, 1U >^ pbytes = get_os_bytes(pos, size);
//
//   writer->WriteBytes(pbytes);
//
//   return writer->DetachBuffer();
//
//}
//
//
//Array < uchar, 1U >^ block::get_os_bytes(memsize pos, memsize size) const
//{
//
//   if (pos > size())
//   {
//
//      throw ::exception(error_bad_argument);
//
//   }
//
//   if (size < 0 || pos + size > size())
//   {
//
//      size = size() - pos;
//
//   }
//
//   return ref memory_new Array < uchar, 1U >(&((uchar*)data())[pos], size);
//
//}
//
//
//#endif


block & block::from_base64(const ::scoped_string & scopedstr) const
{

   ::base64 base64;

   base64.decode(*this, scopedstr);
   //acmesystem()->m_pbase64->decode(*this, psz, iSize);

   return (block &)*this;

}


//string block::to_base64() const
//{
//
//   ::base64 base64;
//
//   return base64.encode(*this);
//
//}


//bool block::operator == (const block & block) const
//{
//
//   if (block.size() != size())
//   {
//
//      return false;
//
//   }
//
//   return __memcmp(block.data(), data(), (size_t)size()) == 0;
//
//}


//fork_block & fork_block::from_base64(const ::scoped_string & scopedstr, strsize iSize)
//{
//
//   m_iSize = (iSize + 1) * 3 / 4;
//
//   m_pdata = (byte *) memory_allocate(m_iSize);
//
//   ::base64 base64;
//
//   m_iSize = base64.decode(*this, psz, iSize);
//
//   return (fork_block &)*this;
//
//}
//


//#ifdef __DEBUG

//#include "block.inl"

//#endif //__DEBUG






block::block(const memory_base & memory) :
   block(memory.data(), memory.size())
{

}


block::block(const memory_base * pmemory) :
   block(pmemory->data(), pmemory->size())
{

}

memsize block::find(const ::block& blockFind, memsize start) const
{

   if (start >= size())
   {

      return -1;

   }
   else if (size() <= 0)
   {

      if (blockFind.size() <= 0)
      {

         return start;

      }
      else
      {

         return -1;

      }

   }
   else
   {

      if (blockFind.size() <= 0)
      {

         return start;

      }
      else if (blockFind.size() > size())
      {

         return -1;

      }
      else
      {

         return _find(blockFind, start);

      }

   }

}


namespace hex
{

   
   CLASS_DECL_ACME string lower_case_from(const block & block)
   {

      return lower_case_from(block.data(), block.size());

   }

   
   CLASS_DECL_ACME string upper_case_from(const block & block)
   {

      return upper_case_from(block.data(), block.size());

   }


} // namespace hex



