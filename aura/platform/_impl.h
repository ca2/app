#pragma once


#if !defined(WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID) && !defined(FREEBSD)

namespace std { enum class align_val_t : std::size_t {}; }

#endif


//inline block::block(const memory_base & memory) :
//   block(memory.get_data(), memory.get_size())
//{
//
//}
//
//
//inline block::block(const memory_base * pmemory) :
//   block(pmemory->get_data(), pmemory->get_size())
//{
//
//}
//
//
//inline fork_block::fork_block(const memory_base & memory) :
//   fork_block(memory.get_data(), memory.get_size())
//{
//
//}
//
//
//template < typename BLOCK_TYPE >
//inline BLOCK_TYPE & memory_template < BLOCK_TYPE > ::operator = (const ::block & block)
//{
//
//   if (block.get_size() < get_size())
//   {
//
//      __throw(error_invalid_argument);
//
//   }
//   
//   ::memcpy_dup(get_data(), block.get_data(), (size_t) get_size());
//   
//   return *get_data();
//
//}
//
//struct lparam_debug :
//   virtual matter
//{
//
//};
//
//extern lparam_debug g_lparamdbg;
//
//inline lparam::lparam(const ::object * p)
//{
//
//   if (is_null(p))
//   {
//
//      m_lparam = 0;
//
//      return;
//
//   }
//
//   ((object *) p)->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PTR(&g_lparamdbg));
//
//   m_lparam = (lparam)p;
//
//}
//
//
//template<class TYPE>
//inline void dump_elements(dump_context & dumpcontext, const TYPE* pElements, ::count nCount)
//{
//
//   ENSURE((nCount == 0) || (pElements != nullptr));
//   ASSERT((nCount == 0) ||
//          __is_valid_address(pElements, (size_t)nCount * sizeof(TYPE), false));
//#ifdef WINDOWS
//   &dumpcontext; // not used
//   pElements;  // not used
//   nCount; // not used
//#endif
//   // default does nothing
//
//}
//
//
//template<class TYPE>
//inline void CopyElements(TYPE* pDest, const TYPE* pSrc, ::count nCount)
//{
//
//   ENSURE((nCount == 0) || ((pDest != 0) && (pSrc != 0)));
//   ASSERT((nCount == 0) || __is_valid_address(pDest, (size_t)nCount * sizeof(TYPE)));
//   ASSERT((nCount == 0) || __is_valid_address(pSrc, (size_t)nCount * sizeof(TYPE)));
//
//   // default is matter-copy using assignment
//   while (nCount--)
//   {
//
//      *pDest++ = *pSrc++;
//
//   }
//
//}
//
//
//
//class CLASS_DECL_AURA c_class
//{
//public:
//
//
//   static c_class s_cclass;
//
//
//   c_class();
//   c_class(const c_class &);
//   virtual ~c_class();
//
//
//};


//namespace aura
//{
//
//
//   template < class APP >
//   __pointer(::aura::application) single_application_library < APP > ::get_new_application(::object * pobject, const ::string & pszAppId)
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
//      __pointer(::aura::application) papp;
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
//      auto estatus = papp->initialize(pobject);
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
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
//} // namespace aura


//inline bool IsDirSep(WCHAR ch)
//{
//
//   return (ch == '\\' || ch == '/');
//
//}


#define new ACME_NEW


//template < typename T >
//::file::path memory_counter_path(T * pthis)
//{
//
//   string str = typeid(*pthis).name();
//
//   str.replace("::", "/");
//
//   return memory_counter_base_path() / (str + ".txt");
//
//}


//template < typename T >
//void memory_counter_increment(T * pthis)
//{
//
//   if (memory_counter_on())
//   {
//
//      synchronous_lock synchronouslock(g_pmutexMemoryCounters);
//
//      ::file::path path = memory_counter_path(pthis);
//
//      int i = atoi(m_psystem->m_pacmefile->as_string(path));
//
//      m_psystem->m_pacmefile->put_contents(path, __string(i + 1));
//
//   }
//
//}


//template < typename T >
//void memory_counter_decrement(T * pthis)
//{
//
//   if (memory_counter_on())
//   {
//
//      synchronous_lock synchronouslock(g_pmutexMemoryCounters);
//
//      ::file::path path = memory_counter_path(pthis);
//
//      int i = atoi(m_psystem->m_pacmefile->as_string(path));
//
//      m_psystem->m_pacmefile->put_contents(path, __string(i - 1));
//
//   }
//
//}


//template < typename RECEIVER >
//void channel::add_route (RECEIVER * preceiver, void (RECEIVER::* phandler)(::message::message * pmessage), const ::id & id)
//{
//
//   add_receiver_route(id, preceiver, phandler);
//
//}


