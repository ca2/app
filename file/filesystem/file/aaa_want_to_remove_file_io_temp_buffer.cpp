// InOutTempBuffer.cpp

#include "framework.h"

/*#include "../../../C/7zCrc.h"

#include "InOutTempBuffer.h"
#include "StreamUtils.h"

using namespace NWindows;
using namespace NFile;
using namespace NDirectory;*/

namespace file
{

   static const u32 kTempBufSize = (1 << 20);

   static const char * kTempFilePrefixString = "7zt";

   temp_io_buffer::temp_io_buffer()
   {
   }

   void temp_io_buffer::create()
   {
      m_memory.set_size(kTempBufSize);
   }

   temp_io_buffer::~temp_io_buffer()
   {
   }

   void temp_io_buffer::InitWriting()
   {
      _bufPos = 0;
      _tempFileCreated = false;
      _size = 0;
      _crc = CRC_INIT_VAL;
   }

   bool temp_io_buffer::write_to_file(const void *data, memsize size)
   {
      if (size == 0)
         return true;
      if (!_tempFileCreated)
      {
         _tempFileName = Context.file().time_square(kTempFilePrefixString);
         _tempFile = Context.file().get(_tempFileName);
         _tempFileCreated = _tempFile.is_set();
      }
      memsize processed = size;
      _outFile->write(data, size);
      _crc = crc_update(_crc, data, processed);
      _size += processed;
      return (processed == size);
   }

   bool temp_io_buffer::write(const void *data, memsize size)
   {
      if (_bufPos < kTempBufSize)
      {
         memory_position_t cur = min(kTempBufSize - _bufPos, size);
         memcpy(m_memory.get_data() + _bufPos, data, cur);
         _crc = crc_update(_crc, data, cur);
         _bufPos += cur;
         size -= cur;
         data = ((const byte *)data) + cur;
         _size += cur;
      }
      return write_to_file(data, size);
   }

   HRESULT temp_io_buffer::write_to_stream(writer *stream)
   {
      _outFile->close();

      u64 size = 0;
      u32 crc = CRC_INIT_VAL;

      if (_bufPos > 0)
      {
         RINOK(::file::write(stream, m_memory.get_data(), (memsize) _bufPos));
         //WriteStream(stream, m_memory.get_data(), _bufPos);
         crc = crc_update(crc, m_memory.get_data(), (memsize) _bufPos);
         size += _bufPos;
      }
      if (_tempFileCreated)
      {
         file_pointer inFile(get_object());
         if (!inFile->open(_tempFileName, ::file::mode_read | ::file::type_binary))
            return E_FAIL;
         while (size < _size)
         {
            u32 processed;
            throw "should implement below ReadPart from InFile";
            /*if (!inFile.ReadPart(m_memory.get_data(), kTempBufSize, processed))
               return E_FAIL;*/
            if (processed == 0)
               break;
            RINOK(::file::write(stream, m_memory.get_data(), processed));
            crc = crc_update(crc, m_memory.get_data(), processed);
            size += processed;
         }
      }
      return (_crc == crc && size == _size) ? S_OK : E_FAIL;
   }

   void temp_io_writer::write(const void *data, memsize size, memsize * processed)
   {
      if (!_buf->write(data, size))
      {
         if (processed != NULL)
            *processed = 0;
         throw E_FAIL;
      }
      if (processed != NULL)
         *processed = size;
   }

} // namespace file
