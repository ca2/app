#pragma once


namespace windows
{


   class CLASS_DECL_ACME file_memory_map :
      virtual public ::file::memory_map
   {
   public:


      HANDLE                     m_hfile;
      HANDLE                     m_hfilemap;


      file_memory_map();
      virtual ~file_memory_map();


      bool open();
      bool close();

      bool is_mapped();

      virtual string calculate_path_from_name(const string & strName) override;

   };


} // namespace file



