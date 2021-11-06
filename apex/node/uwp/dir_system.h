#pragma once


namespace universal_windows
{


   class CLASS_DECL_APEX dir_system :
      virtual public ::dir_system
   {
   public:


      ::file::path         m_strCa2;
      ::file::path         m_strTimeFolder;
      ::file::path         m_strNetSeedFolder;


      dir_system();
      virtual ~dir_system();



      virtual ::e_status initialize(::object * pobject) override;


      virtual bool update_module_path() override;



   };


} // namespace universal_windows





