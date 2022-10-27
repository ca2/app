#pragma once


//namespace apex
//{
//
//
//   template < class APP >
//   ::pointer<::matter>single_application_library < APP > ::new_application(const char * pszAppId)
//   {
//
//      if(!contains_app(pszAppId))
//      {
//
//         return error_not_found;
//
//      }
//
//      auto pappNew = __new(APP);
//
//      if(pappNew == nullptr)
//      {
//
//         return error_no_memory;
//
//      }
//
//      ::pointer<::apex::application>papp;
//
//      papp = pappNew;
//
//      if (!papp)
//      {
//
//         return error_wrong_type;
//
//      }
//
////      auto estatus = papp->initialize(pparticle);
////
////      if (!estatus)
////      {
////
////         return estatus;
////
////      }
//
//      return papp;
//
//   }
//
//
//   template < class APP >
//   void single_application_library < APP > ::get_extension_list(string_array & stra)
//   {
//
//      if (m_strFileExt.has_char())
//      {
//
//         stra.add(m_strFileExt);
//
//      }
//
//   }
//
//
//} // namespace apex


//template < typename RECEIVER >
//void channel::add_route (RECEIVER * preceiver, void (RECEIVER::* phandler)(::message::message * pmessage))
//{
//
//  add_receiver_route(atom, preceiver, phandler);
//
//}


//template < typename RECEIVER, typename MESSAGE_PRED >
//void channel::add_route (const ::atom & atom, RECEIVER * preceiverDerived, MESSAGE_PRED message_predicate)
//{
//
//  get_typed_route < typename ::erase_reference < decltype(*preceiverDerived) >::TYPE, ::message::message >(atom, preceiverDerived) = message_predicate;
//
//}


//template < typename RECEIVER >
//bool channel::add_message_handler(const ::atom & atom, RECEIVER* preceiver, void (RECEIVER::* phandler)(::message::message * pmessage))
//{
//
//   ::message::__handler(preceiver, phandler)
//
//   return _add_message_handler(atom, preceiver, reinterpret_cast<void *&>(phandler), );
//
//}


//template < typename RECEIVER >
//::message::route & channel::add_route(const ::atom & idParam, RECEIVER * preceiverDerived, void (RECEIVER:: * phandler)(MESSAGE * pmessage))
//{
//
//   ::atom atom(idParam);
//
//   if (atom.m_etype == ::atom::e_type_integer)
//   {
//
//      atom.m_etype = ::atom::e_type_message;
//
//   }
//
//  synchronous_lock synchronouslock(channel_mutex());
//
//  ::object* pobjectReceiver = dynamic_cast <::object*> (preceiverDerived);
//
//  ::type typeReceiver(typeid(RECEIVER));
//
//  if (!m_bNewChannel && m_idroute.is_empty() && m_idrouteNew.get_count() > 0)
//  {
//
//     m_idroute = m_idrouteNew;
//
//  }
//
//  auto & proutea = m_idroute[atom];
//
//  ::pointer<::message::route>proute;
//
//  if (proutea.is_set())
//  {
//
//     auto pred = [=](auto & proute)
//     {
//
//        return proute->m_pobjectReceiver == pobjectReceiver
//        && proute->m_typeReceiver == typeReceiver
//        && proute->m_phandler = phandler;
//
//     };
//
//     index iFind = proutea->predicate_find_first(pred);
//
//     if (iFind >= 0)
//     {
//
//        proute = proutea->sp_at(iFind);
//
//     }
//
//  }
//
//  object * preceiver = dynamic_cast <object*>(preceiverDerived);
//
//  if (preceiver == nullptr)
//  {
//
//     ASSERT(false);
//
//     throw ::exception(error_bad_argument);
//
//  }
//
//  if (proute.is_null())
//  {
//
//     proute = ::message::create_typed_route<MESSAGE>(preceiver, pobjectReceiver, typeReceiver);
//
//     if (proute.is_null())
//     {
//
//        throw resource_exception();
//
//     }
//
//     if (proutea.is_null())
//     {
//
//        proutea = __new(::message::route_array);
//
//     }
//
//     proutea->add(proute);
//
//  }
//
//  if (proute.is_null())
//  {
//
//     throw resource_exception();
//
//  }
//
//  return *proute;
//
//}


