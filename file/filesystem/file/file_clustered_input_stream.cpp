// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "framework.h"


namespace file
{


   memsize clustered_istream::read(void *data, memsize size)
   {

      memsize processedSize = 0;

      if (_virtPos >= Size)
      {
         if(_virtPos == Size)
            return 0;
         else
            throw ::exception(system_exception(E_FAIL));
      }

      if (_curRem == 0)
      {
         filesize blockSize = (filesize)1 << (filesize) BlockSizeLog;
         filesize virtBlock = _virtPos >> BlockSizeLog;
         filesize offsetInBlock = _virtPos & (blockSize - 1);
         filesize phyBlock = Vector[virtBlock];
         filesize newPos = StartOffset + ((u64)phyBlock << BlockSizeLog) + offsetInBlock;
         if (newPos != _physPos)
         {
            _physPos = newPos;
            SeekToPhys();
         }
         _curRem = blockSize - offsetInBlock;
         for (i32 i = 1; i < 64 && (virtBlock + i) < (u32)Vector.get_size() && phyBlock + i == Vector[(virtBlock + i)]; i++)
            _curRem += (u64)((u64) 1 << (u64) BlockSizeLog);
         auto rem = Size - _virtPos;
         if (_curRem > rem)
            _curRem = rem;
      }
      if (size > _curRem)
         size = (memsize) _curRem;
      size = Stream->read(data, size);
      processedSize = size;
      _physPos += size;
      _virtPos += size;
      _curRem -= size;
      return processedSize;
   }

   filesize clustered_istream::seek(filesize offset, enum_seek seekOrigin)
   {
      u64 newVirtPos = offset;
      switch(seekOrigin)
      {
      case STREAM_SEEK_SET: break;
      case STREAM_SEEK_CUR: newVirtPos += _virtPos; break;
      case STREAM_SEEK_END: newVirtPos += Size; break;
      default:
         throw ::exception(system_exception(STG_E_INVALIDFUNCTION));
      }
      if (_virtPos != newVirtPos)
         _curRem = 0;
      _virtPos = newVirtPos;
      return newVirtPos;
   }


} // namespace file




