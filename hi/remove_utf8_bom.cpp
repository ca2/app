#include "framework.h"
#include "application.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/primitive/primitive/memory.h"


namespace console_hello
{


   void application::remove_utf8_bom_phase1()
   {

      ::file::listing listing;

      auto pathFolder = acmedirectory()->get_current();

      listing.set_pattern_file_listing(pathFolder, {"*.h", "*.cpp", "*.c", "*.hpp", "*.mm", "*.java" }, e_depth_recursively);
      ::file::path_array patha;

      memory memoryNull;

      memoryNull.append('\0');

      listing.m_functionOnNewPath = [this,&patha,&memoryNull](auto & path)
         {
            auto memory = acmefile()->as_memory(path);

            if (memory.size() >= 3 && !memory.find(memoryNull))
            {

               auto & ch0 = memory[0];
               auto & ch1 = memory[1];
               auto & ch2 = memory[2];

               if (ch0 == 0xEF && ch1 == 0xBB && ch2 == 0xBF)
               {

                  patha.add(path);
                  informationf("%s", path.c_str());

               }

            }



};

      acmedirectory()->enumerate(listing);

      auto pathFileWithBoms = pathFolder / "file_with_boms.txt";


      //for (auto & path : listing)
      //{

      //   if (path.case_insensitive_ends("/thumbnail_dc.cpp"))
      //   {


      //   }

      //   //char szBomCandidate;

      //   //pfile->read(szBomCandidate, 3);

      //   //if (szBomCandidate[0] == '0xEF'
      //   //   && szBomCandidate[1] == '0xBB'
      //   //   && szBomCandidate[1] == '0xBF')
      //   //{


      //   //}

      //}

      acmefile()->put_lines(pathFileWithBoms, patha);

   }


   void application::remove_utf8_bom_phase2()
   {

      auto pathFolder = acmedirectory()->get_current();
      auto pathFileWithBoms = pathFolder / "file_with_boms.txt";


      auto patha = acmefile()->lines(pathFileWithBoms);

      memory memoryNull;

      memoryNull.append('\0');


      for (auto & path : patha)
      {
         auto memory = acmefile()->as_memory(path);

         if (memory.size() >= 3 && !memory.find(memoryNull))
         {

            auto & ch0 = memory[0];
            auto & ch1 = memory[1];
            auto & ch2 = memory[2];

            if (ch0 == 0xEF && ch1 == 0xBB && ch2 == 0xBF)
            {

               memory.eat_begin(nullptr, 3);

               acmefile()->put_block(path, memory);

            }

         }


      }


   }


} // namespace console_hello



