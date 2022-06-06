//
//  _opaque_system.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/06/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


class system;


struct PLANE_SYSTEM
{
 
   
   void system_main_application_open_url(const char * pszUrl, const ::function < void(bool) > & functionCompletionSucceeded);
   
};


inline class ::system * get_system(OPAQUE_SYSTEM * psystem)
{
   
   return (class ::system *) (void*)psystem;
   
}


inline ::OPAQUE_SYSTEM * get_opaque_system(class ::system * psystem)
{
   
   return (::OPAQUE_SYSTEM *) (void*)psystem;
   
}






