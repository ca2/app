#include "folder_google_drive/platform.h"
#include "folder_google_drive/folder.h"
#include "apex/filesystem/fs/set.h"
#include "acme/platform/acme.h"

namespace
{
   class recording_filesystem : public ::fs::data
   {
   public:
      int m_iCalls = 0;
      ::file::path m_pathParent;
      ::string m_strName;

      ::file::path create_folder(const ::file::path & pathParent, const ::scoped_string & scopedstrName) override
      {
         ++m_iCalls;
         m_pathParent = pathParent;
         m_strName = scopedstrName;
         return "test://created-id";
      }
   };
}

int main()
{
   ::acme::acme runtime;
   ::exception::s_bEnableCallStackBackTrace = false;
   ::pointer < recording_filesystem > pfilesystem(allocate_t{});
   ::fs::set router;
   router.fsmap()["test://"] = pfilesystem;
   auto path = router.create_folder("test://parent-id", "Project invoices");
   if (path != "test://created-id" || pfilesystem->m_iCalls != 1
      || pfilesystem->m_pathParent != "test://parent-id"
      || pfilesystem->m_strName != "Project invoices") return 1;

   ::folder unsupportedFolder;
   try { unsupportedFolder.create_folder("test://", "name"); return 2; }
   catch (const ::exception & exception) { if (exception.m_estatus != error_not_supported) return 3; }
   ::fs::data unsupportedFilesystem;
   try { unsupportedFilesystem.create_folder("test://", "name"); return 4; }
   catch (const ::exception & exception) { if (exception.m_estatus != error_not_supported) return 5; }

   // Invalid names must fail before login or any remote mutation through either interface.
   ::folder_google_drive::folder drive;
   ::folder & virtualFolder = drive;
   try { virtualFolder.create_folder("google-drive://", "../outside"); return 6; }
   catch (const ::exception & exception) { if (exception.m_estatus != error_bad_argument) return 7; }
   ::fs::data & filesystem = drive;
   try { filesystem.create_folder("google-drive://", " "); return 8; }
   catch (const ::exception & exception) { if (exception.m_estatus != error_bad_argument) return 9; }
   return 0;
}
