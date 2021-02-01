#pragma once


class db_server;
class FileSystemSizeWnd;


class CLASS_DECL_AURA file_size_table :
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


      virtual void write(::file::output_stream & ostream) const;
      virtual void read(::file::input_stream & istream);


   };


   class item :
      virtual public matter
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
      index FindName(::object * pobject, const char * pszName, index & iIteration);

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





   file_size_table(::layered * pobjectContext);
   ~file_size_table();

   bool check_map();

};



class CLASS_DECL_AURA DBFileSystemSizeSet :
   virtual public ::object
{
public:


   file_size_table            m_table;
   index                     m_iMaxIteration;


   DBFileSystemSizeSet(::layered * pobjectContext);
   ~DBFileSystemSizeSet();



   bool get_cache_fs_size(i64 & i64Size, const char * pszPath, bool & bPending);
   bool get_fs_size(i64 & i64Size, const char * pszPath, bool & bPending);


   bool get_fs_size(i64 & i64Size, const char * pszPath, bool & bPending, index & iIteration);


};





class CLASS_DECL_AURA FileSystemSizeServerThread :
   virtual public thread
{
public:

   FileSystemSizeServerThread(::layered * pobjectContext);

   bool initialize_thread() override;

};




class CLASS_DECL_AURA FileSystemSizeWnd :
   public ::user::interaction_impl *,
   public ::object
{
public:


   class size_map :
      public string_map < file_size_table::get_fs_size, file_size_table::get_fs_size >
   {
   public:
   };


   millis m_millisLastStartTime;
   bool                             m_bServer;
   file_size_table::get_fs_size     m_size;
   bool                             m_bRet;
   critical_section                 m_criticalsection;
   array < file_size_table::get_fs_size, file_size_table::get_fs_size & > m_sizea;

   size_map                         m_map;


   FileSystemSizeWnd(::layered * pobjectContext);

   bool CreateClient();
   bool CreateServer();



   void ClientStartServer();
   bool get_fs_size(i64 & i64Size, const char * pszPath, bool & bPending);

   void install_message_routing(::channel * pchannel);

   DECL_GEN_SIGNAL(_001OnCopyData);
   void _001OnTimer(::timer * ptimer);


};


