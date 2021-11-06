#pragma once


namespace user
{




   class CLASS_DECL_CORE mesh_item :
      virtual public ::matter
   {
   public:


      list_item *                            m_plistitem;
      mesh *                                 m_pmesh;
      index                                  m_iGroup;
      index                                  m_iItem;
      index                                  m_iDisplayItem;
      index                                  m_iColumn;
      index                                  m_iOrder;
      index                                  m_iSubItem;
      index                                  m_iListItem;
      string                                 m_strText;
      status < ::color::color >       m_colorText;
      status < ::color::color >       m_colorTextBackground;
      status < ::color::color >       m_colorItemBackground;
      i32                                    m_iState;
      index                                  m_iImage;
      bool                                   m_bOk;

      index          m_iGroupTopDisplayIndex;
      ::count        m_iGroupCount;

      mesh_item(mesh * pmesh);

      ::index item_index() const { return (::index) m_iItem; }
      ::index subitem_index() const { return (::index) m_iSubItem; }
      ::index list_item_index() const { return (::index) m_iListItem; }

   };


   class CLASS_DECL_CORE draw_mesh_item :
      virtual public mesh_item,
      virtual public ::aura::draw_context
   {
   public:


      ::rectangle_i32                     m_rectangleGroup;
      ::rectangle_i32                     m_rectangleItem;
      ::rectangle_i32                     m_rectangleSubItem;
      ::rectangle_i32                     m_rectangleListItem;
      ::rectangle_i32                     m_rectangleImage;
      ::rectangle_i32                     m_rectangleText;
      rectangle_i32 *                     m_prectClient;


      index                      m_iGroupRectGroup;

      index                      m_iItemRectItem;

      i32                        m_iColumnWidth;

      index                      m_iSubItemRectItem;
      index                      m_iSubItemRectSubItem;
      index                      m_iSubItemRectOrder;
      index                      m_iSubItemRectColumn;


      index                      m_iListItemRectItem;
      index                      m_iListItemRectSubItem;
      index                      m_iListItemRectListItem;

      ::write_text::font *           m_pfont;
      ::e_align                  m_ealign;
      ::e_draw_text              m_edrawtext;


      draw_mesh_item(mesh * pmesh);


      __pointer(::image_list) get_image_list();
      bool draw_image();
      bool draw_group_image();
      void update_item_color();
      void set_text_color();
      void draw_text();


      ::user::enum_state get_user_state() const;


   };



} // namespace user



