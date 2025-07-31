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
      long long  m_iSize;
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
      long long     m_iSize;
      ::collection::index       m_iStep;
      bool        m_bDir;
      bool        m_bPendingLs;

      pointer_array < item >   m_itema;


      item();


      void update_size(::particle * pparticle, ::collection::index & iIteration);
      void update_size_recursive(::particle * pparticle, ::collection::index & iIteration);

      item * FindItem(::particle * pparticle, const ::scoped_string & scopedstrPath, ::collection::index & iIteration);
      ::collection::index FindName(::particle * pparticle, const ::scoped_string & scopedstrName, ::collection::index & iIteration);

      string path();

      void ls(::particle * pparticle, ::collection::index & iIteration);
   };



   item                    m_item;
   HANDLE                  m_hmap;
   class get_fs_size *     m_pgetfssize;
   FileSystemSizeWnd *     m_puserinteraction;
   FileSystemSizeWnd *     m_puserinteractionServer;
   oswindow                    m_oswindowServer;
   ::happening *               m_pevExec;
   ::happening *               m_pevDone;
   ::pointer< ::mutex >               mutex();





   file_size_table(::particle * pparticle);
   ~file_size_table();

   bool check_map();

};



class CLASS_DECL_AURA DBFileSystemSizeSet :
   virtual public ::object
{
public:


   file_size_table            m_table;
   ::collection::index                     m_iMaxIteration;


   DBFileSystemSizeSet(::particle * pparticle);
   ~DBFileSystemSizeSet();



   bool get_cache_fs_size(long long & i64Size, const ::scoped_string & scopedstrPath, bool & bPending);
   bool get_fs_size(long long & i64Size, const ::scoped_string & scopedstrPath, bool & bPending);


   bool get_fs_size(long long & i64Size, const ::scoped_string & scopedstrPath, bool & bPending, ::collection::index & iIteration);


};





class CLASS_DECL_AURA FileSystemSizeServerThread :
   virtual public thread
{
public:

   FileSystemSizeServerThread(::particle * pparticle);

   bool initialize_thread() override;

};




class CLASS_DECL_AURA FileSystemSizeWnd :
   public ::windowing::window *,
   public ::object
{
public:


   class size_map :
      public string_map < file_size_table::get_fs_size, file_size_table::get_fs_size >
   {
   public:
   };


   class ::time m_timeLastStartTime;
   bool                             m_bServer;
   file_size_table::get_fs_size     m_size;
   bool                             m_bRet;
   critical_section                 m_criticalsection;
   array < file_size_table::get_fs_size, file_size_table::get_fs_size & > m_sizea;

   size_map                         m_map;


   FileSystemSizeWnd(::particle * pparticle);

   bool CreateClient();
   bool CreateServer();



   void ClientStartServer();
   bool get_fs_size(long long & i64Size, const ::scoped_string & scopedstrPath, bool & bPending);

   void install_message_routing(::channel * pchannel);

   DECLARE_MESSAGE_HANDLER(_001OnCopyData);
   void on_timer(::timer * ptimer);


};


