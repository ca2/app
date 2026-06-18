#pragma once


template < class TOOLBAR >
bool simple_frame_window::LoadToolBar(atom idToolBar, const ::scoped_string & scopedstrToolBar,::u32 dwCtrlStyle,::u32 uStyle)
{

   return LoadToolBar(::type<TOOLBAR>(),idToolBar,pszToolBar,dwCtrlStyle,uStyle);

}



