#pragma once


namespace file
{


   class CLASS_DECL_APEX set :
      virtual public ::object
   {
   public:


      __pointer(::file::patha)      m_ppathaSearch;
      __pointer(bool_array)         m_pbaRecursive;
      string_array                  m_straFilter;
      ::file::listing               m_listing;
      ::file::listing               m_listingAddUp;


      set();
      virtual ~set();


      // reference
      virtual void add_search(const ::file::path & pathSearchFolder, bool bRecursive);
      virtual void add_search(const ::file::patha & pathaSearchFolder, const bool_array & baRecursive);
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

      virtual string get_next_file(const char * psz);


      virtual bool initialize_os_wallpaper(bool bAddSearch);


   };


   typedef ___pointer < set > set_pointer;


} // namespace file





