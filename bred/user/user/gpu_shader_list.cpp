// Created by camilo on 2026-11-02 06:11 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
#include "platform.h"
#include "gpu_shader_list.h"
#include "acme/filesystem/filesystem/directory_context.h"


namespace user
{


   gpu_shader_list::gpu_shader_list()
   {


   }

   gpu_shader_list::~gpu_shader_list() 
   {

   }


   void gpu_shader_list::initialize_user_gpu_shader_list(::particle * pparticleParent)
   {

      initialize(pparticleParent);

      defer_create_synchronization();

      get_shader_listing(m_filelisting);

   }


   string gpu_shader_list::get_next_shader_path(const ::scoped_string & scopedstrPath)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto next = m_filelisting.get_next(scopedstrPath);

      return ::transfer(next);

   }


   void gpu_shader_list::get_shader_listing(::file::listing_base & listing)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      string_array_base straFolders;

      if (!m_papplication->is_sandboxed())
      {

         // Prefer the user's local shader collection before cloud-provider defaults.
         straFolders.add(directory()->home() / "dropbox" / "shader" / "simple shader");
         straFolders.add("cloud://shader/simple shader/");

      }

      straFolders.add("matter://shader/simple shader/");

      for (const auto & folder : straFolders)
      {

         listing.clear();
         listing.set_pattern_file_listing(folder, { "*.frag", "*.shader" });
         directory()->enumerate(listing);

         information() << "app_shader: shader folder: " << folder
            << "; files found: " << listing.size();

         if (listing.has_elements())
         {

            break;

         }

      }

      listing.order();

   }


} // namespace user



