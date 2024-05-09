#pragma once


#include "core/user/user/list_data.h"


namespace userfs
{


   class CLASS_DECL_CORE list_data :
      public ::user::list_data
   {
   public:


      ::collection::index                      m_iNameSubItem;
      ::collection::index                      m_iNameSubItemText;
      ::collection::index                      m_iSelectionSubItem;
      ::collection::index                      m_iSizeSubItem;
      class ::time                 m_timeLastFileSizeGet;

      ::pointer<list_item_array>m_pitema;



      list_data();
      ~list_data() override;


      void initialize(::particle * pparticle) override;


      ::userfs::list_item * item(::collection::index i);

      virtual void update(::userfs::data * puserfsdata);

      void _001GetSubItemText(::user::mesh_subitem * psubitem) override;

      ::collection::count _001GetItemCount() override;

      void _001GetSubItemImage(::user::mesh_subitem * psubitem) override;


   };


} // namespace userfs

