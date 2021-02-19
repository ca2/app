//
// Created by camilo on 13/02/2021.
//
#pragma once


namespace posix
{


   class CLASS_DECL_ACME file_memory_map :
      virtual public ::file::memory_map
   {
   public:


      int                        m_iFile;


      file_memory_map();
      virtual ~file_memory_map();


      virtual bool open() override;
      virtual bool close() override;

      virtual bool is_mapped() override;


      virtual string calculate_path_from_name(const string & strName) override;


   };


} // namespace posix



