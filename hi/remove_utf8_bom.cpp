#include "framework.h"
#include "application.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/prototype/prototype/memory.h"


namespace console_hello
{


   void application::remove_utf8_bom_phase1()
   {

      ::file::listing_base listing;

      auto pathFolder = directory_system()->get_current();

      listing.set_pattern_file_listing(pathFolder, {"*.h", "*.cpp", "*.c", "*.hpp", "*.mm", "*.java" }, e_depth_recursively);
      ::file::path_array_base patha;

      memory memoryNull;

      memoryNull.append('\0');

      listing.m_functionOnNewPath = [this,&patha,&memoryNull](auto & path)
         {
            auto memory = file_system()->as_memory(path);

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

      directory_system()->enumerate(listing);

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

      file_system()->put_lines(pathFileWithBoms, patha);

   }


   void application::remove_utf8_bom_phase2()
   {

      auto pathFolder = directory_system()->get_current();
      auto pathFileWithBoms = pathFolder / "file_with_boms.txt";


      auto patha = file_system()->lines(pathFileWithBoms);

      memory memoryNull;

      memoryNull.append('\0');


      for (auto & path : patha)
      {
         auto memory = file_system()->as_memory(path);

         if (memory.size() >= 3 && !memory.find(memoryNull))
         {

            auto & ch0 = memory[0];
            auto & ch1 = memory[1];
            auto & ch2 = memory[2];

            if (ch0 == 0xEF && ch1 == 0xBB && ch2 == 0xBF)
            {

               memory.eat_begin(nullptr, 3);

               file_system()->put_block(path, memory);

            }

         }


      }


   }


} // namespace console_hello



