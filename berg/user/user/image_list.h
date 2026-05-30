#pragma once


//#include "acme/platform/timer_array.h"
#include "aura/user/user/scroll_base.h"
#include "margin.h"
#include "show.h"


namespace user
{


   class CLASS_DECL_BERG image_list :
      virtual public ::user::scroll_base
   {
   public:


      ::i32                                 m_iTextHeight;
      ::i32                                 m_iMargin;
      bool                                m_bLabel;
      ::i32                               m_iLabelHeight;
      ::e_align                           m_ealign;
      string_to_string_base                    m_mapName;

      ::pointer<::image::image_array>     m_pimagea;
      ::pointer<::image::image_array>     m_pimageaThumb;

      index_array                         m_iaSel;
      //::item                            m_itemLButtonDown;
      ::i32_size                          m_size;
      bool                                m_bMultiSel;
      ::i32_size                          m_sizeImage;
      //::i32_rectangle                   m_rectangleTotal;


      image_list();
      ~image_list() override;


      ::item_pointer on_hit_test(const ::i32_point & point, ::user::e_zorder ezorder) override;

      //virtual bool get_rect(::item & item) override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      virtual bool _001GetItemText(string & str, ::collection::index iItem);

      virtual void update_data(bool bSaveAndValidate) override;


#ifdef _DEBUG

      ::i64 increment_reference_count() override
      {
         return ::object::increment_reference_count();
      }
      ::i64 decrement_reference_count() override
      {
         return ::object::decrement_reference_count();
      }

#endif

      void install_message_routing(::channel * pchannel) override;

      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual ::image::image *get_current_image();

      virtual string get_current_image_link();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      bool on_click(::item * pitem, ::user::mouse * pmouse) override;

      ::item_pointer current_item() override;

      index_array get_selection();

      void set_current_item(::collection::index iFind, const ::action_context & action_context);

      void set_selection(const index_array & ia, const ::action_context & action_context);


   };


   class CLASS_DECL_BERG image_list_impact :
      virtual public show < margin < ::user::image_list > >
   {
   public:


      image_list_impact();
      ~image_list_impact() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

#ifdef _DEBUG
      ::i64 increment_reference_count() override
      {
         return ::object::increment_reference_count();
      }
      ::i64 decrement_reference_count() override
      {
         return ::object::decrement_reference_count();
      }
#endif

      void install_message_routing(::channel * pchannel) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;



      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);


      //virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace user


