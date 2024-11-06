// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace file
{


   class clustered_istream:
      public istream
   {
      huge_natural _virtPos;
      huge_natural _physPos;
      huge_natural _curRem;
   public:
      istream * Stream;
      huge_natural StartOffset;
      huge_natural Size;
      int BlockSizeLog;
      u64_array Vector;

      huge_natural SeekToPhys()
      {
         return Stream->seek((filesize) _physPos, seek_begin);
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


} // namespace file


