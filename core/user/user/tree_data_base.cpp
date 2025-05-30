#include "framework.h"
#include "tree_data.h"
#include "tree.h"
#include "acme/prototype/data/listener.h"
#include "aura/graphics/draw2d/draw2d.h"


namespace user
{


   tree_data_base::tree_data_base()
   {



   }


   tree_data_base::~tree_data_base()
   {

   }


   ::collection::count tree_data_base::get_data_bound_impact_count() const
   {

      return m_usertreeaBound.get_count();

   }


   ::user::element * tree_data_base::get_data_bound_impact(::collection::index iImpact)
   {

      return m_usertreeaBound[iImpact].raw_cast <::user::element>();

   }


   //::user::element * tree_data::get_data_bound_impact(::collection::index iImpact)
   //{

   //   return m_usertreeaBound[iImpact].cast < ::user::element >();

   //}





   //void tree_data::_001OnTreeDataChange()
   //{

   //   ::data::tree::_001OnTreeDataChange();

   //}







   //void tree_data::_001ExpandItem(::data::tree_item * pitem, const ::action_context & context,bool bExpand,bool bRedraw,bool bLayout)
   //{

   //   for(::collection::index i = 0; i < m_usertreea.get_count(); i++)
   //   {

   //      m_usertreea[i]->_001ExpandItem(pitem,context,bExpand,bRedraw,bLayout);

   //   }

   //}

   //void tree_data::_001EnsureVisible(::data::tree_item * pitem)
   //{

   //   for(::collection::index i = 0; i < m_usertreea.get_count(); i++)
   //   {

   //      m_usertreea[i]->_001EnsureVisible(pitem);

   //   }

   //}


   //void tree_data::_001SelectItem(::data::tree_item * pitem)
   //{

   //   for(::collection::index i = 0; i < m_usertreea.get_count(); i++)
   //   {

   //      m_usertreea[i]->_001SelectItem(pitem);

   //   }

   //}

   //void tree_data::get_selection(::data::tree_item_ptr_array & itemptraSelected) const
   //{

   //   for(::collection::index i = 0; i < m_usertreea.get_count(); i++)
   //   {

   //      itemptraSelected.add_unique(*m_usertreea[i]->m_pitemptraSelected);

   //   }

   //}


   //bool tree_data::is_selected(const ::data::tree_item * pitem) const
   //{

   //   for(::collection::index i = 0; i < m_usertreea.get_count(); i++)
   //   {

   //      if (m_usertreea[i]->is_selected(pitem))
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   //bool tree_data::is_selected(const ::item * pitem) const
   //{

   //   for(::collection::index i = 0; i < m_usertreea.get_count(); i++)
   //   {

   //      if (m_usertreea[i]->is_selected(pitem))
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   //void tree_data::_001OnItemExpand(::data::tree_item * pitem, const ::action_context & context)
   //{

   //   if (pitem->is_expanded())
   //   {

   //      return;

   //   }

   //   pitem->on_fill_children();

   //   if(pitem->get_children_count() > 0)
   //   {

   //      pitem->m_dwState |= ::data::e_tree_item_state_expanded;

   //      pitem->m_dwState |= ::data::e_tree_item_state_expandable;

   //   }

   //   /*      for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
   //   {

   //   m_usertreea[i]->_001OnItemExpand(pitem, context);

   //   }*/




   //}


   //void tree_data::_001OnItemCollapse(::data::tree_item * pitem, const ::action_context & context)
   //{

   //   if(!pitem->is_expanded())
   //      return;
   //   if(pitem->get_children_count() > 0)
   //   {
   //      pitem->m_dwState |= ::data::e_tree_item_state_expandable;
   //   }
   //   pitem->m_dwState &= ~::data::e_tree_item_state_expanded;
   //   /*for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
   //   {

   //   m_usertreea[i]->_001OnItemCollapse(pitem);

   //   }*/

   //}


   //void tree_data::_001OnOpenItem(::data::tree_item * pitem, const ::action_context & context)
   //{

