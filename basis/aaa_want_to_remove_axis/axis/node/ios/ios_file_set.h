#pragma once


namespace ios
{
   
   
   class CLASS_DECL_AXIS file_set :
      virtual public ::file::set
   {
   public:
      
      
      string_array           m_straSearch;
      bool_array        m_baRecursive;
      string_array           m_straFilter;
      ::file::listing   m_straFile;
      
      
      file_set(::layered * pobjectContext);
      virtual ~file_set();
      
      
      virtual void add_search(string_array & stra, bool_array & baRecursive);
      virtual void add_filter(string_array & stra);
      virtual ::count get_file_count();
      virtual void file_at(::index i, string & str);
      virtual ::index find_first_file(const char * lpcszFilePath, ::index iStart = 0);
      virtual void clear_search();
      virtual void clear_filter();
      virtual void clear_file();
      virtual void refresh();
      
      
   };
   
   
} // namespace ios


