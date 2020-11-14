#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? nullptr : (_cpc2)-1)

#define _wcsinc(_pc)    ((_pc)+1)

::u32 __get_file_title(const widechar * pszPathName, widechar * pszTitle, ::u32 nMax);


bool _set_reg_key(const widechar * pszKey, const widechar * pszValue, const widechar * pszValueName = nullptr);


void __get_module_short_file_name(HINSTANCE hInst, string& strShortName);



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
   const char document_manager::gen_PrintArg[] = " /point \"%1\"";
   const char document_manager::gen_PrintToArg[] = " /point \"%1\" \"%2\" \"%3\" \"%4\"";
   const char document_manager::gen_DDEArg[] = " /dde";

   const char document_manager::gen_DDEExec[] = "ddeexec";
   const char document_manager::gen_DDEOpen[] = "[open(\"%1\")]";
   const char document_manager::gen_DDEPrint[] = "[print(\"%1\")]";
   const char document_manager::gen_DDEPrintTo[] = "[printto(\"%1\",\"%2\",\"%3\",\"%4\")]";

   const char document_manager::gen_ShellNewValueName[] = "NullFile";
   const char document_manager::gen_ShellNewValue[] = "";


   document_manager::document_manager()
   {

      defer_create_mutex();

   }


   void document_manager::UnregisterShellFileTypes()
   {
      ::exception::throw_not_implemented();
      /*   ASSERT(!m_templateptra.is_empty());  // must have some doc templates

      string strPathName, strTemp;

      __get_module_short_file_name(System.m_hInstance, strPathName);

      POSITION pos = m_templateptra.get_head_position();
      for (i32 nTemplateIndex = 1; pos != nullptr; nTemplateIndex++)
      {
      __pointer(impact_system) ptemplate = (__pointer(impact_system))m_templateptra.get_next(pos);

      string strFilterExt, strFileTypeId, strFileTypeName;
      if (ptemplate->GetDocString(strFileTypeId,
      impact_system::regFileTypeId) && !strFileTypeId.is_empty())
      {
      // enough info to register it
      if (!ptemplate->GetDocString(strFileTypeName,
      impact_system::regFileTypeName))
      strFileTypeName = strFileTypeId;    // use id name

      ASSERT(strFileTypeId.find(' ') == -1);  // no spaces allowed

      strTemp.Format(gen_DefaultIconFmt, (const char *)strFileTypeId);
      __delete_reg_key(strTemp);

      // If MDI System
      if (!ptemplate->GetDocString(strTemp, impact_system::windowTitle) ||
      strTemp.is_empty())
      {
      // path\shell\open\ddeexec = [open("%1")]
      strTemp.Format(gen_ShellOpenFmt, (const char *)strFileTypeId,
      (const char *)gen_DDEExec);
      __delete_reg_key(strTemp);

      // path\shell\print\ddeexec = [print("%1")]
      strTemp.Format(gen_ShellPrintFmt, (const char *)strFileTypeId,
      (const char *)gen_DDEExec);
      __delete_reg_key(strTemp);

      // path\shell\printto\ddeexec = [printto("%1","%2","%3","%4")]
      strTemp.Format(gen_ShellPrintToFmt, (const char *)strFileTypeId,
      (const char *)gen_DDEExec);
      __delete_reg_key(strTemp);
      }

      // path\shell\open\command = path filename
      strTemp.Format(gen_ShellOpenFmt, (const char *)strFileTypeId,
      (const char *)gen_Command);
      __delete_reg_key(strTemp);

      // path\shell\print\command = path /point filename
      strTemp.Format(gen_ShellPrintFmt, (const char *)strFileTypeId,
      (const char *)gen_Command);
      __delete_reg_key(strTemp);

      // path\shell\printto\command = path /point filename printer driver port
      strTemp.Format(gen_ShellPrintToFmt, (const char *)strFileTypeId,
      (const char *)gen_Command);
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
      strTemp.Format(gen_ShellNewFmt, (const char *)strFilterExt);
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
      UNREFERENCED_PARAMETER(bCompat);
      ::exception::throw_not_implemented();

      /*   ASSERT(!m_templateptra.is_empty());  // must have some doc templates

      string strPathName, strTemp;

      __get_module_short_file_name(System.m_hInstance, strPathName);

      POSITION pos = m_templateptra.get_head_position();
      for (i32 nTemplateIndex = 1; pos != nullptr; nTemplateIndex++)
      {
      __pointer(impact_system) ptemplate = (__pointer(impact_system))m_templateptra.get_next(pos);

      string strOpenCommandLine = strPathName;
      string strPrintCommandLine = strPathName;
      string strPrintToCommandLine = strPathName;
      string strDefaultIconCommandLine = strPathName;

      if (bCompat)
      {
      string strIconIndex;
      HICON hIcon = ::ExtractIcon(System.m_hInstance, strPathName, nTemplateIndex);
      if (hIcon != nullptr)
      {
      strIconIndex.Format(gen_IconIndexFmt, nTemplateIndex);
      DestroyIcon(hIcon);
      }
      else
      {
      strIconIndex.Format(gen_IconIndexFmt, DEFAULT_ICON_INDEX);
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
      strFileTypeName = strFileTypeId;    // use id name

      ASSERT(strFileTypeId.find(' ') == -1);  // no spaces allowed

      // first register the type ID of our server
      if (!__set_reg_key(strFileTypeId, strFileTypeName))
      continue;       // just skip it

      if (bCompat)
      {
      // path\DefaultIcon = path,1
      strTemp.Format(gen_DefaultIconFmt, (const char *)strFileTypeId);
      if (!__set_reg_key(strTemp, strDefaultIconCommandLine))
      continue;       // just skip it
      }

      // If MDI System
      if (!ptemplate->GetDocString(strTemp, impact_system::windowTitle) ||
      strTemp.is_empty())
      {
      // path\shell\open\ddeexec = [open("%1")]
      strTemp.Format(gen_ShellOpenFmt, (const char *)strFileTypeId,
      (const char *)gen_DDEExec);
      if (!__set_reg_key(strTemp, gen_DDEOpen))
      continue;       // just skip it

      if (bCompat)
      {
      // path\shell\print\ddeexec = [print("%1")]
      strTemp.Format(gen_ShellPrintFmt, (const char *)strFileTypeId,
      (const char *)gen_DDEExec);
      if (!__set_reg_key(strTemp, gen_DDEPrint))
      continue;       // just skip it

      // path\shell\printto\ddeexec = [printto("%1","%2","%3","%4")]
      strTemp.Format(gen_ShellPrintToFmt, (const char *)strFileTypeId,
      (const char *)gen_DDEExec);
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
      // path\shell\print\command = path /point filename
      // path\shell\printto\command = path /point filename printer driver port
      strOpenCommandLine += gen_OpenArg;
      if (bCompat)
      {
      strPrintCommandLine += gen_PrintArg;
      strPrintToCommandLine += gen_PrintToArg;
      }
      }

      // path\shell\open\command = path filename
      strTemp.Format(gen_ShellOpenFmt, (const char *)strFileTypeId,
      (const char *)gen_Command);
      if (!__set_reg_key(strTemp, strOpenCommandLine))
      continue;       // just skip it

      if (bCompat)
      {
      // path\shell\print\command = path /point filename
      strTemp.Format(gen_ShellPrintFmt, (const char *)strFileTypeId,
      (const char *)gen_Command);
      if (!__set_reg_key(strTemp, strPrintCommandLine))
      continue;       // just skip it

      // path\shell\printto\command = path /point filename printer driver port
      strTemp.Format(gen_ShellPrintToFmt, (const char *)strFileTypeId,
      (const char *)gen_Command);
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
      strTemp.Format(gen_ShellNewFmt, (const char *)strFilterExt);
      ()__set_reg_key(strTemp, gen_ShellNewValue, gen_ShellNewValueName);
      }
      }
      }
      }
      }*/
   }

   /*
   __STATIC void _::aura::AppendFilterSuffix(string & filter, OPENFILENAME& ofn,
   __pointer(impact_system) ptemplate, string* pstrDefaultExt)
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
   *pstrDefaultExt = strExtension.Mid( 1 );  // skip the '.'
   ofn.pstrDefExt = const_cast< char * >((const char *)(*pstrDefaultExt));

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
         ptemplate->load_template();
      }
      
      add_composite(ptemplate);

   }


   void document_manager::remove_document_template(::user::impact_system * ptemplate)
   {

      ptemplate->close_all_documents(false);

      ::count c = m_templateptra.remove(ptemplate);

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
         __pointer(::user::impact_system) ptemplate = m_templateptra[index];
         ASSERT_KINDOF(::user::impact_system, ptemplate);
         if (!ptemplate->save_all_modified())
            return FALSE;
      }
      return TRUE;
   }



   void document_manager::pre_close_all_documents()
   {

      ::count count = m_templateptra.get_count();

      for(index index = 0; index < count; index++)
      {

         __pointer(::user::impact_system) ptemplate = m_templateptra[index];

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

         __pointer(::user::impact_system) ptemplate = m_templateptra[index];

         ASSERT_KINDOF(::user::impact_system, ptemplate);

         ptemplate->close_all_documents(bEndApp);

      }

      if (bEndApp)
      {

         m_templateptra.remove_all();

      }

   }


   bool document_manager::do_prompt_file_name(var & varFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
   {

      throw_todo();

      //return System.do_prompt_file_name(varFile, nIDSTitle, lFlags, bOpenFileDialog, ptemplate, pdocument);

      return false;

   }

   ::count document_manager::get_document_count()
   {
      // ::count all documents
      ::count nCount = 0;
      ::count count = m_templateptra.get_count();
      for(index index = 0; index < count; index++)
      {
         __pointer(::user::impact_system) ptemplate = m_templateptra[index];
         nCount += ptemplate->get_document_count();
      }
      return nCount;
   }

   bool document_manager::OnDDECommand(char * pszCommand)

   {
      UNREFERENCED_PARAMETER(pszCommand);

      /*string strCommand = pszCommand;

      __pointer(::user::document) pDoc = nullptr;

      // open format is "[open("%s")]" - no whitespace allowed, one per line
      // print format is "[print("%s")]" - no whitespace allowed, one per line
      // print to format is "[printto("%s","%s","%s","%s")]" - no whitespace allowed, one per line
      command & cmdInfo = System.handler();
      command.m_nShellCommand = command_line::FileDDE;

      if (strCommand.Left(7) == _T("[open(\""))
      {
      cmdInfo.m_nShellCommand = command_line::FileOpen;
      strCommand = strCommand.Right(strCommand.get_length() - 7);
      }
      else if (strCommand.Left(8) == _T("[print(\""))
      {
      cmdInfo.m_nShellCommand = command_line::FilePrint;
      strCommand = strCommand.Right(strCommand.get_length() - 8);
      }
      else if (strCommand.Left(10) == _T("[printto(\""))
      {
      cmdInfo.m_nShellCommand = command_line::FilePrintTo;\
      strCommand = strCommand.Right(strCommand.get_length() - 10);
      }
      else
      return FALSE; // not a command we handle

      i32 i = strCommand.find('"');
      if (i == -1)
      return FALSE; // illegally terminated

      cmdInfo.m_varFile = strCommand.Left(i);
      strCommand = strCommand.Right(strCommand.get_length() - i);

      //command_line* pOldInfo = nullptr;
      bool bRetVal = TRUE;

      // // If we were started up for DDE retrieve the Show state
      //   System.command_line() = cmdInfo;

      if (cmdInfo.m_nShellCommand == command_line::FileOpen)
      {
      // show the application window
      __pointer(::user::interaction) pMainWnd = System.m_puiMain;
      edisplay edisplay = System.m_nCmdShow;
      if (nCmdShow == -1 || nCmdShow == SW_SHOWNORMAL)
      {
       trans         if (pMainWnd->is_iconic())
      nCmdShow = SW_RESTORE;
      else
      nCmdShow = display_normal;
      //}
      pMainWnd->display(nCmdShow);
       trans      if (nCmdShow != SW_MINIMIZE)
      pMainWnd->SetForegroundWindow();

      // then open the document
      System.open_document_file(get_context_application(), cmdInfo.m_varFile);


      // next time, show the window as default
      System.m_nCmdShow = -1;
      goto RestoreAndReturn;
      }

      if (cmdInfo.m_nShellCommand == command_line::FilePrintTo)
      {
      if (strCommand.Left(3) != _T("\",\""))
      {
      bRetVal = FALSE;
      goto RestoreAndReturn;
      }
      else
      {
      strCommand = strCommand.Right(strCommand.get_length() - 3);
      i = strCommand.find('"');
      if (i == -1)
      {
      bRetVal = FALSE;
      goto RestoreAndReturn;
      }
      else
      {
      cmdInfo.m_strPrinterName = strCommand.Left(i);
      strCommand = strCommand.Right(strCommand.get_length() - i);
      }
      }

      if (strCommand.Left(3) != _T("\",\""))
      {
      bRetVal = FALSE;
      goto RestoreAndReturn;
      }
      else
      {
      strCommand = strCommand.Right(strCommand.get_length() - 3);
      i = strCommand.find('"');
      if (i == -1)
      {
      bRetVal = FALSE;
      goto RestoreAndReturn;
      }
      else
      {
      cmdInfo.m_strDriverName = strCommand.Left(i);
      strCommand = strCommand.Right(strCommand.get_length() - i);
      }
      }

      if (strCommand.Left(3) != _T("\",\""))
      {
      bRetVal = FALSE;
      goto RestoreAndReturn;
      }
      else
      {
      strCommand = strCommand.Right(strCommand.get_length() - 3);
      i = strCommand.find('"');
      if (i == -1)
      {
      bRetVal = FALSE;
      goto RestoreAndReturn;
      }
      else
      {
      cmdInfo.m_strPortName = strCommand.Left(i);
      strCommand = strCommand.Right(strCommand.get_length() - i);
      }
      }
      }

      // get document ::count before opening it
      i32 nOldCount; nOldCount = get_document_count();

      // open the document, then print it.
      pDoc = System.open_document_file(get_context_application(), cmdInfo.m_varFile);
      //System.m_pCmdInfo = &cmdInfo;
      System.m_puiMain->SendMessage(e_message_command, ID_FILE_PRINT_DIRECT);
      //System.m_pCmdInfo = nullptr;

      // close the document if it wasn't open previously (based on doc count)
      if (get_document_count() > nOldCount)
      pDoc->on_close_document();


      RestoreAndReturn:
      //System.m_pCmdInfo = pOldInfo;
      return bRetVal;*/
      return TRUE;
   }

   //#ifdef WINDOWS

   /*
   void document_manager::_001OnFileNew()
   {
   if (m_templateptra.is_empty())
   {
   TRACE(trace_category_appmsg, 0, "Error: no document templates registered with application.\n");
   // linux System.message_box(__IDP_FAILED_TO_CREATE_DOC);
   System.message_box(nullptr, "Failed to create document");
   return;
   }

   __pointer(impact_system) ptemplate = (__pointer(impact_system))m_templateptra.first();
   if (m_templateptra.get_count() > 1)
   {
   // more than one document template to choose from
   // bring up dialog prompting ::account::user
   return;     // none - cancel operation
   }

   ASSERT(ptemplate != nullptr);
   ASSERT_KINDOF(impact_system, ptemplate);

   ptemplate->open_document_file(get_context_application(), nullptr, TRUE, System.m_puiInitialPlaceHolderContainer);
   // if returns nullptr, the ::account::user has already been alerted*/
   //   return TRUE;
   //}

   //#endif

   void document_manager::on_file_open()
   {
      // prompt the ::account::user (with all document templates)

      __pointer(::create) pcreate(e_create);

      if (!do_prompt_file_name(pcreate->m_pcommandline->m_varFile, "" /*__IDS_OPENFILE */, 0 /*OFN_HIDEREADONLY | OFN_FILEMUSTEXIST*/, TRUE, nullptr, nullptr))
         return; // open cancelled

      auto psession = Session;

      psession->do_request(pcreate);
      // if returns nullptr, the ::account::user has already been alerted
   }


   void document_manager::assert_valid() const
   {

      object::assert_valid();

      ::count count = m_templateptra.get_count();

      for(index index = 0; index < count; index++)
      {

         __pointer(::user::impact_system) ptemplate = (__pointer(::user::impact_system)) m_templateptra[index];

         ASSERT_VALID(ptemplate);

      }

   }


   void document_manager::dump(dump_context & dumpcontext) const
   {
      object::dump(dumpcontext);

      if (dumpcontext.GetDepth() != 0)
      {
         dumpcontext << "\nm_templateList[] = {";
         ::count count = m_templateptra.get_count();
         for(index index = 0; index < count; index++)
         {
            __pointer(::user::impact_system) ptemplate = m_templateptra[index];
            dumpcontext << "\ntemplate " << ::hex::lower_from((::iptr)ptemplate.m_p);
         }
         dumpcontext << "}";
      }

      dumpcontext << "\n";
   }



   void document_manager::request(::create * pcreate)
   {

      if(pcreate->m_pcommandline->m_varFile.is_empty())
      {

         __throw(invalid_argument_exception());

      }

      // find the highest confidence
      ::count count = m_templateptra.get_count();

      ::user::impact_system::Confidence bestMatch = ::user::impact_system::noAttempt;

      __pointer(::user::impact_system) pBestTemplate;

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


      //if( ::aura::FullPath(szPath, szTemp) == FALSE )
      //{
      //   ASSERT(FALSE);
      //   return nullptr; // We won't open the file. aura API requires paths with
      // length < _MAX_PATH
      //}

      /*   char szLinkName[_MAX_PATH];
      if (::aura::ResolveShortcut(System.m_puiMain, szPath, szLinkName, _MAX_PATH))
      ::aura::tcscpy_s(szPath, _countof(szPath), szLinkName);
      */

      for(index index = 0; index < count; index++)
      {
         __pointer(::user::impact_system) ptemplate = m_templateptra[index];
         ASSERT_KINDOF(::user::impact_system, ptemplate);

         ::user::impact_system::Confidence match;
         ASSERT(pOpenDocument == nullptr);
         match = ptemplate->MatchDocType(pcreate->m_pcommandline->m_varFile, pOpenDocument);
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
         __pointer(::user::impact) pview = pOpenDocument->get_view(0); // get first one
         if(pview != nullptr)
         {
            ASSERT_VALID(pview);
            __pointer(::user::frame_window) pFrame = pview->GetParentFrame();

            if (pFrame == nullptr)
               TRACE(trace_category_appmsg, trace_level_error, "Error: Can not find a frame for document to activate.\n");
            else
            {
               pFrame->ActivateFrame();

               if (pFrame->GetParent() != nullptr)
               {
                  __pointer(::user::frame_window) pAppFrame;
                  ASSERT_KINDOF(frame_window, pAppFrame);
                  pAppFrame->ActivateFrame();
               }
            }
         }
         else
            TRACE(trace_category_appmsg, trace_level_error, "Error: Can not find a ::user::impact for document to activate.\n");

         pcreate->m_pcommandline->m_varQuery["document"] = pOpenDocument;
      }

      if (pBestTemplate == nullptr)
      {

         // linux System.message_box(__IDP_FAILED_TO_OPEN_DOC);

         System.message_box("Failed to open document");

         return;

      }

      pBestTemplate->do_request(pcreate);

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


   void document_manager::on_apply(::action * paction)
   {

      auto templateptra = m_templateptra;

      for(auto & ptemplate : templateptra.ptra())
      {

         ptemplate->apply(paction);

      }

   }


} // namespace user

//
//namespace base
//{
//
//
//   //void application::remove_document_template(::user::impact_system * pimpactsystem)
//   //{
//
//   //   if (m_pdocmanager == nullptr)
//   //      return;
//
//   //   document_manager()->remove_document_template(pimpactsystem);
//
//   //}
//
//
//   //::user::document * application::open_document_file(::object * pobject, const char * pszFileName)
//
//   //{
//
//   //   ASSERT(Application.m_pdocmanager != nullptr);
//
//   //   __pointer(::create) cc(e_create);
//
//   //   cc->m_pcommandline->m_varFile = pszFileName;
//
//
//   //   Application.document_manager()->request(cc);
//
//   //   return ::user::__document(cc);
//
//   //}
//
//
//} // namespace base
//


