// Created by camilo on 203-06-08 22:50 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/prototype/prototype/memory.h"


namespace console_hello
{


   void application::search_special_characters()
   {

      ::file::listing_base listing;

      auto pathFolder = directory_system()->get_current();

      listing.set_pattern_file_listing(pathFolder, {"*.h", "*.cpp", "*.c", "*.hpp" }, e_depth_recursively);
      ::file::path_array_base patha;
      ::string strReports;

      listing.m_functionOnNewPath = [this,&patha,&strReports](auto & path)
         {


         if (path.contains("aaa_") || path.contains("aaaa_") || path.contains("aaaaa_"))
         {

            return;

         }

         if (path.contains("archive_2021"))
         {

            return;

         }

            auto lines = file_system()->lines(path);

            for(int iLine = 1; iLine <= lines.size(); iLine++)
            {

               auto & line = lines[iLine - 1];

               for (int iCharacter = 1; iCharacter <= line.size(); iCharacter++)
               {

                  auto & character = line[iCharacter - 1];

                  if (character & 0x80)
                  {

                     string strReport;

                     strReport.formatf("%s(%d,%d): %s\r\n",path.c_str(), iLine, iCharacter, line.substr(iCharacter - 1, line.length() - iCharacter + 1).c_str());

                     output_debug_string_formatf("%s", strReport.c_str());

                     information(strReport);

                     strReports += strReport;

                     break;

                  }

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

      file_system()->put_lines(pathFileWithBoms, strReports);

   }


} // namespace console_hello



