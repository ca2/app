#include "framework.h"
#include "memory_base.h"
#include "acme/primitive/primitive/atom.h"
#include "acme/primitive/string/base64.h"
#include "acme/primitive/string/hex.h"


block::block(const atom & atom) :
   ::block(atom.is_text() ? atom.m_str : nullptr, atom.is_text() ? atom.m_str.length() : 0) 
{

}


//block::block(const ::string & str) :
//   ::block(str.c_str(), str.get_length())
//{
//
//}


//block::block(const ::string & str, ::strsize s) : 
//   ::block((const void *)str.c_str(), (::i64)(s >= 0 ? s : str.get_length() + s + 1))
//{
//
//
//}



//void block::to_string(string & str) const
//{
//
//   str.assign((const ansichar *)get_data(), get_size());
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
//   if (pos > get_size())
//   {
//
//      throw ::exception(error_bad_argument);
//
//   }
//
//   if (size < 0 || pos + size > get_size())
//   {
//
//      size = get_size() - pos;
//
//   }
//
//   return ref memory_new Array < uchar, 1U >(&((uchar*)get_data())[pos], size);
//
//}
//
//
//#endif


block & block::from_base64(const char * psz, strsize iSize) const
{

   ::base64 base64;

   base64.decode(*this, psz, iSize);
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
//   if (block.get_size() != get_size())
//   {
//
//      return false;
//
//   }
//
//   return __memcmp(block.get_data(), get_data(), (size_t)get_size()) == 0;
//
//}


//fork_block & fork_block::from_base64(const char * psz, strsize iSize)
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
   block(memory.get_data(), memory.get_size())
{

}


block::block(const memory_base * pmemory) :
   block(pmemory->get_data(), pmemory->get_size())
{

}




namespace hex
{
   CLASS_DECL_ACME string lower_from(const block & block)
   {

      return lower_from(block.get_data(), block.get_size());

   }

   
   CLASS_DECL_ACME string upper_from(const block & block)
   {

      return upper_from(block.get_data(), block.get_size());

   }


} // namespace hex