//template < typename RECEIVER, typename MESSAGE >
//::message::typed_route < MESSAGE > & channel::get_typed_route (const ::atom & atom, RECEIVER * preceiverDerived)
//{
//
//  synchronous_lock synchronouslock(s_pmutexChannel);
//
//  ::object * pobjectReceiver = dynamic_cast < ::object * > (preceiverDerived);
//
//  ::type typeReceiver(typeid(RECEIVER));
//
//  if(!m_bNewChannel && m_idroute.is_empty() && m_idrouteNew.get_count() > 0)
//  {
//
//     m_idroute = m_idrouteNew;
//
//  }
//
//  ::pointer<::message::route_array>& proutea = m_idroute[atom];
//
//  pointer< ::message::typed_route < MESSAGE > > proute;
//
//  if (proutea.is_set())
//  {
//
//     auto pred = [=](auto & proute)
//     {
//
//        return proute->m_pobjectReceiver == pobjectReceiver && proute->m_typeReceiver == typeReceiver;
//
//     };
//
//     index iFind = proutea->predicate_find_first(pred);
//
//     if(iFind >= 0)
//     {
//
//        proute = proutea->sp_at(iFind);
//
//     }
//
//  }
//
//  ::object * preceiver = dynamic_cast < object * >(preceiverDerived);
//
//  if (preceiver == nullptr)
//  {
//
//     ASSERT(false);
//
//     throw ::exception(error_bad_argument);
//
//  }
//
//  if(proute.is_null())
//  {
//
//     proute = ::message::create_typed_route<MESSAGE>(preceiver, pobjectReceiver, typeReceiver);
//
//     if (proutea.is_null())
//     {
//
//        proutea = __new(::message::route_array);
//
//     }
//
//     proutea->add(proute);
//
//  }
//
//  return *proute;
//
//}


//CLASS_DECL_APEX inline ::object * get_app_object()
//{
//
//   return ::get_app();
//
//}


//CLASS_DECL_APEX inline ::context * get_context(::context * pcontext)
//{
//
//   return pcontext;
//
//}


//CLASS_DECL_APEX inline ::application * get_app(::apex::application * papp)
//{
//
//  return papp;
//
//}


//CLASS_DECL_APEX inline ::apex::session * get_session(::apex::session * psession)
//{
//
//  return psession;
//
//}


