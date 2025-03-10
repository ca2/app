// OutBuffer.h
// from 7-zip on 2012-12-23, dawn
#pragma once


/*#include "../IStream.h"
#include "../../Common/MyCom.h"
#include "../../Common/MyException.h"*/

namespace file
{

   class CLASS_DECL_CA2_FILE out_buffer_exception: 
      virtual public system_exception
   {
   public:
      out_buffer_exception(HRESULT errorCode) : 
         system_exception(errorCode)
      {
      }
   };

   class CLASS_DECL_CA2_FILE out_buffer :
      virtual public ::object
   {
   public:
      virtual_memory                   m_memory;
      filesize                        _pos;
      filesize                        _limitPos;
      filesize                        _streamPos;
      writer *                         _stream;
      unsigned long long                           _processedSize;
      unsigned char *                           _buffer2;
      bool                             _overDict;

      HRESULT ErrorCode;

      out_buffer();
      ~out_buffer();

      bool create(memsize bufferSize);
      void destroy();

      void SetMemStream(unsigned char *buffer);
      void SetStream(writer *stream);
      void Init();
      HRESULT flush();
      void FlushWithCheck();
      void ReleaseStream();
      HRESULT FlushPart();

      void WriteByte(unsigned char b);
      void WriteBytes(const void *data, size_t size);

      unsigned long long GetProcessedSize() const;


   };


} // namespace file


