#pragma once


namespace apex
{


   template < class APP >
   __result(::apex::application) single_application_library < APP > ::get_new_application(::layered * pobjectContext, const char * pszAppId)
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

      auto estatus = papp->initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

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


template < typename RECEIVER >
void channel::add_route (RECEIVER * preceiver, void (RECEIVER::* phandler)(::message::message * pmessage), ::message::id id)
{

  add_receiver_route(id, preceiver, phandler);

}


template < typename RECEIVER, typename MESSAGE_PRED >
void channel::add_route (::message::id id, RECEIVER * preceiverDerived, MESSAGE_PRED message_pred)
{

  get_typed_route < typename ::remove_reference < decltype(*preceiverDerived) >::TYPE, ::message::message >(id, preceiverDerived) = message_pred;

}


template < typename RECEIVER, typename MESSAGE_TYPE >
void channel::add_receiver_route(::message::id id, RECEIVER* preceiver, void (RECEIVER::* phandler)(MESSAGE_TYPE* pmessage))
{

  add_route(id, preceiver).m_pmessageable = __new(::message::receiver_route<RECEIVER, MESSAGE_TYPE>(preceiver, phandler));

}


template < typename RECEIVER >
::message::route & channel::add_route(::message::id id, RECEIVER * preceiverDerived)
{

  sync_lock sl(channel_mutex());

  ::object* pobjectReceiver = dynamic_cast <::object*> (preceiverDerived);

  ::type typeReceiver(typeid(RECEIVER));

  if (!m_bNewChannel && m_idroute.is_empty() && m_idrouteNew.get_count() > 0)
  {

     m_idroute = m_idrouteNew;

  }

  auto & proutea = m_idroute[id];

  __pointer(::message::route) proute;

  if (proutea.is_set())
  {

     auto pred = [=](auto & proute)
     {

        return proute->m_pobjectReceiver == pobjectReceiver && proute->m_typeReceiver == typeReceiver;

     };

     index iFind = proutea->pred_find_first(pred);

     if (iFind >= 0)
     {

        proute = proutea->sp_at(iFind);

     }

  }

  object * preceiver = dynamic_cast <object*>(preceiverDerived);

  if (preceiver == nullptr)
  {

     ASSERT(FALSE);

     __throw(invalid_argument_exception());

  }

  if (proute.is_null())
  {

     proute = ::message::create_typed_route<MESSAGE>(preceiver, pobjectReceiver, typeReceiver);

     if (proute.is_null())
     {

        throw resource_exception();

     }

     if (proutea.is_null())
     {

        proutea = __new(::message::route_array);

     }

     proutea->add(proute);

  }

  if (proute.is_null())
  {

     throw resource_exception();

  }

  return *proute;

}


template < typename RECEIVER, typename MESSAGE >
::message::typed_route < MESSAGE > & channel::get_typed_route (::message::id id, RECEIVER * preceiverDerived)
{

  sync_lock sl(s_pmutexChannel);

  ::object * pobjectReceiver = dynamic_cast < ::object * > (preceiverDerived);

  ::type typeReceiver(typeid(RECEIVER));

  if(!m_bNewChannel && m_idroute.is_empty() && m_idrouteNew.get_count() > 0)
  {

     m_idroute = m_idrouteNew;

  }

  __pointer(::message::route_array) & proutea = m_idroute[id];

  __pointer(::message::typed_route < MESSAGE >) proute;

  if (proutea.is_set())
  {

     auto pred = [=](auto & proute)
     {

        return proute->m_pobjectReceiver == pobjectReceiver && proute->m_typeReceiver == typeReceiver;

     };

     index iFind = proutea->pred_find_first(pred);

     if(iFind >= 0)
     {

        proute = proutea->sp_at(iFind);

     }

  }

  ::object * preceiver = dynamic_cast < object * >(preceiverDerived);

  if (preceiver == nullptr)
  {

     ASSERT(FALSE);

     __throw(invalid_argument_exception());

  }

  if(proute.is_null())
  {

     proute = ::message::create_typed_route<MESSAGE>(preceiver, pobjectReceiver, typeReceiver);

     if (proutea.is_null())
     {

        proutea = __new(::message::route_array);

     }

     proutea->add(proute);

  }

  return *proute;

}


CLASS_DECL_APEX inline ::object * get_app_object()
{

   return ::get_context_application();

}


CLASS_DECL_APEX inline ::context * get_context(::context * pcontext)
{

   return pcontext;

}


CLASS_DECL_APEX inline ::apex::application * get_context_application(::apex::application * papp)
{

  return papp;

}


CLASS_DECL_APEX inline ::apex::session * get_context_session(::apex::session * psession)
{

  return psession;

}


CLASS_DECL_APEX inline ::apex::system * get_context_system(::apex::system * psystem)
{

  return psystem;

}

//
//template < typename T >
//inline __pointer(T) & pointer < T >::clone(::layered * pobjectContext)
//{
//
//   if (::is_null(pobjectContext))
//   {
//
//      release();
//
//      return *this;
//
//   }
//
//   return operator = (pobjectContext->clone());
//
//}
//
//
//template < typename PRED >
//::image_pointer get_image(::object * pobject, const var & varFile, bool bAsync = false)
//{
//
//   ::file::path path = varFile.get_file_path();
//
//   if (path.is_empty())
//   {
//
//      return nullptr;
//
//   }
//
//   sync_lock sl(::apex::get_image_mutex());
//
//   ::image_pointer & pimage = ::get_context_system()->m_mapImage[path];
//
//   if (!pimage)
//   {
//
//      pimage = pobject->create_image();
//
//      pimage->set_nok();
//
//      sl.unlock();
//
//      System.m_pimaging->_load_image(pobject->get_context(), pimage, varFile, !bAsync, false);
//
//   }
//
//   return pimage;
//
//}
//
//
//#ifndef __DEBUG
//
//#include "apex/primitive/primitive/block.inl"
//
//#endif // !__DEBUG
//
//
//namespace str
//{
//
//
//   inline void from(string & str, const tick & tick)
//   {
//
//      str.Format(__prtick, tick.m_i);
//
//   }
//
//
//   inline void from(string & str, const bool & b)
//   {
//
//      if(b)
//      {
//
//         str = "{[(true)]}";
//
//      }
//      else
//      {
//
//         str = "{[(false)]}";
//
//      }
//
//   }
//
//
//} // namespace str
//
//
//inline void copy(void *, const void *) /* = 0 */ {__throw(interface_only_exception()); }
//
//
//namespace papaya
//{
//
//
//   namespace chill
//   {
//
//
//      template < typename TYPE >
//      inline TYPE default_value()
//      {
//
//         __throw(::exception::exception("template only exception"));
//
//      }
//
//
//   } // namespace chill
//
//
//} // namespace papaya
//
//
//inline float i32muldiv(float f, i32 iNum, i32 iDen)
//{
//
//   return (float) (f * iNum / iDen);
//
//}
//
//
//inline double i32muldiv(double d, i32 iNum, i32 iDen)
//{
//
//   return (double) (d * iNum / iDen);
//
//}
//
//
//inline i32 i32muldiv(i32 i, i32 iNum, i32 iDen)
//{
//
//   return (i32) ::MulDiv(i, iNum, iDen);
//
//}
//
//
//#ifndef WINDOWS
//
//
//inline i64 MulDiv(i64 nNumber, i32 iNum, i32 iDen)
//{
//
//   return nNumber * iNum / iDen;
//
//}
//
//#endif
//
//
//inline ::i64 i32muldiv(::i64 i, i32 iNum, i32 iDen)
//{
//
//   return i * iNum / iDen;
//
//}
//
//
//inline string __str(const ::edisplay & edisplay) { return __str((::e_display) edisplay); }
//
//
//namespace apex
//{
//
//
//   template < typename TYPE >
//   bool application::gudo_get(const string & strKey, TYPE & obj)
//   {
//
//      ::file::path strPath(strKey);
//
//      strPath.replace("::", "/");
//
//      sync_lock sl(System.m_spmutexUserAppData);
//
//      {
//
//         file_pointer file = this->file().get_file(Context.dir().appdata() / "gudo" / strPath, ::file::mode_read);
//
//         if (file.is_null())
//         {
//
//            return false;
//
//         }
//
//         ::file::buffered_file buffer(this, file);
//
//         ::binary_stream reader(&buffer);
//
//         try
//         {
//
//            reader >> obj;
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }
//
//      return true;
//
//   }
//
//
//   template < typename TYPE >
//   bool application::gudo_set(const string & strKey, const TYPE & obj)
//   {
//
//      string strPath(strKey);
//
//      strPath.replace("::", "/");
//
//      sync_lock sl(System.m_spmutexUserAppData);
//
//      {
//
//         file_pointer file = this->file().get_file(Context.dir().appdata() / "gudo" / strPath, ::file::mode_write | ::file::mode_create | ::file::defer_create_directory);
//
//         if (file.is_null())
//         {
//
//            return false;
//
//         }
//
//         ::file::buffered_file buffer(this, file);
//
//         ::binary_stream writer(&buffer);
//
//         try
//         {
//
//            writer << obj;
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }
//
//      return true;
//
//   }
//
//
//} // namespace apex
//
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
//inline i64 add_ref(c_derived * pca OBJ_REF_DBG_ADD_PARAMS_DEF)
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
//inline i64 release(c_derived *& pca OBJ_REF_DBG_ADD_PARAMS_DEF)
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
//inline i64 release(__composite(COMPOSITE) & pcomposite OBJ_REF_DBG_ADD_PARAMS)
//{
//
//   return release(pcomposite.m_p OBJ_REF_DBG_ADD_ARGS);
//
//}
//
//
//template < class TYPE >
//inline i64 release(__pointer(TYPE) & pointer OBJ_REF_DBG_ADD_PARAMS)
//{
//
//   return release(pointer.m_p OBJ_REF_DBG_ADD_ARGS);
//
//}
//
//
//template < class REFERENCE >
//inline i64 release(__reference(REFERENCE) & preference OBJ_REF_DBG_ADD_PARAMS)
//{
//
//   return release(preference.m_p OBJ_REF_DBG_ADD_ARGS);
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
//   //__pointer(::user::document) session::create_form(__pointer(::user::interaction) pwndParent, var var, ::var varArgs)
//   //{
//
//   //   return create_form(__type(VIEW), pwndParent, var);
//
//   //}
//
//
//   //template < typename VIEW >
//   //__pointer(::user::document) session::create_child_form(__pointer(::user::interaction) pwndParent, var var)
//   //{
//
//   //   return create_child_form(__type(VIEW), pwndParent, var);
//
//   //}
//
//
//} // namespace apex


#if !defined(DEBUG)


inline void object::set_context(::context* pcontext)
{

   m_pcontextContext = pcontext;

}


inline void object::set_context_thread(::thread* pthread)
{

   m_pthreadContext = pthread;

}


inline void object::set_context_app(::apex::application* pappContext)
{

   m_pappContext = pappContext;

}


inline void object::set_context_session(::apex::session* psessionContext)
{

   m_psessionContext = psessionContext;

}


inline void object::set_context_system(::apex::system* psystemContext)
{

   m_psystemContext = psystemContext;

}


#endif



inline ::object * get_context_object()
{
   
   return ::get_context();
   
}


