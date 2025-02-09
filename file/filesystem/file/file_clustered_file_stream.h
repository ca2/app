// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace file
{


   class clustered_istream:
      public istream
   {
      unsigned long long _virtPos;
      unsigned long long _physPos;
      unsigned long long _curRem;
   public:
      istream * Stream;
      unsigned long long StartOffset;
      unsigned long long Size;
      int BlockSizeLog;
      u64_array Vector;

      unsigned long long SeekToPhys()
      {
         return Stream->seek((filesize) _physPos, seek_begin);
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


} // namespace file


