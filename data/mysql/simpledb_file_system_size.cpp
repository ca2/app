#include "framework.h"


file_size_table::get_fs_size::get_fs_size()
{
}

file_size_table::get_fs_size::get_fs_size(const get_fs_size & getfssize)
{
   operator = (getfssize);
}

file_size_table::get_fs_size & file_size_table::get_fs_size::operator = (const get_fs_size & getfssize)
{
   if(this != & getfssize)
   {
      m_strPath         = getfssize.m_strPath;
      m_bPending        = getfssize.m_bPending;
      m_iSize           = getfssize.m_iSize;
      m_bRet            = getfssize.m_bRet;
      m_oswindow            = getfssize.m_oswindow;

   }
   return *this;
}


file_size_table::file_size_table(::object * pobject) :
   ::object(pobject)
{
   m_hmap = nullptr;
   m_item.m_pitemParent = nullptr;
   m_puserinteractionServer = nullptr;
   m_oswindowServer = nullptr;

   /*   SECURITY_ATTRIBUTES MutexAttributes;
      ZeroMemory( &MutexAttributes, sizeof(MutexAttributes) );
      MutexAttributes.nLength = sizeof( MutexAttributes );
      MutexAttributes.bInheritHandle = false; // object uninheritable

      // declare and initialize a security descriptor
      SECURITY_DESCRIPTOR SD;
      bool bInitOk = InitializeSecurityDescriptor(
                        &SD,
                        SECURITY_DESCRIPTOR_REVISION );
      if ( bInitOk )
      {
         // give the security descriptor a Null Dacl
         // done using the  "true, (PACL)nullptr" here
         bool bSetOk = SetSecurityDescriptorDacl( &SD,
                                               true,
                                               (PACL)nullptr,
                                               false );
         if ( bSetOk )
         {
            // Make the security attributes point_i32
            // to the security descriptor
            MutexAttributes.lpSecurityDescriptor = &SD;*/
   //mutex() = new ::mutex(false, "Global\\::draw2d::account::file_system_size::7807e510-5579-11dd-ae16-0800200c7784", &MutexAttributes);
   //m_pevExec = new event(false, false, "Global\\::draw2d::account::file_system_size::exec_event::7807e510-5579-11dd-ae16-0800200c7784", &MutexAttributes);
   //m_pevDone = new event(false, false, "Global\\::draw2d::account::file_system_size::done_event::7807e510-5579-11dd-ae16-0800200c7784", &MutexAttributes);
   //mutex() = new ::mutex(false, "Local\\::draw2d::account::file_system_size::7807e510-5579-11dd-ae16-0800200c7784");
   //m_pevExec = new event(false, false, "Local\\::draw2d::account::file_system_size::exec_event::7807e510-5579-11dd-ae16-0800200c7784");
   //m_pevDone = new event(false, false, "Local\\::draw2d::account::file_system_size::done_event::7807e510-5579-11dd-ae16-0800200c7784");
   /*      }
      }*/
   m_puserinteraction  = new FileSystemSizeWnd(pobject);
   m_puserinteraction->CreateClient();
}

file_size_table::~file_size_table()
{
}



bool file_size_table::check_map()
{
   return true;
}

file_size_table::item::item()
{
   m_iSize = 0;
   m_iStep = 0;
   m_bPending = false;
   m_bPendingLs = true;
   m_pitemParent = nullptr;
}

void file_size_table::item::ls(::object * pobject, index & iIteration)
{
   if(m_bDir)
   {
      string_array               straPath;
      string_array               straTitle;
      i64_array iaSize;
      bool_array baIsDir;
      if(path().is_empty())
      {
         Sess(papp).dir().root_ones(straPath, straTitle);
         for(i32 i = 0; i < straPath.get_size(); i++)
         {
            item item;
            item.m_bPending = true;
            item.m_bDir = true;
            item.m_strName = straPath[i];
            item.m_pitemParent = this;
            if(item.m_strName.Right(1) == "\\")
               item.m_strName = item.m_strName.Left(item.m_strName.get_length() - 1);
            item.m_iStep = 0;
            m_itema.add(new file_size_table::item(item));
         }
      }
      else
      {
         Sess(papp).dir().ls(path(), &straPath, &straTitle, &baIsDir, &iaSize);
         for(i32 i = 0; i < straTitle.get_size(); i++)
         {
            item item;
            item.m_bPending = baIsDir[i];
            item.m_bPendingLs = baIsDir[i];
            item.m_bDir = baIsDir[i];
            item.m_strName = straTitle[i];
            item.m_pitemParent = this;
            if(baIsDir[i])
            {
               item.m_iStep = 0;
            }
            else
            {
               item.m_iSize = iaSize[i];
               item.m_iStep = -1;
            }
            m_itema.add(new file_size_table::item(item));
            iIteration++;
         }
      }
      m_bPendingLs = false;

   }
}

