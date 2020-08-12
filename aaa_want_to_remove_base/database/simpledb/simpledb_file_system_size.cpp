#include "framework.h"




//file_size_table::get_fs_size::get_fs_size()
//{
//}
//
//file_size_table::get_fs_size::get_fs_size(const get_fs_size & getfssize)
//{
//   operator = (getfssize);
//}
//
//file_size_table::get_fs_size & file_size_table::get_fs_size::operator = (const get_fs_size & getfssize)
//{
//   if(this != & getfssize)
//   {
//      m_strPath         = getfssize.m_strPath;
//      m_bPending        = getfssize.m_bPending;
//      m_iSize           = getfssize.m_iSize;
//      m_bRet            = getfssize.m_bRet;
//      m_oswindow            = getfssize.m_oswindow;
//
//   }
//   return *this;
//}
//
//
//file_size_table::file_size_table(::object * pobject) :
//   ::object(pobject)
//{
//   m_hmap = nullptr;
//   m_item.m_pitemParent = nullptr;
//   m_pwndServer = nullptr;
//   m_oswindowServer = nullptr;
//
//   /*   SECURITY_ATTRIBUTES MutexAttributes;
//      ZeroMemory( &MutexAttributes, sizeof(MutexAttributes) );
//      MutexAttributes.nLength = sizeof( MutexAttributes );
//      MutexAttributes.bInheritHandle = FALSE; // object uninheritable
//
//      // declare and initialize a security descriptor
//      SECURITY_DESCRIPTOR SD;
//      bool bInitOk = InitializeSecurityDescriptor(
//                        &SD,
//                        SECURITY_DESCRIPTOR_REVISION );
//      if ( bInitOk )
//      {
//         // give the security descriptor a Null Dacl
//         // done using the  "TRUE, (PACL)nullptr" here
//         bool bSetOk = SetSecurityDescriptorDacl( &SD,
//                                               TRUE,
//                                               (PACL)nullptr,
//                                               FALSE );
//         if ( bSetOk )
//         {
//            // Make the security attributes point
//            // to the security descriptor
//            MutexAttributes.pSecurityDescriptor = &SD;*/

