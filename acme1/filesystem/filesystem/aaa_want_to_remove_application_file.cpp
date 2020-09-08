#include "framework.h"
//#include "acme/net/sockets/_.h"


namespace file
{


   application_file::application_file()
   {

   }


   application_file::~application_file()
   {

   }


   ::status::result application_file::copy(var varTarget, var varSource, bool bFailIfExists, e_extract eextract)
   {

      return get_context_application()->get_context_system()->m_spfile->copy(varTarget, varSource, bFailIfExists, eextract, get_context_application());

   }


   ::status::result application_file::move(const ::file::path & pszNew,const ::file::path & pszOld)
   {

      return get_context_application()->get_context_system()->m_spfile->move(pszNew,pszOld,get_context_application());

   }


   ::status::result application_file::del(const ::file::path & psz)
   {
      return get_context_application()->get_context_system()->m_spfile->del(psz,get_context_application());
   }

   ::status::result application_file::rename(const ::file::path & pszNew,const ::file::path & pszOld)
   {
      return get_context_application()->get_context_system()->m_spfile->rename(pszNew,pszOld,get_context_application());
   }

   void application_file::trash_that_is_not_trash(const ::file::path & psz)
   {
      return get_context_application()->get_context_system()->m_spfile->trash_that_is_not_trash(psz, get_context_application());
   }

   void application_file::trash_that_is_not_trash(::file::patha & stra)
   {
      return get_context_application()->get_context_system()->m_spfile->trash_that_is_not_trash(stra, get_context_application());
   }

   ::status::result application_file::replace(const ::file::path & pszContext,const string & pszFind,const string & pszReplace)
   {
      return get_context_application()->get_context_system()->m_spfile->replace(pszContext, pszFind, pszReplace, get_context_application());
   }


   bool application_file::exists(const ::file::path & pszPath)
   {

      return get_context_application()->get_context_system()->m_spfile->exists(pszPath, get_context_application());

   }


   bool application_file::is_file_or_dir(const ::file::path & pszPath, e_type * petype)
   {

      return get_context_application()->get_context_system()->m_spfile->is_file_or_dir(pszPath, nullptr, petype, get_context_application());

   }


   /*  bool application_file::exists(const string & strPath)
     {

        return get_context_application()->get_context_system()->m_spfile->exists(strPath, get_context_application());

     }

     bool application_file::exists(const var & var)
     {

        const string & strPath = var.get_string();


        return get_context_application()->get_context_system()->m_spfile->exists(strPath, get_context_application());

     }*/


   var application_file::length(const ::file::path & pszPath)
   {

      return get_context_application()->get_context_system()->m_spfile->length(pszPath, get_context_application());

   }


   //var application_file::length(const string & strPath)
   //{


   //   return get_context_application()->get_context_system()->m_spfile->length(strPath, get_context_application());

   //}


   //var application_file::length(const var & var)
   //{

   //   return get_context_application()->get_context_system()->m_spfile->length(var.get_string(), get_context_application());

   //}


   ::file::path application_file::time(const ::file::path & pszBasePath,i32 iDepth,const string & pszPrefix,const string & pszSuffix)
   {

      return get_context_application()->get_context_system()->m_spfile->time(get_context_application(), pszBasePath, iDepth, pszPrefix, pszSuffix);

   }


   ::file::path application_file::time_square(const string & pszPrefix,const string & pszSuffix)
   {

      return get_context_application()->get_context_system()->m_spfile->time_square(get_context_application(), pszPrefix, pszSuffix);

   }

   ::file::path application_file::time_log(const string & pszId)
   {
      return get_context_application()->get_context_system()->m_spfile->time_log(get_context_application(), pszId);
   }

   file_pointer application_file::time_square_file(const char * pszPrefix, const char * pszSuffix)
   {
      return get_context_application()->get_context_system()->m_spfile->time_square_file(get_context_application(), pszPrefix, pszSuffix);
   }


   file_pointer application_file::get(const ::file::path & name)
   {

      return get_context_application()->get_context_system()->m_spfile->get(name, get_context_application());

   }


   var application_file::as_json(const var & varFile)
   {

      return get_context_application()->get_context_system()->m_spfile->as_json(get_context_application(), varFile);

   }


   string application_file::as_string(const var & varFile)
   {

      return get_context_application()->get_context_system()->m_spfile->as_string(get_context_application(), varFile);

   }


   bool application_file::as_memory(const var & varFile, memory_base & mem)
   {

      return get_context_application()->get_context_system()->m_spfile->as_memory(get_context_application(), varFile, mem);

   }


   void application_file::lines(string_array & stra, const var & varFile)
   {

      return get_context_application()->get_context_system()->m_spfile->lines(stra, varFile, get_context_application());

   }


   void application_file::put_lines(const var & varFile, const string_array & stra)
   {
      return get_context_application()->get_context_system()->m_spfile->put_lines(varFile, stra, get_context_application());
   }

   bool application_file::put_contents(const var & varFile, const void * pvoidContents, ::count count)
   {
      return get_context_application()->get_context_system()->m_spfile->put_contents(varFile, pvoidContents, count, get_context_application());
   }

   bool application_file::put_contents(const var & varFile, const char * pcszContents)

   {
      return get_context_application()->get_context_system()->m_spfile->put_contents(varFile, pcszContents, get_context_application());

   }


