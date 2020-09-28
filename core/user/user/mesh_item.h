#pragma once


namespace user
{




   class CLASS_DECL_CORE mesh_item :
      virtual public ::elemental
   {
   public:

      list_item *             m_plistitem;
      mesh *                  m_pmesh;
      index           m_iGroup;
      index           m_iItem;
      index           m_iDisplayItem;
      index           m_iColumn;
      index           m_iOrder;
      index           m_iSubItem;
      index           m_iListItem;
      string                  m_strText;
      COLORREF                m_crText;
      COLORREF                m_crTextBackground;
      COLORREF                m_crItemBackground;
      i32                     m_iState;
      index           m_iImage;
      bool                    m_bOk;

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


      ::rect                     m_rectGroup;
      ::rect                     m_rectItem;
      ::rect                     m_rectSubItem;
      ::rect                     m_rectListItem;
      ::rect                     m_rectImage;
      ::rect                     m_rectText;
      rect *                     m_prectClient;


      index              m_iGroupRectGroup;

      index              m_iItemRectItem;

      i32                        m_iColumnWidth;

      index              m_iSubItemRectItem;
      index              m_iSubItemRectSubItem;
      index              m_iSubItemRectOrder;
      index              m_iSubItemRectColumn;


      index              m_iListItemRectItem;
      index              m_iListItemRectSubItem;
      index              m_iListItemRectListItem;

      ::draw2d::font *           m_pfont;
      int                        m_iDrawTextFlags;


      draw_mesh_item(mesh * pmesh);


      __pointer(::image_list) get_image_list();
      bool draw_image();
      bool draw_group_image();
      void update_item_color();
      void set_text_color();
      void draw_text();


      ::user::estate get_user_state() const;


   };



} // namespace user



