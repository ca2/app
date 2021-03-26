


namespace ios
{


   namespace axis
   {


      dir::dir(::aura::application *   papp) :
         ::object(pobject),
         ::file::system_dir(pobject),
         ::file::dir::axis::system(pobject),
         ::ios::dir(pobject),
         ::file_watcher::file_watcher(pobject)
      {

//      string strCa2Module = ca2module();
//
//      m_strCa2 = strCa2Module;
//
//      pcontext->m_pcontext->file().path().eat_end_level(m_strCa2, 2, "/");

      }


      ::file::listing & dir::ls(::object * pobject, ::file::listing & listing)
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


      bool dir::is(const ::file::path & lpcszPath, ::aura::application * papp)
      {

         if(::ios::dir::is(lpcszPath,papp))
            return true;

         if(::file::dir::axis::system::is(lpcszPath, papp))
            return true;

         return false;

      }

      //   bool dir::is(const string & strPath, ::aura::application * papp)
      //   {
      //
      //      if(::linux::dir::is(strPath,papp))
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

         if(thread_set(id_thread_zip_is_dir) && iLast >= 3 && !ansi_count_compare_ci(&((const char *)str)[iLast - 3],".zip",4))
         {

            return true;

         }

         strsize iFind = ::str::find_ci(".zip:", str);

         if(thread_set(id_thread_zip_is_dir) && iFind >= 0 && iFind < iLast)
         {

            bool bHasSubFolder = m_pziputil->has_sub_folder(papp, str);

            return bHasSubFolder;

         }

         bool bIsDir = ::dir::is(str.Left(iLast));

         return bIsDir;

      }


   } // namespace axis

} // namespace ios
