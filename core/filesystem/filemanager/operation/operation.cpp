#include "framework.h"
#include "operation.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/file/status.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "apex/platform/node.h"
//#include "apex/platform/os_context.h"

#include "aura/user/user/interaction.h"
#include "aura/platform/context.h"


namespace filemanager
{

   bool has_digit(const ::scoped_string & scopedstrName);
   string get_number_mask(const ::scoped_string & scopedstrName);
   long long get_number_value(const ::scoped_string & scopedstrName);
   string set_number_value(const ::scoped_string & scopedstrName, long long iValue);


   operation::operation()
   {

      m_oswindowCallback = nullptr;

      m_bReplaceAll = false;

      m_eoperation = e_operation_none;

      m_iBufferSize = 1024 * 1024;

   }


   operation::~operation()
   {


   }


   enum_operation operation::get_operation()
   {

      return m_eoperation;

   }


   void operation::set_operation(enum_operation eoperation)
   {

      m_eoperation = eoperation;

   }


   bool operation::set_copy(::file::listing_base & stra,const ::file::path & pathTargetBase,const ::file::path & pathSourceBase,bool bExpand)
   {

      set_operation(e_operation_copy);

      if(bExpand)
      {

         expand(m_filelisting,stra);

      }
      else
      {

         m_filelisting = stra;

      }

      m_path = pathTargetBase;

      string pathBase;

      if (pathSourceBase.has_character())
      {

         pathBase = pathSourceBase;

      }
      else
      {

         pathBase = stra[0].folder();

         ::file::path strCompare;

         for(int i = 1; i < stra.get_size(); i++)
         {
            
            strCompare = stra[i].folder();

            for(int j = 0; j < minimum(strCompare.length(),pathBase.length()); j++)
            {

               if(strCompare[j] != pathBase[j])
               {
                  
                  pathBase = ::file::path(strCompare.left(j)).folder();

                  break;

               }

            }

         }

      }

      m_pathBase = pathBase;

      m_dRead = 0.0;

      m_iFile = 0;

      try
      {

         initialize(this);

         return true;

      }
      catch (...)
      {

         return false;

      }
      
   }


   bool operation::set_move(::file::listing_base & stra,const ::file::path & path)
   {

      set_operation(e_operation_move);

      m_filelisting = stra;

      m_path = path;

      m_dRead = 0.0;

      m_iFile = 0;

      try
      {

         initialize(this);

         return true;

      }
      catch (...)
      {

         return false;

      }

   }


   bool operation::set_delete(::file::listing_base & stra)
   {

      set_operation(e_operation_delete);

      m_filelisting = stra;

      m_dRead = 0.0;

      m_iFile = 0;

      try
      {

         initialize(this);

         return true;

      }
      catch (...)
      {

         return false;

      }
      
   }


