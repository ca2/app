#pragma once


namespace apex
{


   template < class APP >
   __transport(::apex::application) single_application_library < APP > ::new_application(const char * pszAppId)
   {

      if(!contains_app(pszAppId))
      {

         return error_not_found;

      }

      auto pappNew = __new(APP);

      if(pappNew == nullptr)
      {

         return error_no_memory;

      }

      __pointer(::apex::application) papp;

      papp = pappNew;

      if (!papp)
      {

         return error_wrong_type;

      }

//      auto estatus = papp->initialize(pcontextobject);
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }

      return papp;

   }


   template < class APP >
   void single_application_library < APP > ::get_extension_list(string_array & stra)
   {

      if (m_strFileExt.has_char())
      {

         stra.add(m_strFileExt);

      }

   }


} // namespace apex


//template < typename RECEIVER >
//void channel::add_route (RECEIVER * preceiver, void (RECEIVER::* phandler)(::message::message * pmessage))
//{
//
//  add_receiver_route(id, preceiver, phandler);
//
//}


//template < typename RECEIVER, typename MESSAGE_PRED >
//void channel::add_route (const ::id & id, RECEIVER * preceiverDerived, MESSAGE_PRED message_predicate)
//{
//
//  get_typed_route < typename ::remove_reference < decltype(*preceiverDerived) >::TYPE, ::message::message >(id, preceiverDerived) = message_predicate;
//
//}


template < typename RECEIVER >
bool channel::add_handler(const ::id & id, RECEIVER* preceiver, void (RECEIVER::* phandler)(::message::message * pmessage))
{

   return _add_handler(id, preceiver, reinterpret_cast<void *&>(phandler), __handler(preceiver, phandler));

}


//template < typename RECEIVER >
//::message::route & channel::add_route(const ::id & idParam, RECEIVER * preceiverDerived, void (RECEIVER:: * phandler)(MESSAGE * pmessage))
//{
//
//   ::id id(idParam);
//
//   if (id.m_etype == ::id::e_type_integer)
//   {
//
//      id.m_etype = ::id::e_type_message;
//
//   }
//
//  synchronization_lock synchronizationlock(channel_mutex());
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
//  auto & proutea = m_idroute[id];
//
//  __pointer(::message::route) proute;
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
//     __throw(error_invalid_argument);
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
//::message::typed_route < MESSAGE > & channel::get_typed_route (const ::id & id, RECEIVER * preceiverDerived)
//{
//
//  synchronization_lock synchronizationlock(s_pmutexChannel);
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
//  __pointer(::message::route_array) & proutea = m_idroute[id];
//
//  __pointer(::message::typed_route < MESSAGE >) proute;
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
//     __throw(error_invalid_argument);
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
//   return ::get_application();
//
//}


//CLASS_DECL_APEX inline ::context * get_context(::context * pcontext)
//{
//
//   return pcontext;
//
//}


//CLASS_DECL_APEX inline ::apex::application * get_application(::apex::application * papp)
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
//::stream & read_container_as_parent(::stream & stream, __pointer_array(TYPE) & a)
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
//::stream & write_container_as_parent(::stream & stream, const __pointer_array(TYPE) & a)
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
//inline i64 add_ref(c_derived * pca OBJ_REF_DBG_COMMA_PARAMS_DEF)
//{
//
//   if (::is_null(pca))
//   {
//
//      return -1;
//
//   }
//
//   return pca->add_ref(OBJ_REF_DBG_ARGS);
//
//}
//
//
//template < class c_derived, typename SOURCE >
//inline i64 add_ref(c_derived * & pca, const SOURCE * psource)
//{
//
//   c_derived * pderived = dynamic_cast <c_derived *>((SOURCE *)psource);
//
//   if (::is_null(pderived))
//   {
//
//      __throw(::exception::exception(::error_wrong_type));
//
//   }
//
//   pca = pderived;
//
//   return add_ref(pca);
//
//}
//
//
//template < class c_derived, typename SOURCE >
//inline i64 add_ref(c_derived *& pderived, const __pointer(SOURCE) & psource)
//{
//
//   return add_ref(pderived, psource.m_p);
//
//}
//
//
//template < class c_derived >
//inline i64 release(c_derived *& pca OBJ_REF_DBG_COMMA_PARAMS_DEF)
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
//#ifdef DEBUG
//
////   ::id id = p->m_id;
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
//      //::output_debug_string("exception release pca = nullptr; (" + string(id) + ")\n");
//      ::output_debug_string("exception release pca = nullptr; \n");
//
//   }
//
//   try
//   {
//
//      return ptr->release(OBJ_REF_DBG_ARGS);
//
//   }
//   catch (...)
//   {
//
//      //::output_debug_string("exception release p->release() (" + string(id) + ")\n");
//      ::output_debug_string("exception release p->release() \n");
//
//   }
//
//   //#ifdef DEBUG
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
//inline i64 release(__composite(COMPOSITE) & pcomposite OBJ_REF_DBG_COMMA_PARAMS)
//{
//
//   return release(pcomposite.m_p OBJ_REF_DBG_COMMA_ARGS);
//
//}
//
//
//template < class TYPE >
//inline i64 release(__pointer(TYPE) & pointer OBJ_REF_DBG_COMMA_PARAMS)
//{
//
//   return release(pointer.m_p OBJ_REF_DBG_COMMA_ARGS);
//
//}
//
//
//template < class REFERENCE >
//inline i64 release(__reference(REFERENCE) & preference OBJ_REF_DBG_COMMA_PARAMS)
//{
//
//   return release(preference.m_p OBJ_REF_DBG_COMMA_ARGS);
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
//   //__pointer(::user::document) session::create_form(__pointer(::user::interaction) puserinteractionParent, ::payload payload, ::payload varArgs)
//   //{
//
//   //   return create_form(__type(VIEW), puserinteractionParent, payload);
//
//   //}
//
//
//   //template < typename VIEW >
//   //__pointer(::user::document) session::create_child_form(__pointer(::user::interaction) puserinteractionParent, ::payload payload)
//   //{
//
//   //   return create_child_form(__type(VIEW), puserinteractionParent, payload);
//
//   //}
//
//
//} // namespace apex


#if !defined(DEBUG)


inline void object::set_context(::context* pcontext)
{

   m_pcontext = pcontext;

}


inline void object::set_context_thread(::thread* pthread)
{

   m_pthread = pthread;

}


inline void object::set_context_app(::apex::application* pappContext)
{

   m_papplication = pappContext;

}


inline void object::set_context_session(::apex::session* psessionContext)
{

   m_psession = psessionContext;

}


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


