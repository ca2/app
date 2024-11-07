// Created by camilo on 2024-11-07 18:35 <3ThomasBorregaardSorensen>
#include "framework.h"
#include "data.h"
#include "edit_impl.h"
#include "span.h"


void rich_text_factory_exchange(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::user::rich_text::data >();

   pfactory->add_factory_item < ::user::rich_text::edit_impact_impl >();

   pfactory->add_factory_item < ::user::rich_text::edit_impl, ::user::rich_text::edit >();
   //add_factory_item <::user::rich_text::format >();
   pfactory->add_factory_item < ::user::rich_text::span >();
   //pfactory->add_factory_item <::user::rich_text::document >();

   pfactory->add_factory_item < ::user::rich_text::edit_impl >("rich_text_impact");
   pfactory->add_factory_item < ::user::rich_text::edit_impl >();

}



