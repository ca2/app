#include "framework.h"
#include "document_manager.h"
#include "document.h"
#include "impact.h"
#include "impact_system.h"
#include "acme/exception/interface_only.h"
#include "acme/platform/request.h"
#include "apex/platform/session.h"
#include "aura/user/user/frame.h"


#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? nullptr : (_cpc2)-1)

#define _wcsinc(_pc)    ((_pc)+1)

::u32 __get_file_title(const ::wide_character * pszPathName, ::wide_character * pszTitle, ::u32 nMax);


bool _set_reg_key(const ::wide_character * pszKey, const ::wide_character * pszValue, const ::wide_character * pszValueName = nullptr);


#ifdef WINDOWS_DESKTOP


void __get_module_short_file_name(hinstance hInst, string& strShortName);


#endif


#define DEFAULT_ICON_INDEX 0




namespace user
{

   const char document_manager::gen_ShellOpenFmt[] = "%s\\shell\\open\\%s";
   const char document_manager::gen_ShellPrintFmt[] = "%s\\shell\\print\\%s";
   const char document_manager::gen_ShellPrintToFmt[] = "%s\\shell\\printto\\%s";
   const char document_manager::gen_DefaultIconFmt[] = "%s\\DefaultIcon";
   const char document_manager::gen_ShellNewFmt[] = "%s\\ShellNew";

#define DEFAULT_ICON_INDEX 0

   const char document_manager::gen_IconIndexFmt[] = ",%d";
   const char document_manager::gen_Command[] = "command";
   const char document_manager::gen_OpenArg[] = " \"%1\"";
   const char document_manager::gen_PrintArg[] = " /point_i32 \"%1\"";
   const char document_manager::gen_PrintToArg[] = " /point_i32 \"%1\" \"%2\" \"%3\" \"%4\"";
   const char document_manager::gen_DDEArg[] = " /dde";

   const char document_manager::gen_DDEExec[] = "ddeexec";
   const char document_manager::gen_DDEOpen[] = "[open(\"%1\")]";
   const char document_manager::gen_DDEPrint[] = "[print(\"%1\")]";
   const char document_manager::gen_DDEPrintTo[] = "[printto(\"%1\",\"%2\",\"%3\",\"%4\")]";

   const char document_manager::gen_ShellNewValueName[] = "NullFile";
   const char document_manager::gen_ShellNewValue[] = "";


   document_manager::document_manager()
   {

      defer_create_synchronization();

   }


