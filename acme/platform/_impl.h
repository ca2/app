#pragma once


#if !defined(WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)

namespace std { enum class align_val_t : std::size_t {}; }

#endif


inline block::block(const memory_base & memory) :
   block(memory.get_data(), memory.get_size())
{

}


inline block::block(const memory_base * pmemory) :
   block(pmemory->get_data(), pmemory->get_size())
{

}


inline fork_block::fork_block(const memory_base & memory) :
   fork_block(memory.get_data(), memory.get_size())
{

}


template < typename BLOCK_TYPE >
inline BLOCK_TYPE & memory_template < BLOCK_TYPE > ::operator = (const ::block & block)
{

   if (block.get_size() < get_size())
   {

      __throw(invalid_argument_exception());

   }
   
   ::memcpy_dup(get_data(), block.get_data(), (size_t) get_size());
   
   return *get_data();

}

struct lparam_dbg :
   virtual generic
{

};

extern lparam_dbg g_lparamdbg;

inline lparam::lparam(const ::generic * p)
{

   if (is_null(p))
   {

      m_lparam = 0;

      return;

   }

   ((generic *) p)->add_ref(OBJ_REF_DBG_PTR(&g_lparamdbg));

   m_lparam = (LPARAM)p;

}


template<class TYPE>
inline void dump_elements(dump_context & dumpcontext, const TYPE* pElements, ::count nCount)
{

   ENSURE((nCount == 0) || (pElements != nullptr));
   ASSERT((nCount == 0) ||
          __is_valid_address(pElements, (size_t)nCount * sizeof(TYPE), FALSE));
#ifdef WINDOWS
   &dumpcontext; // not used
   pElements;  // not used
   nCount; // not used
#endif
   // default does nothing

}


template<class TYPE>
inline void CopyElements(TYPE* pDest, const TYPE* pSrc, ::count nCount)
{

   ENSURE((nCount == 0) || ((pDest != 0) && (pSrc != 0)));
   ASSERT((nCount == 0) || __is_valid_address(pDest, (size_t)nCount * sizeof(TYPE)));
   ASSERT((nCount == 0) || __is_valid_address(pSrc, (size_t)nCount * sizeof(TYPE)));

   // default is element-copy using assignment
   while (nCount--)
   {

      *pDest++ = *pSrc++;

   }

}



class CLASS_DECL_ACME c_class
{
public:


   static c_class s_cclass;


   c_class();
   c_class(const c_class &);
   virtual ~c_class();


};


//namespace acme
//{
//
//
//   template < class APP >
//   __result(::acme::application) single_application_library < APP > ::get_new_application(::generic * pobject, const char * pszAppId)
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
//      __pointer(::acme::application) papp;
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
//} // namespace acme


inline bool IsDirSep(WCHAR ch)
{

   return (ch == '\\' || ch == '/');

}


#define new ACME_NEW


template < typename T >
::file::path memcnts_path(T * pthis)
{

   string str = typeid(*pthis).name();

   str.replace("::", "/");

   return memcnts_base_path() / (str + ".txt");

}


template < typename T >
void memcnts_inc(T * pthis)
{

   if (memcnts())
   {

      sync_lock sl(g_pmutexMemoryCounters);

      ::file::path path = memcnts_path(pthis);

      int i = atoi(file_as_string(path));

      file_put_contents_dup(path, __str(i + 1));

   }

}


template < typename T >
void memcnts_dec(T * pthis)
{

   if (memcnts())
   {

      sync_lock sl(g_pmutexMemoryCounters);

      ::file::path path = memcnts_path(pthis);

      int i = atoi(file_as_string(path));

      file_put_contents_dup(path, __str(i - 1));

   }

}


//template < typename RECEIVER >
//void channel::add_route (RECEIVER * preceiver, void (RECEIVER::* phandler)(::message::message * pmessage), ::message::id id)
//{
//
//   add_receiver_route(id, preceiver, phandler);
//
//}

//
//template < typename RECEIVER, typename MESSAGE_PRED >
//void channel::add_route (::message::id id, RECEIVER * preceiverDerived, MESSAGE_PRED message_pred)
//{
//
//   get_typed_route < typename ::remove_reference < decltype(*preceiverDerived) >::TYPE, ::message::message >(id, preceiverDerived) = message_pred;
//
//}


