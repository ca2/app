// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace file
{


   class clustered_istream:
      public stream
   {
      memsize _virtPos;
      memsize _physPos;
      memsize _curRem;
   public:
      stream * Stream;
      memsize StartOffset;
      memsize Size;
      int BlockSizeLog;
      u64_array Vector;

      unsigned long long SeekToPhys()
      {
         return Stream->seek_begin((filesize) _physPos);
      }

      unsigned long long InitAndSeek()
      {
         _curRem = 0;
         _virtPos = 0;
         _physPos = StartOffset;
         if (Vector.get_size() > 0)
         {
            _physPos = StartOffset + (Vector[0] << BlockSizeLog);
            return SeekToPhys();
         }
         return 0;
      }


      memsize read(void * data, memsize size);

      filesize seek(filesize offset, enum_seek seekOrigin);


   };


} // namespace aura