   void document_manager::UnregisterShellFileTypes()
   {
      throw ::interface_only();
      /*   ASSERT(!m_templateptra.is_empty());  // must have some doc templates

      string strPathName, strTemp;

      __get_module_short_file_name(psystem->m_hInstance, strPathName);

      POSITION pos = m_templateptra.get_head_position();
      for (i32 nTemplateIndex = 1; pos != nullptr; nTemplateIndex++)
      {
      ::pointer<impact_system>ptemplate = (::pointer<impact_system>_templateptra.get_next(pos);

      string strFilterExt, strFileTypeId, strFileTypeName;
      if (ptemplate->GetDocString(strFileTypeId,
      impact_system::regFileTypeId) && !strFileTypeId.is_empty())
      {
      // enough info to register it
      if (!ptemplate->GetDocString(strFileTypeName,
      impact_system::regFileTypeName))
      strFileTypeName = strFileTypeId;    // use atom name

      ASSERT(strFileTypeId.find(' ') == -1);  // no spaces allowed

      strTemp.format(gen_DefaultIconFmt, (const ::string &)strFileTypeId);
      __delete_reg_key(strTemp);

      // If MDI System
      if (!ptemplate->GetDocString(strTemp, impact_system::windowTitle) ||
      strTemp.is_empty())
      {
      // path\shell\open\ddeexec = [open("%1")]
      strTemp.format(gen_ShellOpenFmt, (const ::string &)strFileTypeId,
      (const ::string &)gen_DDEExec);
      __delete_reg_key(strTemp);

      // path\shell\print\ddeexec = [print("%1")]
      strTemp.format(gen_ShellPrintFmt, (const ::string &)strFileTypeId,
      (const ::string &)gen_DDEExec);
      __delete_reg_key(strTemp);

      // path\shell\printto\ddeexec = [printto("%1","%2","%3","%4")]
      strTemp.format(gen_ShellPrintToFmt, (const ::string &)strFileTypeId,
      (const ::string &)gen_DDEExec);
      __delete_reg_key(strTemp);
      }

      // path\shell\open\command = path filename
      strTemp.format(gen_ShellOpenFmt, (const ::string &)strFileTypeId,
      (const ::string &)gen_Command);
      __delete_reg_key(strTemp);

      // path\shell\print\command = path /point_i32 filename
      strTemp.format(gen_ShellPrintFmt, (const ::string &)strFileTypeId,
      (const ::string &)gen_Command);
      __delete_reg_key(strTemp);

      // path\shell\printto\command = path /point_i32 filename printer driver port
      strTemp.format(gen_ShellPrintToFmt, (const ::string &)strFileTypeId,
      (const ::string &)gen_Command);
      __delete_reg_key(strTemp);

      ptemplate->GetDocString(strFilterExt, impact_system::filterExt);
      if (!strFilterExt.is_empty())
      {
      ASSERT(strFilterExt[0] == '.');

      ::i32 lSize = _MAX_PATH * 2;
      ::i32 lResult = ::RegQueryValue(HKEY_CLASSES_ROOT, strFilterExt,
      strTemp.GetBuffer(lSize), &lSize);
      strTemp.ReleaseBuffer();

      if (lResult != ERROR_SUCCESS || strTemp.is_empty() ||
      strTemp == strFileTypeId)
      {
      strTemp.format(gen_ShellNewFmt, (const ::string &)strFilterExt);
      __delete_reg_key(strTemp);

      // no association for that suffix
      __delete_reg_key(strFilterExt);
      }
      }
      }
      }*/
   }


