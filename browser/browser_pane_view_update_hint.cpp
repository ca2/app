﻿#include "framework.h"


namespace browser
{


   ::update::update()
   {

      m_eview = impact_none;

      m_etype = type_none;

   }


   ::update::~::update()
   {

   }


   bool ::update::is_type_of(enum_type enum_type)
   {

      return m_etype == enum_type;

   }


   void ::update::set_type(enum_type enum_type)
   {

      m_etype = enum_type;

   }


} // namespace browser



