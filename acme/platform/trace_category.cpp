#include "framework.h"
#include "trace_category.h"
//#include "acme/prototype/collection/pointer_array.h"
#include "acme/platform/system.h"


CLASS_DECL_ACME void trace_category_static_init(::platform::system * psystem);
CLASS_DECL_ACME void trace_category_static_term();



pointer_array < trace_category > * trace_category::s_ptracecategorya = nullptr;


void trace_category_static_init(::platform::system * psystem)
{

#if REFERENCING_DEBUGGING

   refdbg_top_track holdtoptrack(psystem);

#endif

   trace_category::s_ptracecategorya = ___new pointer_array < trace_category > ();

   const ::ansi_character * psza[] =
   {
   "general",
      "com",
      "qi",
      "registrar",
      "refcount",
      "windowing",
      "controls",
      "hosting",
      "dbclient",
      "dbprovider",
      "snapin",
      "notimpl",
      "allocation",
      "exception",
      "time",
      "cache",
      "stencil",
      "string",
      "map",
      "util",
      "security",
      "synchronization",
      "isapi",
      "user",
      "user2",
      "user3",
      "user4",
      "appmsg",        // Main message pump trace (includes dde)
      "winmsg",        // windows message tracing
      "cmdrouting",    // windows command routing trace
      "ole",          // special ole callback trace
      "database",     // special database trace
      "internet",     // special internet client trace
      "dumpcontext",   // traces from dump_context
      "memory",      // matter non-kernel memory traces
      "html",         // html traces
      "socket",      // socket traces
      "colorertake5",
      "prodevian",
      NULL
   };


   int iCategory = 0;

   auto p = psza;

   while (*p != nullptr)
   {

      enum_trace_category etracecategory = (enum_trace_category)iCategory;

      const ::scoped_string & scopedstrCategory = *p;

      auto pcategory = __allocate trace_category(etracecategory, scopedstrCategory);

      pcategory->initialize(psystem);

      trace_category::s_ptracecategorya->add(pcategory);

      p++;

      iCategory++;

   }

}


//extern "C"
//void init_trace_category()
//{
//
//
//
//   //::collection::index i = 0;
//
//   //while (scopedstraCategory[i] != NULL && i < g_ptracecategorya->get_size())
//   //{
//
//   //   g_ptracecategorya->element_at(i).m_ecategory = (e_trace_category) i;
//   //   g_ptracecategorya->element_at(i).raw_set_topic_text(scopedstraCategory[i]);
//
//   //}
//
//
//}

//extern "C"
//void term_trace_category()
//{
//
//   //MALLOC_DEL(g_ptracecategorya, trace_category_array);
//
//}


void trace_category_static_term()
{

   ::acme::del(trace_category::s_ptracecategorya);

}




CLASS_DECL_ACME const_char_pointer  trace_category_name(enum_trace_category etracecategory)
{

   if (etracecategory < e_trace_category_first && etracecategory < e_trace_category_count)
   {

      return nullptr;

   }

   return trace_category::s_ptracecategorya->element_at((iptr)etracecategory)->m_strTopicText.c_str();

}


CLASS_DECL_ACME bool enable_trace_category(enum_trace_category etracecategory, bool bEnable)
{

   trace_category::s_ptracecategorya->element_at((iptr)etracecategory)->m_bEnable = bEnable;

   return true;

}


CLASS_DECL_ACME int_bool c_enable_trace_category(enum_trace_category etracecategory, int_bool iEnable)
{

   if (!enable_trace_category(etracecategory, iEnable != false))
   {

      return false;

   }

   return true;

}


CLASS_DECL_ACME const ::particle * general_trace_object()
{

   return trace_category::s_ptracecategorya->element_at(0);

}


CLASS_DECL_ACME const ::particle * trace_object(enum_trace_category etracecategory)
{

   return trace_category::s_ptracecategorya->element_at((iptr)etracecategory);

}


const_char_pointer  g_pszTraceLevelName[] =
{

   "none",
   "info",
   "warning",
   "error",
   "fatal",
   "undefined log level"

};


char g_chaTraceLevel[] =
{

   ' ',
   'I',
   'W',
   'E',
   'F',
   'U'

};


enum_trace_category object_trace_category(::particle * pparticle)
{

   return pparticle->trace_category();

}


const_char_pointer  topic_text(::particle * pparticle)
{

   if (::is_null(pparticle))
   {

      return nullptr;

   }

   return pparticle->topic_text();

}




