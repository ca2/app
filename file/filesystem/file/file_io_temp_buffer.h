// InOutTempBuffer.h
#pragma once


/*#include "../../Common/MyCom.h"
#include "../../Windows/FileDir.h"
#include "../../Windows/FileIO.h"

#include "../IStream.h"*/

namespace file
{

   class temp_io_buffer :
      virtual public ::object

   {
   public:
      //NWindows::NFile::NDirectory::CTempFile _tempFile;
      //NWindows::NFile::NIO::COutFile _outFile;
      file_pointer                      _tempFile;
      file_pointer                      _outFile;
      string                           _tempFileName;
      bool                             _tempFileCreated;
      u32                           _crc;
      memory              m_memory;
      memsize     _bufPos;
      memsize         _size;


      temp_io_buffer();
      virtual ~temp_io_buffer();

      bool write_to_file(const void * data, memsize size);
      void create();

      void InitWriting();
      bool write(const void *data, memsize size);

      HRESULT write_to_stream(writer *stream);
      memsize GetDataSize() const
      {
         return _size;
      }
   };

   class temp_io_writer :
      virtual public writer
   {
      temp_io_buffer *_buf;
   public:
      void Init(temp_io_buffer *buffer)
      {
         _buf = buffer;
      }
      void write(const void *data, memsize size, memsize * processedSize);
   };


} // namespace file



