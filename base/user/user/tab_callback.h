#pragma once


namespace user
{


   class tab;


   class CLASS_DECL_BASE tab_callback
   {
   public:


      tab_callback();
      virtual ~tab_callback();


      virtual void _001OnTabClick(tab * ptab, ::raw::index iTab);
      virtual void _001OnTabClose(tab * ptab, ::raw::index iTab);
      virtual bool _001IsAddTab(tab * ptab, ::raw::index iTab);
      virtual ::user::interaction * _001GetTabWnd(::raw::index iTab);

      virtual void _001OnShowTab(tab * ptab);

      virtual void _001OnDropTab(::raw::index iTab, enum_position eposition);

      virtual void _001DropTargetWindowInitialize(tab * pinterface);
      virtual void _001DropTargetWindowRelay(tab * pinterface);
      virtual void _001DropTargetWindowFinalize(tab * pinterface);

   };


} // namespace user


