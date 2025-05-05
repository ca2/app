#pragma once


#include "acme/prototype/collection/raw_pointer_array.h"
#include "aura/user/user/scroll_base.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "core/user/user/tree_data.h"

class image_list;


namespace user
{


   class CLASS_DECL_CORE tree :
      virtual public ::user::scroll_base
   {
   public:


      //int_size                                m_sizeTotal;
      ::e_align                                                m_ealignText;
      ::e_draw_text                                            m_edrawtext;
      ::pointer < ::user::tree_data_base >                     m_ptreedata;
      ::pointer_array < ::user::tree_data_base >               m_treeaBound;
      ::pointer < ::pointer_array <::data::tree_item_base > >  m_ptreeitemptraSelected;
      ::data::tree_item_base *                                 m_ptreeitemHover;

      ::pointer<::draw2d::graphics_extension>                  m_pgraphicsextension;
      ::collection::index                                      m_dwFirstVisibleItem;
      ::collection::index                                      m_iItemCount;
      unsigned int                                             m_uiLButtonUpFlags;
      int_point                                                m_pointLButtonUp;
      ::pointer < ::data::tree_item_base >                     m_ptreeitemFirstVisible;
      ::collection::index                                      m_iFirstVisibleItemProperIndex;
      int                                                      m_iCurrentImpactWidth;
      ::int_size                                               m_sizeItemMaximum;
      //::color::color                                         m_colorTextSelected;
      //::color::color                                         m_colorTextHighlight;
      //::color::color                                         m_colorTextSelectedHighlight;
      unsigned_int_array                                       m_dwaItemState;
      ::image::image_list_pointer                              m_pimagelist;
      ::collection::index                                      m_iImageCollapse;
      ::collection::index                                      m_iImageExpand;
      ::collection::index                                      m_iImageCollapseDark;
      ::collection::index                                      m_iImageExpandDark;
      ::draw2d::brush_pointer                                  m_pbrushTextSelected;
      ::draw2d::brush_pointer                                  m_pbrushTextSelectedHighlight;
      ::draw2d::brush_pointer                                  m_pbrushTextHighlight;
      ::draw2d::brush_pointer                                  m_pbrushText;
      ::write_text::font_pointer                               m_pfontTreeItem;
      status < ::color::color >                                m_colorTreeBackground;

      bool                                                     m_bPendingDrawingObjectsUpdate;

      bool                                                     m_bHover;
      class ::time                                             m_timeHoverStart;
      int                                                      m_iHoverAlpha;
      int                                                      m_iHoverAlphaInit;
      class ::time                                             m_timeLeaveStart;
      int                                                      m_iLeaveAlphaInit;

      manual_reset_happening                                   m_happeningExpand;
      manual_reset_happening                                   m_happeningOpen;
      raw_pointer_array < ::data::tree_item_base >             m_treeitemaExpand;
      raw_pointer_array < ::data::tree_item_base >             m_treeitemaOpen;



      tree();
      ~tree() override;


      // ::core::application* get_app();
      // ::core::session* get_session();
      // ::core::system* get_system();
      virtual ::data::tree_item_base * tree_item_base(::item * pitem);

      void user_tree_common_construct();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawItem(tree_draw_item & data);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual ::pointer<::data::tree_base>find_data_tree(::data::tree_item_base * ptreeitem) const;
      virtual ::pointer<::data::tree_item_base>find_data_tree_item(::item * pitem, ::collection::index * piIndex = nullptr);
      virtual bool contains(::item * pitem);
      virtual bool contains(::data::tree_item_base * ptreeitem);

      void update_drawing_objects();


      void on_would_change_total_size(::user::enum_layout elayout = ::user::e_layout_sketch) override;


      void _001OnTreeDataChange();
      ::pointer<::data::tree_item_base>CalcFirstVisibleItem(::collection::index & iProperIndex);
      virtual void _001CalculateItemHeight(::draw2d::graphics_pointer & pgraphics);
      virtual int _001CalcCurrentImpactWidth();
      virtual int _001CalcTotalImpactWidth(::draw2d::graphics_pointer & pgraphics);
      virtual int _001CalcTotalImpactHeight();
      void _001SelectItem(::data::tree_item_base * ptreeitem);
      ::collection::count _001GetProperItemCount();
      ::collection::count _001GetVisibleItemCount();
      void _001SetCollapseImage(const ::string & pszMatter);
      void _001SetExpandImage(const ::string & pszMatter);
      void _001SetCollapseImageDark(const ::string & pszMatter);
      void _001SetExpandImageDark(const ::string & pszMatter);
      void update_tree_hover();
      void update_tree_hover(int_point point);
      virtual void _001OnOpenItem(::data::tree_item_base * ptreeitem, const ::action_context & action_context);
      virtual void _001OnItemContextMenu(::data::tree_item_base * ptreeitem, const ::action_context & action_context, ::user::tree * ptree, const ::int_point & point);
      void _001ExpandItem(::data::tree_item_base * ptreeitem, const ::action_context & action_context, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001OnItemExpand(::data::tree_item_base * ptreeitem, const ::action_context & action_context);
      virtual void _001OnItemCollapse(::data::tree_item_base * ptreeitem, const ::action_context & action_context);
      virtual bool _001GetItemElementRect(::int_rectangle * prectangle, tree_draw_item & drawitem, ::user::enum_tree_element eelement);

      void install_message_routing(::channel * pchannel) override;
      virtual double _001GetItemHeight();
      virtual ::collection::index _001GetIndentation();


      ::pointer<::data::tree_item_base>_001HitTest(const ::int_point & point, ::user::enum_tree_element & eelement);

      bool on_click(::item * pitem, ::user::mouse * pmouse) override;

      bool on_right_click(::item * pitem, ::user::mouse * pmouse) override;

      virtual void perform_click();

      virtual void perform_right_click(uptr uFlags, const ::int_point & point);

      virtual int get_wheel_scroll_delta() override;

      //void on_context_offset_layout(::draw2d::graphics_pointer & pgraphics) override;

      void on_change_context_offset(::user::enum_layout elayout) override;

      ::image::image_list_pointer get_image_list();

      
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_up);
      void on_timer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_scroll_y);
      DECLARE_MESSAGE_HANDLER(on_message_scroll_x);
      DECLARE_MESSAGE_HANDLER(_001OnChangeExperience);


