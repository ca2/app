//
//  domain.h
//  aura
//
//  Created by camilo on 2026-09-23 23:15 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


namespace acme
{


   namespace draw2d
   {


      class CLASS_DECL_ACME domain :
      virtual public ::particle
      {
      public:
         

         ::f32 m_fDensityDpi;
         ::f32 m_fDensityBaseDpi;
         ::f32 m_fDensity;

         
         domain();
         ~domain() override;

         virtual void initialize_density(::f32 fDensityDpi, ::f32 fDensityBaseDpi);

         inline ::f32 get_density_dpi() const {return m_fDensityDpi;}
         inline ::f32 get_density_base_dpi() const {return m_fDensityBaseDpi;}
         inline ::f32 get_density() const {return m_fDensity;}


      };



   } // namespace draw2d


} // namespace acme


   
   
