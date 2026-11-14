// Created by camilo on 2022-03-13 19:38 <3ThomasBorregaardSorensen!!
// Mummy prepared - hinted that was sort of easy, lot of steps though :)
// Fish with Lemon, Tofu with premium soy sauce, grind ginger and chive, 
// japanese rice, fried egg-plant, some see weed leafs and cola extra coffee.
#pragma once


namespace file
{


   
   // Cached presentation hints. Providers must not authenticate, download, or perform remote I/O here.
   struct image_info
   {
      bool m_bFolder = false;
      ::string m_strName;
      // Existing local image only; an empty path requests a generic type icon.
      ::string m_strLocalThumbnailPath;
      ::particle_array m_particleaNotify;
      image_info()
      {


      }
   };

   // Optional capability: querying it must not change the enumerator vtable.
   class CLASS_DECL_ACME image_info_provider : virtual public ::particle
   {
   public:
      ~image_info_provider() override;
      virtual bool get_file_image_info(const ::file::path & path, ::file::image_info & info) = 0;
   };

   class CLASS_DECL_ACME enumerator :
      virtual public ::particle
   {

   public:


      enumerator() {}
      ~enumerator() override {}


   //protected:


   //   //virtual bool _enumerates(::file::listing_base & listing) = 0;


   //   virtual bool _enumerate(listing_base & listing) = 0;


   //public:


      // returns true if it can do and have done enumeration for the 
      // source m_pathUser member in the listing.
      // returns false the enumerator is not a enumerator for the
      // source m_pathUser member in the listing.
      // throws exception if listing enumeration fails for some reason.
      virtual bool enumerate(listing_base & listing);
      // Nonvirtual adapter; older providers need not implement the optional capability.
      bool get_file_image_info(const ::file::path & path, ::file::image_info & info);

      virtual bool list_base(string_array_base & stra, const ::scoped_string & scopedstr, ::file::e_flag eflag = ::file::e_flag_file_or_folder);

      virtual listing_base get_folders(const ::scoped_string & scopedstr);

      virtual ::file::listing_base folders(const ::file::path& path);
      virtual ::file::listing_base files(const ::file::path& path);
      virtual ::file::listing_base folders_and_files(const ::file::path& path);

      //virtual bool enumerate(::file::listing_base & listing, const ::file::path & path, ::file::e_flag eflag = ::file::e_flag_none, enum_depth edepth = e_depth_none);
      //virtual bool enumerate_pattern(::file::listing_base & listing, const ::file::path & path, const ::string_array_base & straPattern, ::file::e_flag eflag = ::file::e_flag_none, enum_depth edepth = e_depth_none);


   };


} // namespace file



