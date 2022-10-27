


namespace ios
{


   namespace axis
   {


      dir::dir(::aura::application *   papp) :
         ::object(pparticle),
         ::file::system_dir(pparticle),
         ::file::dir::axis::system(pparticle),
         ::ios::dir(pparticle),
         ::file_watcher::file_watcher(pparticle)
      {

//      string strCa2Module = ca2module();
//
//      m_strCa2 = strCa2Module;
//
//      pcontext->m_papexcontext->file().path().eat_end_level(m_strCa2, 2, "/");

      }


      ::file::listing & dir::ls(::particle * pparticle, ::file::listing & listing)
      {


         if(::file::dir::axis::system::ls(papp, listing))
         {

            return listing;

         }

         return ::ios::dir::ls(papp,listing);

      }


      bool dir::initialize()
      {

         if(!::ios::dir::initialize())
            return false;

         return true;

      }


      bool          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->is(const ::file::path & lpcszPath, ::aura::application * papp)
      {

         if(::iospacmedir->is(lpcszPath,papp))
            return true;

         if(::file::dir::axis::system::is(lpcszPath, papp))
            return true;

         return false;

      }

      //   bool          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->is(const ::string & strPath, ::aura::application * papp)
      //   {
      //
      //      if(::linuxpacmedir->is(strPath,papp))
      //         return true;
      //
      //      if(::file::dir::axis::system::is(strPath,papp))
      //         return true;
      //
      //      return false;
      //
      //   }

      bool dir::name_is(const ::file::path & str, ::aura::application * papp)
      {
         //output_debug_string(str);
         strsize iLast = str.get_length() - 1;
         while(iLast >= 0)
         {
            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
               break;
            iLast--;
         }
         while(iLast >= 0)
         {
            if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
               break;
            iLast--;
         }
         if(iLast >= 0)
         {
            while(iLast >= 0)
            {
               if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
               {
                  iLast++;
                  break;
               }
               iLast--;
            }
         }
         else
         {
            return true; // assume empty string is root_ones directory
         }

         if(thread_set(e_task_flag_compress_is_dir) && iLast >= 3 && !ansi_count_compare_ci(&((const ::string &)str)[iLast - 3],".zip",4))
         {

            return true;

         }

         strsize iFind = ::str().find_ci(".zip:", str);

         if(thread_set(e_task_flag_compress_is_dir) && iFind >= 0 && iFind < iLast)
         {

            bool bHasSubFolder = m_pziputil->has_sub_folder(papp, str);

            return bHasSubFolder;

         }

         bool bIsDir =          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->is(str.Left(iLast));

         return bIsDir;

      }


   } // namespace axis

} // namespace ios
