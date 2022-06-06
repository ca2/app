//
//  _opaque_system.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/06/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


class plane_system :
   virtual public ::element
{
public:
   
   
   virtual void _main_application_open_url(const char * pszUrl, const ::function < void(bool) > & functionSucceeded) = 0;
   
};


CLASS_DECL_ACME ::plane_system * get_plane_system();



