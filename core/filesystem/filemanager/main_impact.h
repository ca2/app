#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE main_impact:
      virtual public ::filemanager_show < ::user::split_view >
   {
   public:


      
      file_list *                            m_pfilelist;
      preview *                              m_ppreview;
      __composite(file_properties_form)      m_ppropform;
      ::file::item_array                     m_itema;


      main_impact();
      virtual ~main_impact();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_create_split_impact() override;

      void FileManagerBrowse(const ::string & pcwstr, const ::action_context & action_context);


      virtual void on_command(::message::command * pcommand) override;

      virtual void OpenSelectionProperties();

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


   };


} // namespace filemanager




