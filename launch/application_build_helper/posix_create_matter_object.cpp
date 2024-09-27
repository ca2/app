// From application_build_helper.cpp by camilo on 2023-03-07 17:38 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
////#include "acme/exception/exception.h"
#include "application_build_helper.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/filesystem/acme_directory.h"
//#include "acme/filesystem/filesystem/file_context.h"
#include "acme/operating_system/process.h"
#include "acme/platform/ini.h"
#include "acme/platform/node.h"
#include "acme/prototype/string/str.h"
#include "acme/platform/system.h"
#ifdef WINDOWS_DESTKOP
#include <direct.h>
#endif
#include "application_build_helper.h"
//#include "acme/platform/system.h"
//#include "acme/prototype/collection/string_array.h"
//#include "_factory.h"

namespace application_build_helper
{



   void application_build_helper::posix_create_matter_object()
   {

      ::file::path pathMatterZipO = m_pathFolder / ".link_object/_matter.zip.o";

      acmedirectory()->change_current(m_pathFolder);

      acmedirectory()->create(m_pathFolder / ".link_object");

      string_array straOutput;

      int iExitCode = 0;

      string strCommand;

#if defined(FREEBSD) || defined(OPENBSD)

      strCommand = "ld -r -b binary -o " + pathMatterZipO + " -m elf_x86_64_fbsd -z noexecstack _matter.zip";

#else

      strCommand = "ld -r -z noexecstack -b binary -o " + pathMatterZipO + " _matter.zip";

#endif

      auto functionTrace = [&](auto etracelevel, auto & str)
      {

         straOutput.append_format("%c: %s\n", trace_level_letter(etracelevel), str.c_str());

      };

      iExitCode = acmenode()->command_system(strCommand, functionTrace);

      if (iExitCode != 0)
      {

         fprintf(stderr, "Command failed: %s\n", straOutput.implode("\n").c_str());

      }

   }


} // namespace application_build_helper



