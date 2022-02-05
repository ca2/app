#pragma once


namespace message
{


   class simple_command;
   class command;


   inline ::u32 translate_to_os_message(const ::atom& atom) { return atom.u32(); }


   //class base;


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
      PrototypeSimpleCommand,
      PrototypeObject,

   };


   CLASS_DECL_APEX e_prototype get_message_prototype(enum_message emessage, ::u32 uCode);

//   class ::channel * CreateSignal();


} // namespace message
