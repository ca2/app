#pragma once


namespace file
{


   class listing;


   class CLASS_DECL_APEX listing_provider :
      virtual public ::context_object
   {
   public:


      virtual ::file::listing & perform_file_listing(::file::listing & listing) = 0;
      virtual ::file::listing & perform_file_relative_name_listing(::file::listing & listing) = 0;


   };


   struct CLASS_DECL_APEX listing_meta
   {

      listing_provider *   m_pprovider = nullptr;
      bool                 m_bFile = true;
      bool                 m_bDir = true;
      bool                 m_bRecursive = false;
      e_extract            m_eextract = extract_first;
   };


   class CLASS_DECL_APEX listing:
   // recursive fetchings should set a meaningful m_iRelative value at each returned path
      public ::file::patha,
      public listing_meta
   {
   public:

      ::file::path         m_pathUser;
      ::file::path         m_pathFinal;
      string_array              m_straPattern;
      string_array              m_straIgnoreName;
      ::status::result     m_statusresult;
      string_array              m_straTitle;


      listing(listing_provider * pprovider = nullptr);
      listing(const listing & listing):patha(listing) { m_nGrowBy = 128; }
      virtual ~listing();

      bool succeeded() const
      {

         return m_statusresult.succeeded();

      }

      bool failed() const
      {

         return m_statusresult.failed();

      }

      operator bool() const
      {

         return m_statusresult.succeeded();

      }

      bool operator !() const
      {

         return m_statusresult.failed();

      }

      listing & operator = (const ::estatus & estatus) { m_statusresult.set_error(estatus); return *this; }



      index add_child(const ::file::path & path)
      {

         return add(m_pathUser / path);

      }

      ::file::path & add_child_get(const ::file::path & path)
      {

         return add_get(m_pathUser / path);

      }


      listing & ignore(const string & strName)
      {

         m_straIgnoreName.add(strName);

         return *this;

      }


      listing & ls(const ::file::path & path)
      {

         m_pathUser = path;

         return ls();

      }


      listing & ls_file(const ::file::path & path)
      {

         m_pathUser = path;

         m_bDir = false;

         return ls();

      }


      listing & ls_dir(const ::file::path & path)
      {

         m_pathUser = path;

         m_bFile = false;

         return ls();

      }


      listing & rls(const ::file::path & path = nullptr, e_extract eextract = extract_first)
      {

         m_pathUser = path;

         m_bRecursive = true;

         m_eextract = eextract;

         return ls();

      }


      listing & rls_file(const ::file::path & path)
      {

         m_pathUser = path;

         m_bRecursive = true;

         m_bDir = false;

         return ls();

      }


      listing & rls_dir(const ::file::path & path)
      {

         m_pathUser = path;

         m_bRecursive = true;

         m_bFile = false;

         return ls();

      }


      listing & ls_pattern(const ::file::path & path, const string_array & straPattern)
      {

         m_pathUser = path;

         m_straPattern = straPattern;

         return ls();

      }


      listing & ls_pattern_file(const ::file::path & path,const string_array & straPattern)
      {

         m_pathUser = path;

         m_straPattern = straPattern;

         m_bDir = false;

         return ls();

      }


      listing & ls_pattern_dir(const ::file::path & path,const string_array & straPattern)
      {

         m_pathUser = path;

         m_straPattern = straPattern;

         m_bFile = false;

         return ls();

      }


      listing & rls_pattern(const ::file::path & path,const string_array & straPattern)
      {

         m_pathUser = path;

         m_straPattern = straPattern;

         m_bRecursive = true;

         return ls();

      }


      listing & rls_pattern_file(const ::file::path & path,const string_array & straPattern)
      {

         m_pathUser = path;

         m_straPattern = straPattern;

         m_bRecursive = true;

         m_bDir = false;

         return ls();

      }


      listing & rls_pattern_dir(const ::file::path & path,const string_array & straPattern)
      {

         m_pathUser = path;

         m_straPattern = straPattern;

         m_bRecursive = true;

         m_bFile = false;

         return ls();

      }


      virtual listing & ls();

      virtual listing & ls_relative_name();

      void clear_results() { m_straTitle.remove_all(); m_statusresult.clear(); remove_all(); }


      string title(index i)
      {

         if(i >= 0 && i < m_straTitle.get_count())
         {

            return m_straTitle[i];

         }

         return operator[](i).title();

      }

      string name(index i)
      {

         if (i >= 0 && i < m_straTitle.get_count())
         {

            return m_straTitle[i];

         }

         return operator[](i).name();

      }


      void to_name()
      {

         for(index i = 0; i < get_size(); i++)
         {

            element_at(i) = element_at(i).name();

         }

      }

      listing & operator = (const listing & listing)
      {

         if(this == &listing)
            return *this;

         patha::operator         = (listing);
         *((listing_meta*)this)  = (const listing_meta &) listing;
         m_pathUser              = listing.m_pathUser;
         m_pathFinal             = listing.m_pathFinal;
         m_straPattern           = listing.m_straPattern;
         m_straIgnoreName        = listing.m_straIgnoreName;
         m_statusresult          = listing.m_statusresult;
         m_straTitle             = listing.m_straTitle;

         return *this;

      }

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
         string t = i < m_straTitle.get_count() ? m_straTitle[ i] : "";
         remove_at(i);
         insert_at(iIndex,pcsz);

         return true;
      }


      bool preferred_name(const path & pcsz)

      {
         return name_move_ci(pcsz,0);

      }


      ::count preferred_name(patha  & stra)
      {
         ::count count = 0;
         for(index i = stra.get_upper_bound(); i >= 0; i--)
         {
            if(preferred_name(stra[ i]))
               count++;
         }
         return count;
      }



   };

   class CLASS_DECL_APEX relative_name_listing :
      virtual public listing
   {
   public:


      relative_name_listing(listing_provider * pprovider = nullptr);
      relative_name_listing(const relative_name_listing & listing) { operator = (listing); }
      virtual ~relative_name_listing();


      using listing::ls;
      virtual listing & ls() override;

   };



} // namespace file




CLASS_DECL_APEX string normalize_wildcard_criteria(const string & strPattern);


CLASS_DECL_APEX bool matches_wildcard_criteria(const string_array & straCriteria, const string & strValue);
CLASS_DECL_APEX bool matches_wildcard_criteria_ci(const string_array & straCriteria, const string & strValue);


