#pragma once


class fimemory
{
public:

   FIMEMORY * m_pfimemory;

   fimemory(const memory & memory)
   {


      m_pfimemory = FreeImage_OpenMemory(memory.get_data(), (::u32) memory.get_size());

   }


   ~fimemory()
   {

      if (m_pfimemory != nullptr)
      {

         FreeImage_CloseMemory(m_pfimemory);

      }

   }

   operator FIMEMORY * ()
   {

      return m_pfimemory;

   }

   FREE_IMAGE_FORMAT get_image_format()
   {

      return FreeImage_GetFileTypeFromMemory(m_pfimemory);

   }

};