   bool application_file::add_contents(const var & varFile,const char * pcszContents)
   {

      return get_context_application()->get_context_system()->m_spfile->add_contents(varFile,pcszContents,get_context_application());

   }

   
   //bool application_file::put_contents(const var & varFile, const ::stream & stream)
   //{

   //   return get_context_application()->get_context_system()->m_spfile->put_contents(varFile, stream, get_context_application());

   //}


   bool application_file::put_contents(const var & varFile, memory & mem)
   {

      return get_context_application()->get_context_system()->m_spfile->put_contents(varFile, mem, get_context_application());

   }


   bool application_file::put_contents_utf8(const var & varFile, const char * pcszContents)
   {

      return get_context_application()->get_context_system()->m_spfile->put_contents_utf8(varFile, pcszContents, get_context_application());

   }


   string application_file::sys_temp(const char * lpszName, const char * pszExtension)
   {
      return get_context_application()->get_context_system()->m_spfile->sys_temp(lpszName, pszExtension, get_context_application());
   }


   rp(::file::file) application_file::friendly_get_file(const var & varFile, UINT nOpenFlags)
   {

      try
      {

         return get_file(varFile, nOpenFlags);

      }
      catch (const ::exception_pointer & pe)
      {

         return pe;

      }
      catch(...)
      {

         return ::error_failed;

      }

   }


   ::file_result application_file::get_file(const var & varFile, UINT nOpenFlags)
   {

      return Context.file().get_file(get_context_application(), varFile, nOpenFlags);

   }



   void application_file::dtf(const ::file::path & pszFile,const ::file::path & pszDir)
   {

      return get_context_application()->get_context_system()->m_spfile->dtf(pszFile,pszDir,get_context_application());

   }

   bool application_file::is_read_only(const path & psz)
   {

      return get_context_application()->get_context_system()->m_spfile->is_read_only(psz, get_context_application());
   }


   void application_file::dtf(const ::file::path & pszFile,::file::patha & stra,::file::patha & straRelative)
   {

      return get_context_application()->get_context_system()->m_spfile->dtf(pszFile,stra,get_context_application());

   }


   void application_file::ftd(const ::file::path & pszDir,const ::file::path & pszFile)
   {

      return get_context_application()->get_context_system()->m_spfile->ftd(pszDir,pszFile,get_context_application());

   }


   bool application_file::crypto_set(const var & varFile,const char * pszData,const char * pszSalt)
   {

      __throw(interface_only_exception());

      return false;

   }


   bool application_file::crypto_get(const var & varFile,string & str,const char * pszSalt)
   {

      __throw(interface_only_exception());

      return false;

   }



   bool application_file::save_lines(const var & varFile,string_array & stra)
   {

      string str = stra.implode("\n");

      put_contents_utf8(varFile, str);

      return true;

   }


   bool application_file::load_lines(string_array & stra,const var & varFile)
   {

      string str = as_string(varFile);

      stra.add_lines(str);

      return true;

   }


   //bool application_file::transfer(const path & pathOut, const path & pszSource)

   //{

   //   return Context.file().transfer(get_context_application(), pathOut, pszSource);


   //}


   //bool application_file::transfer(const path & pathOut, ::file::file * pfileIn)
   //{

   //   return Context.file().transfer(get_context_application(), pathOut, pfileIn);

   //}


   //bool application_file::transfer(const path & pathOut, ::file::file & reader)
   //{

   //   return Context.file().transfer(get_context_application(), pathOut, reader);

   //}


   bool application_file::transfer(::file::file * pfileOut, ::file::file * pfileIn)
   {

       return Context.file().transfer(get_context_application(), pfileOut, pfileIn);

   }


   //bool application_file::transfer(file * pfileOut, ::file::file * pfileIn)
   //{

   //   return Context.file().transfer(get_context_application(), pfileOut, pfileIn);

   //}


   //bool application_file::transfer(file * pfileOut, ::file::file & is)
   //{

   //   return Context.file().transfer(get_context_application(), *pfileOut, is);

   //}


   //bool application_file::transfer(::file::file & os, const path & pszSource)
   //{

   //   return Context.file().transfer(get_context_application(), os, pszSource);

   //}


   //bool application_file::transfer(::file::file & os, ::file::file * pfileIn)
   //{

   //   return Context.file().transfer(get_context_application(), os, pfileIn);

   //}


   //bool application_file::transfer(::file::file & os, ::file::file & is)
   //{

   //   return Context.file().transfer(get_context_application(), os, is);

   //}


   bool application_file::touch(const ::file::path & path)
   {

      if (!exists(path))
      {

         char ch;

         if (!put_contents(path, &ch, 0))
         {

            return false;

         }

      }

      return true;

   }

   string application_file::md5(const var & varFile)
   {
      return get_context_application()->get_context_system()->m_spfile->md5(varFile, get_context_application());
   }

   string application_file::nessie(const var & varFile)
   {
      return get_context_application()->get_context_system()->m_spfile->nessie(varFile, get_context_application());
   }


   ::file::path application_file::dropbox_info_json()
   {

      return get_context_application()->get_context_system()->m_spfile->dropbox_info_json( get_context_application());

   }


   ::file::path application_file::onedrive_global_ini()
   {
      
      return get_context_application()->get_context_system()->m_spfile->onedrive_global_ini( get_context_application());
      
   }


   ::file::path application_file::onedrive_cid_ini()
   {
      
      return get_context_application()->get_context_system()->m_spfile->onedrive_cid_ini( get_context_application());
      
   }


} // namespace file










