//CLASS_DECL_APEX inline ::apex::system * ::apex::get_system(::apex::system * psystem)
//{
//
//  return psystem;
//
//}
//
//template < typename TYPE >
//::stream & read_container_as_parent(::stream & stream, pointer_array < TYPE > & a)
//{
//
//   ::count c = 0;
//
//   stream >> c;
//
//   if (stream.fail())
//   {
//
//      return stream;
//
//   }
//
//   while (c > 0)
//   {
//
//      auto p = __new(TYPE(&a));
//
//      stream >> *p;
//
//      if (stream.fail())
//      {
//
//         break;
//
//      }
//
//      a.add(p);
//
//      c--;
//
//   }
//
//   return stream;
//
//}
//
//
//template < typename TYPE >
//::stream & write_container_as_parent(::stream & stream, const pointer_array < TYPE > & a)
//{
//
//   ::count c = a.get_count();
//
//   stream << c;
//
//   if (stream.fail())
//   {
//
//      return stream;
//
//   }
//
//   for (auto & item : a)
//   {
//
//      stream >> item;
//
//      c--;
//
//   }
//
//   return stream;
//
//}
//
//
//template < class c_derived >
//inline i64 increment_reference_count(c_derived * pca OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   if (::is_null(pca))
//   {
//
//      return -1;
//
//   }
//
//   return pca->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//}
//
//
//template < class c_derived, typename SOURCE >
//inline i64 increment_reference_count(c_derived * & pca, const SOURCE * psource)
//{
//
//   c_derived * pderived = dynamic_cast <c_derived *>((SOURCE *)psource);
//
//   if (::is_null(pderived))
//   {
//
//      throw ::exception(::exception(::error_wrong_type));
//
//   }
//
//   pca = pderived;
//
//   return increment_reference_count(pca);
//
//}
//
//
//template < class c_derived, typename SOURCE >
//inline i64 increment_reference_count(c_derived *& pderived, const ::pointer<SOURCE>& psource)
//{
//
//   return increment_reference_count(pderived, psource.m_p);
//
//}
//
//
//template < class c_derived >
//inline i64 release(c_derived *& pca OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   if (::is_null(pca))
//   {
//
//      return -1;
//
//   }
//
//   c_derived * ptr = pca;
//
//#ifdef _DEBUG
//
////   ::atom atom = p->m_atom;
//   //char * pszType = nullptr;
//   //
//   //try
//   //{
//
//   //   pszType = _strdup(typeid(*p).name());
//
//   //}
//   //catch (...)
//   //{
//
//   //   ::output_debug_string("exception release strdup(typeid(*p).name())\n");
//
//   //}
//
//#endif
//
//   try
//   {
//
//      pca = nullptr;
//
//   }
//   catch (...)
//   {
//
//      //::output_debug_string("exception release pca = nullptr; (" + string(atom) + ")\n");
//      ::output_debug_string("exception release pca = nullptr; \n");
//
//   }
//
//   try
//   {
//
//      return ptr->release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//   }
//   catch (...)
//   {
//
//      //::output_debug_string("exception release p->release() (" + string(atom) + ")\n");
//      ::output_debug_string("exception release p->release() \n");
//
//   }
//
//   //#ifdef _DEBUG
//   //
//   //   try
//   //   {
//   //
//   //      ::free(pszType);
//   //
//   //   }
//   //   catch (...)
//   //   {
//   //
//   //      ::output_debug_string("exception release ::free(pszType)\n");
//   //
//   //   }
//   //
//   //#endif
//
//   return -1;
//
//}
//
//
//template < class COMPOSITE >
//inline i64 release(::pointer<COMPOSITE>& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
//{
//
//   return release(pcomposite.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}
//
//
//template < typename TYPE >
//inline i64 release(::pointer<TYPE>& pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
//{
//
//   return release(pointer.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}
//
//
//template < class REFERENCE >
//inline i64 release(::pointer<REFERENCE>& preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
//{
//
//   return release(preference.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}
//
//
//template < class c_derived >
//inline i64 ref_count(c_derived * pca)
//{
//
//   if (pca == nullptr)
//   {
//
//      return -1;
//
//   }
//
//   return pca->get_ref_count();
//
//}
//
//
//
//namespace apex
//{
//
//
//   //template < typename VIEW >
//   //::pointer<::user::document>session::create_form(::pointer<::user::interaction>userinteractionParent, ::payload payload, ::payload varArgs)
//   //{
//
//   //   return create_form(__type(VIEW), puserinteractionParent, payload);
//
//   //}
//
//
//   //template < typename VIEW >
//   //::pointer<::user::document>session::create_child_form(::pointer<::user::interaction>userinteractionParent, ::payload payload)
//   //{
//
//   //   return create_child_form(__type(VIEW), puserinteractionParent, payload);
//
//   //}
//
//
//} // namespace apex


#if !defined(DEBUG)


//inline void object::set_context(::context* pcontext)
//{
//
//   m_pcontext = pcontext;
//
//}


//inline void object::set_context_thread(::thread* pthread)
//{
//
//   m_pthread = pthread;
//
//}


//inline void object::set_context_app(::apex::application* pappContext)
//{
//
//   m_pacmeapplication = pappContext;
//
//}


//inline void object::set_context_session(::apex::session* psessionContext)
//{
//
//   m_psession = psessionContext;
//
//}


//inline void object::set_context_system(::apex::system* psystemContext)
//{
//
//   m_psystemContext = psystemContext;
//
//}


#endif



//inline ::object * this
//{
//   
//   return get_context();
//   
//}


