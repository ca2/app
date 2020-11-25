#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE main_view:
      virtual public ::user::split_view,
      virtual public impact
   {
   public:


      
      file_list *                            m_pfilelist;
      preview *                              m_ppreview;
      __composite(file_properties_form)      m_ppropform;
      ::file::item_array                     m_itema;


      main_view();
      virtual ~main_view();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_create_split_impact() override;

      void FileManagerBrowse(const char * pcwstr, const ::action_context & action_context);


      virtual void on_command(::user::command * pcommand) override;

      virtual void OpenSelectionProperties();

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;


   };


} // namespace filemanager




