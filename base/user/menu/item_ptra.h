// From (menu/)item.h by camilo on 2022-08-27 22:50 <3ThomasBorregaardSorensen!!
#pragma once


namespace menu
{


   class CLASS_DECL_BASE item_ptra :
public pointer_array < ::menu::item >
   {
   public:


      ::menu::item * m_pitemParent;


      item_ptra(::menu::item * pitemParent);
      ~item_ptra() override;


      ::menu::item * find(const atom & atom);


   };


} // namespace menu



