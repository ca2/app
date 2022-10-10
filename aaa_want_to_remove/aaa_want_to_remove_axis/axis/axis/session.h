#pragma once


namespace axis
{


   class CLASS_DECL_AXIS session:
      virtual public ::aura::session
   {
   public:


      ::pointer<::userpresence::department>                m_puserpresence;


      ::pointer<::ftpfs>                                 m_pftpfs;
      ::pointer<::fs::remote_native>                     m_premotefs;
      ::pointer<::fs::fs>                                m_pfs;
      ::pointer<::fs::data>                              m_pfsdata;
      ::pointer<::ifs>                                   m_pifs;
      //ke
      bool                                                  m_bIfs;

      bool                                                  m_bMatterFromHttpCache;

      ::u32                                                 m_dwLongPhRESSingTime;


      session();
      virtual ~session();


      virtual void     initialize(::object * pobject) override;

      inline ::userpresence::department & userpresence() { return *m_puserpresence; }

      virtual bool is_session() const override;

      //void construct(::object * pobject, int iPhase) override;

      virtual void process_init() override;

      virtual void init1() override;

      virtual void init2() override;

      virtual void init_session() override;

      virtual void init() override;

      virtual void term() override;

      virtual void term_session() override;


      inline class ::fs::data * fs() { return m_pfsdata; }
      
      
      //inline ::sockets::sockets & sockets() { return *m_psockets; }


      virtual size get_window_minimum_size() override;


      //virtual void  get_cursor_position(POINT32 * ppoint);



      virtual void on_request(::create * pcreate) override;


      //virtual string matter_as_string(const ::string & pszMatter, const ::string & pszMatter2);
      //virtual string dir().matter(const ::string & pszMatter, const ::string & pszMatter2);

      //virtual bool is_inside_time_dir(const ::string & pszPath);
      //virtual bool file_is_read_only(const ::string & pszPath);

      // Long PhRESSing time
      // time in ::durations that a pressing is considered a double click
      virtual ::u32 get_Long_PhRESSing_time();

      virtual void defer_initialize_user_presence() override;

      //virtual void     interactive_credentials(::account::credentials * pcredentials) override;

      virtual bool on_create_frame_window() override;

      //virtual string account_get_user_sessid(const ::string & str) override;

      virtual void translate_os_key_message(::user::key * pkey) override;

      virtual void on_user_logon(::account::user * puser) override;


   };


} // namespace axis



