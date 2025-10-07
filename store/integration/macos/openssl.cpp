#include "framework.h"
#include "openssl.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/integration_context.h"
#include "acme/platform/node.h"


namespace console_integration
{


namespace macos
{

openssl::openssl()
{
   
}


openssl::~openssl()
{
   
}


void openssl::initialize(::particle * pparticle)
{
   
   ::particle::initialize(pparticle);
   
   acmenode()->integration_factory();
   
   øconstruct(m_papplication);
   
   m_papplication->m_bMsys = true;
   
   m_papplication->m_strName = "openssl";
   
}


void openssl::build()
{
   
   if(m_papplication->m_strPlatform.is_empty())
   {
      
      m_papplication->m_strPlatform = "amd64";
      
      build();
      
      m_papplication->m_strPlatform = "arm";
      
      build();
      
      m_papplication->m_strPlatform.empty();
      
   }
   else
   {
      
      prepare();
      
      clean();
      
      download();
      
      configure();
      
      compile();
      
   }
   
   install();
   
}


void openssl::clean()
{
   
   m_papplication->clean();
   
}


void openssl::prepare()
{
   
   m_papplication->m_strRelease = "3.0.8";
   
   m_papplication->m_pathDownloadURL = "https://www.openssl.org/source/openssl-" + m_papplication->m_strRelease + ".tar.gz";
   
   m_papplication->prepare();
   
   if (m_papplication->m_strPlatform == "amd64")
   {
      
      if (m_papplication->m_strConfiguration.case_insensitive_contains("Debug"))
      {
         
         m_strConfigure = "debug-VC-WIN32";
         
         m_strDebug = "--debug";
         
      }
      else
      {
         
         m_strConfigure = "VC-WIN32";
         
         m_strDebug = "";
         
      }
      
   }
   else if (m_papplication->m_strPlatform == "arm")
   {
      
      if(m_papplication->m_strConfiguration.case_insensitive_contains("Debug"))
      {
         
         m_strConfigure = "debug-VC-WIN64A";
         
         m_strDebug = "--debug";
         
      }
      else
      {
         
         m_strConfigure = "VC-WIN64A";
         
         m_strDebug = "";
         
      }
      
   }
   else
   {
      
      throw ::exception(error_failed, "Unsupported Platform \"" + m_papplication->m_strPlatform + "\"?!?");
      
   }
   
   if (m_papplication->m_strConfiguration.case_insensitive_contains("Static"))
   {
      
      m_strShared = "no-shared";
      
   }
   else
   {
      
      m_strShared = "shared";
      
   }
   
   auto pathBase = m_papplication->m_pathFolder;
   
   auto path = m_papplication->m_pathBase / m_papplication->m_pathPlatformConfiguration;
   
   m_papplication->m_pathPrefix = pathBase / path / "build";
   
   m_papplication->prepare_compile_and_link_environment();
   
}


void openssl::download()
{
   
   m_papplication->change_to_source_directory();
   
   m_papplication->download_and_uncompress();
   
}


void openssl::configure()
{
   
   m_papplication->change_to_source_directory();
   
   string strPrefix = m_papplication->prepare_path(m_papplication->m_pathPrefix);
   
   ::string strCommand;
   
   auto pathProgram = m_papplication->m_pathFolder / m_papplication->m_pathBase / m_papplication->m_pathPlatformConfiguration / "program";
   
   strCommand += "perl Configure " + m_strConfigure + " " + m_strDebug;
   
   strCommand += " --prefix=" + strPrefix + " --openssldir=" + pathProgram + " " + m_strShared;
   
   m_papplication->command_system(strCommand);
   
}


void openssl::compile()
{
   
   m_papplication->change_to_source_directory();
   
   m_papplication->command_system("nmake");
   
}


void openssl::install()
{
   
   m_papplication->change_to_source_directory();
   
   m_papplication->command_system("nmake install_sw");
   
   auto pathOperatingSystemIncludeFolder = m_papplication->m_pathOperatingSystemIncludeFolder;
   
   auto pathOperatingSystemStorageFolder = m_papplication->m_pathOperatingSystemStorageFolder / m_papplication->m_strPlatform / m_papplication->m_strConfiguration;
   
   directory_system()->create(pathOperatingSystemIncludeFolder / "include");
   
   directory_system()->create(pathOperatingSystemStorageFolder / "binary");
   
   directory_system()->create(pathOperatingSystemStorageFolder / "library");
   
   auto strPrefix = m_papplication->prepare_path(m_papplication->m_pathPrefix);
   
   auto strInclude = m_papplication->prepare_path(pathOperatingSystemIncludeFolder);
   
   auto strStorage = m_papplication->prepare_path(pathOperatingSystemStorageFolder);
   
   m_papplication->bash("cp -f " + strPrefix + "/include/* " + strInclude + "/include/");
   m_papplication->bash("cp -f " + strPrefix + "/bin/* " + strStorage + "/binary/");
   m_papplication->bash("cp -f " + strPrefix + "/lib/* " + strStorage + "/library/");
   
}

} // namespace macos


} // namespace console_integration



