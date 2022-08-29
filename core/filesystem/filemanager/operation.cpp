#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "operation.h"
#include "aura/user/user/interaction.h"


namespace filemanager
{

   bool has_digit(string strName);
   string get_number_mask(string strName);
   i64 get_number_value(string strName);
   string set_number_value(string strName, i64 iValue);


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


   bool operation::set_copy(::file::listing & stra,const ::file::path & pszDestBase,const ::file::path & pszSrcBase,bool bExpand)
   {

      set_operation(e_operation_copy);

      if(bExpand)
      {

         expand(m_stra,stra);

      }
      else
      {

         m_stra = stra;

      }

      m_str = pszDestBase;

      string strBase;

      if(pszSrcBase.has_char())
      {

         strBase = pszSrcBase;

      }
      else
      {

         strBase = stra[0].folder();

         ::file::path strCompare;

         for(i32 i = 1; i < stra.get_size(); i++)
         {
            
            strCompare = stra[i].folder();

            for(i32 j = 0; j < minimum(strCompare.get_length(),strBase.get_length()); j++)
            {

               if(strCompare[j] != strBase[j])
               {
                  
                  strBase = ::file::path(strCompare.Left(j)).folder();

                  break;

               }

            }

         }

      }

      m_strBase = strBase;

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


   bool operation::set_move(::file::listing & stra,const ::file::path & psz)
   {

      set_operation(e_operation_move);

      m_stra = stra;

      m_str = psz;

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


   bool operation::set_delete(::file::listing & stra)
   {

      set_operation(e_operation_delete);

      m_stra = stra;

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


   bool operation::open_src_dst(const ::file::path & pszSrc,::file::path & strDst,const ::file::path & pszDir)
   {

      auto pcontext = get_context();

      if(pcontext->m_papexcontext->dir().is(pszSrc) && !::str().ends_ci(pszSrc,".zip"))
      {

         pcontext->m_papexcontext->dir().create(strDst.folder());

         return false;

      }

      m_fileSrc = pcontext->m_papexcontext->file().get_file(pszSrc,::file::e_open_read | ::file::e_open_binary | ::file::e_open_share_deny_write);

      if(m_fileSrc.is_null())
      {

         INFORMATION("\n Could not open source file(" << m_iFile <<")="<< pszSrc);

         return false;

      }

      if(!m_bReplaceAll)
      {

         //if(pcontext->m_papexcontext->file().exists(pszDst))
         //{
         //   property_set propertyset;
         //   propertyset["srcfile"].get_value().set_string(pszSrc);
         //   propertyset["dstfile"].get_value().set_string(pszDst);
         //   output_error_message("filemanager\\do_you_want_to_replace_the_file.xml", propertyset);
         //   return false;
         //}

         if(pcontext->m_papexcontext->file().exists(strDst) || pcontext->m_papexcontext->dir().is(strDst))
         {

            //auto function = function_arg([](::payload& varRet, const ::payload& varVal)
            //   {

            //      if (varVal == "no")
            //      {

            //         if (!make_duplicate_name(strDst, pszDir))
            //         {
            //
            //            return false;

            //         }

            //      }

            //   });

            //papp->sync_output_error_message("Do you want to overwrite?\n\nThere is already a existing file with the same name: " + strDst.name() + e_message_box_icon_question + e_message_box_yes_no_cancel + parent(m_oswindowCallback));

            //if(iResult == e_dialog_result_yes)
            //{
            //}
            //else if(iResult == e_dialog_result_no)
            //{


            //   if (!make_duplicate_name(strDst, pszDir))
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

      pcontext->m_papexcontext->dir().create(strDst.folder());

      m_fileDst = pcontext->m_papexcontext->file().get_file(strDst,::file::e_open_write | ::file::e_open_binary | ::file::e_open_create);

      auto papp = get_app();

      if(m_fileDst.is_null())
      {

         INFORMATION("\n Could not open dest file("<<m_iFile<<")=" << strDst);

         property_set propertyset;

         propertyset["filepath"] = strDst;

         papp->m_papplication->dialog_box("filemanager\\not_accessible_destination_file.xhtml",propertyset);

         return false;

      }

      INFORMATION( m_iFile << " Opened "<<pszSrc<<" "<< strDst);

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

         ::file::path strName = m_str / m_stra[m_iFile].Mid(m_strBase.get_length());

         if(m_str == m_strBase)
         {

            make_duplicate_name(strName,m_str);

         }

         if (!open_src_dst(m_stra[m_iFile], strName, m_str))
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

         ::file::path strPath = m_str / m_stra[m_iFile].name();

         if (!open_src_dst(m_stra[m_iFile], strPath, m_str))
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

   
   bool operation::step()
   {

      auto pcontext = get_context();

      switch(m_eoperation)
      {
      case e_operation_copy:
      {

         if (m_iFile >= m_stra.get_size())
         {

            return false;

         }

         memsize uRead = m_fileSrc->read(m_pchBuffer,m_iBufferSize);
         if(uRead > 0)
         {
            m_fileDst->write(m_pchBuffer,uRead);
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

                  m_fileSrc->get_status(st);

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

                     pcontext->m_papexcontext->os_context()->set_file_status(strDestPath,st);

                  }
                  catch(...)
                  {

                     bStatusOk = false;

                  }

                  if(!bStatusOk)
                  {

                     FORMATTED_TRACE("Failed to set status of destination file '%s' using file status of '%s' file",strDestPath.c_str(),m_fileSrc->get_file_path().c_str());

                  }

               }
               else
               {

                  FORMATTED_TRACE("Failed to get status of source file '%s' for setting file status of '%s' file",m_fileSrc->get_file_path().c_str(),strDestPath.c_str());

               }

               m_fileSrc->close();

            }
            m_iFile++;
            while(m_iFile < m_stra.get_size() && pcontext->m_papexcontext->dir().is(m_stra[m_iFile]) && !::str().ends_ci(m_stra[m_iFile],".zip"))
            {
               m_iFile++;
            }

            if(m_iFile >= m_stra.get_size())
               return false;

            ::file::path strName = m_str / m_stra[m_iFile].Mid(m_strBase.get_length());

            if(m_str == m_strBase)
            {

               make_duplicate_name(strName,m_str);

            }

            if(!open_src_dst(m_stra[m_iFile],strName, m_str))
            {

               return false;
            }
         }
         return true;
      }
      case e_operation_delete:
      {

         if (m_iFile >= m_stra.get_size())
         {

            return false;

         }

         pcontext->m_papexcontext->file().erase(m_stra[m_iFile]);

         m_iFile++;

      }
      break;
      case e_operation_move:
      {

         if (m_iFile >= m_stra.get_size())
         {

            return false;

         }

         memsize uRead = m_fileSrc->read(m_pchBuffer,m_iBufferSize);

         m_fileDst->write(m_pchBuffer,uRead);

         m_daRead[m_iFile] += uRead;

         m_dRead += uRead;

         if(uRead == 0)
         {

            m_fileSrc->close();

            m_fileDst->close();

            pcontext->m_papexcontext->file().erase(m_stra[m_iFile]);

            m_iFile++;

            if(m_iFile >= m_stra.get_size())
               return false;

            ::file::path strPath = m_str / m_stra[m_iFile].name();

            if(!open_src_dst(m_stra[m_iFile], strPath,m_str))
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

         m_oswindowCallback->send_message(m_atom,m_wparamCallback);

      }

      return true;

   }


   void operation::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_dSize = 0.0;

      ::payload varLen;

      auto pcontext = get_context();

      for(i32 i = 0; i < m_stra.get_size(); i++)
      {

         if(pcontext->m_papexcontext->dir().is(m_stra[i]) && !::str().ends_ci(m_stra[i],".zip"))
         {

            m_daSize.add(0.0);

            m_daRead.add(0.0);

         }
         else
         {

            varLen = pcontext->m_papexcontext->file().length(m_stra[i]);

            if(varLen.is_null())
            {

               m_daSize.add(0.0);

               m_daRead.add(0.0);

            }
            else
            {

               m_dSize += varLen.u32();

               m_daSize.add((double)varLen.u32());

               m_daRead.add(0.0);

            }

         }

      }

      //return estatus;

   }


   i32 operation::get_item_count()
   {

      return (i32)m_stra.get_size();

   }


   string operation::get_item_message(i32 iItem)
   {

      string str;

      str.format("Copying %s (%s) to %s", m_stra[iItem].name().c_str(),m_stra[iItem].name().c_str(),m_str.c_str());

      return str;

   }


   double operation::get_item_progress(i32 iItem)
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


   double operation::get_item_read(i32 iItem)
   {

      return m_daRead[iItem];

   }


   double operation::get_item_size(i32 iItem)
   {

      return m_daSize[iItem];

   }


   bool has_digit(string strName)
   {

      for(index i= 0; i < strName.get_length(); i++)
      {

         if(::ansi_char_is_digit(strName[i]))
         {

            return true;

         }

      }

      return false;

   }


   string get_number_mask(string strName)
   {

      string strResult;

      bool bFirst = true;

      for(index i= 0; i < strName.get_length(); i++)
      {

         if(::ansi_char_is_digit(strName[i]))
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


   i64 get_number_value(string strName)
   {

      string strResult;

      string strMask = get_number_mask(strName);

      index i;

      for(i= strMask.get_length() - 1; i >= 0 ; i--)
      {

         if(strMask[i] == '1' || strMask[i] == 'X')
         {

            strResult = strName[i] + strResult;

         }

         if(strMask[i] == '1')
         {

            break;

         }

      }

      return ansi_to_i64(strResult);

   }


   string set_number_value(string strName, i64 iValue)
   {

      string strValue = __string(iValue);

      string strResult = strName;

      string strMask = get_number_mask(strName);

      strsize j = strValue.get_length() - 1;

      if (strMask.get_length() < strValue.get_length())
      {

         return strValue;

      }

      index i;

      for(i= strMask.get_length()-1; i >= 0 ; i--)
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

         strValue.Insert(i,strValue[j]);

         j--;

      }

      return strResult;

   }


   bool operation::make_duplicate_name(::file::path & str,const ::file::path & psz)
   {

      string strDir = psz;
      string strName = str.Mid(strDir.get_length());
      string strExtension;
      bool bDir;
      strsize iFind = strName.find("\\");
      bDir = iFind > 0;
      if(bDir)
      {
         strExtension = "\\" + strName.Mid(iFind + 1);
         strName = strName.Left(iFind);
      }
      else
      {
         strName = str.title();
         strExtension = "." + str.final_extension();
      }


      auto pcontext = get_context();

      if(has_digit(strName))
      {
         i64 iValue = get_number_value(strName);
         string strFormat;
         for(i32 i = 1; i < 1000; i++)
         {
            strFormat = set_number_value(strName, iValue + i);
            str = strDir /strFormat + strExtension;
            if(!pcontext->m_papexcontext->file().exists(str))
               return true;
         }
      }
      else
      {

         string strFormat;
         for(i32 i = 1; i < 1000; i++)
         {
            strFormat.format("-Copy-%03d",i);
            str = strDir /strName + strFormat + strExtension;
            if(!pcontext->m_papexcontext->file().exists(str))
               return true;
         }
      }
      return false;
   }


   void operation::expand(::file::listing & listingExpanded,::file::path_array & pathaExpand)
   {

      auto pcontext = m_pcontext->m_pauracontext;

      listingExpanded.m_penumerator = pcontext;

      auto papp = get_app();

      for(i32 i = 0; i < pathaExpand.get_size(); i++)
      {

         if(pcontext->m_papexcontext->dir().is(pathaExpand[i]) && !::str().ends_ci(pathaExpand[i],".zip"))
         {

            listingExpanded.set_listing(pathaExpand[i]);

            pcontext->m_papexcontext->dir().enumerate(listingExpanded);

         }
         else
         {

            listingExpanded.defer_add(pathaExpand[i]);

         }

      }

   }


} // namespace filemanager