string file_size_table::item::path()
{
   if(m_pitemParent == nullptr)
      return m_strName;
   else if(m_pitemParent->m_pitemParent == nullptr)
      return m_strName;
   else
      return m_pitemParent->path() + "\\" + m_strName;
}

file_size_table::item * file_size_table::item::FindItem(::object * pobject, const ::string & pszPath, index & iIteration)
{
   string strName;
   string strPath(pszPath);
   strPath.replace('/', '\\');

   while(strPath.Left(1) == "\\")
      strPath = strPath.Mid(1);
   strsize iFind = strPath.find('\\');
   strsize iFindName;
   if(iFind < 0)
   {
      iFindName = FindName(papp, strPath, iIteration);
      if(iFindName < 0)
         return nullptr;
      return m_itema[iFindName];
   }
   else
   {
      iFindName = FindName(papp, strPath.Left(iFind), iIteration);
      if(iFindName < 0)
         return nullptr;
      return m_itema[iFindName]->FindItem(papp, strPath.Mid(iFind + 1), iIteration);

   }
}


index file_size_table::item::FindName(::object * pobject, const ::string & pszName, index & iIteration)
{
   if(m_bPendingLs)
   {
      ls(papp, iIteration);
   }
   for(index i = 0; i < m_itema.get_size(); i++)
   {
      if(m_itema[i]->m_strName == pszName)
         return i;
   }
   return -1;
}

void file_size_table::item::update_size(::object * pobject, index & iIteration)
{
   __UNREFERENCED_PARAMETER(pobject);
   __UNREFERENCED_PARAMETER(iIteration);
   if(m_bDir)
   {
      m_iSize = 0;
      m_bPending = false;
      for(i32 i = 0; i < m_itema.get_size(); i++)
      {
         m_iSize += m_itema[i]->m_iSize;
         if(m_itema[i]->m_bPending || m_itema[i]->m_bPendingLs)
            m_bPending = true;
      }
      if(m_pitemParent != nullptr && m_bPending)
         m_pitemParent->m_bPending = true;
   }

}

void file_size_table::item::update_size_recursive(::object * pobject, index & iIteration)
{
   if(m_bPendingLs)
   {
      ls(papp, iIteration);
   }
   for(i32 i = 0; i < m_itema.get_size(); i++)
   {
      m_itema[i]->update_size_recursive(papp, iIteration);
      if(iIteration > 230)
         break;
   }
   update_size(papp, iIteration);
}



DBFileSystemSizeSet::DBFileSystemSizeSet(::object * pobject) :
   ::object(pobject), m_table(pobject)
{
   m_iMaxIteration = 230;
}

DBFileSystemSizeSet::~DBFileSystemSizeSet()
{
}


bool DBFileSystemSizeSet::get_cache_fs_size(i64 & i64Size, const ::string & pszPath, bool & bPending)
{
   return false;
   single_lock synchronouslock(m_table.mutex(), false);
   // Wait for ::mutex. Once it is obtained, no other client may
   // communicate with the server
   if(!synchronouslock.lock(duration::zero()))
      return false;
   if(!m_table.check_map())
      return false;

   m_table.m_puserinteraction->get_fs_size(i64Size, pszPath, bPending);
   file_size_table::get_fs_size size;
   FileSystemSizeWnd::size_map::pair * ppair = m_table.m_puserinteraction->m_map.plookup(pszPath);
   if(ppair != nullptr)
   {
      i64Size     = ppair->element2().m_iSize;
      bPending    = ppair->element2().m_bPending;
      return true;
   }
   return  false;

   // Fill shared memory
   //::ZeroMemory(&m_pMsg, sizeof(TSharedMemory));
   //m_pMsg->m_dwProcessID = m_dwProcessId;
   /*    _tcscpy(m_table.m_pgetfssize->m_szPath, pszPath);

       // Signal server to process this request
       m_table.m_pevExec->SetEvent();
       // Wait for server to finish
       if (m_table.m_pevDone->lock(0))
       {
         // Server finished processing data, handle data returned by the Server
          i64Size = m_table.m_pgetfssize->m_iSize;
          bPending = m_table.m_pgetfssize->m_bPending;
          return m_table.m_pgetfssize->m_bRet;
       }
       else
       {
         // Timeout waiting for response from server
          return false;
       }*/
}

