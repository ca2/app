#pragma once


////#include "acme/primitive/primitive/object.h"
#include "acme/primitive/collection/bool_array.h"
//#include "acme/primitive/collection/string_array.h"
#include "acme/filesystem/filesystem/listing.h"


namespace file
{


   class CLASS_DECL_APEX set :
      virtual public ::object
   {
   public:


      ::pointer<::file::path_array>    m_ppathaSearch;
      ::pointer<bool_array>            m_pbaRecursive;
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
      virtual ::count get_file_count();
      virtual void file_at(::index i, string & str);
      virtual ::index find_first_file(const char * pcszFilePath, ::index iStart = 0);

      virtual void clear_file();
      virtual void clear_search();
      virtual void clear_filter();
      virtual void refresh();

      // derived
      virtual bool get_next_file(const char * pcszCurrentFilePath, string & wstrNextFilePath);

      virtual string get_next_file(const scoped_string & str);


      virtual void initialize_os_wallpaper(bool bAddSearch);


   };


   typedef ::pointer<set>set_pointer;


} // namespace file





