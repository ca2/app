#include "framework.h"


//#ifdef _UWP
//
//
//::Windows::Storage::Streams::IBuffer^ block::get_os_buffer(memsize pos, memsize size) const
//{
//
//   ::Windows::Storage::Streams::DataWriter^ writer = ref new ::Windows::Storage::Streams::DataWriter();
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
//      __throw(error_invalid_argument);
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
//   return ref new Array < uchar, 1U >(&((uchar*)get_data())[pos], size);
//
//}
//
//
//#endif


block & block::from_base64(const char * psz, strsize iSize) const
{

   ::str::base64 base64;

   base64.decode(*this, psz, iSize);
   //get_system()->m_pbase64->decode(*this, psz, iSize);

   return (block &)*this;

}


string block::to_base64() const
{

   ::str::base64 base64;

   return base64.encode(*this);

}




//fork_block & fork_block::from_base64(const char * psz, strsize iSize)
//{
//
//   m_iSize = (iSize + 1) * 3 / 4;
//
//   m_pdata = (byte *) memory_allocate(m_iSize);
//
//   ::str::base64 base64;
//
//   m_iSize = base64.decode(*this, psz, iSize);
//
//   return (fork_block &)*this;
//
//}
//


#ifdef __DEBUG

#include "block.inl"

#endif //__DEBUG