   bool operation::open_src_dst(const ::file::path & pathSource,::file::path & pathTarget,const ::file::path & pathFolder)
   {

      // auto pcontext = get_context();

      if(directory()->is(pathSource) && !case_insensitive_string_ends(pathSource,".zip"))
      {

         directory()->create(pathTarget.folder());

         return false;

      }

      m_fileSrc = file()->get_file(pathSource,::file::e_open_read | ::file::e_open_binary | ::file::e_open_share_deny_write);

      if(m_fileSrc.is_null())
      {

         information() << "\n Could not open source file(" << m_iFile <<")="<< pathSource;

         return false;

      }

      if(!m_bReplaceAll)
      {

         //if(file()->exists(scopedstrDst))
         //{
         //   ::property_set propertyset;
         //   propertyset["srcfile"].get_value().set_string(pathSource);
         //   propertyset["dstfile"].get_value().set_string(scopedstrDst);
         //   output_error_message("filemanager\\do_you_want_to_replace_the_file.xml", propertyset);
         //   return false;
         //}

         if(file()->exists(pathTarget) || directory()->is(pathTarget))
         {

            //auto function = function_arg([](::payload& varRet, const ::payload& varVal)
            //   {

            //      if (varVal == "no")
            //      {

            //         if (!make_duplicate_name(pathTarget, pszDir))
            //         {
            //
            //            return false;

            //         }

            //      }

            //   });

            //papp->sync_output_error_message("Do you want to overwrite?\n\nThere is already a existing file with the same name: " + pathTarget.name() + e_message_box_icon_question + e_message_box_yes_no_cancel + parent(m_oswindowCallback));

            //if(iResult == e_dialog_result_yes)
            //{
            //}
            //else if(iResult == e_dialog_result_no)
            //{


            //   if (!make_duplicate_name(pathTarget, pszDir))
            //   {

            //      return false;

            //   }
            //}
            //else
            //{
            //   return false;
            //}

         }

      }

      directory()->create(pathTarget.folder());

      m_fileDst = file()->get_file(pathTarget,::file::e_open_write | ::file::e_open_binary | ::file::e_open_create);

      auto papp = get_app();

      if(m_fileDst.is_null())
      {

         information() << "\n Could not open dest file("<<m_iFile<<")=" << pathTarget;

         ::property_set propertyset;

         propertyset["filepath"] = pathTarget;

         papp->dialog_box("filemanager\\not_accessible_destination_file.xhtml",propertyset);

         return false;

      }

      information() <<  m_iFile << " Opened "<<pathSource<<" "<< pathTarget;

      return true;

   }


   void operation::start()
   {

      switch(m_eoperation)
      {
      case e_operation_copy:
      {

         m_iFile = 0;

         m_pchBuffer = (char *)malloc(m_iBufferSize);

         ::file::path strName = m_path / m_filelisting[m_iFile].substr(m_pathBase.length());

         if(m_path == m_pathBase)
         {

            make_duplicate_name(strName,m_path);

         }

         if (!open_src_dst(m_filelisting[m_iFile], strName, m_path))
         {

            throw ::exception(error_failed);

         }

      }
      break;

      case e_operation_delete:
      {
      }
      break;

      case e_operation_move:
      {

         m_iFile = 0;

         m_pchBuffer = (char *)malloc(m_iBufferSize);

         ::file::path strPath = m_path / m_filelisting[m_iFile].name();

         if (!open_src_dst(m_filelisting[m_iFile], strPath, m_path))
         {

            throw ::exception(error_failed);

         }

      }
      break;
      default:

         break;
      }

      //return success;

   }

   
   bool operation::file_operation_thread_step()
   {

      // auto pcontext = get_context();

      switch(m_eoperation)
      {
      case e_operation_copy:
      {

         if (m_iFile >= m_filelisting.get_size())
         {

            return false;

         }

         memsize uRead = m_fileSrc->read({ m_pchBuffer,m_iBufferSize });
         if(uRead > 0)
         {
            m_fileDst->write({ m_pchBuffer,uRead });
            m_daRead[m_iFile] += uRead;
            m_dRead += uRead;
         }
         else
         {

            {

               string strDestPath = m_fileDst->get_file_path();

               m_fileDst->close();

               ::file::file_status st;

               bool bOk = true;

               try
               {

                  st = m_fileSrc->get_status();

               }
               catch(...)
               {

                  bOk = false;

               }

               if(bOk)
               {

                  bool bStatusOk = true;

                  try
                  {

                     node()->set_file_status(strDestPath,st);

                  }
                  catch(...)
                  {

                     bStatusOk = false;

                  }

                  if(!bStatusOk)
                  {

                     informationf("Failed to set status of destination file '%s' using file status of '%s' file",strDestPath.c_str(),m_fileSrc->get_file_path().c_str());

                  }

               }
               else
               {

                  informationf("Failed to get status of source file '%s' for setting file status of '%s' file",m_fileSrc->get_file_path().c_str(),strDestPath.c_str());

               }

               m_fileSrc->close();

            }
            m_iFile++;
            while(m_iFile < m_filelisting.get_size() && directory()->is(m_filelisting[m_iFile]) && !case_insensitive_string_ends(m_filelisting[m_iFile],".zip"))
            {
               m_iFile++;
            }

            if(m_iFile >= m_filelisting.get_size())
               return false;

            ::file::path strName = m_path / m_filelisting[m_iFile].substr(m_pathBase.length());

            if(m_path == m_pathBase)
            {

               make_duplicate_name(strName,m_path);

            }

            if(!open_src_dst(m_filelisting[m_iFile],strName, m_path))
            {

               return false;
            }
         }
         return true;
      }
      case e_operation_delete:
      {

         if (m_iFile >= m_filelisting.get_size())
         {

            return false;

         }

         file()->erase(m_filelisting[m_iFile]);

         m_iFile++;

      }
      break;
      case e_operation_move:
      {

         if (m_iFile >= m_filelisting.get_size())
         {

            return false;

         }

         memsize uRead = m_fileSrc->read({ m_pchBuffer,m_iBufferSize });

         m_fileDst->write({ m_pchBuffer,uRead });

         m_daRead[m_iFile] += uRead;

         m_dRead += uRead;

         if(uRead == 0)
         {

            m_fileSrc->close();

            m_fileDst->close();

            file()->erase(m_filelisting[m_iFile]);

            m_iFile++;

            if(m_iFile >= m_filelisting.get_size())
               return false;

            ::file::path strPath = m_path / m_filelisting[m_iFile].name();

            if(!open_src_dst(m_filelisting[m_iFile], strPath,m_path))
               return false;

         }
      }
      break;
      default:

         break;
      }

      return true;

   }


