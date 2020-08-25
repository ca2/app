#pragma once


namespace user
{


   class tab;


   class CLASS_DECL_BASE tab_callback
   {
   public:


      tab_callback();
      virtual ~tab_callback();


      virtual void _001OnTabClick(tab * ptab, ::index iTab);
      virtual void _001OnTabClose(tab * ptab, ::index iTab);
      virtual bool _001IsAddTab(tab * ptab, ::index iTab);
      virtual ::user::interaction * _001GetTabWnd(::index iTab);

      virtual void _001OnShowTab(tab * ptab);

      virtual void _001OnDropTab(::index iTab, e_position eposition);

      virtual void _001DropTargetWindowInitialize(tab * pinterface);
      virtual void _001DropTargetWindowRelay(tab * pinterface);
      virtual void _001DropTargetWindowFinalize(tab * pinterface);

   };


} // namespace user