//template < typename RECEIVER, typename MESSAGE_PRED >
//void channel::add_route (const ::id & id, RECEIVER * preceiverDerived, MESSAGE_PRED message_predicate)
//{
//
//   get_typed_route < typename ::erase_reference < decltype(*preceiverDerived) >::TYPE, ::message::message >(id, preceiverDerived) = message_predicate;
//
//}


//template < typename RECEIVER, typename MESSAGE_TYPE >
//void channel::add_receiver_route(const ::id & id, RECEIVER* preceiver, void (RECEIVER::* phandler)(MESSAGE_TYPE* pmessage))
//{
//
//   add_route(id, preceiver).m_pmessageable = __new(::message::receiver_route<RECEIVER, MESSAGE_TYPE>(preceiver, phandler));
//
//}


//template < typename RECEIVER >
//::message::route & channel::add_route(const ::id & id, RECEIVER * preceiverDerived)
//{
//
//   synchronous_lock synchronouslock(defer_mutex_channel());
//
//   ::object* pobjectReceiver = dynamic_cast <::object*> (preceiverDerived);
//
//   ::type typeReceiver(typeid(RECEIVER));
//
//   if (!m_bNewChannel && m_idroute.is_empty() && m_idrouteNew.get_count() > 0)
//   {
//
//      m_idroute = m_idrouteNew;
//
//   }
//
//   auto & proutea = m_idroute[id];
//
//   __pointer(::message::route) proute;
//
//   if (proutea.is_set())
//   {
//
//      auto pred = [=](auto & proute)
//      {
//
//         return proute->m_pobjectReceiver == pobjectReceiver && proute->m_typeReceiver == typeReceiver;
//
//      };
//
//      index iFind = proutea->predicate_find_first(pred);
//
//      if (iFind >= 0)
//      {
//
//         proute = proutea->sp_at(iFind);
//
//      }
//
//   }
//
//   object * preceiver = dynamic_cast <object*>(preceiverDerived);
//
//   if (preceiver == nullptr)
//   {
//
//      ASSERT(false);
//
//      __throw(error_invalid_argument);
//
//   }
//
//   if (proute.is_null())
//   {
//
//      proute = ::message::create_typed_route<MESSAGE>(preceiver, pobjectReceiver, typeReceiver);
//
//      if (proute.is_null())
//      {
//
//         throw resource_exception();
//
//      }
//
//      if (proutea.is_null())
//      {
//
//         proutea = __new(::message::route_array);
//
//      }
//
//      proutea->add(proute);
//
//   }
//
//   if (proute.is_null())
//   {
//
//      throw resource_exception();
//
//   }
//
//   return *proute;
//
//}


//template < typename RECEIVER, typename MESSAGE >
//::message::typed_route < MESSAGE > & channel::get_typed_route (const ::id & id, RECEIVER * preceiverDerived)
//{
//
//   synchronous_lock synchronouslock(s_pmutexChannel);
//
//   ::object * pobjectReceiver = dynamic_cast < ::object * > (preceiverDerived);
//
//   ::type typeReceiver(typeid(RECEIVER));
//
//   if(!m_bNewChannel && m_idroute.is_empty() && m_idrouteNew.get_count() > 0)
//   {
//
//      m_idroute = m_idrouteNew;
//
//   }
//
//   __pointer(::message::route_array) & proutea = m_idroute[id];
//
//   __pointer(::message::typed_route < MESSAGE >) proute;
//
//   if (proutea.is_set())
//   {
//
//      auto pred = [=](auto & proute)
//      {
//
//         return proute->m_pobjectReceiver == pobjectReceiver && proute->m_typeReceiver == typeReceiver;
//
//      };
//
//      index iFind = proutea->predicate_find_first(pred);
//
//      if(iFind >= 0)
//      {
//
//         proute = proutea->sp_at(iFind);
//
//      }
//
//   }
//
//   ::object * preceiver = dynamic_cast < object * >(preceiverDerived);
//
//   if (preceiver == nullptr)
//   {
//
//      ASSERT(false);
//
//      __throw(error_invalid_argument);
//
//   }
//
//   if(proute.is_null())
//   {
//
//      proute = ::message::create_typed_route<MESSAGE>(preceiver, pobjectReceiver, typeReceiver);
//
//      if (proutea.is_null())
//      {
//
//         proutea = __new(::message::route_array);
//
//      }
//
//      proutea->add(proute);
//
//   }
//
//   return *proute;
//
//}


//namespace aura
//{
//
//
//   template < typename T >
//   inline void delobj(T * & p)
//   {
//
//      //Thank you Fiora a Eterna!!
//
//      //Fiora Aeterna☄ ‏@FioraAeterna 20m20 minutes ago
//
//      //   maybe it's cynical but I'm starting to think the real reason so many newer games have constant autosaves is because they crash all the time
//      //   Details
//
//      // BRT 2015-02-18 19:08
//      // catch all (...) here in acme::del ... but should erase try catch from all underlying calls (frees, memory_frees, memory_debug_frees).
//
//      try
//      {
//
//         if (::is_set(p))
//         {
//
//            T * pdel = p;
//
//            p = nullptr;
//
//            delete pdel;
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//
//
//} // namespace aura


