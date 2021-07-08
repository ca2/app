#pragma once


namespace user
{


   class CLASS_DECL_BASE image_list :
      virtual public ::user::box
   {
   public:


      int                     m_iTextHeight;
      bool                    m_bNoName;
      int                     m_iPad;
      ::e_align                 m_ealign;
      string_to_string        m_mapName;

      image_array             m_imagea;
      image_array             m_imageaThumb;

      index_array             m_iaSel;
      //::user::item            m_itemLButtonDown;
      ::size_i32                  m_size;
      bool                    m_bMultiSel;
      ::size_i32                  m_sizeImage;


      image_list();
      virtual ~image_list();


      virtual void on_hit_test(::user::item & item) override;

      virtual bool get_rect(::user::item & item) override;



      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual bool _001GetItemText(string & str, index iItem);

      virtual bool update_data(bool bSaveAndValidate) override;


#ifdef DEBUG

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
      {
         return ::object::add_ref(OBJ_REF_DBG_ARGS);
      }
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
      {
         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      }

#endif

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual image * get_current_image();

      virtual string get_current_image_link();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      virtual bool on_click(const ::user::item & item) override;

      virtual ::user::item current_item() override;

      index_array _001GetSelection();

      void set_current_item(index iFind, const ::action_context & action_context);

      void _001SetSelection(const index_array & ia, const ::action_context & action_context);


   };


   class CLASS_DECL_BASE image_list_view :
      virtual public show < margin < ::user::image_list > >
   {
   public:


      image_list_view();
      virtual ~image_list_view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

#ifdef DEBUG
      virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
      {
         return ::object::add_ref(OBJ_REF_DBG_ARGS);
      }
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
      {
         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      }
#endif

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;



      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);


   };


} // namespace user


