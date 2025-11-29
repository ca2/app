#pragma once


template < class TOOLBAR >
bool simple_frame_window::LoadToolBar(atom idToolBar, const ::scoped_string & scopedstrToolBar,unsigned int dwCtrlStyle,unsigned int uStyle)
{

   return LoadToolBar(typeid(TOOLBAR),idToolBar,pszToolBar,dwCtrlStyle,uStyle);

}



