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
     unsigned int sizeToRead = (unsigned int)minimum((_size - _pos), (unsigned long long)int_size);
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