   void document_manager::RegisterShellFileTypes(bool bCompat)
   {
      __UNREFERENCED_PARAMETER(bCompat);
      throw ::interface_only();

      /*   ASSERT(!m_templateptra.is_empty());  // must have some doc templates

      string strPathName, strTemp;

      __get_module_short_file_name(psystem->m_hInstance, strPathName);

      POSITION pos = m_templateptra.get_head_position();
      for (i32 nTemplateIndex = 1; pos != nullptr; nTemplateIndex++)
      {
      ::pointer<impact_system>ptemplate = (::pointer<impact_system>_templateptra.get_next(pos);

      string strOpenCommandLine = strPathName;
      string strPrintCommandLine = strPathName;
      string strPrintToCommandLine = strPathName;
      string strDefaultIconCommandLine = strPathName;

      if (bCompat)
      {
      string strIconIndex;
      HICON hIcon = ::ExtractIcon(psystem->m_hInstance, strPathName, nTemplateIndex);
      if (hIcon != nullptr)
      {
      strIconIndex.format(gen_IconIndexFmt, nTemplateIndex);
      DestroyIcon(hIcon);
      }
      else
      {
      strIconIndex.format(gen_IconIndexFmt, DEFAULT_ICON_INDEX);
      }
      strDefaultIconCommandLine += strIconIndex;
      }

      string strFilterExt, strFileTypeId, strFileTypeName;
      if (ptemplate->GetDocString(strFileTypeId,
      impact_system::regFileTypeId) && !strFileTypeId.is_empty())
      {
      // enough info to register it
      if (!ptemplate->GetDocString(strFileTypeName,
      impact_system::regFileTypeName))
      strFileTypeName = strFileTypeId;    // use atom name

      ASSERT(strFileTypeId.find(' ') == -1);  // no spaces allowed

      // first register the type ID of our server
      if (!__set_reg_key(strFileTypeId, strFileTypeName))
      continue;       // just skip it

      if (bCompat)
      {
      // path\DefaultIcon = path,1
      strTemp.format(gen_DefaultIconFmt, (const ::string &)strFileTypeId);
      if (!__set_reg_key(strTemp, strDefaultIconCommandLine))
      continue;       // just skip it
      }

      // If MDI System
      if (!ptemplate->GetDocString(strTemp, impact_system::windowTitle) ||
      strTemp.is_empty())
      {
      // path\shell\open\ddeexec = [open("%1")]
      strTemp.format(gen_ShellOpenFmt, (const ::string &)strFileTypeId,
      (const ::string &)gen_DDEExec);
      if (!__set_reg_key(strTemp, gen_DDEOpen))
      continue;       // just skip it

      if (bCompat)
      {
      // path\shell\print\ddeexec = [print("%1")]
      strTemp.format(gen_ShellPrintFmt, (const ::string &)strFileTypeId,
      (const ::string &)gen_DDEExec);
      if (!__set_reg_key(strTemp, gen_DDEPrint))
      continue;       // just skip it

      // path\shell\printto\ddeexec = [printto("%1","%2","%3","%4")]
      strTemp.format(gen_ShellPrintToFmt, (const ::string &)strFileTypeId,
      (const ::string &)gen_DDEExec);
      if (!__set_reg_key(strTemp, gen_DDEPrintTo))
      continue;       // just skip it

      // path\shell\open\command = path /dde
      // path\shell\print\command = path /dde
      // path\shell\printto\command = path /dde
      strOpenCommandLine += gen_DDEArg;
      strPrintCommandLine += gen_DDEArg;
      strPrintToCommandLine += gen_DDEArg;
      }
      else
      {
      strOpenCommandLine += gen_OpenArg;
      }
      }
      else
      {
      // path\shell\open\command = path filename
      // path\shell\print\command = path /point_i32 filename
      // path\shell\printto\command = path /point_i32 filename printer driver port
      strOpenCommandLine += gen_OpenArg;
      if (bCompat)
      {
      strPrintCommandLine += gen_PrintArg;
      strPrintToCommandLine += gen_PrintToArg;
      }
      }

      // path\shell\open\command = path filename
      strTemp.format(gen_ShellOpenFmt, (const ::string &)strFileTypeId,
      (const ::string &)gen_Command);
      if (!__set_reg_key(strTemp, strOpenCommandLine))
      continue;       // just skip it

      if (bCompat)
      {
      // path\shell\print\command = path /point_i32 filename
      strTemp.format(gen_ShellPrintFmt, (const ::string &)strFileTypeId,
      (const ::string &)gen_Command);
      if (!__set_reg_key(strTemp, strPrintCommandLine))
      continue;       // just skip it

      // path\shell\printto\command = path /point_i32 filename printer driver port
      strTemp.format(gen_ShellPrintToFmt, (const ::string &)strFileTypeId,
      (const ::string &)gen_Command);
      if (!__set_reg_key(strTemp, strPrintToCommandLine))
      continue;       // just skip it
      }

      ptemplate->GetDocString(strFilterExt, impact_system::filterExt);
      if (!strFilterExt.is_empty())
      {
      ASSERT(strFilterExt[0] == '.');

      ::i32 lSize = _MAX_PATH * 2;
      ::i32 lResult = ::RegQueryValue(HKEY_CLASSES_ROOT, strFilterExt,
      strTemp.GetBuffer(lSize), &lSize);
      strTemp.ReleaseBuffer();

      if (lResult != ERROR_SUCCESS || strTemp.is_empty() ||
      strTemp == strFileTypeId)
      {
      // no association for that suffix
      if (!__set_reg_key(strFilterExt, strFileTypeId))
      continue;

      if (bCompat)
      {
      strTemp.format(gen_ShellNewFmt, (const ::string &)strFilterExt);
      ()__set_reg_key(strTemp, gen_ShellNewValue, gen_ShellNewValueName);
      }
      }
      }
      }
      }*/
   }

