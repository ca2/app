#pragma once

//
//class CLASS_DECL_APEX message_box
//{
//public:
//
//   ::pointer<::user::interaction_base>    m_puserprimitive;
//   string                           m_strMessage;
//   string                           m_strTitle;
//   const ::user::e_message_box &                    m_emessagebox;
//   class ::time                       m_timeTimeout;
//   callback                         m_callback;
//
//
//   message_box();
//   message_box(const ::payload & payload);
//   virtual ~message_box();
//
//
//   void show(::object* pparticle);
//
//
//};
//inline ::payload operator + (::payload payload, const ::user::enum_message_box& emessagebox)
//{
//
//   if (payload.get_type() != e_type_property_set)
//   {
//
//      payload["message"] = payload.get_string();
//
//   }
//
//   payload["flags"] = (long long) emessagebox;
//
//   return ::payload;
//
//}
//
//
//template < typename TYPE_CHAR >
//inline ::payload operator +(const string_base < TYPE_CHAR >& str, const enum_message_box& e)
//{
//
//   return ::payload(str) + e;
//
//}
//inline ::payload operator + (const ::scoped_string & scopedstr, const ::user::enum_message_box& emessagebox)
//{
//
//   return ::payload(scopedstr) + emessagebox;
//
//}
//CLASS_DECL_APEX void auto pmessageboxpayload = __initialize_new ::message_box_payload(::acme::windowing::window * pacmewindowingwindow, const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, ::callback callback = ::callback());

send(pmessageboxpayload);
//CLASS_DECL_APEX void message_box(::user::interaction_base * puiOwner, const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, ::callback callback = ::callback());
//
//
//inline void message_box_synchronous(const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, ::callback callback = ::callback())
//{
//
//   return auto pmessageboxpayload = __initialize_new ::message_box_payload(nullptr, pszText, pszTitle, emessagebox, callback);

send(pmessageboxpayload);
//
//}
//
//
//inline void message_box(const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, ::callback callback = ::callback())
//{
//
//   return message_box(nullptr, pszText, pszTitle, emessagebox, callback);
//
//}
//
//
//
