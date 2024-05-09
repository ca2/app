#pragma once


namespace user
{


   class tab;


   class CLASS_DECL_BASE tab_callback
   {
   public:


      tab_callback();
      virtual ~tab_callback();


      virtual void _001OnTabClick(tab * ptab, ::collection::index iTab);
      virtual void _001OnTabClose(tab * ptab, ::collection::index iTab);
      virtual bool _001IsAddTab(tab * ptab, ::collection::index iTab);
      virtual ::user::interaction * _001GetTabWnd(::collection::index iTab);

      virtual void _001OnShowTab(tab * ptab);

      virtual void _001OnDropTab(::collection::index iTab, enum_position eposition);

      virtual void _001DropTargetWindowInitialize(tab * pinterface);
      virtual void _001DropTargetWindowRelay(tab * pinterface);
      virtual void _001DropTargetWindowFinalize(tab * pinterface);

   };


} // namespace user


