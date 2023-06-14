//
//  ios_plane_system.hpp
//  ios_aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 03/10/17.
//

#pragma once

#ifdef __cplusplus

#ifdef __OBJC__

typedef UIWindow * ui_window_ptr;
typedef void * aura_system_ptr;

#else

typedef void * ui_window_ptr;
typedef ::aura::system * aura_system_ptr;

#endif


struct plane_system
{
   
   aura_system_ptr    acmesystem();
   
   plane_system();
   
   ui_window_ptr plane_system_initialize(CGRect rectangle_i32);
   
   void plane_system_begin();
   
};

#endif


