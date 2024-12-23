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

      huge_natural SeekToPhys()
      {
         return Stream->seek_begin((filesize) _physPos);
      }

      huge_natural InitAndSeek()
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




