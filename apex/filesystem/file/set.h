#pragma once


////#include "acme/prototype/prototype/object.h"
#include "acme/prototype/collection/bool_array.h"
//#include "acme/prototype/collection/string_array.h"
#include "acme/filesystem/filesystem/listing.h"


namespace file
{


   class CLASS_DECL_APEX set :
      virtual public ::object
   {
   public:


      ::pointer< ::file::path_array >  m_ppathaSearch;
      ::pointer< bool_array >          m_pbaRecursive;
      string_array                     m_straFilter;
      ::file::listing                  m_listing;
      ::file::listing                  m_listingAddUp;


      set();
      ~set() override;


      void on_initialize_particle() override;


      // reference
      virtual void add_search(const ::file::path & pathSearchFolder, bool bRecursive);
      virtual void add_search(const ::file::path_array & pathaSearchFolder, const bool_array & baRecursive);
      virtual void add_filter(string_array & stra);
      virtual ::collection::count get_file_count();
      virtual void file_at(::collection::index i, string & str);
      virtual ::collection::index find_first_file(const ::scoped_string & scopedstrFilePath, ::collection::index iStart = 0);

      virtual void clear_file();
      virtual void clear_search();
      virtual void clear_filter();
      virtual void refresh();

      // derived
      virtual bool get_next_file(const ::scoped_string & scopedstrCurrentFilePath, string & wstrNextFilePath);

      virtual string get_next_file(const ::scoped_string & scopedstr);


      virtual void initialize_os_wallpaper(bool bAddSearch);


   };


   typedef ::pointer<set>set_pointer;


} // namespace file





