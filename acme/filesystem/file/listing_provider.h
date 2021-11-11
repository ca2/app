#pragma once


namespace file
{


   class listing;


   class CLASS_DECL_ACME listing_provider :
      virtual public ::matter
   {
   public:


      virtual ::file::listing& perform_file_listing(::file::listing& listing) = 0;
      virtual ::file::listing& perform_file_relative_name_listing(::file::listing& listing) = 0;


   };


} // namespace file


