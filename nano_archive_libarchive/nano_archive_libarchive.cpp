//
// Created by camilo on 5/26/24.
//
#include "framework.h"
#include "nano_archive_libarchive.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include <archive.h>
#include <archive_entry.h>
//#include <unistd.h>


namespace libarchive
{


   namespace nano
   {


      namespace archive
      {

         archive::archive()
         {


         }


         archive::~archive()
         {

         }


         void archive::untar(const ::file::path & pathFolder, const ::payload & payloadTar, int iStripComponent, ::function<void(const::scoped_string& scopedstr) > functionCallback)
         {
            struct ::archive * a;
            struct ::archive_entry * entry;
            int r;

            a = archive_read_new();
            archive_read_support_filter_all(a);
            archive_read_support_format_all(a);

            ::memory memory;

            memory = file()->as_memory(payloadTar);

            //struct archive * a = archive_read_new();
            //archive_read_support_compression_gzip(a);
            //archive_read_support_format_tar(a);
            r = archive_read_open_memory(a, memory.data(), memory.size());
            //r = archive_read_open_filename(a, "archive.tar", 10240); // Note 1
            if (r != ARCHIVE_OK)
            {

               throw exception(error_failed);

            }
            ::memory memory2;
            memory2.set_size(1_MiB);
            while (archive_read_next_header(a, &entry) == ARCHIVE_OK)
            {
               //printf("%s\n", archive_entry_pathname(entry));
               string strPathName(archive_entry_pathname_w(entry));
               if (!strPathName.ends("/") && !strPathName.ends("\\"))
               {

                  ::file::path path(strPathName);

                  for(int i = 0; i < iStripComponent; i++)
                  {

                     auto p = path.find_first_character_in("/\\");

                     if (!p)
                     {

                        goto next;

                     }

                     p = path(p).skip_any_character_in("/\\");

                     path = p;

                  }

                  string strSymlink(archive_entry_symlink_w(entry));

                  if(strSymlink.has_character())
                  {

                     ::file::path pathSymlinkSource(strSymlink);

                     for(int i = 0; i < iStripComponent; i++)
                     {

                        auto p = pathSymlinkSource.find_first_character_in("/\\");

                        if (!p)
                        {

                           goto next;

                        }

                        p = pathSymlinkSource(p).skip_any_character_in("/\\");

                        pathSymlinkSource = p;

                     }
                     auto pathTarget = pathFolder / path;
                     auto pathSource = pathTarget.folder() / pathSymlinkSource;
                     path_system()->symbolic_link(pathTarget, pathSource);
                     goto next;

                  }


                  auto pfile = file()->get_writer(pathFolder / path);

                  for (;;) {
                     auto size = archive_read_data(a, memory2.data(), memory2.size());
                     if (size < 0) {
                        throw ::exception(error_failed);
                     }
                     if (size == 0)
                        break;
                     pfile->write(memory2(0, size));
                     //write(1, buff, size);
                  }
                  if (functionCallback)
                  {
                     functionCallback(strPathName);
                  }
                  //informationf(strPathName + "\n");

               }
               next:
               archive_read_data_skip(a);  // Note 2
            }
            r = archive_read_free(a);  // Note 3
            if (r != ARCHIVE_OK)
            {

               throw exception(error_failed);

            }

         }


      } // namespace archive


   } //namespace nano


} // namespace libarchive



