// From fs/raw_folder by camilo on 2025-03-10 22:08 <3ThomasBorregaardSorensen!!s
#include "framework.h"
#include "raw_folder_protocol.h"
#include "acme/filesystem/filesystem/listing.h"


namespace fs
{


   raw_folder_protocol::raw_folder_protocol()
   {

 
   }


   raw_folder_protocol::~raw_folder_protocol()
   {


   }


   void raw_folder_protocol::on_initialize_particle()
   {

      ::fs::data::on_initialize_particle();

   }

   
   string raw_folder_protocol::protocol()
   {

      return {};

   }


   ::file::listing & raw_folder_protocol::root_ones(::file::listing & listing)
   {

      ::file::path path;

      path = this->protocol() + "://";

      path.set_existent_folder();

      listing.defer_add(path);

      listing.m_straTitle.add("User Intelligent File psystem");

      return listing;


   }


} // namespace fs