//template < typename RECEIVER, typename MESSAGE_TYPE >
//void channel::add_receiver_route(::message::id id, RECEIVER* preceiver, void (RECEIVER::* phandler)(MESSAGE_TYPE* pmessage))
//{
//
//   add_route(id, preceiver).m_pmessageable = __new(::message::receiver_route<RECEIVER, MESSAGE_TYPE>(preceiver, phandler));
//
//}

//
//template < typename RECEIVER >
//::message::route & channel::add_route(::message::id id, RECEIVER * preceiverDerived)
//{
//
//   sync_lock sl(defer_mutex_channel());
//
//   ::generic* pobjectReceiver = dynamic_cast <::generic*> (preceiverDerived);
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
//      index iFind = proutea->pred_find_first(pred);
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
//   generic * preceiver = dynamic_cast <generic*>(preceiverDerived);
//
//   if (preceiver == nullptr)
//   {
//
//      ASSERT(FALSE);
//
//      __throw(invalid_argument_exception());
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
//
//
//template < typename RECEIVER, typename MESSAGE >
//::message::typed_route < MESSAGE > & channel::get_typed_route (::message::id id, RECEIVER * preceiverDerived)
//{
//
//   sync_lock sl(s_pmutexChannel);
//
//   ::generic * pobjectReceiver = dynamic_cast < ::generic * > (preceiverDerived);
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
//      index iFind = proutea->pred_find_first(pred);
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
//   ::generic * preceiver = dynamic_cast < generic * >(preceiverDerived);
//
//   if (preceiver == nullptr)
//   {
//
//      ASSERT(FALSE);
//
//      __throw(invalid_argument_exception());
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


namespace acme
{


   template < typename T >
   inline void delobj(T * & p)
   {

      //Thank you Fiora a Eterna!!

      //Fiora Aeterna☄ ‏@FioraAeterna 20m20 minutes ago

      //   maybe it's cynical but I'm starting to think the real reason so many newer games have constant autosaves is because they crash all the time
      //   Details

      // BRT 2015-02-18 19:08
      // catch all (...) here in acme::del ... but should remove try catch from all underlying calls (frees, memory_frees, memory_dbg_frees).

      try
      {

         if (::is_set(p))
         {

            T * pdel = p;

            p = nullptr;

            delete pdel;

         }

      }
      catch (...)
      {

      }

   }


} // namespace acme


inline stream & operator >> (stream & s, ::datetime::time & time);


template < typename BASE >
inline __pointer(BASE) alloc_object(::generic * pobject)
{

   return BASE::g_pallocfactory->alloc_object(pobject);

}


template < typename BASE >
inline __pointer(BASE) & alloc_object(__pointer(BASE) & p, ::generic * pobject)
{

   return p = ::alloc_object < BASE > (pobject);

}

//
//inline class ::sync * generic::get_mutex()
//{
//
//   return ::is_null(this) ? nullptr : mutex();
//
//}


template < typename TDST, typename TSRC >
inline __pointer(TDST) & clone(__pointer(TDST) & dst, const __pointer(TSRC) & src)
{

   if (src.is_null())
   {

      dst.release();

      return dst;

   }

   return dst = src->clone();

}


template < typename T >
inline __pointer(T) clone(const __pointer(T) & t)
{

   if (t.is_null())
   {

      return nullptr;

   }

   return t->clone();

}


