#pragma once


template < class TOOLBAR >
bool simple_frame_window::LoadToolBar(atom idToolBar, const ::string & pszToolBar,unsigned int dwCtrlStyle,unsigned int uStyle)
{

   return LoadToolBar(::type < TOOLBAR >(),idToolBar,pszToolBar,dwCtrlStyle,uStyle);

}



