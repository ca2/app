#pragma once


namespace message
{


   class simple_command;


   CLASS_DECL_AQUA UINT translate_to_os_message(const e_message && emessage);


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


   CLASS_DECL_AQUA e_prototype get_message_prototype(UINT_PTR uiMessage, UINT uiCode);

//   class ::channel * CreateSignal();


} // namespace message