//CLASS_DECL_ACME inline ::context * get_context(::generic * pobject)
//{
//
//   if (pobject == nullptr)
//   {
//
//      return ::get_context();
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
//   return ::get_context();
//
//}
//
//
//CLASS_DECL_ACME inline ::acme::application * get_context_application(::generic * pobject)
//{
//
//   if (pobject == nullptr)
//   {
//
//      return ::get_context_application();
//
//   }
//
//   ::acme::application * papplication = pobject->get_context_application();
//
//   if (papplication != nullptr)
//   {
//
//      return papplication;
//
//   }
//
//   return ::get_context_application();
//
//}
//
//
//CLASS_DECL_ACME inline ::acme::session * get_context_session(::generic * pobject)
//{
//
//   if (pobject == nullptr)
//   {
//
//      return ::get_context_session();
//
//   }
//
//   ::acme::session * psessionContext = pobject->get_context_session();
//
//   if (psessionContext != nullptr)
//   {
//
//      return psessionContext;
//
//   }
//
//   return ::get_context_session();
//
//}
//
//
//CLASS_DECL_ACME inline ::acme::system * get_context_system(::generic * pobject)
//{
//
//   if (pobject == nullptr)
//   {
//
//      return ::get_context_system();
//
//   }
//
//   ::acme::system * psystemContext = pobject->get_context_system();
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
//
//
//CLASS_DECL_ACME inline ::generic * get_app_object()
//{
//
//   return ::get_context_application();
//
//}
//
//
//CLASS_DECL_ACME inline ::context * get_context(::context * pcontext)
//{
//
//   return pcontext;
//
//}
//
//
//CLASS_DECL_ACME inline ::acme::application * get_context_application(::acme::application * papp)
//{
//
//   return papp;
//
//}
//
//
//CLASS_DECL_ACME inline ::acme::session * get_context_session(::acme::session * psession)
//{
//
//   return psession;
//
//}
//
//
//CLASS_DECL_ACME inline ::acme::system * get_context_system(::acme::system * psystem)
//{
//
//   return psystem;
//
//}


template < typename T >
inline __pointer(T) & pointer < T >::clone(::generic * pobjectContext)
{

   if (::is_null(pobjectContext))
   {

      release();

      return *this;

   }

   return operator = (pobjectContext->clone());

}


//template < typename PRED >
//::image_pointer get_image(::generic * pobject, const var & varFile, bool bAsync = false)
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
//   sync_lock sl(::acme::get_image_mutex());
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


#ifndef __DEBUG

#include "acme/primitive/primitive/block.inl"

#endif // !__DEBUG


namespace str
{


   inline void from(string & str, const tick & tick)
   {

      str.Format(__prtick, tick.m_i);

   }


   inline void from(string & str, const bool & b)
   {

      if(b)
      {

         str = "{[(true)]}";

      }
      else
      {

         str = "{[(false)]}";

      }

   }


} // namespace str


inline void copy(void *, const void *) /* = 0 */ {__throw(interface_only_exception()); }


namespace papaya
{


   namespace chill
   {


      template < typename TYPE >
      inline TYPE default_value()
      {

         __throw(::exception::exception("template only exception"));

      }


   } // namespace chill


} // namespace papaya


inline float i32muldiv(float f, i32 iNum, i32 iDen)
{

   return (float) (f * iNum / iDen);

}


inline double i32muldiv(double d, i32 iNum, i32 iDen)
{

   return (double) (d * iNum / iDen);

}


inline i32 i32muldiv(i32 i, i32 iNum, i32 iDen)
{

   return (i32) ::MulDiv(i, iNum, iDen);

}


#ifndef WINDOWS


inline i64 MulDiv(i64 nNumber, i32 iNum, i32 iDen)
{

   return nNumber * iNum / iDen;

}

#endif


inline ::i64 i32muldiv(::i64 i, i32 iNum, i32 iDen)
{

   return i * iNum / iDen;

}


inline string __str(const ::edisplay & edisplay) { return __str((::e_display) edisplay); }

//
//namespace acme
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
//} // namespace acme


template < typename TYPE >
::stream & read_container_as_parent(::stream & stream, __pointer_array(TYPE) & a)
{

   ::count c = 0;

   stream >> c;

   if (stream.fail())
   {

      return stream;

   }

   while (c > 0)
   {

      auto p = __new(TYPE(&a));

      stream >> *p;

      if (stream.fail())
      {

         break;

      }

      a.add(p);

      c--;

   }

   return stream;

}


template < typename TYPE >
::stream & write_container_as_parent(::stream & stream, const __pointer_array(TYPE) & a)
{

   ::count c = a.get_count();

   stream << c;

   if (stream.fail())
   {

      return stream;

   }

   for (auto & item : a)
   {

      stream >> item;

      c--;

   }

   return stream;

}


