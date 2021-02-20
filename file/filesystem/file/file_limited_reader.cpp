// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "framework.h"

/*#include "LimitedStreams.h"
#include "../../Common/Defs.h"*/

namespace file
{

   memsize limited_reader::read(void *data, memsize size)
   {
     memsize realProcessedSize = 0;
     u32 sizeToRead = (u32)minimum((_size - _pos), (u64)size_i32);
//     HRESULT result = S_OK;
     if (sizeToRead > 0)
     {
       realProcessedSize = _stream->read(data, sizeToRead);
       _pos += realProcessedSize;
       if (realProcessedSize == 0)
         _wasFinished = true;
     }
     return realProcessedSize;
   }


} // namespace file