   /*
   __STATIC void _::aura::AppendFilterSuffix(string & filter, OPENFILENAME& ofn,
   ::pointer<impact_system>ptemplate, string* pstrDefaultExt)
   {
   ENSURE_VALID(ptemplate);
   ASSERT_KINDOF(impact_system, ptemplate);

   string strFilterExt, strFilterName;
   if (ptemplate->GetDocString(strFilterExt, impact_system::filterExt) &&
   !strFilterExt.is_empty() &&
   ptemplate->GetDocString(strFilterName, impact_system::filterName) &&
   !strFilterName.is_empty())
   {
   if (pstrDefaultExt != nullptr)
   pstrDefaultExt->Empty();

   // add to filter
   filter += strFilterName;
   ASSERT(!filter.is_empty());  // must have a file type name
   filter += (char)'\0';  // next string please

   i32 iStart = 0;
   do
   {
   string strExtension = strFilterExt.Tokenize( _T( ";" ), iStart );

   if (iStart != -1)
   {
   // a file based document template - add to filter list

   // If you hit the following ASSERT, your document template
   // string is formatted incorrectly.  The department of your
   // document template string that specifies the allowable file
   // extensions should be formatted as follows:
   //    .<ext1>;.<ext2>;.<ext3>
   // Extensions may contain wildcards (e.g. '?', '*'), but must
   // begin with a '.' and be separated from one another by a ';'.
   // Example:
   //    .jpg;.jpeg
   ASSERT(strExtension[0] == '.');
   if ((pstrDefaultExt != nullptr) && pstrDefaultExt->is_empty())
   {
   // set the default extension
   *pstrDefaultExt = strExtension.substr( 1 );  // skip the '.'
   ofn.pstrDefExt = const_cast< char * >((const ::string &)(*pstrDefaultExt));

   ofn.nFilterIndex = ofn.nMaxCustFilter + 1;  // 1 based number
   }

   filter += (char)'*';
   filter += strExtension;
   filter += (char)';';  // Always append a ';'.  The last ';' will get replaced with a '\0' later.
   }
   } while (iStart != -1);

   filter.set_at( filter.get_length()-1, '\0' );;  // replace the last ';' with a '\0'
   ofn.nMaxCustFilter++;
   }
   }
   */

   void document_manager::add_document_template(::user::impact_system * ptemplate)
   {
      
      ASSERT_VALID(ptemplate);
      
      if(m_templateptra.add_unique(ptemplate))
      {
         
         ptemplate->initialize(this);

         ptemplate->load_template();

      }
      
      //add_composite(ptemplate);

   }


   void document_manager::erase_document_template(::user::impact_system * ptemplate)
   {

      ptemplate->close_all_documents(false);

      ::count c = m_templateptra.erase(ptemplate);

      if (c <= 0)
      {

         TRACE("removing document template not managed by document manager");

      }


   }

   ::count document_manager::get_template_count() const
   {
      return m_templateptra.get_count();
   }


   ::user::impact_system * document_manager::get_template(index index) const
   {

      if(index < 0 || index >= m_templateptra.get_count())
         return nullptr;

      return m_templateptra.element_at(index);

   }


   bool document_manager::save_all_modified()
   {
      ::count count = m_templateptra.get_count();
      for(index index = 0; index < count; index++)
      {
         ::pointer<::user::impact_system>ptemplate = m_templateptra[index];
         ASSERT_KINDOF(::user::impact_system, ptemplate);
         if (!ptemplate->save_all_modified())
            return false;
      }
      return true;
   }



   void document_manager::pre_close_all_documents()
   {

      ::count count = m_templateptra.get_count();

      for(index index = 0; index < count; index++)
      {

         ::pointer<::user::impact_system>ptemplate = m_templateptra[index];

         ASSERT_KINDOF(::user::impact_system, ptemplate);

         ptemplate->pre_close_all_documents();

      }

   }


   /// close_all_documents stack
   /// shouldn't ask confirmation to close documents or end session
   void document_manager::close_all_documents(bool bEndApp)
   {

      ::count count = m_templateptra.get_count();

      for(index index = 0; index < count; index++)
      {

         ::pointer<::user::impact_system>ptemplate = m_templateptra[index];

         ASSERT_KINDOF(::user::impact_system, ptemplate);

         ptemplate->close_all_documents(bEndApp);

      }

      if (bEndApp)
      {

         m_templateptra.erase_all();

      }

   }


