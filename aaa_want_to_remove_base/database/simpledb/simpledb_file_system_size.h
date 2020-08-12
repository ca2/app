#pragma once


class db_server;
class FileSystemSizeWnd;


class CLASS_DECL_BASE file_size_table :
   virtual public ::object
{
public:


   class get_fs_size :
      public ::object
   {
   public:


      string   m_strPath;
      bool     m_bPending;
      i64  m_iSize;
      bool     m_bRet;
      oswindow     m_oswindow;


      get_fs_size();
      get_fs_size(const get_fs_size & getfssize);


      get_fs_size & operator = (const get_fs_size & getfssize);


      virtual ::stream & write(::stream & stream) const override;
virtual ::stream & read(::stream & stream) override;


   };


   class item :
      virtual public object
   {
   public:


      item *      m_pitemParent;
      string      m_strName;
      bool        m_bPending;
      i64     m_iSize;
      index       m_iStep;
      bool        m_bDir;
      bool        m_bPendingLs;

      __pointer_array(item)   m_itema;


      item();


      void update_size(::object * pobject, index & iIteration);
      void update_size_recursive(::object * pobject, index & iIteration);

      item * FindItem(::object * pobject, const char * pszPath, index & iIteration);
      index FindName(::object * pobject, const char * lpszName, index & iIteration);

      string path();

      void ls(::object * pobject, index & iIteration);
   };


   item                    m_item;
   HANDLE                  m_hmap;
   class get_fs_size *     m_pgetfssize;
   FileSystemSizeWnd *     m_puserinteraction;
   FileSystemSizeWnd *     m_pwndServer;
   oswindow                    m_oswindowServer;
   ::event *               m_pevExec;
   ::event *               m_pevDone;
   ::mutex *               mutex();





   file_size_table(::object * pobject);
   ~file_size_table();

   bool check_map();

};



class CLASS_DECL_BASE DBFileSystemSizeSet :
   virtual public ::object
{
public:


   file_size_table            m_table;
   index                     m_iMaxIteration;


   DBFileSystemSizeSet(::object * pobject);
   ~DBFileSystemSizeSet();



   bool get_cache_fs_size(i64 & i64Size, const char * pszPath, bool & bPending);
   bool get_fs_size(i64 & i64Size, const char * pszPath, bool & bPending);


   bool get_fs_size(i64 & i64Size, const ::file::path & pszPath, bool & bPending, index & iIteration);


};





class CLASS_DECL_BASE FileSystemSizeServerThread :
   virtual public thread
{
public:

   FileSystemSizeServerThread(::object * pobject);

   bool init_thread() override;

};




class CLASS_DECL_BASE FileSystemSizeWnd :
   public ::object
{
public:


   class size_map :
      public string_map < file_size_table::get_fs_size, file_size_table::get_fs_size >
   {
   public:
   };


   tick m_tickLastStartTime;
   bool                             m_bServer;
   file_size_table::get_fs_size     m_size;
   bool                             m_bRet;
   critical_section                 m_cs;
   array < file_size_table::get_fs_size, file_size_table::get_fs_size & > m_sizea;

   size_map                         m_map;
   ::user::interaction *            m_puserinteraction;

   FileSystemSizeWnd(::object * pobject);

   bool CreateClient();
   bool CreateServer();



   void ClientStartServer();
   bool get_fs_size(i64 & i64Size, const char * pszPath, bool & bPending);

   void install_message_routing(::channel * pchannel);

   DECL_GEN_SIGNAL(_001OnCopyData);
   void _001OnTimer(::timer * ptimer);


};