template < class c_derived >
inline i64 add_ref(c_derived * pca OBJ_REF_DBG_ADD_PARAMS_DEF)
{

   if (::is_null(pca))
   {

      return -1;

   }

   return pca->add_ref(OBJ_REF_DBG_ARGS);

}


template < class c_derived, typename SOURCE >
inline i64 add_ref(c_derived * & pca, const SOURCE * psource)
{

   c_derived * pderived = dynamic_cast <c_derived *>((SOURCE *)psource);

   if (::is_null(pderived))
   {

      __throw(::exception::exception(::error_wrong_type));

   }

   pca = pderived;

   return add_ref(pca);

}


template < class c_derived, typename SOURCE >
inline i64 add_ref(c_derived *& pderived, const __pointer(SOURCE) & psource)
{

   return add_ref(pderived, psource.m_p);

}


template < class c_derived >
inline i64 release(c_derived *& pca OBJ_REF_DBG_ADD_PARAMS_DEF)
{

   if (::is_null(pca))
   {

      return -1;

   }

   c_derived * ptr = pca;

#ifdef DEBUG

//   ::id id = p->m_id;
   //char * pszType = nullptr;
   //
   //try
   //{

   //   pszType = _strdup(typeid(*p).name());

   //}
   //catch (...)
   //{

   //   ::output_debug_string("exception release strdup(typeid(*p).name())\n");

   //}

#endif

   try
   {

      pca = nullptr;

   }
   catch (...)
   {

      //::output_debug_string("exception release pca = nullptr; (" + string(id) + ")\n");
      ::output_debug_string("exception release pca = nullptr; \n");

   }

   try
   {

      return ptr->release(OBJ_REF_DBG_ARGS);

   }
   catch (...)
   {

      //::output_debug_string("exception release p->release() (" + string(id) + ")\n");
      ::output_debug_string("exception release p->release() \n");

   }

   //#ifdef DEBUG
   //
   //   try
   //   {
   //
   //      ::free(pszType);
   //
   //   }
   //   catch (...)
   //   {
   //
   //      ::output_debug_string("exception release ::free(pszType)\n");
   //
   //   }
   //
   //#endif

   return -1;

}


template < class COMPOSITE >
inline i64 release(__composite(COMPOSITE) & pcomposite OBJ_REF_DBG_ADD_PARAMS)
{

   return release(pcomposite.m_p OBJ_REF_DBG_ADD_ARGS);

}


template < class TYPE >
inline i64 release(__pointer(TYPE) & pointer OBJ_REF_DBG_ADD_PARAMS)
{

   return release(pointer.m_p OBJ_REF_DBG_ADD_ARGS);

}


template < class REFERENCE >
inline i64 release(__reference(REFERENCE) & preference OBJ_REF_DBG_ADD_PARAMS)
{

   return release(preference.m_p OBJ_REF_DBG_ADD_ARGS);

}


template < class c_derived >
inline i64 ref_count(c_derived * pca)
{

   if (pca == nullptr)
   {

      return -1;

   }

   return pca->get_ref_count();

}



namespace acme
{


   //template < typename VIEW >
   //__pointer(::user::document) session::create_form(__pointer(::user::interaction) pwndParent, var var, ::var varArgs)
   //{

   //   return create_form(__type(VIEW), pwndParent, var);

   //}


   //template < typename VIEW >
   //__pointer(::user::document) session::create_child_form(__pointer(::user::interaction) pwndParent, var var)
   //{

   //   return create_child_form(__type(VIEW), pwndParent, var);

   //}


} // namespace acme


#if !defined(DEBUG)


//inline void generic::set_context(::context* pcontext)
//{
//
//   m_pcontextContext = pcontext;
//
//}
//
//
//inline void generic::set_context_thread(::thread* pthread)
//{
//
//   m_pthreadContext = pthread;
//
//}
//
//
//inline void generic::set_context_app(::acme::application* pappContext)
//{
//
//   m_pappContext = pappContext;
//
//}
//
//
//inline void generic::set_context_session(::acme::session* psessionContext)
//{
//
//   m_psessionContext = psessionContext;
//
//}
//
//
//inline void generic::set_context_system(::acme::system* psystemContext)
//{
//
//   m_psystemContext = psystemContext;
//
//}


#endif