   bool operation::end()
   {

      switch(m_eoperation)
      {
      case e_operation_copy:
      {
         free(m_pchBuffer);
      }
      break;
      case e_operation_delete:
      {
      }
      break;
      case e_operation_move:
      {
         free(m_pchBuffer);
      }
      break;
      default:

         break;
      }

      if(m_oswindowCallback != nullptr)
      {

         m_oswindowCallback->send_message(m_emessageFileManagerOperation,m_wparamCallback);

      }

      return true;

   }


   void operation::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_dSize = 0.0;

      ::payload varLen;

      // auto pcontext = get_context();

      for(int i = 0; i < m_filelisting.get_size(); i++)
      {

         if(directory()->is(m_filelisting[i]) && !case_insensitive_string_ends(m_filelisting[i],".zip"))
         {

            m_daSize.add(0.0);

            m_daRead.add(0.0);

         }
         else
         {

            varLen = file()->length(m_filelisting[i]);

            if(varLen.is_null())
            {

               m_daSize.add(0.0);

               m_daRead.add(0.0);

            }
            else
            {

               m_dSize += varLen.as_unsigned_int();

               m_daSize.add((double)varLen.as_unsigned_int());

               m_daRead.add(0.0);

            }

         }

      }

      //return estatus;

   }


   int operation::get_item_count()
   {

      return (int)m_filelisting.get_size();

   }


   string operation::get_item_message(int iItem)
   {

      string str;

      str.formatf("Copying %s (%s) to %s", ::string(m_filelisting[iItem].name()).c_str(), ::string(m_filelisting[iItem].name()).c_str(),m_path.c_str());

      return str;

   }


   double operation::get_item_progress(int iItem)
   {

      if(m_daSize[iItem] == 0.0)
      {

         if(m_iFile > iItem)
         {

            return 1.0;

         }
         else
         {

            return 0.0;

         }

      }

      return m_daRead[iItem] / m_daSize[iItem];

   }


   double operation::get_item_read(int iItem)
   {

      return m_daRead[iItem];

   }


   double operation::get_item_size(int iItem)
   {

      return m_daSize[iItem];

   }


   bool has_digit(const ::scoped_string & scopedstrName)
   {

      for(::collection::index i= 0; i < scopedstrName.length(); i++)
      {

         if(::ansi_char_isdigit(scopedstrName[i]))
         {

            return true;

         }

      }

      return false;

   }


   string get_number_mask(const ::scoped_string & scopedstrName)
   {

      string strResult;

      bool bFirst = true;

      for(::collection::index i= 0; i < scopedstrName.length(); i++)
      {

         if(::ansi_char_isdigit(scopedstrName[i]))
         {

            if(bFirst)
            {

               bFirst = false;

               strResult += "1";

            }
            else
            {

               strResult += "X";

            }

         }
         else
         {

            strResult += "0";

         }

      }

      return strResult;

   }


   long long get_number_value(const ::scoped_string & scopedstrName)
   {

      string strResult;

      string strMask = get_number_mask(scopedstrName);

      ::collection::index i;

      for(i= strMask.length() - 1; i >= 0 ; i--)
      {

         if(strMask[i] == '1' || strMask[i] == 'X')
         {

            strResult = scopedstrName[i] + strResult;

         }

         if(strMask[i] == '1')
         {

            break;

         }

      }

      return ansi_to_long_long(strResult);

   }


   string set_number_value(const ::scoped_string & scopedstrName, long long iValue)
   {

      string strValue = as_string(iValue);

      string strResult = scopedstrName;

      string strMask = get_number_mask(scopedstrName);

      character_count j = strValue.length() - 1;

      if (strMask.length() < strValue.length())
      {

         return strValue;

      }

      ::collection::index i;

      for(i= strMask.length()-1; i >= 0 ; i--)
      {

         if(strMask[i] == 'X' || strMask[i] == '1')
         {

            if(j >= 0)
            {

               strResult.set_at(i,strValue[j]);

               j--;

            }
            else
            {

               strResult.set_at(i, '0');

            }

            if(strMask[i] == '1')
            {

               break;

            }

         }

      }

      while(j >= 0)
      {

         strValue.insert(i,strValue[j]);

         j--;

      }

      return strResult;

   }


   bool operation::make_duplicate_name(::file::path & str,const ::file::path & path)
   {

      string strDir = path;
      string strName = str.substr(strDir.length());
      string strExtension;
      bool bDir;
      auto iFind = strName.find_index("\\");
      bDir = iFind > 0;
      if(bDir)
      {
         strExtension = "\\" + strName(iFind + 1);
         strName = strName(0, iFind);
      }
      else
      {
         strName = str.title();
         strExtension = "." + str.final_extension();
      }


      // auto pcontext = get_context();

      if(has_digit(strName))
      {
         long long iValue = get_number_value(strName);
         string strFormat;
         for(int i = 1; i < 1000; i++)
         {
            strFormat = set_number_value(strName, iValue + i);
            str = strDir /strFormat + strExtension;
            if(!file()->exists(str))
               return true;
         }
      }
      else
      {

         string strFormat;
         for(int i = 1; i < 1000; i++)
         {
            strFormat.formatf("-Copy-%03d",i);
            str = strDir /strName + strFormat + strExtension;
            if(!file()->exists(str))
               return true;
         }
      }
      return false;
   }


   void operation::expand(::file::listing_base & listingExpanded,::file::path_array & pathaExpand)
   {

      auto papplication = m_papplication;

      ::cast < ::file::enumerator > pfileenumerator = papplication;

      listingExpanded.m_penumerator = pfileenumerator;

      auto papp = get_app();

      for(int i = 0; i < pathaExpand.get_size(); i++)
      {

         if(directory()->is(pathaExpand[i]) && !case_insensitive_string_ends(pathaExpand[i],".zip"))
         {

            listingExpanded.set_listing(pathaExpand[i]);

            directory()->enumerate(listingExpanded);

         }
         else
         {

            listingExpanded.defer_add(pathaExpand[i]);

         }

      }

   }


} // namespace filemanager