inline stream & operator >> (stream & s, ::datetime::time & time);


//template < typename BASE >
//inline __pointer(BASE) alloc_object(::object * pobject)
//{
//
//   return BASE::g_pallocfactory->alloc_object(pobject);
//
//}


//template < typename BASE >
//inline __pointer(BASE) & alloc_object(__pointer(BASE) & p, ::object * pobject)
//{
//
//   return p = ::alloc_object < BASE > (pobject);
//
//}


//inline class ::synchronization_object * object::get_mutex()
//{
//
//   return ::is_null(this) ? nullptr : mutex();
//
//}
//
//
//template < typename TDST, typename TSRC >
//inline __pointer(TDST) & clone(__pointer(TDST) & dst, const __pointer(TSRC) & src)
//{
//
//   if (src.is_null())
//   {
//
//      dst.release();
//
//      return dst;
//
//   }
//
//   return dst = src->clone();
//
//}


//template < typename T >
//inline __pointer(T) clone(const __pointer(T) & t)
//{
//
//   if (t.is_null())
//   {
//
//      return nullptr;
//
//   }
//
//   return t->clone();
//
//}


//CLASS_DECL_AURA inline ::context * get_context(::object * pobject)
//{
//
//   if (pobject == nullptr)
//   {
//
//      return get_context();
//
//   }
//
//   ::context * pcontext = pobject->get_context();
//
//   if (pcontext != nullptr)
//   {
//
//      return pcontext;
//
//   }
//
//   return get_context();
//
//}


//CLASS_DECL_AURA inline ::aura::application * get_application(::object * pobject)
//{
//
//   if (pobject == nullptr)
//   {
//
//      return ::get_application();
//
//   }
//
//   ::aura::application * papplication = pobject->get_application();
//
//   if (papplication != nullptr)
//   {
//
//      return papplication;
//
//   }
//
//   return ::get_application();
//
//}


//CLASS_DECL_AURA inline ::aura::session * get_session(::object * pobject)
//{
//
//   if (pobject == nullptr)
//   {
//
//      return ::get_session();
//
//   }
//
//   ::aura::session * psessionContext = pobject->get_session();
//
//   if (psessionContext != nullptr)
//   {
//
//      return psessionContext;
//
//   }
//
//   return ::get_session();
//
//}


//CLASS_DECL_AURA inline ::aura::system * get_context_system(::object * pobject)
//{
//
//   if (pobject == nullptr)
//   {
//
//      return ::get_context_system();
//
//   }
//
//   ::aura::system * psystemContext = pobject->get_context_system();
//
//   if (psystemContext != nullptr)
//   {
//
//      return psystemContext;
//
//   }
//
//   return ::get_context_system();
//
//}


//CLASS_DECL_AURA inline ::object * get_app_object()
//{
//
//   return ::get_application();
//
//}


//CLASS_DECL_AURA inline ::context * get_context(::context * pcontext)
//{
//
//   return pcontext;
//
//}


//CLASS_DECL_AURA inline ::aura::application * get_application(::aura::application * papp)
//{
//
//   return papp;
//
//}


//CLASS_DECL_AURA inline ::aura::session * get_session(::aura::session * psession)
//{
//
//   return psession;
//
//}


//CLASS_DECL_AURA inline ::aura::system * get_context_system(::aura::system * psystem)
//{
//
//   return psystem;
//
//}


//template < typename T >
//inline __pointer(T) & pointer < T >::clone(::object * pobject)
//{
//
//   if (::is_null(pobject))
//   {
//
//      release();
//
//      return *this;
//
//   }
//
//   return operator = (pobject->clone());
//
//}


//template < typename PRED >
//::image_pointer get_image(::object * pobject, const ::payload & payloadFile, bool bAsync = false)
//{
//
//   ::file::path path = payloadFile.get_file_path();
//
//   if (path.is_empty())
//   {
//
//      return nullptr;
//
//   }
//
//   synchronous_lock synchronouslock(::aura::get_image_mutex());
//
//   ::image_pointer & pimage = psystem->m_mapImage[path];
//
//   if (!pimage)
//   {
//
//      pimage = pobject->create_image();
//
//      pimage->set_nok();
//
//      synchronouslock.unlock();
//
//      psystem->m_pimaging->_load_image(pobject->get_context(), pimage, payloadFile, !bAsync, false);
//
//   }
//
//   return pimage;
//
//}


//#ifndef __DEBUG
//
//#include "aura/primitive/primitive/block.inl"
//
//#endif // !__DEBUG