   //   for(::collection::index i = 0; i < m_usertreea.get_count(); i++)
   //   {

   //      m_usertreea[i]->_001OnOpenItem(pitem,context);

   //   }

   //}


   //void tree_data::_001OnItemContextMenu(::data::tree_item * pitem, const ::action_context & context,::user::tree * ptree,const ::int_point & point)
   //{

   //   for(::collection::index i = 0; i < m_usertreea.get_count(); i++)
   //   {

   //      m_usertreea[i]->_001OnItemContextMenu(pitem, context, ptree, point);

   //   }

   //}


   //::collection::count   tree_data::selection_set(::data::tree_item_ptr_array & itemptra)
   //{

   //   ::collection::count c = 0;

   //   for(::collection::index iTree = 0; iTree < m_usertreea.get_count(); iTree++)
   //   {

   //      c += m_usertreea[iTree]->selection_set(itemptra);

   //   }

   //   return c;

   //}


   //bool      tree_data::selection_set(::data::tree_item * pitem,bool bIfNotInSelection,bool bIfParentInSelection)
   //{

   //   bool bAllOk = true;

   //   for(::collection::index iTree = 0; iTree < m_usertreea.get_count(); iTree++)
   //   {

   //      if(!m_usertreea[iTree]->selection_set(pitem))
   //         bAllOk = false;

   //   }


   //   return bAllOk;

   //}


   //bool      tree_data::selection_set(::item * pitem,bool bIfNotInSelection,bool bIfParentInSelection)
   //{

   //   bool bAllOk = true;

   //   for(::collection::index iTree = 0; iTree < m_usertreea.get_count(); iTree++)
   //   {

   //      if(!m_usertreea[iTree]->selection_set(pitem,bIfNotInSelection,bIfParentInSelection))
   //         bAllOk = false;

   //   }

   //   return bAllOk;

   //}


   //bool      tree_data::selection_set(::collection::index iIndex,::item * pitem,bool bIfNotInSelection,bool bIfParentInSelection)
   //{

   //   bool bAllOk = true;

   //   for(::collection::index iTree = 0; iTree < m_usertreea.get_count(); iTree++)
   //   {

   //      if(!m_usertreea[iTree]->selection_set(iIndex,pitem,bIfNotInSelection,bIfParentInSelection))
   //         bAllOk = false;

   //   }

   //   return bAllOk;

   //}


   ::image::image_list * tree_data_base::get_tree_image_list()
   {

      return m_pimagelist;

   }

   //void tree_data::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   for (auto& pusertree : m_usertreea)
   //   {

   //      pusertree->handle(ptopic, phandlercontext);

   //   }

   //}



//   void tree_data::on_fill_children()
//   {
//
//   }
//
//
//   void tree_data::on_tree_layout()
//   {
//      
//      if(m_usertreea.has_element())
//      {
//
//         for(::collection::index i = 0; i < m_usertreea.get_count(); i++)
//         {
//
//            auto pusertree = m_usertreea[i];
//
//            try
//            {
//
//               auto psystem = system();
//
//               auto pdraw2d = psystem->draw2d();
//
//               auto pgraphics = pdraw2d->create_memory_graphics(pusertree);
//
//               pusertree->on_layout(pgraphics);
//
//            }
//            catch(...)
//            {
//            }
//
//         }
//         
//      }
//
//   }
//
//
//   void tree_data::on_merge_user_tree(::user::tree * pusertree)
//   {
//
//      __UNREFERENCED_PARAMETER(pusertree);
//
//   }
//
//
//   void tree_data::on_bind_user_tree(::user::tree * pusertree)
//   {
//
//      __UNREFERENCED_PARAMETER(pusertree);
//
//   }
//

void tree_data_base::on_merge_user_tree(::user::tree * pusertree)
{

   __UNREFERENCED_PARAMETER(pusertree);

}


void tree_data_base::on_bind_user_tree(::user::tree * pusertree)
{

   __UNREFERENCED_PARAMETER(pusertree);

}

} // namespace data