//   //mutex() = new ::mutex(FALSE, "Global\\::draw2d::account::file_system_size::7807e510-5579-11dd-ae16-0800200c7784", &MutexAttributes);
//   //m_pevExec = new event(FALSE, FALSE, "Global\\::draw2d::account::file_system_size::exec_event::7807e510-5579-11dd-ae16-0800200c7784", &MutexAttributes);
//   //m_pevDone = new event(FALSE, FALSE, "Global\\::draw2d::account::file_system_size::done_event::7807e510-5579-11dd-ae16-0800200c7784", &MutexAttributes);
//   //mutex() = new ::mutex(FALSE, "Local\\::draw2d::account::file_system_size::7807e510-5579-11dd-ae16-0800200c7784");
//   //m_pevExec = new event(FALSE, FALSE, "Local\\::draw2d::account::file_system_size::exec_event::7807e510-5579-11dd-ae16-0800200c7784");
//   //m_pevDone = new event(FALSE, FALSE, "Local\\::draw2d::account::file_system_size::done_event::7807e510-5579-11dd-ae16-0800200c7784");
//   /*      }
//      }*/
//   m_puserinteraction  = new FileSystemSizeWnd(pobject);
//   m_puserinteraction->CreateClient();
//}
//
//file_size_table::~file_size_table()
//{
//}
//
//
//
//bool file_size_table::check_map()
//{
//   return true;
//}
//
//file_size_table::item::item()
//{
//   m_iSize = 0;
//   m_iStep = 0;
//   m_bPending = false;
//   m_bPendingLs = true;
//   m_pitemParent = nullptr;
//}
//
//void file_size_table::item::ls(::object * pobject, index & iIteration)
//{
//
//   if(m_bDir)
//   {
//
//      ::file::listing               listing(get_object());
//
//      if(path().is_empty())
//      {
//
//         Sess(papp).dir().root_ones(listing);
//
//         for(i32 i = 0; i < listing.get_size(); i++)
//         {
//            item item;
//            item.m_bPending = true;
//            item.m_bDir = true;
//            item.m_strName = listing[i];
//            item.m_pitemParent = this;
//            item.m_iStep = 0;
//            m_itema.add(new file_size_table::item(item));
//         }
//      }
//      else
//      {
//
//         listing.ls(path());
//
//         for(i32 i = 0; i < listing.get_size(); i++)
//         {
//
//            item item;
//            item.m_bPending = listing[i].m_iDir == 1;
//            item.m_bPendingLs = listing[i].m_iDir == 1;
//            item.m_bDir = listing[i].m_iDir == 1;
//            item.m_strName = listing[i].name();
//            item.m_pitemParent = this;
//            if(listing[i].m_iDir)
//            {
//               item.m_iStep = 0;
//            }
//            else
//            {
//               item.m_iSize = listing[i].m_iSize;
//               item.m_iStep = -1;
//            }
//            m_itema.add(new file_size_table::item(item));
//            iIteration++;
//         }
//      }
//      m_bPendingLs = false;
//
//   }
//}
//
//string file_size_table::item::path()
//{
//   if(m_pitemParent == nullptr)
//      return m_strName;
//   else if(m_pitemParent->m_pitemParent == nullptr)
//      return m_strName;
//   else
//      return m_pitemParent->path() + "\\" + m_strName;
//}
//
//file_size_table::item * file_size_table::item::FindItem(::object * pobject, const char * pszPath, index & iIteration)
//{
//   string strName;
//   string strPath(pszPath);
//   strPath.replace('/', '\\');
//
//   while(strPath.Left(1) == "\\")
//      strPath = strPath.Mid(1);
//   strsize iFind = strPath.find('\\');
//   strsize iFindName;
//   if(iFind < 0)
//   {
//      iFindName = FindName(papp, strPath, iIteration);
//      if(iFindName < 0)
//         return nullptr;
//      return m_itema[iFindName];
//   }
//   else
//   {
//      iFindName = FindName(papp, strPath.Left(iFind), iIteration);
//      if(iFindName < 0)
//         return nullptr;
//      return m_itema[iFindName]->FindItem(papp, strPath.Mid(iFind + 1), iIteration);
//
//   }
//}
//
//
//index file_size_table::item::FindName(::object * pobject, const char * lpszName, index & iIteration)
//{
//   if(m_bPendingLs)
//   {
//      ls(papp, iIteration);
//   }
//   for(index i = 0; i < m_itema.get_size(); i++)
//   {
//      if(m_itema[i]->m_strName == lpszName)
//         return i;
//   }
//   return -1;
//}
//
//void file_size_table::item::update_size(::object * pobject, index & iIteration)
//{
//   UNREFERENCED_PARAMETER(pobject);
//   UNREFERENCED_PARAMETER(iIteration);
//   if(m_bDir)
//   {
//      m_iSize = 0;
//      m_bPending = false;
//      for(i32 i = 0; i < m_itema.get_size(); i++)
//      {
//         m_iSize += m_itema[i]->m_iSize;
//         if(m_itema[i]->m_bPending || m_itema[i]->m_bPendingLs)
//            m_bPending = true;
//      }
//      if(m_pitemParent != nullptr && m_bPending)
//         m_pitemParent->m_bPending = true;
//   }
//
//}
//
//void file_size_table::item::update_size_recursive(::object * pobject, index & iIteration)
//{
//   if(m_bPendingLs)
//   {
//      ls(papp, iIteration);
//   }
//   for(i32 i = 0; i < m_itema.get_size(); i++)
//   {
//      m_itema[i]->update_size_recursive(papp, iIteration);
//      if(iIteration > 230)
//         break;
//   }
//   update_size(papp, iIteration);
//}
//
//
//
//DBFileSystemSizeSet::DBFileSystemSizeSet(::object * pobject) :
//   ::object(pobject), m_table(pobject)
//{
//   m_iMaxIteration = 230;
//}
//
//DBFileSystemSizeSet::~DBFileSystemSizeSet()
//{
//}
//
//
//bool DBFileSystemSizeSet::get_cache_fs_size(i64 & i64Size, const char * pszPath, bool & bPending)
//{
//
//   return false;
//
////   single_lock sl(m_table.mutex(), FALSE);
////  // Wait for ::mutex. Once it is obtained, no other client may
////  // communicate with the server
////   if(!sl.lock(duration::zero()))
////      return false;
////   if(!m_table.check_map())
////      return false;
////
////   m_table.m_puserinteraction->get_fs_size(i64Size, pszPath, bPending);
////   file_size_table::get_fs_size size;
////   FileSystemSizeWnd::size_map::pair * ppair = m_table.m_puserinteraction->m_map.plookup(pszPath);
////   if(ppair != nullptr)
////   {
////      i64Size     = ppair->element2().m_iSize;
////      bPending    = ppair->element2().m_bPending;
////      return true;
////   }
////   return  false;
////
////    // Fill shared memory
////    //::ZeroMemory(&m_pMsg, sizeof(TSharedMemory));
////    //m_pMsg->m_dwProcessID = m_dwProcessId;
/////*    _tcscpy(m_table.m_pgetfssize->m_szPath, pszPath);
////
////    // Signal server to process this request
////    m_table.m_pevExec->SetEvent();
////    // Wait for server to finish
////    if (m_table.m_pevDone->lock(0))
////    {
////      // Server finished processing data, handle data returned by the Server
////       i64Size = m_table.m_pgetfssize->m_iSize;
////       bPending = m_table.m_pgetfssize->m_bPending;
////       return m_table.m_pgetfssize->m_bRet;
////    }
////    else
////    {
////      // Timeout waiting for response from server
////       return false;
////    }*/
//
//}
//
//
//bool DBFileSystemSizeSet::get_fs_size(i64 & i64Size, const char * pszPath, bool & bPending)
//{
//   index iIteration = 0;
//   single_lock sl(m_table.mutex(), FALSE);
//   if(!sl.lock(duration::zero()))
//      return false;
//   if(!get_fs_size(i64Size, pszPath, bPending, iIteration))
//      return false;
//
//   return true;
//}
//
//bool DBFileSystemSizeSet::get_fs_size(i64 & i64Size,const ::file::path & pszPath,bool & bPending,index & iIteration)
//{
//   single_lock sl(m_table.mutex(), FALSE);
//   if(!sl.lock(duration::zero()))
//      return false;
//   if(iIteration >= m_iMaxIteration)
//   {
//      bPending = true;
//      return true;
//   }
//
//   string strTitle = pszPath.name();
//
//   file_size_table::item * pitem = m_table.m_item.FindItem(get_context_application(), pszPath, iIteration);
//
//   if(pitem != nullptr)
//   {
//      bPending = pitem->m_bPending;
//      i64Size = pitem->m_iSize;
//      if(!bPending)
//      {
//         return true;
//      }
//   }
//   else
//   {
//      return false;
//   }
//   pitem->update_size_recursive(get_context_application(), iIteration);
//   bPending = pitem->m_bPending;
//   i64Size = pitem->m_iSize;
//   return true;
//}
//
//FileSystemSizeWnd::FileSystemSizeWnd(::object * pobject) :
//   ::object(pobject)
//{
//   m_puserinteraction = new ::user::interaction(pobject);
//}
//
//
//void FileSystemSizeWnd::install_message_routing(::channel * pchannel)
//{
//
//   m_puserinteraction->install_message_routing(pchannel);
//
//   IGUI_MSG_LINK(WM_COPYDATA, pchannel, this, &FileSystemSizeWnd::_001OnCopyData);
//
//}
//
//
//bool FileSystemSizeWnd::CreateClient()
//{
//
////#ifdef WINDOWS
//
//   m_bServer = false;
//   return m_puserinteraction->create_message_queue("::draw2d::account::FileSystemSizeWnd::Client");
//   /*  __pointer(::user::interaction) puiMessage = nullptr;
//      puiMessage = System.ui_from_handle(HWND_MESSAGE);
//      return m_puserinteraction->create(nullptr, "::draw2d::account::FileSystemSizeWnd::Client", 0, rect(0, 0, 0, 0), puiMessage, id()) != FALSE;*/
//
////#else
//
//   // ::exception::throw_not_implemented();
//
////#endif
//
//}
//
//bool FileSystemSizeWnd::CreateServer()
//{
//
//#ifdef WINDOWS
//
//   m_bServer = true;
//   if(!m_puserinteraction->create_window("Local\\::draw2d::account::FileSystemSizeWnd::Server",0,nullptr,System.ui_from_handle(HWND_MESSAGE),id()))
//      return false;
//   m_puserinteraction->SetTimer(100, 100, nullptr);
//   return true;
//
//#else
//
//   ::exception::throw_not_implemented();
//
//   return false;
//
//#endif
//
//}
//
//bool FileSystemSizeWnd::get_fs_size(i64 & i64Size, const char * pszPath, bool & bPending)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   db_server * pcentral = dynamic_cast < db_server * > (&System.m_psimpledb->db());
//   oswindow oswindow = pcentral->m_pfilesystemsizeset->m_table.m_oswindowServer;
//   if(oswindow == nullptr || ! ::IsWindow(oswindow))
//   {
//      if(pcentral->m_pfilesystemsizeset->m_table.m_oswindowServer == nullptr)
//      {
//         ClientStartServer();
//      }
//      return false;
//   }
//   file_size_table::get_fs_size size;
//   size.m_strPath = pszPath;
//   size.m_bRet = false;
//
//
//   memory_file file(get_object());
//
//   {
//
//      writer writer(&file);
//
//      writer(size);
//
//   }
//
//   COPYDATASTRUCT data;
//   data.dwData = 0;
//   data.cbData = (u32)file.get_length();
//   data.pData = file.get_data();

