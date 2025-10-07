//
// Created by camilo on 2025-09-28 14:27 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "_ktx.h"
#include "acme/filesystem/filesystem/file_context.h"


namespace gpu
{


   ktxResult loadKTXFile(::particle *pparticle, const ::file::path & path, ktxTexture **target)
   {

      ktxResult result = KTX_SUCCESS;

      if (!pparticle->file()->exists(path))
      {

         throw ::exception(error_file_not_found, "KTX file not found: " + path);
      }

      auto memory = pparticle->file()->as_memory(path);

      result =
         ktxTexture_CreateFromMemory(memory.data(), memory.size(), KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT, target);

      return result;
   }


} // namespace gpu


