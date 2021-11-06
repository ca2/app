#pragma once


namespace file
{


   class CLASS_DECL_ACME memory_map :
      virtual public matter
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
      virtual bool open_name(const char * pszName, bool bRead, bool bWrite, bool bCreate, memsize size);
      virtual bool open_path(const char * pszPath, bool bRead, bool bWrite, bool bCreate, memsize size);
      virtual bool open(const char * pszName, const char * pszPath, bool bRead, bool bWrite, bool bCreate, memsize size);
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



