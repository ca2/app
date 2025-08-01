#include "framework.h"
#include "simple_item.h"
#include "data.h"
#include "listener.h"
#include "tree.h"
#include "tree_item.h"
#include "acme/user/user/item.h"
#include "acme/user/user/item_base.h"


namespace data
{


   simple_item::simple_item(::data::tree <::item > * pdatatree) :
      m_pdatatree(pdatatree)
   {

      m_iImage          = -1;
      m_iImageSelected  = -1;

   }


   simple_item::~simple_item()
   {

   }


   string simple_item::get_item_text(::user::item_base * puseritembase, ::collection::index iSubItem)
   {
      __UNREFERENCED_PARAMETER(puseritembase);
      __UNREFERENCED_PARAMETER(iSubItem);
      return m_str;
   }


   ::collection::index simple_item::get_item_image(::user::item_base * puseritembase, ::collection::index iSubItem)
   {

      __UNREFERENCED_PARAMETER(puseritembase);
      __UNREFERENCED_PARAMETER(iSubItem);

      if(puseritembase->m_eitemstate & ::user::e_item_state_selected)
      {

         return m_iImageSelected;

      }
      else
      {

         return m_iImage;

      }

   }


   ::image::image_list * simple_item::get_item_image_list(::user::item_base * puseritembase, ::collection::index iSubItem)
   {

      return m_pdatatree->get_tree_image_list();

   }


/*
   void * simple_item::operator new(size_t, const_char_pointer , int)
   {
      return _alloc001SimpleTreeItem.Alloc();
   }

   void * simple_item::operator new(size_t)
   {
      return _alloc001SimpleTreeItem.Alloc();
   }
*/

/*   void simple_item::operator delete(void * p)
   {
      return _alloc001SimpleTreeItem.Free(point);
   }

   void simple_item::operator delete(void * p, const_char_pointer , int)
   {
      return _alloc001SimpleTreeItem.Free(point);
   }*/

} // namespace data
