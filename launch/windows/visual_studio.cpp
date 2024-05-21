#include "framework.h"
#include "visual_studio.h"
#include "acme_windows/_.h"
#include "acme_windows/registry.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/listing.h"


namespace microsoft
{


   visual_studio::visual_studio()
   {

   }


   visual_studio::~visual_studio()
   {

   }


   ::string_array visual_studio::get_instances()
   {

      auto pathProgramData = acmedirectory()->program_data();

      ::file::listing listing;

      auto pathInstances = pathProgramData / "Microsoft\\VisualStudio\\Packages\\_Instances";

      listing.set_folder_listing(pathInstances);

      acmedirectory()->enumerate(listing);

      ::string_array straInstances;

      for (auto& path : listing)
      {

         straInstances.add(path.name());

      }

      return straInstances;

   }


   string visual_studio::get_a_visual_studio_2022_instance()
   {

      auto straInstances = get_instances();

      for (auto& strInstance : straInstances)
      {

         acme_windows::registry::key key;

         ::string strRegistryPath;

         strRegistryPath = "SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + strInstance;

         if (key._open(HKEY_LOCAL_MACHINE, strRegistryPath))
         {

            auto strDisplayVersion = key.get("DisplayVersion");

            if (strDisplayVersion.begins("17."))
            {

               return strInstance;

            }

         }

      }

      return {};

   }


   ::file::path visual_studio::get_an_existing_visual_studio_2022_install_location()
   {

      auto straInstances = get_instances();

      for (auto& strInstance : straInstances)
      {

         acme_windows::registry::key key;

         ::string strRegistryPath;

         strRegistryPath = "SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + strInstance;

         if (key._open(HKEY_LOCAL_MACHINE, strRegistryPath))
         {

            auto strDisplayVersion = key.get("DisplayVersion");

            if (strDisplayVersion.begins("17."))
            {

               ::file::path pathInstallLocation= key.get("InstallLocation");

               if (acmedirectory()->is(pathInstallLocation))
               {

                  return pathInstallLocation;

               }

            }

         }

      }

      return {};

   }


} // namespace microsoft


