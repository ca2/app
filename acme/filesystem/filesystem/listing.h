#pragma once


namespace file
{


   class listing;


   struct CLASS_DECL_ACME LISTING
   {


      enumerator *         m_penumerator = nullptr;
      bool                 m_bFile = true;
      bool                 m_bDir = true;
      bool                 m_bRecursive = false;
      e_extract            m_eextract = extract_first;


   };


   class CLASS_DECL_ACME listing:
   // recursive fetchings should set a meaningful m_iRelative value at each returned path
      public ::file::path_array,
      public LISTING
   {
   protected:

      
      using ::file::path_array::add;


   public:

      
      ::file::path            m_pathUser;
      ::file::path            m_pathFinal;
      ::file::path            m_pathBasePath;
      ::file::e_flag          m_eflag;
      ::enum_depth            m_edepth;
      string_array            m_straPattern;
      string_array            m_straIgnoreName;
      string_array            m_straTitle;


      listing();
      listing(const listing & listing);
      ~listing() override;



      inline void fix_flag()
      {

         fix_file_listing_flag(m_eflag);

      }


      virtual bool on_start_enumerating(::file::enumerator * penumerator);

      
      //bool succeeded() const
      //{

      //   return m_estatus.succeeded();

      //}

      //bool failed() const
      //{

      //   return m_estatus.failed();

      //}

      //operator bool() const
      //{

      //   return m_estatus.succeeded();

      //}

      //bool operator !() const
      //{

      //   return m_estatus.failed();

      //}

      //listing & operator = (const ::e_status & estatus) { m_estatus.set_error(estatus); return *this; }


      //listing& operator = (const ::e_status & estatus) { return *this; }
      template < container_type CONTAINER >
      inline ::index add_listing(const CONTAINER & container)
      {

         return ::file::path_array::add(container);

      }


      void operator()(const ::file::path& path)
      {

         m_pathUser = path;
         m_pathFinal = path;

      }


      index add_child(const ::file::path & path)
      {

         return add(m_pathUser / path);

      }

      ::file::path & add_child_get(const ::file::path & path)
      {

         return add_get(m_pathUser / path);

      }


      listing & ignore(const ::string & strName)
      {

         m_straIgnoreName.add(strName);

         return *this;

      }


      //void clear_results() { m_straTitle.erase_all(); m_estatus.clear(); erase_all(); }
      void clear_results() { m_straTitle.erase_all(); erase_all(); }


      string title(index i);


      string name(index i);


      void to_name();


      listing & operator = (const listing & listing);


      index name_find_first_ci(const path & pcsz,index find = 0,index last = -1) const

      {
         if(find < 0)
            find += this->get_count();
         if(last < 0)
            last += this->get_count();
         for(; find <= last; find++)
         {
            if(ansi_icmp(this->element_at(find).name(), pcsz) == 0)

               return find;
         }
         return -1;
      }

      bool name_move_ci(const path & pcsz,index iIndex)

      {
         index i = name_find_first_ci(pcsz);

         if(i < 0)
            return false;
         path point = element_at(i);
         
         string t;
         
         if (i < m_straTitle.get_count())
         {
         
            t = m_straTitle[i];

         }

         erase_at(i);
         insert_at(iIndex,pcsz);

         return true;
      }


      bool preferred_name(const path & pcsz)

      {
         return name_move_ci(pcsz,0);

      }


      ::count preferred_name(path_array & stra)
      {
         ::count count = 0;
         for(index i = stra.get_upper_bound(); i >= 0; i--)
         {
            if(preferred_name(stra[ i]))
               count++;
         }
         return count;
      }


      void defer_add(::file::path & path);


      void set_listing(const ::file::path & path, enum_depth edepth = e_depth_none, ::file::e_flag eflag = ::file::e_flag_none)
      {

         m_penumerator = nullptr;

         m_pathUser = path;

         m_eflag = eflag;

         m_edepth = edepth;

      }


      void set_folder_listing(const ::file::path & path, enum_depth edepth = e_depth_none)
      {

         set_listing(path, edepth, ::file::e_flag_folder);

      }


      void set_file_listing(const ::file::path & path, enum_depth edepth = e_depth_none)
      {

         set_listing(path, edepth, ::file::e_flag_file);

      }


      void set_pattern_listing(const ::file::path & path, const ::string_array & straPattern, enum_depth edepth = e_depth_none, ::file::e_flag eflag = ::file::e_flag_none)
      {

         m_straPattern = straPattern;

         set_listing(path, edepth, eflag);

      }


      void set_pattern_folder_listing(const ::file::path & path, const ::string_array & straPattern, enum_depth edepth = e_depth_none)
      {

         set_pattern_listing(path, straPattern, edepth, ::file::e_flag_folder);

      }


      void set_pattern_file_listing(const ::file::path & path, const ::string_array & straPattern, enum_depth edepth = e_depth_none)
      {

         set_pattern_listing(path, straPattern, edepth, ::file::e_flag_file);

      }


   };


   class CLASS_DECL_ACME relative_name_listing :
      virtual public listing
   {
   public:


      relative_name_listing();
      relative_name_listing(const relative_name_listing & listing);
      virtual ~relative_name_listing();

     
   };


} // namespace file




CLASS_DECL_ACME string normalize_wildcard_criteria(const ::string & strPattern);


CLASS_DECL_ACME bool matches_wildcard_criteria(const string_array & straCriteria, const ::string & strValue);
CLASS_DECL_ACME bool matches_wildcard_criteria_ci(const string_array & straCriteria, const ::string & strValue);


