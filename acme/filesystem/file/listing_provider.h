#pragma once


namespace file
{


   class listing;


   class CLASS_DECL_ACME listing_provider :
      virtual public ::matter
   {
   public:


      virtual bool perform_file_listing(::file::listing& listing) = 0;
      virtual bool perform_file_relative_name_listing(::file::listing& listing) = 0;


   };


} // namespace file


