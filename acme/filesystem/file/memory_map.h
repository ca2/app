#pragma once



namespace file
{


   class CLASS_DECL_ACME memory_map :
      virtual public generic
   {
   public:

      string                     m_strName;
      void *                     m_pdata;
#ifdef WINDOWS
      HANDLE                     m_hfile;
      HANDLE                     m_hfilemap;
#else
      int                        m_iFile;
#endif
      bool                       m_bRead;
      bool                       m_bWrite;
      bool                       m_bCreate;
      memsize                    m_size;
      __pointer(::mutex)         m_pmutex;


      memory_map();
      memory_map(const char * psz, bool bRead, bool bWrite, bool bCreate, memsize size);
      virtual ~memory_map();


      void construct();

      bool open();
      bool open(const char * psz, bool bRead, bool bWrite, bool bCreate, memsize size);
      bool close();

      void * get_data();

      bool is_mapped();

      inline string get_name();
      string get_path();

   };




   inline string memory_map::get_name()
   {

      return m_strName;

   }


   inline void * memory_map::get_data()
   {

      return m_pdata;

   }


} // namespace file
