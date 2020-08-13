#pragma once



namespace simple_shader
{


   class CLASS_DECL_APP_SHADER application :
      virtual public ::aura::application
   {
   public:


      ::enum_check &                         m_echeckSimple;
      ::enum_check &                         m_echeckNoClientFrame;
      string &                               m_strSimple;

      bool                                   m_bMultiverseChat;

      ::user::document *                     m_pdocMenu;
      ::user::plain_edit_view *              m_prollfps;
      __composite(window)                    m_pwindow;

      string                                 m_strMainTitle;


      application();
      virtual ~application();

      virtual string preferred_experience() override;
      virtual ::estatus init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::create * pcreate) override;

#ifdef DEBUG
      virtual int64_t add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual int64_t dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif

      virtual string get_main_title() const;
      virtual string get_hover_font() const;


      //DECL_GEN_SIGNAL(_001OnSimpleCheckbox);

      // slowly phase out this idle/poll approach?
      // is it good for later consolidated evaluation?
      // is this "consolidated" evaluation the only advantage?
      // can it be replaced by custom-on-demand delayed consolidated active update when it is proper to do so?
      // isn't it taking this "_001OnUpdate" approach (and assuming this single advantage) builtin
      // early optimization with the cost of idle update? (is it really a optimization if the update is
      // done through idle/polled evaluation)?
      //DECL_GEN_SIGNAL(_001OnUpdateSimpleCheckbox);


      virtual ::id translate_property_id(const ::id& id) override;
   };


} // namespace simple_shader



