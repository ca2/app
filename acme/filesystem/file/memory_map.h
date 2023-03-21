#pragma once


// #include "acme/primitive/string/string.h"
#include "acme/primitive/primitive/particle.h"


namespace file
{


   class CLASS_DECL_ACME memory_map :
      virtual public particle
   {
   public:


      string                     m_strName;
      string                     m_strPath;
      void *                     m_pdata;
      bool                       m_bRead;
      bool                       m_bWrite;
      bool                       m_bCreate;
      memsize                    m_size;


      memory_map();
      virtual ~memory_map();

      

      virtual bool open();
      virtual bool open_name(const ::scoped_string & scopedstrName, bool bRead, bool bWrite, bool bCreate, memsize size = -1);
      virtual bool open_path(const ::file::path & path, bool bRead, bool bWrite, bool bCreate, memsize size = -1);
      virtual bool open(const ::scoped_string & scopedstrName, const ::file::path & path, bool bRead, bool bWrite, bool bCreate, memsize size = -1);
      virtual bool close();

      virtual void * get_data();

      virtual bool is_mapped();

      virtual string get_path();

      virtual string calculate_path_from_name(const ::string & strName);


   };


   inline void * memory_map::get_data()
   {

      return m_pdata;

   }


} // namespace file



