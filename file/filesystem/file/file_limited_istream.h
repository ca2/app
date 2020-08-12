// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace file
{

   class limited_istream:
      public stream
   {
      stream *    _stream;
      u64            _virtPos;
      u64            _physPos;
      u64            _size;
      u64         _startOffset;

      u64 SeekToPhys()
      { 
         return _stream->seek_begin((iptr) _physPos); 
      }
   public:

      void SetStream(stream *stream)
      { 
         
         _stream = stream; 

      }

      //HRESULT InitAndSeek(u64 startOffset, u64 size)
      u64 InitAndSeek(u64 startOffset, u64 size)
      {
         _startOffset = startOffset;
         _physPos = startOffset;
         _virtPos = 0;
         _size = size;
         return SeekToPhys();
      }

      memsize read(void * data, memsize size);
      filesize seek(filesize offset, e_seek seekOrigin);

   };

   ::file::file * create_limited_istream(stream *inStream, u64 pos, u64 size);


} // namespace file




