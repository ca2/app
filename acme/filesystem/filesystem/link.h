// Created by camilo on 2023-03-13 23:46 <3ThomasBorregaardSorensen!!
#pragma once


namespace file
{


   class CLASS_DECL_ACME link :
      virtual public ::particle
   {
   public:


      ::file::path         m_path;


      e_link               m_elink;


      ::string             m_strArguments;
      ::file::path         m_pathTarget;
      ::file::path         m_pathFolder;
      ::file::path         m_pathIcon;
      int                  m_iIcon;


      link();
      ~link() override;


      void clear();


      virtual ::pointer < ::file::link > create_clean_new() const;

      virtual void open(const ::file::path & path, ::file::e_link elink = ::file::e_link_all);

      /// @brief write link/shortcut to file
      /// @return flags of items that were successfully set
      virtual ::file::e_link write(const ::file::path & pathWriteAs = "");

      /// @brief patches link path member with find and replace
      /// @param scopedstrSource text to find
      /// @param scopedstrTarget text to replace
      /// @return flags of items that were changed
      virtual ::file::e_link path_find_replace(const ::scoped_string & scopedstrSource, const ::scoped_string & scopedstrTarget);


      virtual ::file::path path_find_replace(const ::file::path & path, const ::scoped_string & scopedstrSource, const ::scoped_string & scopedstrTarget) const;

      virtual ::file::e_link check_link();

   };


} // namespace file



