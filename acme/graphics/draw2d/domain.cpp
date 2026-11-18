//
//  domain.cpp
//  aura
//
//  Created by camilo on 2026-09-23 23:15 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "platform.h"
#include "domain.h"


namespace acme
{


   namespace draw2d
   {


      domain::domain()
      {

         m_fDensityDpi = 96.f;
         m_fDensityBaseDpi = 96.f;
         m_fDensity = 1.f;

      }


      domain::~domain()
      {
         
         
      }


      void domain::initialize_density(::f32 fDensityDpi, ::f32 fDensityBaseDpi)
      {

         if (!::std::isfinite(fDensityDpi) || fDensityDpi < 24.0f || fDensityDpi > 1536.0f)
         {

            throw ::exception(error_bad_argument);

         }

         if (!::std::isfinite(fDensityBaseDpi) || fDensityBaseDpi < 24.0f || fDensityBaseDpi > 1536.0f)
         {

            throw ::exception(error_bad_argument);

         }

         m_fDensityDpi = fDensityDpi;

         m_fDensityBaseDpi = fDensityBaseDpi;

         m_fDensity = m_fDensityDpi / m_fDensityBaseDpi;

      }


      // ::f32 domain::get_density_dpi() const
      // {
      //
      //    return m_fDensityDpi;
      //
      // }
      //
      //
      // void domain::set_density_base_dpi(::f32 fDensityBaseDpi)
      // {
      //
      //    if (::std::isfinite(fDensityBaseDpi) && fDensityBaseDpi >= 24.0f && fDensityBaseDpi <= 1536.0f)
      //    {
      //
      //       m_fDensityBaseDpi = fDensityBaseDpi;
      //
      //    }
      //
      // }
      //
      //
      // ::f32 domain::get_density_base_dpi() const
      // {
      //
      //    return m_fDensityBaseDpi;
      //
      // }
      //
      //
      // ::f32 domain::get_density() const
      // {
      //
      //    return get_density_dpi() / get_density_base_dpi();
      //
      // }



   } // namespace draw2d



} // namespace acme