//namespace str
//{
//
//
//   inline void from(string & str, const ::duration & duration)
//   {
//
//      str.format(__prtick, ::duration.m_i);
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


//inline void copy(void *, const void *) /* = 0 */ {throw ::interface_only_exception(); }


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
//         __throw(::exception("template only exception"));
//
//      }
//
//
//   } // namespace chill
//
//
//} // namespace papaya


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


//inline string __string(const ::e_display & edisplay) { return __string((::enum_display) edisplay); }


//namespace aura
//{
//
//
//   template < typename TYPE >
//   bool application::gudo_get(const ::string & strKey, TYPE & obj)
//   {
//
//      ::file::path strPath(strKey);
//
//      strPath.replace("::", "/");
//
//      synchronous_lock synchronouslock(psystem->m_spmutexUserAppData);
//
//      {
//
//         file_pointer file = this->file().get_file(pcontext->m_papexcontext->dir().appdata() / "gudo" / strPath, ::file::e_open_read);
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
//   bool application::gudo_set(const ::string & strKey, const TYPE & obj)
//   {
//
//      string strPath(strKey);
//
//      strPath.replace("::", "/");
//
//      synchronous_lock synchronouslock(psystem->m_spmutexUserAppData);
//
//      {
//
//         file_pointer file = this->file().get_file(pcontext->m_papexcontext->dir().appdata() / "gudo" / strPath, ::file::e_open_write | ::file::e_open_create | ::file::e_open_defer_create_directory);
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
//} // namespace aura


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


//template < class c_derived, typename SOURCE >
//inline i64 increment_reference_count(c_derived * & pca, const SOURCE * psource)
//{
//
//   c_derived * pderived = dynamic_cast <c_derived *>((SOURCE *)psource);
//
//   if (::is_null(pderived))
//   {
//
//      __throw(::exception(::error_wrong_type));
//
//   }
//
//   pca = pderived;
//
//   return increment_reference_count(pca);
//
//}


//template < class c_derived, typename SOURCE >
//inline i64 increment_reference_count(c_derived *& pderived, const __pointer(SOURCE) & psource)
//{
//
//   return increment_reference_count(pderived, psource.m_p);
//
//}


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
//      return ptr->release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
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


//template < class COMPOSITE >
//inline i64 release(__composite(COMPOSITE) & pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
//{
//
//   return release(pcomposite.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}


//template < typename TYPE >
//inline i64 release(__pointer(TYPE) & pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
//{
//
//   return release(pointer.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}


//template < class REFERENCE >
//inline i64 release(__reference(REFERENCE) & preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
//{
//
//   return release(preference.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}


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



//namespace aura
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
//} // namespace aura


//#if !defined(DEBUG)
//
//
//inline void object::set_context(::context* pcontext)
//{
//
//   m_pcontext = pcontext;
//
//}
//
//
//inline void object::set_context_thread(::thread* pthread)
//{
//
//   m_pthread = pthread;
//
//}
//
//
//inline void object::set_context_app(::aura::application* pappContext)
//{
//
//   m_papplication = pappContext;
//
//}
//
//
//inline void object::set_context_session(::aura::session* psessionContext)
//{
//
//   m_psession = psessionContext;
//
//}
//
//
//inline void object::set_context_system(::aura::system* psystemContext)
//{
//
//   m_psystemContext = psystemContext;
//
//}
//
//
//#endif


namespace aura
{


   inline ::aura::system* application::get_system() 
   {
      
      return ::is_set(m_psystem) ? dynamic_cast <::aura::system*> (m_psystem) : nullptr; 
   
   }


   inline ::aura::system* session::get_system() const
   {
      
      return ::is_set(m_psystem) ? dynamic_cast <::aura::system*> (m_psystem) : nullptr; 
   
   }


   //inline ::aura::application* object::get_application()
   //{
   //   
   //   return m_papplication ? m_papplication.cast < ::aura::application >() : nullptr; 
   //
   //}


   //inline ::aura::session * object::get_session()
   //{

   //   return m_psession ? m_psession.cast < ::aura::session >() : nullptr;

   //}


   //inline ::aura::system * object::get_system()
   //{

   //   return ::is_set(m_psystem) ? dynamic_cast < ::aura::system * > (m_psystem) : nullptr;

   //}


   //inline ::aura::application* drawable::get_application()
   //{ 
   //   
   //   return m_papplication ? m_papplication.cast < ::aura::application >() : nullptr; 
   //
   //}


   //inline ::aura::session* drawable::get_session()
   //{
   //   
   //   return m_psession ? m_psession.cast < ::aura::session >() : nullptr; 
   //
   //}

   //
   //inline ::aura::system* drawable::get_system()
   //{
   //   
   //   return ::is_null(m_psystem) ? dynamic_cast <::aura::system*> (m_psystem) : nullptr;
   //
   //}


} // namespace aura



