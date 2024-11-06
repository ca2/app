#pragma once


#include "acme/exception/status.h"
#include "acme/prototype/collection/int_map.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"

#include "aura/platform/draw_context2.h"


namespace user
{

   class mesh_subitem;
   class draw_mesh_subitem;
   class list_subitem;
   class draw_list_subitem;

   class mesh_item;
   class draw_mesh_item;
   class list_item;
   class draw_list_item;

   class mesh_group;
   class draw_mesh_group;
   class list_group;
   class draw_list_group;

   class CLASS_DECL_CORE mesh_subitem :
      virtual public ::particle
   {
   public:


      ::pointer<mesh_item>         m_pitem;


      draw_mesh_subitem *           m_pdrawmeshsubitem;
      list_subitem *                m_plistsubitem;
      draw_list_subitem *           m_pdrawlistsubitem;

      ::pointer<mesh_item>         m_pmeshitem;
      ::collection::index                       m_iSubItem;
      ::collection::index                       m_iOrder;
      ::collection::index                       m_iImage;
      ::pointer<list_column>       m_pcolumn;


      bool                          m_bOk;

      string                        m_strText;


      mesh_subitem();


      void initialize_mesh_subitem(mesh_item * pmeshitem);


      operator mesh_subitem * () { return this; }
      operator draw_mesh_subitem * () { return  m_pdrawmeshsubitem; }
      operator list_subitem * () { return  m_plistsubitem; }
      operator draw_list_subitem * () { return m_pdrawlistsubitem; }


   };


   
   class CLASS_DECL_CORE draw_mesh_subitem :
      virtual public mesh_subitem
   {
   public:


      status < ::color::color >                 m_colorText;
      status < ::color::color >                 m_colorTextBackground;
      status < ::color::color >                 m_colorSubItemBackground;
      ::int_rectangle                           m_rectangleSubItem;
      ::int_rectangle                           m_rectangleImage;
      ::int_rectangle                           m_rectangleText;

      //index                               m_iSubItemRectItem;
      //index                               m_iSubItemRectSubItem;
      //index                               m_iSubItemRectOrder;
      //index                               m_iSubItemRectColumn;

      ::collection::index                                   m_iRectangleOrder;


      draw_mesh_subitem();


      void initialize_draw_mesh_subitem(mesh_item * pmeshitem);


      ::image::image_list_pointer get_image_list();
      bool draw_image();
      void update_color();
      // void draw_group_image();
      void set_text_color();
      void draw_text();



   };


   class CLASS_DECL_CORE mesh_item :
      virtual public ::particle
   {
   public:


      draw_mesh_item *                          m_pdrawmeshitem;
      list_item *                               m_plistitem;
      draw_list_item *                          m_pdrawlistitem;


      mesh *                                    m_pmesh;
      //index                                     m_iGroup;
      ::collection::index                                     m_iItem;
      ::collection::index                                     m_iDisplayItem;
      //index                                     m_iSubItem;
      ::index_map < ::pointer<mesh_subitem >>  m_mapSubItem;
//      index                                   m_iListItem;
      int                                       m_iState;
      bool                                      m_bOk;

      ::collection::index                                     m_iGroupTopDisplayIndex;
      ::collection::count                                   m_iGroupCount;

      mesh_item();

      void initialize_mesh_item(mesh * pmesh);

      ::collection::index item_index() const { return (::collection::index) m_iItem; }
      //::collection::index subitem_index() const { return (::collection::index) m_iSubItem; }
      //::collection::index list_item_index() const { return (::collection::index) m_iListItem; }

      operator mesh_item * () { return this; }
      operator draw_mesh_item * () { return  m_pdrawmeshitem; }
      operator list_item * () { return  m_plistitem; }
      operator draw_list_item * () { return m_pdrawlistitem; }


   };


   class CLASS_DECL_CORE draw_mesh_item :
      virtual public mesh_item,
      virtual public ::aura::draw_context
   {
   public:


      class ::time                        m_timeLastDraw;
      // ::int_rectangle                     m_rectangleGroup;
      ::int_rectangle                     m_rectangleItem;
      //::int_rectangle                     m_rectangleListItem;
      int_rectangle *                     m_prectClient;

      status < ::color::color >           m_colorItemBackground;

      //index                               m_iItemRectItem;

      ::collection::index                             m_iRectangleDisplayItem;

      int                                 m_iColumnWidth;



      //index                               m_iListItemRectItem;
      //index                               m_iListItemRectSubItem;
      //index                               m_iListItemRectListItem;

      ::write_text::font *                m_pfont;
      ::e_align                           m_ealign;
      ::e_draw_text                       m_edrawtext;


      draw_mesh_item();


      void initialize_draw_mesh_item(mesh * pmesh);


      //void update_item_color();


      ::user::enum_state get_user_state() const;


   };



   class CLASS_DECL_CORE mesh_group :
      virtual public ::particle
   {
   public:


      draw_mesh_group * m_pdrawmeshgroup;
      list_group* m_plistgroup;
      draw_list_group * m_pdrawlistgroup;


      mesh * m_pmesh;
      ::collection::index                                     m_iGroup;
      ::collection::index                                     m_iItem;
      //index                                     m_iDisplayItem;
      //index                                     m_iSubItem;
      //::index_map < ::pointer<mesh_subitem >>  m_mapSubitem;
      //      index                                   m_iListItem;
      ::collection::index                                   m_iImage;
      int                                       m_iState;
      bool                                      m_bOk;

      ::collection::index                                     m_iGroupTopDisplayIndex;
      ::collection::count                                   m_iGroupCount;

      mesh_group();

      void initialize_mesh_group(mesh * pmesh);

      ::collection::index group_index() const { return (::collection::index)m_iGroup; }
      //::collection::index subitem_index() const { return (::collection::index) m_iSubItem; }
      //::collection::index list_item_index() const { return (::collection::index) m_iListItem; }

      operator mesh_group * () { return this; }
      operator draw_mesh_group * () { return  m_pdrawmeshgroup; }
      operator list_group * () { return  m_plistgroup; }
      operator draw_list_group * () { return m_pdrawlistgroup; }


   };


   class CLASS_DECL_CORE draw_mesh_group :
      virtual public mesh_group,
      virtual public ::aura::draw_context
   {
   public:


      class ::time                        m_nanoLastDraw;
       ::int_rectangle                    m_rectangleGroup;
      //::int_rectangle                   m_rectangleItem;
      //::int_rectangle                   m_rectangleListItem;
      ::int_rectangle                     m_rectangleImage;
      ::int_rectangle                     m_rectangleText;
      int_rectangle * m_prectClient;

      ::write_text::font * m_pfont;
      ::e_align                           m_ealign;
      ::e_draw_text                       m_edrawtext;

      ::collection::index                               m_iGroupRectGroup;

      //index                               m_iItemRectItem;

      //int                                 m_iColumnWidth;

      //index                               m_iSubItemRectItem;
      //index                               m_iSubItemRectSubItem;
      //index                               m_iSubItemRectOrder;
      //index                               m_iSubItemRectColumn;


      //index                               m_iListItemRectItem;
      //index                               m_iListItemRectSubItem;
      //index                               m_iListItemRectListItem;



      draw_mesh_group();


      void initialize_draw_mesh_group(mesh * pmesh);


      //::image::image_list_pointer get_image_list();
      //bool draw_image();
      void draw_group_image();
      void update_group_color();
      void set_text_color();
      void draw_text();


      ::user::enum_state get_user_state() const;


   };


} // namespace user



