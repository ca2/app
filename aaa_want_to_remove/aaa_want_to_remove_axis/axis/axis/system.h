


namespace axis
{


   class CLASS_DECL_AXIS system:
      virtual public ::aura::system
   {
   public:


      system();
      virtual ~system();


      virtual void  initialize_system(::particle * pparticle, app_core * pappcore) override;

      virtual void init() override;
      //virtual void init_instance() override;
      //virtual void term_instance() override;

      virtual void init_system() override;
      virtual void term_system() override;

      virtual void term() override;

      //::url::department                           & url()     { return m_urldepartment; }



      //virtual string install_get_platform() override;
      //virtual void install_set_platform(const ::string & pszPlatform) override;
      //virtual string install_get_version() override;
      //virtual void install_set_version(const ::string & pszVersion) override;
      //virtual string install_get_latest_build_number(const ::string & pszVersion) override;
      //virtual i32 install_start(const ::string & pszCommandLine, const ::string & pszBuild) override;
      //virtual i32 install_progress_app_add_up(int iAddUp = 1) override;

      //virtual ::install::canvas * install_create_canvas();
      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle & rectangle);
      //virtual int install_canvas_increment_mode();

      //virtual string install_get_platform() override;
      //virtual void install_set_platform(const ::string & pszPlatform) override;
      //virtual string install_get_version() override;
      //virtual void install_set_version(const ::string & pszVersion) override;
      //virtual string install_get_latest_build_number(const ::string & pszVersion) override;
      //virtual i32 install_start(const ::string & pszCommandLine, const ::string & pszBuild) override;
      //virtual i32 install_progress_app_add_up(int iAddUp = 1) override;

      virtual void process_init() override;

      virtual void init1() override;

      virtual void init2() override;


      virtual void verb() override; // ambigous inheritance from ::aura::system/::axis::application


      virtual bool is_system() const override;


      virtual string crypto_md5_text(const ::string & str) override;


      virtual void create_html();

      //virtual ::pointer<::aura::session>on_create_session() override;

      virtual void on_request(::request * prequest) override;

      //virtual void construct(const ::string & pszAppId);

      //virtual bool initialize_application() override;

      //virtual i32 exit_instance();
      //virtual bool destroy();






      //virtual bool verb();





      //virtual bool process_initialize();

      //virtual bool process_init();

      //virtual bool init1();

      //virtual bool init2();

      //virtual bool is_system();






      //virtual ::aura::session * query_session(index iEdge) override;




      //virtual string dir_appmatter_locator(::particle * pparticle);


      virtual void hist_hist(const ::string & psz);


      //virtual void on_request(::request * prequest) override;


      //virtual u32 crc32(u32 dwPrevious, const ::string & psz);


      virtual string url_encode(const ::string & str) override;

   };


} // namespace axis







void CLASS_DECL_AXIS __start_system(::axis::system * psystem);




