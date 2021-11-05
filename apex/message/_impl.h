#pragma once


#define MESSAGE_LINK(id, pchannel, preceiver, phandler) \
   pchannel->add_message_handler((enum_message) (id), { preceiver, phandler } )

//#define ON_TYPED_MESSAGE(id, MESSAGE, name) \
//   this->get_typed_route < typename ::erase_reference < decltype(*this) >::TYPE, MESSAGE >(id, this) = [this](MESSAGE * p ## name)

//#define ON_MESSAGE(id) \
//   ON_TYPED_MESSAGE(id, ::message::message, message)

#define ON_WM_SHOWWINDOW \
   ON_TYPED_MESSAGE(e_message_show_window, ::message::show_window, showwindow)

#define ON_WM_LBUTTONDOWN \
   ON_TYPED_MESSAGE(e_message_left_button_down, ::message::mouse, mouse)

#define ON_WM_LBUTTONUP \
   ON_TYPED_MESSAGE(e_message_left_button_up, ::message::mouse, mouse)

#define ON_WM_MBUTTONDOWN \
   ON_TYPED_MESSAGE(e_message_middle_button_down, ::message::mouse, mouse)

#define ON_WM_MBUTTONUP \
   ON_TYPED_MESSAGE(e_message_middle_button_up, ::message::mouse, mouse)

#define ON_WM_RBUTTONDOWN \
   ON_TYPED_MESSAGE(e_message_right_button_down, ::message::mouse, mouse)

#define ON_WM_RBUTTONUP \
   ON_TYPED_MESSAGE(e_message_right_button_up, ::message::mouse, mouse)

#define ON_WM_MOUSEMOVE \
   ON_TYPED_MESSAGE(e_message_mouse_move, ::message::mouse, mouse)

#define SCAST_MSG(tcast) \
   ::message::tcast * p##tcast = dynamic_cast < ::message::tcast * > (pmessage);



namespace message
{


   //inline void handler::operator()(::message::message* pmessage) const { (*m_p)(pmessage); }


   //inline bool handler::should_run_async() const { return m_p->should_run_async(); }



} // namespace message



