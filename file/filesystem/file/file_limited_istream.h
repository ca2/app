// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace file
{

   class limited_istream:
      public stream
   {
      stream *    _stream;
      huge_natural            _virtPos;
      huge_natural            _physPos;
      huge_natural            _size;
      huge_natural         _startOffset;

      huge_natural SeekToPhys()
      { 
         return _stream->seek_begin((iptr) _physPos); 
      }
   public:

      void SetStream(stream *stream)
      { 
         
         _stream = stream; 

      }

      //HRESULT InitAndSeek(huge_natural startOffset, huge_natural int_size)
      huge_natural InitAndSeek(huge_natural startOffset, huge_natural int_size)
      {
         _startOffset = startOffset;
         _physPos = startOffset;
         _virtPos = 0;
         _size = size;
         return SeekToPhys();
      }

      memsize read(void * data, memsize size);
      filesize seek(filesize offset, enum_seek seekOrigin);

   };

   ::file::file * create_limited_istream(stream *inStream, huge_natural pos, huge_natural int_size);


} // namespace file




