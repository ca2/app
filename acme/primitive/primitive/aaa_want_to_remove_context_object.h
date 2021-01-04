#pragma once


inline ::matter * trace_object(::matter * pobjectContext) { return pobjectContext; }


using eobject = cflag < ::e_object >;


struct CLASS_DECL_ACME matter :
   virtual public matter
{


   mutable __pointer(sync)                mutex();
   ::sticker *                            m_psticker;
   ::matter *                             get_object(); // Context Object
   ::acme::application *                  get_context_application(); // Context Application
   ::eobject                              m_eobject;
   //::id                                   m_id;
   __pointer(__pointer_array(::matter))     m_preferencea;


   matter() : get_object()(nullptr), get_context_application()(nullptr), m_psticker(nullptr) { }
   matter(::matter * pobjectContext);
   virtual ~matter() { }


   virtual ::e_status     initialize(::matter * pobjectContext) override;
   virtual ::e_status     finalize() override;


   virtual void defer_create_mutex();


   inline const char * topic_text() { return ::is_null(m_psticker) ? nullptr : m_psticker->m_pszTopicText; }
   inline void raw_set_topic_text(const char * psz) { m_psticker->raw_set_topic_text(psz); }

   ::acme::application * get_context_application() const { return get_context_application(); }

   ::matter * get_context_object() const { return get_object(); }

   inline void set_context_object(::matter * pobjectContext)
   {

      get_object() = pobjectContext;

      get_context_application() = ::get_context_application(pobjectContext);

   }


   inline void defer_set_context_object(::matter * pobjectContext)
   {

      if (::is_null(get_object()) && ::is_set(pobjectContext))
      {

         set_context_object(pobjectContext);

      }

   }

   ::i64          m_cRun;




   virtual ::e_status     call() override;

   virtual ::e_status     call(::trait & trait) override;


   inline bool is_storing() const { return m_eobject & object_storing; }
   inline bool is_loading() const { return !is_storing(); }


   //inline ::image_pointer create_image();
   //inline ::image_pointer create_image(int cx, int cy, const ::uid & uidCreateImage = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);
   //inline ::image_pointer create_image(const ::size & size, const ::uid & uidCreateImage = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);

   //inline ::image_pointer preserve_image(::image * pimage, int cx, int cy, const ::uid & uidCreateImage = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);
   //inline ::image_pointer preserve_image(::image * pimage, const ::size & size, const ::uid & uidCreateImage = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);



   inline ::matter * context_trace_object() const { return (::matter *)this; }



   inline bool has_flag(e_object eflag) const { return is_set() && (m_eobject & eflag); }
   inline void set_flag(e_object eflag) { m_eobject |= eflag; }
   inline void clear_flag(e_object eflag) { if (is_set()) m_eobject -= eflag; }



   //inline void __throw(::exception::exception * pe) const;


   virtual void __tracea(matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz);
   virtual void __tracef(matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...);
   virtual void __tracev(matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);


   virtual e_trace_category trace_category(matter * pcontext);
   virtual e_trace_category trace_category();




   virtual __pointer(::matter) clone() const;


   virtual sync * get_mutex() const;


   inline i64 get_ref_count()
   {

      return m_countReference;

   }




   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;




   virtual void io(stream & s);



   virtual stream & write(::stream & stream) const override;
   virtual stream & read(::stream & stream) override;

   //virtual stream & call_write(const ::stream& stream) const { return write((::stream &)(stream)); }

   //virtual stream & call_read(const ::stream & stream) { return read((::stream &)(stream)); }

   //virtual void finalize();

   //virtual void call();

//   virtual string to_string() const;

   virtual void dev_log(string str) const;

   ::matter & operator = (const payload & payload);





#ifdef WINDOWS

   static ::u32 WINAPI s_os_thread_proc(void * p)
   {

      return (::u32)s_thread_proc(p);

   }

#else

   static void * s_os_thread_proc(void * p)
   {

      return (void *)(iptr)s_thread_proc(p);

   }

#endif

   virtual u32 thread_proc();

   static u32 s_thread_proc(void * p)
   {

      __pointer(matter) pdata(p);

      return pdata->thread_proc();

   }

   // very close to the operating system
   hthread_t __create_thread(
      ::e_priority epriority = ::priority_normal,
      ::u32 nStackSize = 0,
      u32 uiCreateFlags = 0,
      LPSECURITY_ATTRIBUTES psa = nullptr,
      ithread_t * puiId = nullptr);


   virtual string to_string() const;


   ::image_pointer create_image();

   //::image_pointer create_image(const ::size & size);
   //inline ::image_pointer create_image(int cx, int cy, ::u64 u64Create = OK, int iGoodStride = -1, bool bPreserve = false);

   inline ::image_pointer create_image(const ::size & size, ::u64 u64Create = OK, int iGoodStride = -1, bool bPreserve = false);

   //inline ::image_pointer preserve_image(::image * pimage, int cx, int cy, const ::uid & uidCreateImage = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1)
   //{
   //   pimage->
   //}
   //inline ::image_pointer preserve_image(::image * pimage, const ::size & size, const ::uid & uidCreateImage = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1)
   //{
   //}


   inline ::image_pointer get_image(const payload & varFile, bool bCache = true, bool bSync = false);
   inline ::image_pointer matter_image(const string & strMatter, bool bCache = true, bool bSync = false);


   ::e_status     create(::image_pointer & pimage);
   ::e_status     compose(__composite(::image) & pimage);

   ::e_status     create(::image_pointer & pimage, const ::size & size, ::u64 u64Create = OK, int iGoodStride = -1, bool bPreserve = false);
   ::e_status     compose(__composite(::image) & pimage, const ::size & size, ::u64 u64Create = OK, int iGoodStride = -1, bool bPreserve = false);


   template < typename TYPE, typename PRED >
   inline ::e_status     pred_create(__pointer(TYPE) & p, PRED predNew);

   inline ::e_status     preserve_resize(::image_pointer & pimage, const ::size & size, ::u64 u64Create = OK, int iGoodStride = -1)
   {
      return create(pimage, size, uidCreate, iGoodStride, true);
   }


   inline ::e_status     preserve_compose(__composite(::image) & pimage, const ::size & size, ::u64 u64Create = OK, int iGoodStride = -1)
   {
      return compose(pimage, size, uidCreate, iGoodStride, true);
   }

   template < typename TYPE, typename PRED >
   inline ::e_status     pred_compose(__composite(TYPE) & p, PRED predNew);

   template < typename TYPE >
   inline ::e_status     compose(__composite(TYPE) & p);

   template < typename TYPE >
   inline ::e_status     compose(__composite(TYPE) & p, const ::id & id);

   template < typename TYPE >
   inline ::e_status     compose_new(__composite(TYPE) & p);


   //template < typename TYPE, typename PRED >
   //inline ::e_status     pred_create(__pointer(TYPE) & p, PRED predNew);

   template < typename TYPE >
   inline ::e_status     create(__pointer(TYPE) & p);

   template < typename TYPE >
   inline ::e_status     create(__pointer(TYPE) & p, const ::id & id);

   //template < typename TYPE >
   //inline ::e_status     create_new(__pointer(TYPE) & p);

   //template < typename TYPE, typename PRED >
   //inline ::e_status     pred_create(TYPE *& p, PRED predNew);

   //template < typename TYPE >
   //inline ::e_status     realize(TYPE *& p);

   //template < typename TYPE >
   //inline ::e_status     realize(TYPE *& p, const ::id & id);

   //template < typename TYPE >
   //inline ::e_status     compose(TYPE *& p);

   template < typename TYPE >
   inline ::e_status     _compose(__composite(TYPE) & p);

   //template < typename TYPE >
   //inline ::e_status     destroy(TYPE * & p);

   using matter::release;

   template < typename TYPE >
   inline ::e_status     release(__composite(TYPE) & p);

   template < typename TYPE >
   inline ::e_status     release(__pointer(TYPE) & p);

};
