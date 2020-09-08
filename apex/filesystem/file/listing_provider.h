pragma once


namespace file
{


   class listing;


   class CLASS_DECL_APEX listing_provider
   {
   public:


      virtual listing & perform_file_listing(::file::listing & listing) = 0;


   };



} // namespace file


