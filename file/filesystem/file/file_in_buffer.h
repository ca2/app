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
     unsigned char *_buffer;
     unsigned char *_bufferLimit;
     unsigned char *_bufferBase;
     reader * _stream;
     u64 _processedSize;
     unsigned int _bufferSize;
     bool _wasFinished;

     bool ReadBlock();
     unsigned char ReadBlock2();

   public:
     HRESULT ErrorCode;

     in_buffer();
     ~in_buffer() { Free(); }

     bool Create(unsigned int bufferSize);
     void Free();

     void SetStream(reader *stream);
     void Init();
     void ReleaseStream()
     {
     //   _stream.Release();
     }

     bool ReadByte(unsigned char &b)
     {
       if (_buffer >= _bufferLimit)
         if (!ReadBlock())
           return false;
       b = *_buffer++;
       return true;
     }
     unsigned char ReadByte()
     {
       if (_buffer >= _bufferLimit)
         return ReadBlock2();
       return *_buffer++;
     }
     unsigned int ReadBytes(unsigned char *buf, unsigned int size_i32)
     {
       if ((unsigned int)(_bufferLimit - _buffer) >= size_i32)
       {
         for (unsigned int i = 0; i < size; i++)
           buf[i] = _buffer[i];
         _buffer += size;
         return size;
       }
       for (unsigned int i = 0; i < size; i++)
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




