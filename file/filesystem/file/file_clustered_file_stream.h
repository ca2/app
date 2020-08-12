// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace file
{


   class clustered_istream:
      public istream
   {
      u64 _virtPos;
      u64 _physPos;
      u64 _curRem;
   public:
      istream * Stream;
      u64 StartOffset;
      u64 Size;
      i32 BlockSizeLog;
      u64_array Vector;

      u64 SeekToPhys()
      {
         return Stream->seek((filesize) _physPos, seek_begin);
      }

      u64 InitAndSeek()
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
      filesize seek(filesize offset, e_seek seekOrigin);
   };


} // namespace file


