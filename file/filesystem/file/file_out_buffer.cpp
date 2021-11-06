/*      void SetMemStream(byte *buffer) { _buffer2 = buffer; }
void SetStream(writer *stream);
void Init();
HRESULT flush();
void FlushWithCheck();
void ReleaseStream()
{
// _stream.Release();
}
HRESULT FlushPart();

void WriteByte(byte b)
{
m_memory.get_data()[_pos++] = b;
if(_pos == _limitPos)
FlushWithCheck();
}
void WriteBytes(const void *data, size_t size)
{
for (size_t i = 0; i < size; i++)
WriteByte(((const byte *)data)[i]);
}

u64 GetProcessedSize() const;*/

// OutBuffer.cpp
// from 7-zip on 2012-12-23, dawn
#include "framework.h"

/*#include "../../../C/Alloc.h"

#include "OutBuffer.h"*/


namespace file
{


   out_buffer::out_buffer() :
      _pos(0), _stream(0), _buffer2(0)
   {
   }

   out_buffer::~out_buffer()
   {
      destroy();
   }

   bool out_buffer::create(memsize bufferSize)
   {
      const memsize kMinBlockSize = 1;
      if (bufferSize < kMinBlockSize)
         bufferSize = kMinBlockSize;
      if (m_memory.get_size() == bufferSize)
         return true;
      m_memory.set_size(bufferSize);
      return m_memory.get_data() != nullptr;
   }

   void out_buffer::destroy()
   {
      m_memory.set_size(0);
   }

   void out_buffer::SetStream(writer *stream)
   {
      _stream = stream;
   }

   void out_buffer::Init()
   {
      _streamPos = 0;
      _limitPos = (filesize) m_memory.get_size();
      _pos = 0;
      _processedSize = 0;
      _overDict = false;
#ifdef _NO_EXCEPTIONS
      ErrorCode = S_OK;
#endif
   }

   u64 out_buffer::GetProcessedSize() const
   {
      u64 res = _processedSize + _pos - _streamPos;
      if (_streamPos > _pos)
         res += m_memory.get_size();
      return res;
   }


   HRESULT out_buffer::FlushPart()
   {
      // _streamPos < _bufferSize
      memsize size = (memsize) ((_streamPos >= _pos) ? (m_memory.get_size() - _streamPos) : (_pos - _streamPos));
      HRESULT result = S_OK;
      if (_buffer2 != 0)
      {
         __memmov(_buffer2, m_memory.get_data() + (memsize) _streamPos, (size_t) size);
         _buffer2 += size;
      }

      if (_stream != 0)
      {
         memsize processedSize = 0;
         _stream->write(m_memory.get_data() + (memsize) _streamPos, size, &processedSize);
         size = processedSize;
      }
      _streamPos += size;
      if (_streamPos == m_memory.get_size())
         _streamPos = 0;
      if (_pos == m_memory.get_size())
      {
         _overDict = true;
         _pos = 0;
      }
      _limitPos = (_streamPos > _pos) ? _streamPos : (filesize) m_memory.get_size();
      _processedSize += size;
      return result;
   }

   HRESULT out_buffer::flush()
   {
      while(_streamPos != _pos)
      {
         HRESULT result = FlushPart();
         if (result != S_OK)
            return result;
      }
      return S_OK;
   }

   void out_buffer::FlushWithCheck()
   {
      HRESULT result = flush();
      if (result != S_OK)
         __throw(out_buffer_exception(result));
   }


   void out_buffer::SetMemStream(byte *buffer)
   {
      _buffer2 = buffer;
   }

   void out_buffer::ReleaseStream()
   {
      // _stream.Release();
   }

   void out_buffer::WriteByte(byte b)
   {
      m_memory.get_data()[_pos++] = b;
      if(_pos == _limitPos)
         FlushWithCheck();
   }

   void out_buffer::WriteBytes(const void *data, size_t size)
   {
      for (size_t i = 0; i < size; i++)
         WriteByte(((const byte *)data)[i]);
   }


} // namespace file