//   ::oswindow oswindowWparam = (::oswindow) m_puserinteraction->get_os_data();
//   WPARAM wparam = (WPARAM) oswindowWparam;
//   if(::SendMessage(oswindow, WM_COPYDATA, wparam, (LPARAM) &data))
//   {
//      i64Size = m_size.m_iSize;
//      bPending = m_size.m_bPending;
//
//      return m_bRet;
//   }
//   else
//   {
//      return false;
//   }
//
//#else
//
//   ::exception::throw_not_implemented();
//
//   return false;
//
//#endif
//
//}
//
//
//void FileSystemSizeWnd::_001OnCopyData(::message::message * pmessage)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   SCAST_PTR(::message::database, pbase, pmessage);
//
//   COPYDATASTRUCT * pstruct = (COPYDATASTRUCT *) pbase->m_lparam.m_lparam;
//   if(pstruct->dwData == 0)
//   {
//      //file_size_table::get_fs_size * prec  = (file_size_table::get_fs_size *) pstruct->pData;

//      db_server * pcentral = &System.m_psimpledb->db();
//      file_size_table::get_fs_size size;
//      memory_file file(get_context_application(), pstruct->pData, pstruct->cbData);

//
//      {
//
//         reader reader(&file);
//
//         reader(size);
//
//      }
//
//      cslock sl(&m_cs);
//
//      size.m_oswindow = (oswindow) pbase->m_wparam;
//
//      size.m_bRet =  pcentral->m_pfilesystemsizeset->get_fs_size(
//                     size.m_iSize,
//                     size.m_strPath,
//                     size.m_bPending);
//      m_sizea.add(size);
//      pbase->set_lresult(1);
//   }
//   else if(pstruct->dwData == 1)
//   {
//
//      file_size_table::get_fs_size size;
//
//      memory_file file(get_context_application(), pstruct->pData, pstruct->cbData);

