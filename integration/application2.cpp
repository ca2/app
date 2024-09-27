#include "framework.h"
#include "acme/console.h"
#include <stdio.h>
#include "acme/platform/system.h"
#include "acme/prototype/prototype/url.h"
#include "apex/networking/http/context.h"


namespace console
{


   namespace build_library
   {

      class application :
         virtual public ::apex::application
      {
      public:


         ::file::path m_pathFolder;




         application()
         {

            m_bNetworking = true;

            m_bCrypto = false;

            m_bResource = false;

            m_strAppId = "console/http_get";

            m_pathFolder = "C:\\";


         }


         void main() override
         {

            auto psystem = system();

            auto pplatform = psystem->m_pplatform;

            for (int i = 0; i < pplatform->get_argument_count1(); i++)
            {

               string strArgument = pplatform->get_argument1(i);

               if (strArgument.case_insensitive_equals("ffmpeg"))
               {

                  ffmpeg();

               }
               else if (strArgument.case_insensitive_equals("openssl"))
               {

                  openssl();

               }

            }


         }

         void ffmpeg()
         {

            ffmpeg("Win32", "Debug");
            ffmpeg("Win32", "Release");
            ffmpeg("Win32", "StaticDebug");
            ffmpeg("Win32", "StaticRelease");

            ffmpeg("x64", "Debug");
            ffmpeg("x64", "Release");
            ffmpeg("x64", "StaticDebug");
            ffmpeg("x64", "StaticRelease");


         }


         void ffmpeg(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration)
         {

            printf("Building ffmpeg");

            ::file::path path;

            path = "ffmpeg" / strVersion / scopedstrPlatform / scopedstrConfiguration;

            ::file::path pathPrefix = m_pathFolder / path / "build"

            string strCommand;
            
            strCommand = 
               "configure --enable-asm --enable-yasm --arch=" + strArch + 
               " --disable-doc "+ strShared + strStatic + 
               " --disable-bzlib --disable-libopenjpeg --disable-iconv --disable-zlib" +
               " --prefix=" + strBaseDir + "/" + strPath + "/build$BASE_DIR / $PATH / build --toolchain = msvc $DEBUG


         }

         void openssl()
         {

            printf("Building openssl");


         }


      };


   } // namespace http_get


} // namespace console


::console::http_get::application g_console_http_get_application;



