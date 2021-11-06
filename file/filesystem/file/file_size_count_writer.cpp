#include "framework.h"

namespace file
{

   void size_count_writer::write(const void *data, memsize size, memsize * processedSize)
   {
      memsize realProcessedSize;
      _stream->write(data, size, &realProcessedSize);
      _size += realProcessedSize;
      if (processedSize)
         *processedSize = realProcessedSize;
   }

} // namespace file