//
//      {
//
//         reader reader(&file);
//
//         reader(size);
//
//      }
//
//      m_bRet = true;
//
//      m_map.set_at(size.m_strPath, size);
//
//      pbase->set_lresult(1);
//
//   }
//
//#else
//
//   ::exception::throw_not_implemented();
//
//#endif
//
//
//}
//
//void FileSystemSizeWnd::_001OnTimer(::timer * ptimer)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   if(ptimer->m_nIDEvent == 100)
//   {
//
//      if(m_sizea.get_size() > 0)
//      {
//
//         COPYDATASTRUCT data;
//
//         data.dwData = 1;
//
//         memory_file file(get_object());
//
//         writer writer(&file);
//
//         while(m_sizea.get_size() > 0)
//         {
//
//            cslock sl(&m_cs);
//
//            file_size_table::get_fs_size & size = m_sizea[0];
//
//            file.Truncate(0);
//
//            writer(size);
//
//            data.cbData = (u32) file.get_length();
//
//            data.pData = file.get_data();

//
//            ::SendMessage(size.m_oswindow, WM_COPYDATA, (WPARAM) m_puserinteraction->get_os_data(), (LPARAM) &data);
//
//            m_sizea.remove_at(0);
//
//         }
//
//      }
//
//   }
//
//#else
//
//   ::exception::throw_not_implemented();
//
//#endif
//
//
//}
//
//FileSystemSizeServerThread::FileSystemSizeServerThread(::object * pobject) :
//   ::object(pobject),
//   thread(pobject)
//{
//}
//
//bool FileSystemSizeServerThread::init_thread()
//{
//   db_server * pcentral = &System.m_psimpledb->db();
//   pcentral->m_pfilesystemsizeset->m_table.m_pwndServer->CreateServer();
//   return true;
//}
//
//void FileSystemSizeWnd::ClientStartServer()
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   db_server * pcentral = &System.m_psimpledb->db();
//
//   if(m_tickLastStartTime.elapsed() > 2000)
//   {
//      m_tickLastStartTime = ::get_tick();
//
//      ::aura::shell_launcher launcher(nullptr, nullptr, Context.dir().module() / "winservice_filesystemsizeapp", nullptr, nullptr, display_none);
//
//      launcher.execute();
//
//
//   }
//
//   pcentral->m_pfilesystemsizeset->m_table.m_oswindowServer = ::FindWindowEx(HWND_MESSAGE, nullptr, nullptr, "Local\\::draw2d::account::FileSystemSizeWnd::Server");
//
//#else
//
//   ::exception::throw_not_implemented();
//
//#endif
//
//}
//
//
//void file_size_table::get_fs_size::io(::stream & stream)
//{
//
//   stream(m_strPath);
//   stream(m_bPending);
//   stream(m_iSize);
//   stream(m_bRet);
//
////#ifdef WINDOWS_DESKTOP
////
////   stream((iptr &) m_oswindow);
////
////#else
////
////   __throw(not_implemented());
////
////#endif
//
//}
//
//
////void file_size_table::get_fs_size::read(stream & istream)
////{
////   istream >> m_strPath;
////   istream >> m_bPending;
////   istream >> m_iSize;
////   istream >> m_bRet;
////
//////#ifdef WINDOWS
//////
//////   istream >> (i32 &) m_oswindow;
//////
//////#else
//////
//////   __throw(not_implemented());
//////
//////#endif
////
////
////}
//
//
//
