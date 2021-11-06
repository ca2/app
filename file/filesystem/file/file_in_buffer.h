// InBuffer.h
// from 7-zip on 2012-12-23, dawn
#pragma once

/*#include "../IStream.h"
#include "../../Common/MyCom.h"
#include "../../Common/MyException.h"*/


namespace file
{


   class CLASS_DECL_CA2_FILE in_buffer_exception :
      virtual public system_exception
   {
   public:
      in_buffer_exception( HRESULT errorCode) :
         system_exception(errorCode)
      {
      }
   };

   class CLASS_DECL_CA2_FILE in_buffer :
      virtual public ::object
   {
     byte *_buffer;
     byte *_bufferLimit;
     byte *_bufferBase;
     reader * _stream;
     u64 _processedSize;
     u32 _bufferSize;
     bool _wasFinished;

     bool ReadBlock();
     byte ReadBlock2();

   public:
     HRESULT ErrorCode;

     in_buffer();
     ~in_buffer() { Free(); }

     bool Create(u32 bufferSize);
     void Free();

     void SetStream(reader *stream);
     void Init();
     void ReleaseStream()
     {
     //   _stream.Release();
     }

     bool ReadByte(byte &b)
     {
       if (_buffer >= _bufferLimit)
         if (!ReadBlock())
           return false;
       b = *_buffer++;
       return true;
     }
     byte ReadByte()
     {
       if (_buffer >= _bufferLimit)
         return ReadBlock2();
       return *_buffer++;
     }
     u32 ReadBytes(byte *buf, u32 size_i32)
     {
       if ((u32)(_bufferLimit - _buffer) >= size_i32)
       {
         for (u32 i = 0; i < size; i++)
           buf[i] = _buffer[i];
         _buffer += size;
         return size;
       }
       for (u32 i = 0; i < size; i++)
       {
         if (_buffer >= _bufferLimit)
           if (!ReadBlock())
             return i;
         buf[i] = *_buffer++;
       }
       return size;
     }
     u64 GetProcessedSize() const { return _processedSize + (_buffer - _bufferBase); }
     bool WasFinished() const { return _wasFinished; }
   };


} // namespace file




