#pragma once


template < class TOOLBAR >
bool simple_frame_window::LoadToolBar(atom idToolBar, const ::string & pszToolBar,u32 dwCtrlStyle,u32 uStyle)
{

   return LoadToolBar(__type(TOOLBAR),idToolBar,pszToolBar,dwCtrlStyle,uStyle);

}



