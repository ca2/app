#pragma once


#include "acme/platform/timer_array.h"
#include "aura/user/user/box.h"
#include "margin.h"
#include "show.h"


namespace user
{


   class CLASS_DECL_BASE image_list :
      virtual public ::user::box
   {
   public:


      int                     m_iTextHeight;
      bool                    m_bNoName;
      int                     m_iPad;
      ::e_align               m_ealign;
      string_to_string        m_mapName;

      ::pointer<image_array> m_pimagea;
      ::pointer<image_array> m_pimageaThumb;

      index_array             m_iaSel;
      //::item                m_itemLButtonDown;
      ::size_i32              m_size;
      bool                    m_bMultiSel;
      ::size_i32              m_sizeImage;


      image_list();
      ~image_list() override;


      ::item_pointer on_hit_test(const ::point_i32 & point) override;

      //virtual bool get_rect(::item & item) override;

//      void assert_ok() const override;
//      void dump(dump_context & dumpcontext) const override;

      virtual bool _001GetItemText(string & str, index iItem);

      virtual void update_data(bool bSaveAndValidate) override;


#ifdef _DEBUG

      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }

#endif

      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual image * get_current_image();

      virtual string get_current_image_link();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      virtual bool on_click(::item * pitem) override;

      ::item_pointer current_item() override;

      index_array _001GetSelection();

      void set_current_item(index iFind, const ::action_context & action_context);

      void _001SetSelection(const index_array & ia, const ::action_context & action_context);


   };


   class CLASS_DECL_BASE image_list_impact :
      virtual public show < margin < ::user::image_list > >
   {
   public:


      image_list_impact();
      ~image_list_impact() override;


//      void assert_ok() const override;
//      void dump(dump_context & dumpcontext) const override;

#ifdef _DEBUG
      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
#endif

      void install_message_routing(::channel * pchannel) override;

      void handle(::topic * ptopic, ::context * pcontext) override;



      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);


   };


} // namespace user


