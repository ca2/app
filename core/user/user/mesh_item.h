#pragma once


#include "acme/exception/status.h"
#include "acme/primitive/collection/int_map.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
// #include "acme/primitive/string/string.h"
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
      ::index                       m_iSubItem;
      ::index                       m_iOrder;
      ::index                       m_iImage;
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
      ::rectangle_i32                           m_rectangleSubItem;
      ::rectangle_i32                           m_rectangleImage;
      ::rectangle_i32                           m_rectangleText;

      //index                               m_iSubItemRectItem;
      //index                               m_iSubItemRectSubItem;
      //index                               m_iSubItemRectOrder;
      //index                               m_iSubItemRectColumn;

      ::index                                   m_iRectangleOrder;


      draw_mesh_subitem();


      void initialize_draw_mesh_subitem(mesh_item * pmeshitem);


      ::pointer<::image_list>get_image_list();
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
      index                                     m_iItem;
      index                                     m_iDisplayItem;
      //index                                     m_iSubItem;
      ::index_map < ::pointer<mesh_subitem >>  m_mapSubItem;
//      index                                   m_iListItem;
      i32                                       m_iState;
      bool                                      m_bOk;

      index                                     m_iGroupTopDisplayIndex;
      ::count                                   m_iGroupCount;

      mesh_item();

      void initialize_mesh_item(mesh * pmesh);

      ::index item_index() const { return (::index) m_iItem; }
      //::index subitem_index() const { return (::index) m_iSubItem; }
      //::index list_item_index() const { return (::index) m_iListItem; }

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
      // ::rectangle_i32                     m_rectangleGroup;
      ::rectangle_i32                     m_rectangleItem;
      //::rectangle_i32                     m_rectangleListItem;
      rectangle_i32 *                     m_prectClient;

      status < ::color::color >           m_colorItemBackground;

      //index                               m_iItemRectItem;

      ::index                             m_iRectangleDisplayItem;

      i32                                 m_iColumnWidth;



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
      index                                     m_iGroup;
      index                                     m_iItem;
      //index                                     m_iDisplayItem;
      //index                                     m_iSubItem;
      //::index_map < ::pointer<mesh_subitem >>  m_mapSubitem;
      //      index                                   m_iListItem;
      ::index                                   m_iImage;
      i32                                       m_iState;
      bool                                      m_bOk;

      index                                     m_iGroupTopDisplayIndex;
      ::count                                   m_iGroupCount;

      mesh_group();

      void initialize_mesh_group(mesh * pmesh);

      ::index group_index() const { return (::index)m_iGroup; }
      //::index subitem_index() const { return (::index) m_iSubItem; }
      //::index list_item_index() const { return (::index) m_iListItem; }

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
       ::rectangle_i32                    m_rectangleGroup;
      //::rectangle_i32                   m_rectangleItem;
      //::rectangle_i32                   m_rectangleListItem;
      ::rectangle_i32                     m_rectangleImage;
      ::rectangle_i32                     m_rectangleText;
      rectangle_i32 * m_prectClient;

      ::write_text::font * m_pfont;
      ::e_align                           m_ealign;
      ::e_draw_text                       m_edrawtext;

      index                               m_iGroupRectGroup;

      //index                               m_iItemRectItem;

      //i32                                 m_iColumnWidth;

      //index                               m_iSubItemRectItem;
      //index                               m_iSubItemRectSubItem;
      //index                               m_iSubItemRectOrder;
      //index                               m_iSubItemRectColumn;


      //index                               m_iListItemRectItem;
      //index                               m_iListItemRectSubItem;
      //index                               m_iListItemRectListItem;



      draw_mesh_group();


      void initialize_draw_mesh_group(mesh * pmesh);


      //::pointer<::image_list>get_image_list();
      //bool draw_image();
      void draw_group_image();
      void update_group_color();
      void set_text_color();
      void draw_text();


      ::user::enum_state get_user_state() const;


   };


} // namespace user



