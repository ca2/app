// From (menu/)item.h by camilo on 2022-08-27 22:50 <3ThomasBorregaardSorensen!!
#pragma once


namespace user
{


   class CLASS_DECL_BASE menu_item_ptra :
      public pointer_array < menu_item >
   {
   public:


      menu_item * m_pitemParent;


      menu_item_ptra(menu_item * pitemParent);
      ~menu_item_ptra() override;


      menu_item * find(const atom & atom);


   };


} // namespace user



