#include "framework.h"
#include "trace_category.h"


void trace_category_static_init();
void trace_category_static_term();



pointer_array < trace_category > * trace_category::s_ptracecategorya = nullptr;


void trace_category_static_init()
{

   trace_category::s_ptracecategorya = memory_new pointer_array < trace_category >;

   const ::scoped_string & scopedstra[] =
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

      e_trace_category etracecategory = (e_trace_category)iCategory;

      const ::scoped_string & scopedstrCategory = *p;

      auto pcategory = __new(trace_category(etracecategory, pszCategory));

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
//   //index i = 0;
//
//   //while (pszaCategory[i] != NULL && i < g_ptracecategorya->get_size())
//   //{
//
//   //   g_ptracecategorya->element_at(i).m_ecategory = (e_trace_category) i;
//   //   g_ptracecategorya->element_at(i).raw_set_topic_text(pszaCategory[i]);
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