bool DBFileSystemSizeSet::get_fs_size(i64 & i64Size, const ::string & pszPath, bool & bPending)
{
   index iIteration = 0;
   single_lock synchronouslock(m_table.mutex(), false);
   if(!synchronouslock.lock(duration::zero()))
      return false;
   if(!get_fs_size(i64Size, pszPath, bPending, iIteration))
      return false;

   return true;
}

bool DBFileSystemSizeSet::get_fs_size(i64 & i64Size, const ::string & pszPath, bool & bPending, index & iIteration)
{
   single_lock synchronouslock(m_table.mutex(), false);
   if(!synchronouslock.lock(duration::zero()))
      return false;
   if(iIteration >= m_iMaxIteration)
   {
      bPending = true;
      return true;
   }
   string strTitle = pcontext->m_papexcontext->file().name_(pszPath);
   file_size_table::item * pitem = m_table.m_item.FindItem(get_application(), pszPath, iIteration);
   if(pitem != nullptr)
   {
      bPending = pitem->m_bPending;
      i64Size = pitem->m_iSize;
      if(!bPending)
      {
         return true;
      }
   }
   else
   {
      return false;
   }
   pitem->update_size_recursive(get_application(), iIteration);
   bPending = pitem->m_bPending;
   i64Size = pitem->m_iSize;
   return true;
}

FileSystemSizeWnd::FileSystemSizeWnd(::object * pobject) :
   ::object(pobject),
   ::user::interaction_impl *(pobject)
{
}

void FileSystemSizeWnd::install_message_routing(::channel * pchannel)
{
   m_p->install_message_routing(pchannel);
   MESSAGE_LINK(WM_COPYDATA, pchannel, this, &FileSystemSizeWnd::_001OnCopyData);
   //MESSAGE_LINK(e_message_timer, pchannel, this, &FileSystemSizeWnd::_001OnTimer);
}

bool FileSystemSizeWnd::CreateClient()
{

//#ifdef WINDOWS

   m_bServer = false;
   return m_p->create_message_queue("::draw2d::account::FileSystemSizeWnd::Client");
   /*  __pointer(::user::interaction) puiMessage = nullptr;
      puiMessage = psystem->ui_from_handle(HWND_MESSAGE);
      return m_p->create(nullptr, "::draw2d::account::FileSystemSizeWnd::Client", 0, rectangle_i32(0, 0, 0, 0), puiMessage, id()) != false;*/

//#else

   // ::exception::throw_not_implemented();

//#endif

}

bool FileSystemSizeWnd::CreateServer()
{

#ifdef WINDOWS

   m_bServer = true;
   if(!m_p->create_window("Local\\::draw2d::account::FileSystemSizeWnd::Server",0,::rectangle_i32(),psystem->ui_from_handle(HWND_MESSAGE),id()))
      return false;
   m_p->SetTimer(100, 100, nullptr);
   return true;

#else

   ::exception::throw_not_implemented();

#endif

}

bool FileSystemSizeWnd::get_fs_size(i64 & i64Size, const ::string & pszPath, bool & bPending)
{

#ifdef WINDOWS_DESKTOP

   db_server * pcentral = dynamic_cast < db_server * > (psystem->m_simpledb.db());
   oswindow oswindow = pcentral->m_pfilesystemsizeset->m_table.m_oswindowServer;
   if(oswindow == nullptr || ! ::IsWindow(oswindow))
   {
      if(pcentral->m_pfilesystemsizeset->m_table.m_oswindowServer == nullptr)
      {
         ClientStartServer();
      }
      return false;
   }
   file_size_table::get_fs_size size;
   size.m_strPath = pszPath;
   size.m_bRet = false;


   ::file::byte_stream_memory_file file(this);
   size.write(file);

   COPYDATASTRUCT data;
   data.dwData = 0;
   data.cbData = (u32) file.get_length();
   data.lpData = file.get_data();
   ::oswindow oswindowWparam = (::oswindow) m_p->get_os_data();
   wparam wparam = (WPARAM) oswindowWparam;
   if(::SendMessage(oswindow, WM_COPYDATA, wparam, (LPARAM) &data))
   {
      i64Size = m_size.m_iSize;
      bPending = m_size.m_bPending;

      return m_bRet;
   }
   else
   {
      return false;
   }

#else

   ::exception::throw_not_implemented();

#endif

}


