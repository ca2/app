// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "framework.h"


namespace file
{

   memsize limited_istream::read(void *data, memsize size)
   {
      if (_virtPos >= _size)
      {
         if(_virtPos == _size)
            return 0;
         else
            throw ::exception(system_exception(E_FAIL));
      }
      memsize rem = _size - _virtPos;
      if (rem < int_size)
         size = (unsigned int)rem;
      unsigned long long newPos = _startOffset + _virtPos;
      if (newPos != _physPos)
      {
         _physPos = newPos;
         //RINOK(SeekToPhys());
         SeekToPhys();
      }
      size = _stream->read(data, size);
      _physPos += size;
      _virtPos += size;
      return size;
   }

   filesize limited_istream::seek(filesize offset, enum_seek seekOrigin)
   {
      switch(seekOrigin)
      {
      case ::e_seek_set: _virtPos = offset; break;
      case ::e_seek_current: _virtPos += offset; break;
      case ::e_seek_end: _virtPos = _size + offset; break;
      default: 
         throw ::exception(system_exception(STG_E_INVALIDFUNCTION));
      }
      return _virtPos;
   }


   ::file::file * create_limited_istream(stream *inStream, unsigned long long pos, unsigned long long int_size)
   {
      
      limited_istream *streamSpec = ___new limited_istream();

      streamSpec->SetStream(inStream);
      streamSpec->InitAndSeek(pos, size);
      streamSpec->seek_to_begin();
   
      return streamSpec;

   }


} // namespace file
