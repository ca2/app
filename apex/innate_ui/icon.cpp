// Created by camilo on 2024-09-13 07:38 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "icon.h"
#include "acme/filesystem/filesystem/file_context.h"


namespace innate_ui
{


   icon::icon()
   {
   }


   icon::~icon()
   {

   }


   void icon::_create()
   {

   }


   void icon::create(const ::payload & payloadFile, const ::int_size & size)
   {

      m_memory = file()->as_memory(payloadFile);

      m_size = size;

      _create();


   }


} // namespace innate_ui

