#pragma once


//#define MSG_TYPE_LINK(emessagetype, pchannel, preceiver, phandler) \
//   pchannel->add_route(preceiver, phandler, ::atom((::message::enum_type)(emessagetype)))
//
//#define USER_MESSAGE_LINK(int_message, pchannel, preceiver, phandler) \
//   pchannel->add_route(preceiver, phandler, ::atom(::atom((index) (int_message)), ::message::e_type_message))
//
//#define ON_TYPED_MESSAGE(atom, MESSAGE, name) \
//   this->get_typed_route < typename ::erase_reference < decltype(*this) >::TYPE, MESSAGE >(atom, this) = [this](MESSAGE * p ## name)
//
//#define ON_MESSAGE(atom) \
//   ON_TYPED_MESSAGE(atom, ::message::message, message)
//
//#define ON_WM_SHOWWINDOW \
//   ON_TYPED_MESSAGE(::user::e_message_show_window, ::message::show_window, showwindow)
//
//#define ON_WM_LBUTTONDOWN \
//   ON_TYPED_MESSAGE(::user::e_message_left_button_down, ::message::mouse, mouse)
//
//#define ON_WM_LBUTTONUP \
//   ON_TYPED_MESSAGE(::user::e_message_left_button_up, ::message::mouse, mouse)
//
//#define ON_WM_MBUTTONDOWN \
//   ON_TYPED_MESSAGE(::user::e_message_middle_button_down, ::message::mouse, mouse)
//
//#define ON_WM_MBUTTONUP \
//   ON_TYPED_MESSAGE(::user::e_message_middle_button_up, ::message::mouse, mouse)
//
//#define ON_WM_RBUTTONDOWN \
//   ON_TYPED_MESSAGE(::user::e_message_right_button_down, ::message::mouse, mouse)
//
//#define ON_WM_RBUTTONUP \
//   ON_TYPED_MESSAGE(::user::e_message_right_button_up, ::message::mouse, mouse)
//
//#define ON_WM_MOUSEMOVE \
//   ON_TYPED_MESSAGE(::user::e_message_mouse_move, ::message::mouse, mouse)
//
///*
//
//#define USER_MESSAGE_LINK(emessageenum, pchannel, preceiver, phandler) \
//   USER_MESSAGE_LINK(::message::emessageenum, pchannel, preceiver, phandler)
//
//*/
//
//#define SCAST_MSG(tcast) \
//   ::message::tcast * p##tcast = dynamic_cast < ::message::tcast * > (pmessage);



