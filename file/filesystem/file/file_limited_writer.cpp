// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "framework.h"


namespace file
{


   void limited_writer::write(const void *data, memsize size, memsize * processedSize)
   {
      if (processedSize != nullptr)
         *processedSize = 0;
      if (size > _size)
      {
         if (_size == 0)
         {
            _overflow = true;
            if (!_overflowIsAllowed)
               throw ::exception(system_exception(E_FAIL));
            if (processedSize != nullptr)
               *processedSize = size;
            return;
         }
         size = (unsigned int)_size;
      }
      if (_stream)
         _stream->write(data, size, &size);
      _size -= size;
      if (processedSize != nullptr)
         *processedSize = size;
      return;
   }

} // namespace file
