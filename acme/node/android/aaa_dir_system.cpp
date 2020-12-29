﻿#include "framework.h"
#include "_android.h"


namespace android
{


   dir_system::dir_system()
   {

   }


   dir_system::~dir_system()
   {

   }


   ::e_status dir_system::initialize(::matter * pobjectContext)
   {

      auto estatus = ::dir_system::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_pathInstall = ::dir::install();

      return estatus;

   }




} // namespace android



