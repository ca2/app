// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace file
{

   class limited_istream:
      public stream
   {
      stream *    _stream;
      unsigned long long            _virtPos;
      unsigned long long            _physPos;
      unsigned long long            _size;
      unsigned long long         _startOffset;

      unsigned long long SeekToPhys()
      { 
         return _stream->seek_begin((iptr) _physPos); 
      }
   public:

      void SetStream(stream *stream)
      { 
         
         _stream = stream; 

      }

      //HRESULT InitAndSeek(unsigned long long startOffset, unsigned long long int_size)
      unsigned long long InitAndSeek(unsigned long long startOffset, unsigned long long int_size)
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

   ::file::file * create_limited_istream(stream *inStream, unsigned long long pos, unsigned long long int_size);


} // namespace file




