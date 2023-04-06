#include "framework.h"
#include "_uwp.h"


CLASS_DECL_AURA memsize read_buffer(void* p, ::winrt::Windows::Storage::Streams::IBuffer^ ibuf, memsize size, memsize pos)
{
   
   ::winrt::Windows::Storage::Streams::DataReader^ r = ::winrt::Windows::Storage::Streams::DataReader::FromBuffer(ibuf);
   
   Array<uchar, 1U>^ a = ref memory_new Array<uchar, 1U>(ibuf->Length);
   
   r->ReadBytes(a);

   if (pos > (memsize) a->Length)
   {

      return 0;

   }

   if (size < 0)
   {

      size = a->Length - pos + size + 1;

   }

   if (pos + size > (memsize) a->Length)
   {

      size = a->Length - pos;

   }

   memcpy(p, &a->Data[pos], size);

   return size;

}


CLASS_DECL_AURA memory_file_pointer create_memory_file(::winrt::Windows::Storage::Streams::IInputStream^ stream)
{

   auto pfile = create_memory_file();

   auto pthread = ::get_task();

   while (pthread && pthread->task_get_run())
   {

      ::winrt::Windows::Storage::Streams::IBuffer^ buffer = ref memory_new ::winrt::Windows::Storage::Streams::Buffer(1_mb);

      ::winrt::Windows::Storage::Streams::IBuffer^ buffer2 = ::wait(stream->ReadAsync(buffer, 1_mb, ::winrt::Windows::Storage::Streams::InputStreamOptions::None));

      memory mem;

      mem.set_os_buffer(buffer);

      pfile->write(mem);

      if (mem.get_size() < 1_mb)
      {

         break;

      }

   }

   pfile->seek_begin();

   return pfile;

}



