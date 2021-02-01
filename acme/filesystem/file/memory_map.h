#pragma once



namespace file
{


   class CLASS_DECL_ACME memory_map :
      virtual public matter
   {
   public:


      string                     m_strName;
      void *                     m_pdata;
      bool                       m_bRead;
      bool                       m_bWrite;
      bool                       m_bCreate;
      memsize                    m_size;


      memory_map();
      virtual ~memory_map();

      

      virtual bool open();
      virtual bool open(const char * psz, bool bRead, bool bWrite, bool bCreate, memsize size);
      virtual bool close();

      virtual void * get_data();

      virtual bool is_mapped();

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
