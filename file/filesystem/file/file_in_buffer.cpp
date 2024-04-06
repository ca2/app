// InBuffer.cpp
// from 7-zip on 2012-12-23, dawn
#include "framework.h"

/*#include "../../../C/Alloc.h"

#include "InBuffer.h"*/

namespace file
{

   in_buffer::in_buffer():
      _buffer(0),
      _bufferLimit(0),
      _bufferBase(0),
      _stream(0),
      _bufferSize(0)
   {
   }

   bool in_buffer::Create(u32 bufferSize)
   {
      const u32 kMinBlockSize = 1;
      if (bufferSize < kMinBlockSize)
         bufferSize = kMinBlockSize;
      if (_bufferBase != 0 && _bufferSize == bufferSize)
         return true;
      Free();
      _bufferSize = bufferSize;
      _bufferBase = (::u8 *)::MidAlloc(bufferSize);
      return (_bufferBase != 0);
   }

   void in_buffer::Free()
   {
      ::MidFree(_bufferBase);
      _bufferBase = 0;
   }

   void in_buffer::SetStream(reader *stream)
   {
      _stream = stream;
   }

   void in_buffer::Init()
   {
      _processedSize = 0;
      _buffer = _bufferBase;
      _bufferLimit = _buffer;
      _wasFinished = false;
   #ifdef _NO_EXCEPTIONS
      ErrorCode = S_OK;
   #endif
   }

   bool in_buffer::ReadBlock()
   {
   #ifdef _NO_EXCEPTIONS
      if (ErrorCode != S_OK)
         return false;
   #endif
      if (_wasFinished)
         return false;
      _processedSize += (_buffer - _bufferBase);
      memsize numProcessedBytes;
      try
      {
         numProcessedBytes = _stream->read(_bufferBase, _bufferSize);
      }
      catch(...)
      {
         throw ::exception(in_buffer_exception(E_FAIL));
      }
      _buffer = _bufferBase;
      _bufferLimit = _buffer + numProcessedBytes;
      _wasFinished = (numProcessedBytes == 0);
      return (!_wasFinished);
   }

   ::u8 in_buffer::ReadBlock2()
   {
      if (!ReadBlock())
      {
         _processedSize++;
         return 0xFF;
      }
      return *_buffer++;
   }


} // namespace file