void FileSystemSizeWnd::_001OnCopyData(::message::message * pmessage)
{

#ifdef WINDOWS_DESKTOP

   __pointer(::user::message) pusermessage(pmessage);

   COPYDATASTRUCT * pstruct = (COPYDATASTRUCT *) pusermessage->m_lparam.m_lparam;
   if(pstruct->dwData == 0)
   {
      //file_size_table::get_fs_size * prec  = (file_size_table::get_fs_size *) pstruct->lpData;
      db_server * pcentral = psystem->m_simpledb.db();
      file_size_table::get_fs_size size;
      ::file::byte_stream_memory_file file(get_application(), pstruct->lpData, pstruct->cbData);
      size.read(file);

      single_lock synchronouslock(m_criticalsection, true);
      size.m_oswindow = (oswindow) pusermessage->m_wparam;
      size.m_bRet =  pcentral->m_pfilesystemsizeset->get_fs_size(
                     size.m_iSize,
                     size.m_strPath,
                     size.m_bPending);
      m_sizea.add(size);
      pusermessage->set_lresult(1);
   }
   else if(pstruct->dwData == 1)
   {
      file_size_table::get_fs_size size;
      ::file::byte_stream_memory_file file(get_application(), pstruct->lpData, pstruct->cbData);
      size.read(file);
      m_bRet = true;
      m_map.set_at(size.m_strPath, size);
      pusermessage->set_lresult(1);
   }

#else

   ::exception::throw_not_implemented();

#endif


}

void FileSystemSizeWnd::_001OnTimer(::timer * ptimer)
{

#ifdef WINDOWS_DESKTOP

   super::_001OnTimer(ptimer);;
   if(ptimer->m_uEvent == 100)
   {
      //::PostMessage(pusermessage->m_wparam, WM_COPYDATA, (WPARAM) get_handle(), (LPARAM) &data);
      if(m_sizea.get_size() > 0)
      {
         COPYDATASTRUCT data;
         data.dwData = 1;


         ::file::byte_stream_memory_file file(this);

         while(m_sizea.get_size() > 0)
         {
            single_lock synchronouslock(m_criticalsection, true);
            file_size_table::get_fs_size & size = m_sizea[0];
            file.m_spmemorybuffer->Truncate(0);
            size.write(file);
            data.cbData = (u32) file.get_length();
            data.lpData = file.get_data();
            ::SendMessage(size.m_oswindow, WM_COPYDATA, (WPARAM) m_p->get_os_data(), (LPARAM) &data);
            m_sizea.erase_at(0);
         }
      }
   }

#else

   ::exception::throw_not_implemented();

#endif


}

FileSystemSizeServerThread::FileSystemSizeServerThread(::object * pobject) :
   ::object(pobject),
   thread(pobject)
{
}

bool FileSystemSizeServerThread::init_instance()
{
   db_server * pcentral = psystem->m_simpledb.db();
   pcentral->m_pfilesystemsizeset->m_table.m_puserinteractionServer->CreateServer();
   return true;
}

void FileSystemSizeWnd::ClientStartServer()
{

#ifdef WINDOWS_DESKTOP

   db_server * pcentral = psystem->m_simpledb.db();

   if(m_millisLastStartTime.elapsed() > 2000)
   {
      m_millisLastStartTime= ::millis::now();

      simple_shell_launcher launcher(nullptr, nullptr, pcontext->m_papexcontext->dir().path(psystem->get_module_folder(), "winservice_filesystemsizeapp"), nullptr, nullptr, SW_HIDE);

      launcher.execute();


   }

   pcentral->m_pfilesystemsizeset->m_table.m_oswindowServer = ::FindWindowEx(HWND_MESSAGE, nullptr, nullptr, "Local\\::draw2d::account::FileSystemSizeWnd::Server");

#else

   ::exception::throw_not_implemented();

#endif

}


void file_size_table::get_fs_size::write(::file::output_stream & ostream) const
{
   ostream << m_strPath;
   ostream << m_bPending;
   ostream << m_iSize;
   ostream << m_bRet;

#ifdef WINDOWS_DESKTOP

   ostream << (i32) m_oswindow;

#else

   __throw(error_not_implemented);

#endif


}

void file_size_table::get_fs_size::read(::file::input_stream & istream)
{
   istream >> m_strPath;
   istream >> m_bPending;
   istream >> m_iSize;
   istream >> m_bRet;

#ifdef WINDOWS

   istream >> (i32 &) m_oswindow;

#else

   __throw(error_not_implemented);

#endif


}