      virtual bool      hover(::data::tree_item_base * ptreeitem);
      virtual bool      hover(::item * pitem, ::collection::index i = 0);

      virtual bool      is_hover(const ::data::tree_item_base * ptreeitem) const;
      virtual bool      is_hover(const ::item * pitem) const;


      virtual ::collection::count   clear_selection();




      virtual bool      is_selected(const ::data::tree_item_base * ptreeitem) const;
      virtual bool      is_selected(const ::item * pitem) const;

      virtual ::collection::count   selection_add(::pointer_array <::data::tree_item_base > & itemptra);
      virtual bool      selection_add(::data::tree_item_base * ptreeitem);
      virtual bool      selection_add(::item * pitem, ::collection::index i = 0);

      virtual ::collection::count   selection_set(::pointer_array <::data::tree_item_base > & itemptra);
      virtual bool      selection_set(::data::tree_item_base * ptreeitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(::collection::index iIndex, ::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);

      virtual ::collection::count   selection_erase(::pointer_array <::data::tree_item_base > & itemptra);
      virtual bool      selection_erase(::data::tree_item_base * ptreeitem);
      virtual bool      selection_erase(::item * pitem, ::collection::index i = 0);


      virtual bool      can_merge(const ::user::tree_data_base * ptree) const;
      virtual bool      merge(::user::tree_data_base * ptree, bool bBind);

      virtual ::pointer<::data::tree_item_base>get_proper_item(::collection::index iIndex, ::collection::index * piLevel = nullptr);
      virtual ::pointer<::data::tree_item_base>_get_proper_item(::collection::index iIndex, ::collection::index * piLevel = nullptr, ::collection::index * piCount = nullptr);
      virtual ::collection::index     get_proper_item_index(::data::tree_item_base *pitemParam, ::collection::index * piLevel);
      virtual ::collection::index     get_proper_item_count();

      virtual void      _001EnsureVisible(::data::tree_item_base * ptreeitem);

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      bool keyboard_focus_is_focusable() override;

      //virtual ::double_size get_total_size() override;

      //void on_context_offset(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace user


namespace user
{

   class CLASS_DECL_CORE tree_window :
      virtual public ::user::tree
   {
   public:

      tree_window();
      virtual ~tree_window();

      void install_message_routing(::channel * pchannel) override;
   };

   typedef show < tree > tree_impact;


   template < prototype_item ITEM >
   void tree_data < ITEM >::_001OnOpenItem(::data::tree_item_base * ptreeitembase, const ::action_context & context)
   {

      for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
      {

         m_usertreea[i]->_001OnOpenItem(ptreeitembase, context);

      }

   }

   template < prototype_item ITEM >
   void tree_data < ITEM >::_001OnItemContextMenu(::data::tree_item_base * ptreeitembase, const ::action_context & context, ::user::tree * ptree, const ::int_point & point)
   {

      for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
      {

         m_usertreea[i]->_001OnItemContextMenu(ptreeitembase, context, ptree, point);

      }

   }

   template < prototype_item ITEM >
   void tree_data < ITEM >::_001ExpandItem(::data::tree_item<ITEM> * ptreeitem, const ::action_context & context, bool bExpand, bool bRedraw, bool bLayout)
   {

      for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
      {

         m_usertreea[i]->_001ExpandItem(ptreeitem, context, bExpand, bRedraw, bLayout);

      }

   }





   template < prototype_item ITEM >
   void tree_data < ITEM >::_001EnsureVisible(::data::tree_item<ITEM> * ptreeitem)
   {

      for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
      {

         m_usertreea[i]->_001EnsureVisible(ptreeitem);

      }

   }

   template < prototype_item ITEM >
   void tree_data < ITEM >::_001SelectItem(::data::tree_item<ITEM> * ptreeitem)
   {

      for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
      {

         m_usertreea[i]->_001SelectItem(ptreeitem);

      }

   }
   template < prototype_item ITEM >
   void tree_data < ITEM >::get_selection(::data::tree_item_ptr_array <ITEM> & itemptraSelected) const
   {

      for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
      {

         itemptraSelected.add_unique(*m_usertreea[i]->m_ptreeitemptraSelected);

      }

   }

   template < prototype_item ITEM >
   bool tree_data < ITEM >::is_selected(const ::data::tree_item<ITEM> * ptreeitem) const
   {

      for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
      {

         if (m_usertreea[i]->is_selected(ptreeitem))
         {

            return true;

         }

      }

      return false;

   }


   template < prototype_item ITEM >
   bool tree_data < ITEM >::is_selected(const ITEM * pitem) const
   {

      for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
      {

         if (m_usertreea[i]->is_selected(pitem))
         {

            return true;

         }

      }

      return false;

   }


   template < prototype_item ITEM >
   bool      tree_data < ITEM >::selection_set(::collection::index iIndex, ITEM * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      bool bAllOk = true;

      for (::collection::index iTree = 0; iTree < m_usertreea.get_count(); iTree++)
      {

         if (!m_usertreea[iTree]->selection_set(iIndex, pitem, bIfNotInSelection, bIfParentInSelection))
            bAllOk = false;

      }

      return bAllOk;

   }



   template < prototype_item ITEM >
   bool      tree_data < ITEM >::selection_set(ITEM * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      bool bAllOk = true;

      for (::collection::index iTree = 0; iTree < m_usertreea.get_count(); iTree++)
      {

         if (!m_usertreea[iTree]->selection_set(pitem, bIfNotInSelection, bIfParentInSelection))
            bAllOk = false;

      }

      return bAllOk;

   }

   template < prototype_item ITEM >
   void tree_data < ITEM >::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      for (auto & pusertree : m_usertreea)
      {

         pusertree->handle(ptopic, phandlercontext);

      }

   }

   template < prototype_item ITEM >
   void tree_data < ITEM >::on_tree_layout()
   {

      if (m_usertreea.has_element())
      {

         for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
         {

            auto pusertree = m_usertreea[i];

            try
            {

               auto psystem = this->system();

               auto pdraw2d = psystem->draw2d();

               auto pgraphics = pdraw2d->create_memory_graphics(pusertree);

               pusertree->on_layout(pgraphics);

            }
            catch (...)
            {
            }

         }

      }

   }

   template < prototype_item ITEM >
   bool      tree_data < ITEM >::selection_set(::data::tree_item<ITEM> * ptreeitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      bool bAllOk = true;

      for (::collection::index iTree = 0; iTree < m_usertreea.get_count(); iTree++)
      {

         if (!m_usertreea[iTree]->selection_set(ptreeitem))
            bAllOk = false;

      }


      return bAllOk;

   }


   template < prototype_item ITEM >
   ::collection::count   tree_data < ITEM >::selection_set(::data::tree_item_ptr_array<ITEM> & itemptra)
   {

      ::collection::count c = 0;

      ::pointer_array < ::data::tree_item_base > ptra;

      for (auto p : itemptra)
      {

         ptra.add_item(p);

      }

      for (::collection::index iTree = 0; iTree < m_usertreea.get_count(); iTree++)
      {

         c += m_usertreea[iTree]->selection_set(ptra);

      }

      return c;

   }

} // namespace user



