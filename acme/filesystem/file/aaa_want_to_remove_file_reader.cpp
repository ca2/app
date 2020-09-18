#include "framework.h"


//namespace file
//{
//
//
//   reader::reader()
//   {
//   }
//
//   reader::~reader()
//   {
//   }
//
//
//   memsize reader::read(void * pdata, memsize nCount)
//
//   {
//
//      ::exception::throw_interface_only();
//
//      return 0;
//
//   }
//
//   filesize reader::find(const void * pFind, memsize size, const filesize * limit)
//   {
//      u8 * signature = (u8 *) pFind;
//      memsize signatureSize = size;
//      filesize resPos = 0;
//      byte_buffer byteBuffer2;
//      byteBuffer2.SetCapacity(signatureSize);
//      if(FAILED(read_false(this, byteBuffer2, signatureSize)))
//         __throw(::exception::exception());
//
//      if (__memcmp(byteBuffer2, signature, (size_t) signatureSize) == 0)
//         return resPos;
//
//      const u32 kBufferSize = (1 << 16);
//      byte_buffer byteBuffer;
//      byteBuffer.SetCapacity(kBufferSize);
//      u8 *buffer = byteBuffer;
//      memsize numPrevBytes = signatureSize - 1;
//      ::memcpy_dup(buffer, (const u8 *)byteBuffer2 + 1, numPrevBytes);
//      resPos = 1;
//      for (;;)
//      {
//         if (limit != nullptr)
//            if (resPos > *limit)
//               __throw(::exception::exception());
//         do
//         {
//            memsize numReadBytes = kBufferSize - numPrevBytes;
//            memsize processedSize;
//            processedSize = read(buffer + numPrevBytes, numReadBytes);
//            numPrevBytes += processedSize;
//            if (processedSize == 0)
//               __throw(::exception::exception());
//         }
//         while (numPrevBytes < signatureSize);
//         u32 numTests = (u32) (numPrevBytes - signatureSize + 1);
//         for (u32 pos = 0; pos < numTests; pos++)
//         {
//            byte b = signature[0];
//            for (; buffer[pos] != b && pos < numTests; pos++);
//            if (pos == numTests)
//               break;
//            if (__memcmp(buffer + pos, signature, (size_t) signatureSize) == 0)
//            {
//               resPos += pos;
//               return resPos;
//            }
//         }
//         resPos += numTests;
//         numPrevBytes -= numTests;
//         __memmov(buffer, buffer + numTests, numPrevBytes);
//      }
//
//   }
//
//   void reader::transfer_to(writer & writer, memsize uiBufMax)
//   {
//
//
//      if(get_internal_data() && get_internal_data_size() > 0)
//      {
//
//         if(writer.increase_internal_data_size(get_internal_data_size()) && writer.get_internal_data() != nullptr)
//         {
//
//            if(writer.get_internal_data() == get_internal_data())
//               return;
//
//            __memmov(((u8 *) writer.get_internal_data()) + writer.get_position() + get_internal_data_size(), ((u8 *) writer.get_internal_data()) + writer.get_position(), writer.get_internal_data_size() - get_internal_data_size());
//            ::memcpy_dup(((u8 *) writer.get_internal_data()) + writer.get_position(), get_internal_data(), get_internal_data_size());
//            writer.seek(get_internal_data_size(), seek_current);
//
//         }
//         else
//         {
//
//            writer.write(get_internal_data(), get_internal_data_size());
//
//         }
//
//         return;
//
//      }
//
//      uiBufMax = max(8 * 1024, uiBufMax);
//      memsize uiBufMin = uiBufMax / 8;
//      memsize uiBufSize = uiBufMax;
//      memsize uiBufInc = uiBufSize;
//      memsize uiRead;
//      memsize uiSize = writer.get_internal_data_size();
//
//      while(writer.increase_internal_data_size(uiBufInc) && writer.get_internal_data() != nullptr)
//      {
//         __memmov(((u8 *) writer.get_internal_data()) + writer.get_position() + uiBufInc, ((u8 *) writer.get_internal_data()) + writer.get_position(), uiBufInc);
//         uiRead = read(((u8 *) writer.get_internal_data()) + writer.get_position(), uiBufSize);
//         writer.seek(uiRead, seek_current);
//         uiBufSize -= uiRead;
//         if(uiBufSize < uiBufMin)
//         {
//            uiBufSize   = uiBufMax;
//            uiBufInc    = uiBufSize;
//         }
//      }
//
//      if(uiBufSize > 0)
//      {
//         __memmov(((u8 *) writer.get_internal_data()) + writer.get_position(), ((u8 *) writer.get_internal_data()) + writer.get_position() + uiBufSize, uiBufSize);
//         writer.increase_internal_data_size(-(memsize)uiBufSize);
//      }
//
//      memory buf;
//      buf.set_size(uiBufMax);
//      if(buf.get_data() == nullptr)
//         __throw(::exception::exception("no memory"));
//      try
//      {
//         while(true)
//         {
//            uiRead = read(buf, buf.get_size());
//            writer.write(buf, uiRead);
//            if(uiRead <= 0)
//            {
//               return;
//            }
//            uiSize += uiRead;
//         }
//      }
//      catch(...)
//      {
//
//      }
//
//   }
//
//
//   filesize reader::get_position() const
//   {
//      ::exception::throw_interface_only();
//      return 0;
//   }
//
//
//   bool reader::get_length(filesize & size) const
//   {
//
//      return false;
//
//   }
//
//   
//   ::filesize reader::get_left() const
//   {
//
//      return 0;
//
//   }
//
//
//   static const memsize kBlockSize = ((u32)1 << 31);
//
//
//   HRESULT read(reader * preader, void * data, memsize * processedSize)
//   {
//      memsize size = *processedSize;
//      *processedSize = 0;
//      while (size != 0)
//      {
//         memsize curSize = min(size, kBlockSize);
//         memsize processedSizeLoc;
//         HRESULT res = S_OK;
//         try
//         {
//            processedSizeLoc = preader->read(data, curSize);
//         }
//         catch(...)
//         {
//            res = E_FAIL;
//         }
//         *processedSize += processedSizeLoc;
//         data = (void *)((u8 *)data + processedSizeLoc);
//         size -= processedSizeLoc;
//         RINOK(res);
//         if (processedSizeLoc == 0)
//            return S_OK;
//      }
//      return S_OK;
//   }
//
//   HRESULT read_false(reader * preader, void * data, memsize size)
//   {
//      memsize processedSize = size;
//      RINOK(read(preader, data, &processedSize));
//      return (size == processedSize) ? S_OK : S_FALSE;
//   }
//
//   HRESULT read_fail(reader * preader, void * data, memsize size)
//   {
//      memsize processedSize = size;
//      RINOK(read(preader, data, &processedSize));
//      return (size == processedSize) ? S_OK : E_FAIL;
//   }
//
//
//
//} // namespace file
//
//
//
//
