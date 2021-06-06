


namespace axis
{


   class CLASS_DECL_AXIS system:
      virtual public ::aura::system
   {
   public:


      system();
      virtual ~system();


      virtual ::e_status  initialize_system(::object * pobject, app_core * pappcore) override;

      virtual ::e_status init() override;
      //virtual ::e_status init_instance() override;
      //virtual void term_instance() override;

      virtual ::e_status init_system() override;
      virtual void term_system() override;

      virtual void term() override;

      //::url::department                           & url()     { return m_urldepartment; }



      //virtual string install_get_platform() override;
      //virtual void install_set_platform(const char * pszPlatform) override;
      //virtual string install_get_version() override;
      //virtual void install_set_version(const char * pszVersion) override;
      //virtual string install_get_latest_build_number(const char * pszVersion) override;
      //virtual i32 install_start(const char * pszCommandLine, const char * pszBuild) override;
      //virtual i32 install_progress_app_add_up(int iAddUp = 1) override;

      //virtual ::install::canvas * install_create_canvas();
      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle & rectangle);
      //virtual int install_canvas_increment_mode();

      //virtual string install_get_platform() override;
      //virtual void install_set_platform(const char * pszPlatform) override;
      //virtual string install_get_version() override;
      //virtual void install_set_version(const char * pszVersion) override;
      //virtual string install_get_latest_build_number(const char * pszVersion) override;
      //virtual i32 install_start(const char * pszCommandLine,const char * pszBuild) override;
      //virtual i32 install_progress_app_add_up(int iAddUp = 1) override;

      virtual ::e_status process_init() override;

      virtual ::e_status init1() override;

      virtual ::e_status init2() override;


      virtual ::e_status verb() override; // ambigous inheritance from ::aura::system/::axis::application


      virtual bool is_system() const override;


      virtual string crypto_md5_text(const string & str) override;


      virtual ::e_status create_html();

      //virtual __pointer(::aura::session) on_create_session() override;

      virtual void on_request(::create * pcreate) override;

      //virtual void construct(const char * pszAppId);

      //virtual bool initialize_application() override;

      //virtual i32 exit_instance();
      //virtual bool finalize();






      //virtual bool verb();





      //virtual bool process_initialize();

      //virtual bool process_init();

      //virtual bool init1();

      //virtual bool init2();

      //virtual bool is_system();






      //virtual ::aura::session * query_session(index iEdge) override;




      //virtual string dir_appmatter_locator(::object * pobject);


      virtual void hist_hist(const char * psz);


      //virtual void on_request(::create * pcreate);


      //virtual u32 crc32(u32 dwPrevious, const char * psz);


      virtual string url_encode(const string & str) override;

   };


} // namespace axis







void CLASS_DECL_AXIS __start_system(::axis::system * psystem);




