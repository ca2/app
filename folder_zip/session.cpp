#include "framework.h"
#include "session.h"
#include "file_function_definitions.h"
#include <algorithm>


namespace folder_zip
{


   session::~session()
   {

      close();

   }


   bool session::bind(memory_base * pmemory)
   {

      close();

      if (!pmemory)
      {

         return false;

      }

      ::pointer < memory_file > pfile(allocate_t{}, pmemory);

      auto unzipfile = unzip_Open2("pad", (zlib_filefunc_def *) &g_filefunctiondefinitions, pfile.m_p);

      if (!unzipfile)
      {

         return false;

      }

      m_pmemory = pmemory;
      m_pfile = pfile;
      m_unzipfile = unzipfile;

      return true;

   }


   bool session::reset()
   {

      if (!m_unzipfile)
      {

         return false;

      }

      if (m_bCurrentFileOpen)
      {

         auto iClose = unzip_CloseCurrentFile(m_unzipfile);

         m_bCurrentFileOpen = false;

         if (iClose != UNZ_OK)
         {

            return false;

         }

      }

      return unzip_GoToFirstFile(m_unzipfile) == UNZ_OK;

   }


   void session::close()
   {

      if (m_unzipfile)
      {

         unzip_Close(m_unzipfile);
         m_unzipfile = nullptr;

      }

      m_bCurrentFileOpen = false;
      m_pfile.release();
      m_pmemory.release();

   }


   session_lease::~session_lease()
   {

      return_to_pool();

   }


   unzip_File session_lease::unzip_file() const
   {

      return m_psession ? m_psession->m_unzipfile : nullptr;

   }


   unzip__file_info & session_lease::file_info()
   {

      if (!m_psession)
      {

         throw ::exception(error_wrong_state);

      }

      return m_psession->m_fileinfo;

   }


   bool session_lease::open_current_file()
   {

      if (!m_psession || !m_psession->m_unzipfile)
      {

         return false;

      }

      if (m_psession->m_bCurrentFileOpen)
      {

         close_current_file();

      }

      if (unzip_OpenCurrentFile(m_psession->m_unzipfile) != UNZ_OK)
      {

         return false;

      }

      m_psession->m_bCurrentFileOpen = true;

      return true;

   }


   void session_lease::close_current_file()
   {

      if (m_psession && m_psession->m_unzipfile && m_psession->m_bCurrentFileOpen)
      {

         unzip_CloseCurrentFile(m_psession->m_unzipfile);
         m_psession->m_bCurrentFileOpen = false;

      }

   }


   void session_lease::return_to_pool()
   {

      auto ppool = m_ppool;
      auto psession = m_psession;

      m_ppool = nullptr;
      m_psession = nullptr;

      if (ppool && psession)
      {

         ppool->return_to_pool(psession);

      }

   }


   ::pointer < session_lease > session_pool::lease_session_while_locked(::folder_zip::session * psession)
   {

      ::pointer < session_lease > please(allocate_t{});

      psession->m_bInUse = true;
      m_countActive++;

      please->m_ppool = this;
      please->m_psession = psession;

      return please;

   }


   ::pointer < session_lease > session_pool::acquire(memory_base * pmemory)
   {

      if (!pmemory)
      {

         throw ::exception(error_bad_argument);

      }

      ::std::unique_lock lock(m_mutex);

      for (;;)
      {

         trim_idle_sessions_while_locked();

         for (auto & psession : m_sessiona)
         {

            if (!psession->m_bInUse && psession->m_pmemory.m_p == pmemory)
            {

               return lease_session_while_locked(psession);

            }

         }

         if ((::collection::count) m_sessiona.size() < m_countDesiredMaximum)
         {

            ::pointer < session > psession(allocate_t{});

            if (!psession->bind(pmemory))
            {

               throw ::exception(error_failed);

            }

            m_sessiona.push_back(psession);

            return lease_session_while_locked(psession);

         }

         for (auto & psession : m_sessiona)
         {

            if (!psession->m_bInUse)
            {

               if (!psession->bind(pmemory))
               {

                  throw ::exception(error_failed);

               }

               return lease_session_while_locked(psession);

            }

         }

         m_condition.wait(lock);

      }

   }


   void session_pool::return_to_pool(::folder_zip::session * psession)
   {

      ::std::unique_lock lock(m_mutex);

      if (!psession || !psession->m_bInUse)
      {

         return;

      }

      auto bReusable = psession->reset();

      psession->m_bInUse = false;
      m_countActive--;

      if (!bReusable)
      {

         auto iterator = ::std::find_if(m_sessiona.begin(), m_sessiona.end(),
            [psession](const auto & pitem) { return pitem.m_p == psession; });

         if (iterator != m_sessiona.end())
         {

            m_sessiona.erase(iterator);

         }

      }

      trim_idle_sessions_while_locked();

      lock.unlock();
      m_condition.notify_one();

   }


   void session_pool::reconcile(::collection::count maximum)
   {

      maximum = ::maximum((::collection::count) 1, maximum);

      ::std::unique_lock lock(m_mutex);

      auto bIncreased = maximum > m_countDesiredMaximum;

      m_countDesiredMaximum = maximum;

      trim_idle_sessions_while_locked();

      lock.unlock();

      if (bIncreased)
      {

         m_condition.notify_all();

      }

   }


   void session_pool::trim_idle_sessions_while_locked()
   {

      for (auto iterator = m_sessiona.end();
         iterator != m_sessiona.begin() && (::collection::count) m_sessiona.size() > m_countDesiredMaximum;)
      {

         --iterator;

         if (!(*iterator)->m_bInUse)
         {

            iterator = m_sessiona.erase(iterator);

         }

      }

   }


   ::collection::count session_pool::session_count()
   {

      ::std::scoped_lock lock(m_mutex);

      return (::collection::count) m_sessiona.size();

   }


   ::collection::count session_pool::active_count()
   {

      ::std::scoped_lock lock(m_mutex);

      return m_countActive;

   }


   session_pool & global_session_pool()
   {

      static auto s_ppool = new session_pool;

      return *s_ppool;

   }


} // namespace folder_zip
