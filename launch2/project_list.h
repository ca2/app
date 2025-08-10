// Created by camilo on 2023-03-10 09:09 BRT <3ThomasBorregaardSørensen!!
#pragma once


namespace application_build_helper
{


   class project_list :
      virtual public ::particle
   {
   public:


      ::pointer < application >     m_papplication;
      ::string_array_base                m_straLines;

      
      project_list();
      ~project_list() override;


      void create(application* papplication);


      bool do_base(const ::scoped_string& strProjectId);
      bool do_root(const ::file::path& pathFolder);



   };


} // namespace application_build_helper



