#include "framework.h"
#include "x265.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/integration_context.h"
#include "acme/platform/node.h"


namespace console_integration
{


   namespace macos
   {
   
   
      x265::x265()
      {
         
      }
      
      
      x265::~x265()
      {
         
      }
      
      
      void x265::initialize(::particle * pparticle)
      {
         
         ::console_integration::macos::build::initialize(pparticle);
         ::console_integration::x265::initialize(pparticle);
         
      }
      
      
      void x265::initialize_x265(
                                 const ::scoped_string & scopedstrArch,
                                 const ::scoped_string & scopedstrTargetting,
                                 const ::scoped_string & scopedstrTarget,
                                 const ::scoped_string & scopedstrHost)
      {
         
         initialize_macos_build(scopedstrArch);
         
         m_strArch = scopedstrArch;
         m_strTargetting = scopedstrTargetting;
         m_strTarget = scopedstrTarget;
         m_strHost = scopedstrHost;
         
      }
      
      
      void x265::build()
      {
         
         if(m_papplication->m_strPlatform.is_empty())
         {
            
            initialize_x265("x86_64", "x86_64-apple-macos10.13", "10.13", "x86_64-apple-darwin");

            build();

            initialize_x265("arm64", "arm64-apple-macos11.0", "11.0", "arm64-apple-darwin");

            build();
            
            if(!m_papplication->m_strConfiguration.case_insensitive_contains("static"))
            {
               
               lipo(m_papplication->m_strName + "_main12");
               lipo(m_papplication->m_strName + "_main10");
               lipo();
               
               auto pathPrefixInclude = m_papplication->m_pathPrefix / "include";

               auto pathOperatingSystemIncludeFolder = directory_system()->home() /"workspace/operating_system/operating_system-macos/include";
               
               m_papplication->bash("cp -f " + pathPrefixInclude + "/x265*.h " + pathOperatingSystemIncludeFolder + "/");
               
            }
            
            while (true)
            {
   
               printf("Enter q to quit.\n");
   
               if (getchar() == 'q')
               {
   
                  break;
   
               }
   
            }
            
            return;
            
         }
         
         prepare();
         
         //clean();
      
         download();
      
         configure(12);
      
         compile();
         
         install();

         configure(10);
      
         compile();
         
         install();

         configure(8);
      
         compile();

         install();
         
//         while (true)
//         {
//
//            printf("Enter q to quit.\n");
//
//            if (getchar() == 'q')
//            {
//
//               break;
//
//            }
//
//         }

         auto pathSource = m_papplication->m_pathSource / "source";

         auto pathPrefixInclude = m_papplication->m_pathPrefix / "include";

         directory_system()->create(pathPrefixInclude);
         
         m_papplication->bash("cp -f " + pathSource + "/x265*.h " + pathPrefixInclude + "/");

         auto pathSourceBits = m_pathSourceBits;

         m_papplication->bash("cp -f " + pathSourceBits + "/x265*.h " + pathPrefixInclude + "/");
         
      }
      
      
      void x265::clean()
      {
         
         m_papplication->clean();
         
      }
      
      
      void x265::prepare()
      {
         
         m_papplication->prepare();
         
         if(m_papplication->m_pathPrefix.is_empty())
         {
            
            m_papplication->m_pathPrefix = calculate_prefix_path(m_papplication->m_strPlatform, m_papplication->m_strConfiguration);
            
         }
         
         directory_system()->create(m_papplication->m_pathPrefix);
         
         m_papplication->prepare_compile_and_link_environment();
         
         m_papplication->create_source_directory();
         
      }
      
      
      void x265::download()
      {
         
         m_papplication->create_source_directory();
         
         m_papplication->change_to_source_directory();
         
         m_papplication->git_clone();
         
      }
      
      
      void x265::configure(int iBits)
      {
         
         ::string strBits;
         
         strBits.format("%d", iBits);
         
         switch(iBits)
         {
            case 8:
               m_strTargetName = m_papplication->m_strName;
               break;
            case 10:
               m_strTargetName = m_papplication->m_strName + "_main10";
               break;
            case 12:
               m_strTargetName = m_papplication->m_strName + "_main12";
               break;
            default:
               throw ::exception(error_wrong_state);
         }
         
         m_pathSourceBits = m_papplication->m_pathSource / strBits;
         
         directory_system()->create(m_pathSourceBits);
         
         directory_system()->change_current(m_pathSourceBits);
         
         string strPrefix = m_papplication->prepare_path(m_papplication->m_pathPrefix);
         
         ::file::path pathToolchainFileCmake = directory_system()->home() / "workspace/operating_system/include/toolchain_file.cmake";

         ::file::path pathAsmCompiler = directory_system()->home() / "workspace/operating_system/include/asm_compiler";

         string strCommand;
         
         string strBitDepthFlags;
         
         string strLibraryExtension;
         
         if(m_papplication->m_strConfiguration.case_insensitive_contains("static"))
         {
            
            strLibraryExtension = "a";
            
         }
         else
         {
            
            strLibraryExtension = "dylib";
            
         }
         
         if(iBits      >= 10)
         {
            
            strBitDepthFlags += " -DHIGH_BIT_DEPTH=ON";
            
            if(iBits == 12)
            {
               
               strBitDepthFlags += " -DMAIN12=ON";
               
            }
            
         }
         else
         {
         
            if(m_papplication->m_strConfiguration.case_insensitive_contains("static"))
            {
               
               strBitDepthFlags += " -DLINKED_10BIT=ON -DLINKED_12BIT=ON";
               strBitDepthFlags += " -DEXTRA_LIB=\"x265_main10."+strLibraryExtension+";x265_main12."+strLibraryExtension+"\"";
               strBitDepthFlags += " -DCMAKE_SHARED_LINKER_FLAGS=\"-L"+strPrefix+"/lib\"";

            }
         
         }
            
         
         strCommand += "cmake -G \"Ninja\"";
         //strCommand += "cmake ";
         strCommand += " -DCMAKE_OSX_ARCHITECTURES=\"" + m_papplication->m_strPlatform + "\"";
         //strCommand += " -DCMAKE_BUILD_PARALLEL_LEVEL=\"6\"";
         if(m_papplication->m_strPlatform == "x86_64")
         {
            strCommand += " -DCMAKE_OSX_DEPLOYMENT_TARGET=\"10.13\"";
            strCommand += " -DEXPORT_C_API=ON";
            //strCommand += " -DCMAKE_CROSS_COMPILING=FALSE";
            //strCommand += " -DCMAKE_SYSTEM_PROCESSOR=\"x86_64\"";
            //strCommand += " -DEXPORT_C_API=OFF";
            // used by toolchain_file.cmake
            //strCommand += " -DPLATFORM=\"MAC\"";
         }
         else if(m_papplication->m_strPlatform == "arm64")
         {
            strCommand += " -DCMAKE_OSX_DEPLOYMENT_TARGET=\"11.0\"";
            //strCommand += " -DCMAKE_CROSS_COMPILING=TRUE";
            //strCommand += " -DCMAKE_SYSTEM_PROCESSOR=\"arm64\"";
            // used by toolchain_file.cmake
            strCommand += " -DPLATFORM=\"MAC_ARM64\"";
            strCommand += " -DCROSS_COMPILE_ARM64=\"ON\"";
            strCommand += " -DEXPORT_C_API=ON";
            strCommand += " -DENABLE_ASSEMBLY=OFF";
            //strCommand += " -DCMAKE_ASM_COMPILER=\"" + pathAsmCompiler + "\"";
            //strCommand += " -DENABLE_GAS_PREPROCESSOR=\"ON\"";
            //strCommand += " -DENABLE_ASSEMBLY=\"OFF\"";
            strCommand += " -DCMAKE_TOOLCHAIN_FILE=\"" + pathToolchainFileCmake + "\"";
         }
         else
         {
            strCommand += " -DEXPORT_C_API=OFF";
            strCommand += " -DCMAKE_OSX_DEPLOYMENT_TARGET=\"10.13\"";
            //strCommand += " -DCMAKE_CROSS_COMPILING=TRUE";
         }
         strCommand += " -S ../source";
         strCommand += " -B .";
         //strCommand += " --target=\"x86-shared\"";
         strCommand += " -DCMAKE_INSTALL_PREFIX=\"" + strPrefix + "\"";
         strCommand += " -DENABLE_LIBNUMA=OFF";
         strCommand += " -DENABLE_CLI=OFF";
         strCommand += strBitDepthFlags;
         if(m_papplication->m_strConfiguration.case_insensitive_contains("static"))
         {
            
            strCommand += " -DENABLE_STATIC=ON";
            strCommand += " -DENABLE_SHARED=OFF";

         }
         else
         {
            
            strCommand += " -DENABLE_STATIC=OFF";
            strCommand += " -DENABLE_SHARED=ON";
            
         }
         strCommand += " -DBIN_INSTALL_DIR=\"" + (m_papplication->m_pathOperatingSystemStorageFolder /"binary") + "\"";
         //strCommand += " " + m_strShared + " " + m_strStatic;
         //   if (m_papplication->m_strConfiguration.case_insensitive_contains("Static"))
         //   {
         //
         //      insert_cmp0091_new_in_cmake();
         //
         //      if (m_papplication->m_strConfiguration.case_insensitive_contains("Debug"))
         //      {
         //
         //         strCommand += " -DCMAKE_MSVC_RUNTIME_LIBRARY=\"MultiThreadedDebug\"";
         //
         //      }
         //      else
         //      {
         //
         //         strCommand += " -DCMAKE_MSVC_RUNTIME_LIBRARY=\"MultiThreaded\"";
         //
         //      }
         //
         //   }
         
         
         information() << strCommand;
         
         m_papplication->bash(strCommand);

         information() << "Finishing x265::configure...";
         
      }
      
      
      void x265::compile()
      {
         
         //m_papplication->change_to_source_directory("source");
         
         string strPrefix = m_papplication->prepare_path(m_papplication->m_pathPrefix);
         
         //m_papplication->bash("cmake --build " + (m_papplication->m_pathSource / "source"));
         m_papplication->bash("ninja");
         
      }
      
      
      void x265::install()
      {
         
         if(m_papplication->m_strConfiguration.case_insensitive_contains("static"))
         {
            
            //m_papplication->change_to_source_directory();
            
            //m_papplication->command_system("make install");
            
            //   auto pathOperatingSystemIncludeFolder = m_papplication->m_pathOperatingSystemIncludeFolder;
            //
            auto pathOperatingSystemStorageFolderPlatform = m_papplication->m_pathOperatingSystemStorageFolder / m_papplication->m_strPlatform ;
            //
            //   directory_system()->create(pathOperatingSystemIncludeFolder / "include");
            //
            //   directory_system()->create(pathOperatingSystemStorageFolder / "binary");
            //
            directory_system()->create(pathOperatingSystemStorageFolderPlatform / "library");
            //
            //   auto strPrefix = m_papplication->prepare_path(m_papplication->m_pathPrefix);
            //
            //   auto strInclude = m_papplication->prepare_path(pathOperatingSystemIncludeFolder);
            //
            //   auto strStorage = m_papplication->prepare_path(pathOperatingSystemStorageFolder);
            //
            //   m_papplication->bash("cp -f " + strPrefix + "/include/* " + strInclude + "/include/");
            //   m_papplication->bash("cp -f " + strPrefix + "/bin/* " + strStorage + "/binary/");
            ::string strA = "lib" + m_papplication->m_strName + ".a";
            
            ::string strTarget = "lib" + m_strTargetName + ".a";

            auto pathOriginal = m_pathSourceBits / strA;

            auto pathTarget = m_pathSourceBits / strTarget;

            ::string strCommand2 ="mv -f " + pathOriginal + " " + pathTarget;

            m_papplication->bash(strCommand2);

            ::string strCommand ="cp -f " + pathTarget + " " + (pathOperatingSystemStorageFolderPlatform / "library/") ;
            
            m_papplication->bash(strCommand);
            
         }
         else
         {
            
            {
               
               ::string strDylib = "lib" + m_papplication->m_strName + ".dylib";

               ::string strDylibOriginal = "lib" + m_papplication->m_strName + "-original.dylib";

               auto path = m_pathSourceBits / strDylib;

               auto pathOriginal = m_pathSourceBits / strDylibOriginal;
               
               ::string strCommand2 ="mv -f " + path + " " + pathOriginal;

               m_papplication->bash(strCommand2);
               
               ::string strTargetDylib = "lib" + m_strTargetName + ".dylib";

               auto pathTarget = m_pathSourceBits / strTargetDylib;

               file_system()->copy(pathTarget, pathOriginal, true);
               
               ::string strCommand3 ="install_name_tool -id @executable_path/" + strTargetDylib + " " + path;

               m_papplication->bash(strCommand3);
               
               auto pathPrefix = m_papplication->m_pathPrefix / "lib" / strTargetDylib;

               information() << "Copying from \"" << pathTarget << "\" to \"" << pathPrefix << "\"";
               
               file_system()->copy(pathPrefix, pathTarget, true);
             
               m_mappath[m_strTargetName][m_papplication->m_strPlatform] = pathPrefix;
               
            }
            
            if(m_strTargetName == m_papplication->m_strName)
            {
               
               ::string strPc = m_papplication->m_strName + ".pc";
               
               auto pathOriginal = m_pathSourceBits / strPc;
               
               auto path = m_papplication->m_pathPrefix / "lib/pkgconfig" / strPc;
               
               information() << "Copying from \"" << pathOriginal << "\" to \"" << path << "\"";
               
               file_system()->copy(path, pathOriginal, true);
               
            }

         }
         
      }
   
   
   } // namespace macos



} // namespace console_integration



