#pragma once


namespace message
{


   class simple_command;


   inline UINT translate_to_os_message(const ::id& id) { return id.u32(); }


   class base;


   enum e_prototype
   {
      PrototypeNone,
      PrototypeMouse,
      PrototypeScroll,
      PrototypeSize,
      PrototypeMove,
      PrototypeMeasureItem,
      PrototypeCreate,
      PrototypeActivate,
      PrototypeNcActivate,
      PrototypeMouseActivate,
      PrototypeEraseBkgnd,
      PrototypeShowWindow,
      PrototypeSetCursor,
      PrototypeTimer,
      PrototypeMouseWheel,
      PrototypeInitMenuPopup,
      PrototypeEnable,
      PrototypeNcHitTest,
      PrototypeKey,
      PrototypeNotify,
      PrototypeUpdateCommandUserInterface,
      PrototypeCtlColor,
      PrototypeCtlColorReflect,
      PrototypeKillFocus,
      PrototypeSetFocus,
      PrototypeCommand,
      PrototypeWindowPos,
      PrototypeNcCalcSize,
      PrototypeOnDraw,
      PrototypeSimpleCommand

   };


   CLASS_DECL_APEX e_prototype get_message_prototype(UINT_PTR emessage, UINT uiCode);

//   class ::channel * CreateSignal();


} // namespace message
