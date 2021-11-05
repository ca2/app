#include "framework.h"


namespace file
{


   byte *dynamic_buffered_writer::GetBufPtrForWriting(size_t addSize)
   {

      addSize += _size;

      if (addSize < _size)
         return nullptr;

      _buffer.EnsureCapacity(addSize);

      return (byte *)_buffer + _size;

   }


   void dynamic_buffered_writer::CopyToBuffer(byte_buffer &dest) const
   {

      dest.SetCapacity(_size);

      ::memcpy_dup(dest, _buffer, _size);

   }


   void dynamic_buffered_writer::write(const void *data, uptr size, uptr *processedSize)
   {
      if (processedSize)
         *processedSize = 0;
      if (size == 0)
         return;
      byte *buf = GetBufPtrForWriting(size);
      if (!buf)
         __throw(error_no_memory);
      ::memcpy_dup(buf, data, size);
      UpdateSize(size);
      if (processedSize)
         *processedSize = size;
   }


} // namespace aura



