#include "framework.h"


namespace file
{


   unsigned char *dynamic_buffered_writer::GetBufPtrForWriting(size_t addSize)
   {

      addSize += _size;

      if (addSize < _size)
         return nullptr;

      _buffer.EnsureCapacity(addSize);

      return (unsigned char *)_buffer + _size;

   }


   void dynamic_buffered_writer::CopyToBuffer(byte_buffer &dest) const
   {

      dest.SetCapacity(_size);

      ::memory_copy(dest, _buffer, _size);

   }


   void dynamic_buffered_writer::write(const void *data, uptr size, uptr *processedSize)
   {
      if (processedSize)
         *processedSize = 0;
      if (size == 0)
         return;
      unsigned char *buf = GetBufPtrForWriting(size);
      if (!buf)
         throw ::exception(error_no_memory);
      ::memory_copy(buf, data, size);
      UpdateSize(size);
      if (processedSize)
         *processedSize = size;
   }


} // namespace aura