   bool document_manager::do_prompt_file_name(::payload & payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
   {

      throw_todo();

      //return psystem->do_prompt_file_name(payloadFile, nIDSTitle, lFlags, bOpenFileDialog, ptemplate, pdocument);

      return false;

   }

   ::count document_manager::get_document_count()
   {
      // ::count all documents
      ::count nCount = 0;
      ::count count = m_templateptra.get_count();
      for(index index = 0; index < count; index++)
      {
         ::pointer<::user::impact_system>ptemplate = m_templateptra[index];
         nCount += ptemplate->get_document_count();
      }
      return nCount;
   }

   bool document_manager::OnDDECommand(char * pszCommand)

   {
      __UNREFERENCED_PARAMETER(pszCommand);

      /*string strCommand = pszCommand;

      ::pointer<::user::document>pDoc = nullptr;

      // open format is "[open("%s")]" - no whitespace allowed, one per line
      // print format is "[print("%s")]" - no whitespace allowed, one per line
      // print to format is "[printto("%s","%s","%s","%s")]" - no whitespace allowed, one per line
      command & cmdInfo = psystem->handler();
      command.m_nShellCommand = command_line::FileDDE;

      if (strCommand.left(7) == _T("[open(\""))
      {
      cmdInfo.m_nShellCommand = command_line::FileOpen;
      strCommand = strCommand.right(strCommand.length() - 7);
      }
      else if (strCommand.left(8) == _T("[print(\""))
      {
      cmdInfo.m_nShellCommand = command_line::FilePrint;
      strCommand = strCommand.right(strCommand.length() - 8);
      }
      else if (strCommand.left(10) == _T("[printto(\""))
      {
      cmdInfo.m_nShellCommand = command_line::FilePrintTo;\
      strCommand = strCommand.right(strCommand.length() - 10);
      }
      else
      return false; // not a command we handle

      i32 i = strCommand.find('"');
      if (i == -1)
      return false; // illegally terminated

      cmdInfo.m_payloadFile = strCommand.left(i);
      strCommand = strCommand.right(strCommand.length() - i);

      //command_line* pOldInfo = nullptr;
      bool bRetVal = true;

      // // If we were started up for DDE retrieve the Show state
      //   psystem->command_line() = cmdInfo;

      if (cmdInfo.m_nShellCommand == command_line::FileOpen)
      {
      // show the application window
      ::pointer<::user::interaction>pMainWnd = psystem->m_puiMain;
      ::e_display edisplay = psystem->m_nCmdShow;
      if (nCmdShow == -1 || nCmdShow == SW_SHOWNORMAL)
      {
       trans         if (pMainWnd->is_iconic())
      nCmdShow = SW_RESTORE;
      else
      nCmdShow = e_display_restored;
      //}
      pMainWnd->display(nCmdShow);
       trans      if (nCmdShow != SW_MINIMIZE)
      pMainWnd->SetForegroundWindow();

      // then open the document
      psystem->open_document_file(get_app(), cmdInfo.m_payloadFile);


      // next time, show the window as default
      psystem->m_nCmdShow = -1;
      goto RestoreAndReturn;
      }

      if (cmdInfo.m_nShellCommand == command_line::FilePrintTo)
      {
      if (strCommand.left(3) != _T("\",\""))
      {
      bRetVal = false;
      goto RestoreAndReturn;
      }
      else
      {
      strCommand = strCommand.right(strCommand.length() - 3);
      i = strCommand.find('"');
      if (i == -1)
      {
      bRetVal = false;
      goto RestoreAndReturn;
      }
      else
      {
      cmdInfo.m_strPrinterName = strCommand.left(i);
      strCommand = strCommand.right(strCommand.length() - i);
      }
      }

      if (strCommand.left(3) != _T("\",\""))
      {
      bRetVal = false;
      goto RestoreAndReturn;
      }
      else
      {
      strCommand = strCommand.right(strCommand.length() - 3);
      i = strCommand.find('"');
      if (i == -1)
      {
      bRetVal = false;
      goto RestoreAndReturn;
      }
      else
      {
      cmdInfo.m_strDriverName = strCommand.left(i);
      strCommand = strCommand.right(strCommand.length() - i);
      }
      }

      if (strCommand.left(3) != _T("\",\""))
      {
      bRetVal = false;
      goto RestoreAndReturn;
      }
      else
      {
      strCommand = strCommand.right(strCommand.length() - 3);
      i = strCommand.find('"');
      if (i == -1)
      {
      bRetVal = false;
      goto RestoreAndReturn;
      }
      else
      {
      cmdInfo.m_strPortName = strCommand.left(i);
      strCommand = strCommand.right(strCommand.length() - i);
      }
      }
      }

      // get document ::count before opening it
      i32 nOldCount; nOldCount = get_document_count();

      // open the document, then print it.
      pDoc = psystem->open_document_file(get_app(), cmdInfo.m_payloadFile);
      //psystem->m_pCmdInfo = &cmdInfo;
      psystem->m_puiMain->SendMessage(e_message_command, ID_FILE_PRINT_DIRECT);
      //psystem->m_pCmdInfo = nullptr;

      // close the document if it wasn't open previously (based on doc count)
      if (get_document_count() > nOldCount)
      pDoc->on_close_document();


      RestoreAndReturn:
      //psystem->m_pCmdInfo = pOldInfo;
      return bRetVal;*/
      return true;
   }

   //#ifdef WINDOWS

   /*
   void document_manager::_001OnFileNew()
   {
   if (m_templateptra.is_empty())
   {
   TRACE(trace_category_appmsg, 0, "Error: no document templates registered with application.\n");
   // linux message_box(__IDP_FAILED_TO_CREATE_DOC);
   message_box(nullptr, "Failed to create document");
   return;
   }

   ::pointer<impact_system>ptemplate = (::pointer<impact_system>_templateptra.first();
   if (m_templateptra.get_count() > 1)
   {
   // more than one document template to choose from
   // bring up dialog prompting ::account::user
   return;     // none - cancel operation
   }

   ASSERT(ptemplate != nullptr);
   ASSERT_KINDOF(impact_system, ptemplate);

   ptemplate->open_document_file(get_app(), nullptr, true, psystem->m_puiInitialPlaceHolderContainer);
   // if returns nullptr, the ::account::user has already been alerted*/
   //   return true;
   //}

   //#endif

   void document_manager::on_file_open()
   {
      // prompt the ::account::user (with all document templates)

      ::pointer<::request>prequest(e_create, this);

      if (!do_prompt_file_name(prequest->m_payloadFile, "" /*__IDS_OPENFILE */, 0 /*OFN_HIDEREADONLY | OFN_FILEMUSTEXIST*/, true, nullptr, nullptr))
         return; // open cancelled

      auto psession = acmesession();

      psession->post_request(prequest);
      // if returns nullptr, the ::account::user has already been alerted
   }


//   void document_manager::assert_ok() const
//   {
//
//      object::assert_ok();
//
//      ::count count = m_templateptra.get_count();
//
//      for(index index = 0; index < count; index++)
//      {
//
//         ::pointer<::user::impact_system>ptemplate = m_templateptra[index];
//
//         ASSERT_VALID(ptemplate);
//
//      }
//
//   }
//
//
//   void document_manager::dump(dump_context & dumpcontext) const
//   {
//      object::dump(dumpcontext);
//
//      //if (dumpcontext.GetDepth() != 0)
//      //{
//      //   dumpcontext << "\nm_templateList[] = {";
//      //   ::count count = m_templateptra.get_count();
//      //   for(index index = 0; index < count; index++)
//      //   {
//      //      ::pointer<::user::impact_system>ptemplate = m_templateptra[index];
//      //      dumpcontext << "\ntemplate " << ::hex::lower_from((::iptr)ptemplate.m_p);
//      //   }
//      //   dumpcontext << "}";
//      //}
//
//      //dumpcontext << "\n";
//   }



   void document_manager::request(::request * prequest)
   {

      if(prequest->m_payloadFile.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      // find the highest confidence
      ::count count = m_templateptra.get_count();

      ::user::impact_system::Confidence bestMatch = ::user::impact_system::noAttempt;

      ::pointer<::user::impact_system>pBestTemplate;

      ::user::document * pOpenDocument = nullptr;

      /*char szPath[_MAX_PATH];
      ASSERT(lstrlen(varFileName) < _countof(szPath));
      char szTemp[_MAX_PATH];
      if (pszFileName[0] == '\"')

      ++pszFileName;

      ::aura::tcsncpy_s(szTemp, _countof(szTemp), varFileName, _TRUNCATE);
      char * pszLast = _tcsrchr(szTemp, '\"');

      if (pszLast != nullptr)

      *pszLast = 0;*/


      //if( ::aura::FullPath(szPath, szTemp) == false )
      //{
      //   ASSERT(false);
      //   return nullptr; // We won't open the file. aura API requires paths with
      // length < _MAX_PATH
      //}

      /*   char szLinkName[_MAX_PATH];
      if (::aura::ResolveShortcut(psystem->m_puiMain, szPath, szLinkName, _MAX_PATH))
      ::aura::tcscpy_s(szPath, _countof(szPath), szLinkName);
      */

      for(index index = 0; index < count; index++)
      {
         ::pointer<::user::impact_system>ptemplate = m_templateptra[index];
         ASSERT_KINDOF(::user::impact_system, ptemplate);

         ::user::impact_system::Confidence match;
         ASSERT(pOpenDocument == nullptr);
         match = ptemplate->MatchDocType(prequest->m_payloadFile, pOpenDocument);
         if (match > bestMatch)
         {
            bestMatch = match;
            pBestTemplate = ptemplate;
         }
         if (match == ::user::impact_system::yesAlreadyOpen)
            break;      // stop here
      }

      if (pOpenDocument != nullptr)
      {
         
         auto pimpact = pOpenDocument->get_impact(0); // get first one

         if(pimpact != nullptr)
         {
            
            ASSERT_VALID(pimpact);

            while(auto pFrame = pimpact->parent_frame())
            {

               pFrame->ActivateFrame();

            }

         }
         else
         {

            CATEGORY_ERROR(appmsg, "Error: Can not find a ::user::impact for document to activate.");

         }

         prequest->payload("document") = pOpenDocument;

      }

      if (pBestTemplate == nullptr)
      {

         output_error_message("Failed to open document");

         return;

      }

      pBestTemplate->request(prequest);

   }


   ::count document_manager::get_open_document_count()
   {

      ::count nOpen = 0;

      ::count count = m_templateptra.get_count();

      for(index index = 0; index < count; index++)
      {

         auto ptemplate = m_templateptra[index];

         nOpen += ptemplate->get_document_count();

      }

      return nOpen;

   }


   document_manager::~document_manager()
   {

   }


   void document_manager::_001OnFileNew()
   {

   }


   void document_manager::handle(::topic * ptopic, ::context * pcontext)
   {

      auto templateptra = m_templateptra;

      for(auto & ptemplate : templateptra.ptra())
      {

         ptemplate->handle(ptopic, pcontext);

      }

   }


} // namespace user

//
//namespace base
//{
//
//
//   //void application::erase_document_template(::user::impact_system * pimpactsystem)
//   //{
//
//   //   if (m_pdocmanager == nullptr)
//   //      return;
//
//   //   document_manager()->erase_document_template(pimpactsystem);
//
//   //}
//
//
//   //::user::document * application::open_document_file(::particle * pparticle, const ::string & pszFileName)
//
//   //{
//
//   //   ASSERT(papp->m_pdocmanager != nullptr);
//
//   //   ::pointer<::create>cc(e_create);
//
//   //   cc->m_pcommandline->m_payloadFile = pszFileName;
//
//
//   //   papp->document_manager()->request(cc);
//
//   //   return ::user::__document(cc);
//
//   //}
//
//
//} // namespace base
//


