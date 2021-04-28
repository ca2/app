// LockedStream.cpp

#include "framework.h"

namespace file
{

   memsize locked_in_stream::read(filesize startPos, void *data, memsize size)
   {
      critical_section_lock synchronouslock(&_criticalSection);
      _stream->seek((filesize) startPos, ::file::seek_begin);
      return _stream->read(data, size);
   }

   memsize locked_reader::read(void *data, memsize size)
   {
      memsize realProcessedSize = _lockedInStream->read((filesize) _pos, data, size);
      _pos += realProcessedSize;
      return realProcessedSize;
   }

} // namespace file
