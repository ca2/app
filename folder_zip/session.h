#pragma once


#include "unzip.h"
#include "acme/filesystem/file/memory_file.h"
#include <condition_variable>
#include <mutex>
#include <vector>


namespace folder_zip
{


   class CLASS_DECL_FOLDER_ZIP session :
      virtual public ::particle
   {
   public:


      ::pointer < memory_base >  m_pmemory;
      ::pointer < memory_file >  m_pfile;
      unzip_File                 m_unzipfile = nullptr;
      unzip__file_info           m_fileinfo{};
      bool                       m_bCurrentFileOpen = false;
      bool                       m_bInUse = false;


      ~session();


      bool bind(memory_base * pmemory);
      bool reset();
      void close();


   };


   class session_pool;


   class CLASS_DECL_FOLDER_ZIP session_lease :
      virtual public ::particle
   {
   public:


      session_pool * m_ppool = nullptr;
      ::folder_zip::session * m_psession = nullptr;


      ~session_lease() override;


      unzip_File unzip_file() const;
      unzip__file_info & file_info();
      bool open_current_file();
      void close_current_file();
      void return_to_pool();


   };


   class CLASS_DECL_FOLDER_ZIP session_pool
   {
   public:


      ::std::mutex                 m_mutex;
      ::std::condition_variable    m_condition;
      ::std::vector < ::pointer < session > > m_sessiona;
      ::collection::count          m_countActive = 0;
      ::collection::count          m_countDesiredMaximum = 8;


      ::pointer < session_lease > acquire(memory_base * pmemory);
      void return_to_pool(::folder_zip::session * psession);
      void reconcile(::collection::count maximum);
      ::collection::count session_count();
      ::collection::count active_count();


   protected:


      void trim_idle_sessions_while_locked();
      ::pointer < session_lease > lease_session_while_locked(::folder_zip::session * psession);


   };


   CLASS_DECL_FOLDER_ZIP session_pool & global_session_pool();


} // namespace folder_zip
