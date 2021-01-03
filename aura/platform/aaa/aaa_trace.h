#pragma once

//class CLASS_DECL_AURA trace_interface
//{
//public:
//
//
//   virtual void __tracea(::object * pcontextobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz) = 0;
//
//
//};



class CLASS_DECL_AURA simple_trace :
   virtual public ::matter
{
public:


   simple_trace();
   virtual ~simple_trace();


   virtual void __tracea(::matter * pcontextobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz) override;


};


extern const char * g_pszTraceLevelName[];
extern char g_chaTraceLevel[];


enum e_log
{

   log_this,

};


class CLASS_DECL_AURA trace_logger
{
public:


   ::matter *            m_pobject;
   const char * const         m_pszFunction;
   const char * const         m_pszFile;
   const i32                  m_iLine;


   trace_logger(const char * pszFunction, const char * pszFile, i32 iLine, ::matter * pcontextobject) :
      m_pszFunction(pszFunction), m_pszFile(pszFile), m_iLine(iLine), m_pobject(pcontextobject)
   {

   }


   inline void __cdecl operator()(e_trace_category ecategory, e_trace_level elevel, const char * pszFormat, ...) const
   {

      va_list ptr;

      va_start(ptr, pszFormat);

      ::__tracev(m_pobject, elevel, m_pszFunction, m_pszFile, m_iLine, pszFormat, ptr);

      va_end(ptr);

   }

   template < typename T >
   inline void __cdecl operator()(T & t) const
   {

      ::__tracea(m_pobject, trace_level_information, m_pszFunction, m_pszFile, m_iLine, (const char *) t);

   }


   inline void __cdecl operator()(const char * pszFormat, ...) const
   {

      va_list valist;

      va_start(valist, pszFormat);

      ::__tracev(m_pobject, trace_level_none, m_pszFunction, m_pszFile, m_iLine, pszFormat, valist);

      va_end(valist);

   }


   inline void __cdecl operator()(e_log elog, const string & strContext, i32 iError, const string & strMessage) const
   {

      ::__tracef(m_pobject, trace_level_none, m_pszFunction, m_pszFile, m_iLine, "%d %d %s", strContext.c_str(), iError, strMessage.c_str());

   }


   inline void __cdecl operator()(::object * pcontextobject, const string & strContext, i32 iError, const string & strMessage) const
   {

      ::__tracef(pcontextobject, trace_level_none, m_pszFunction, m_pszFile, m_iLine, "%d %d %s", strContext.c_str(), iError, strMessage.c_str());

   }


};


class CLASS_DECL_AURA trace_logger_level :
   public trace_logger
{
public:


   e_trace_level           m_elevel;


   trace_logger_level(const char * pszFunction, const char * pszFile, i32 iLine, ::matter * pcontextobject, e_trace_level elevel) :
      trace_logger(pszFunction, pszFile, iLine, pcontextobject),
      m_elevel(elevel)
   {

   }


   inline void operator()(e_trace_category ecategory, const char * pszFormat, ...) const
   {

      va_list ptr;

      va_start(ptr, pszFormat);

      ::__tracev(m_pobject, m_elevel, m_pszFunction, m_pszFile, m_iLine, pszFormat, ptr);

      va_end(ptr);

   }

   template < typename T >
   inline void operator()(T & t) const
   {

      ::__tracea(m_pobject, m_elevel, m_pszFunction, m_pszFile, m_iLine, (const char *) t);

   }

   inline void operator()(const char * pszFormat, ...) const
   {

      if(m_pobject->has(e_object_log_disable))
      {

         return;

      }

      va_list ptr;

      va_start(ptr, pszFormat);

      ::__tracev(m_pobject, m_elevel, m_pszFunction, m_pszFile, m_iLine, pszFormat, ptr);

      va_end(ptr);

   }


   inline void operator()(e_log elog, const string & strContext, i32 iError, const string & strMessage) const
   {

      if (iError == 0)
      {

         ::__tracef(m_pobject, m_elevel, m_pszFunction, m_pszFile, m_iLine, "%s %s", strContext.c_str(), strMessage.c_str());

      }
      else
      {

         ::__tracef(m_pobject, m_elevel, m_pszFunction, m_pszFile, m_iLine, "%s %s (%d)", strContext.c_str(), strMessage.c_str(), iError);

      }

   }


   inline void operator()(::object * pcontextobject, const string & strContext, i32 iError, const string & strMessage) const
   {

      ::__tracef(pcontextobject, m_elevel, m_pszFunction, m_pszFile, m_iLine, "%d %d %s", strContext.c_str(), iError, strMessage.c_str());

   }


};


#undef __trace_logger


#define __trace_logger(trace_context) trace_logger(__FUNCTION__, __FILE__, __LINE__, trace_object(trace_context))


#undef TRACE
#undef _S_TRACE


#define TRACE __trace_logger(ALOG_CONTEXT)
#define _S_TRACE __trace_logger(_S_ALOG_CONTEXT)


#undef WARN
#undef INFO
#undef ERR
#undef FATAL


#undef __trace_logger_level


#define __trace_logger_level(trace_context, trace_level) trace_logger_level(__FUNCTION__, __FILE__, __LINE__, trace_object(trace_context), trace_level)


#define CWARN(category_radix) __trace_logger_level(::trace_object(trace_category_ ## category_radix), trace_level_warning)
#define CINFO(category_radix) __trace_logger_level(::trace_object(trace_category_ ## category_radix), trace_level_information)
#define CERR(category_radix) __trace_logger_level(::trace_object(trace_category_ ## category_radix), trace_level_error)
#define CFATAL(category_radix) __trace_logger_level(::trace_object(trace_category_ ## category_radix), trace_level_fatal)


#define WARN __trace_logger_level(ALOG_CONTEXT, trace_level_warning)
#define INFO __trace_logger_level(ALOG_CONTEXT, trace_level_information)
#define ERR __trace_logger_level(ALOG_CONTEXT, trace_level_error)
#define FATAL __trace_logger_level(ALOG_CONTEXT, trace_level_fatal)


#define _S_WARN __trace_logger_level(_S_ALOG_CONTEXT, trace_level_warning)
#define _S_INFO __trace_logger_level(_S_ALOG_CONTEXT, trace_level_information)
#define _S_ERR __trace_logger_level(_S_ALOG_CONTEXT, trace_level_error)
#define _S_FATAL __trace_logger_level(_S_ALOG_CONTEXT, trace_level_fatal)


namespace aura
{


   CLASS_DECL_AURA void raw_trace_v(const char *pszFileName,i32 nLine,u32 dwCategory,u32 nLevel,const char * pszFmt,va_list args);


   namespace trace
   {




      class trace;


      // Declare a global instance of this class to automatically register a custom trace category at startup
      class CLASS_DECL_AURA category
      {
      public:

         
         e_trace_category           m_ecategory;
         const char *               m_pszName;
         e_trace_level              m_elevelMin;
         bool                       m_bEnabled;


         category();
         ~category();


         e_trace_level get_level() const { return m_elevelMin; }
         void set_level(e_trace_level elevel) { m_elevelMin = elevel;  }
         bool is_enabled() const { return m_bEnabled; }
         void enable(bool bEnable = true) { m_bEnabled = bEnable; }

         operator e_trace_category () const { return m_ecategory; }



      };


      class CLASS_DECL_AURA trace :
         virtual public ::object
      {
      public:


         category       m_categorya[trace_category_count];

         
         trace();
         virtual ~trace();

         //virtual ::e_status initialize(::object* pcontextobject) override;

         category * operator[](e_trace_category ecategory)
         {
            if (ecategory < trace_category_general || ecategory >= trace_category_count)
               return nullptr;
            return &m_categorya[ecategory];
         }

         
         category * enabled_get(e_trace_category ecategory, e_trace_level elevel)
         {

            auto pcategory = operator[](ecategory);
            
            if (pcategory == nullptr)
               return nullptr;
            
            if (!pcategory->is_enabled() || elevel < pcategory->m_elevelMin)
               return nullptr;

            return pcategory;

         }

         void TraceV(const char *pszFileName,i32 nLine,e_trace_category ecategory, e_trace_level elevel,const char * pszFmt,va_list args) const;


         /*bool LoadSettings(const char * pszFileName = nullptr) const
         { return 0 != gen_TraceLoadSettings(pszFileName);}
         void SaveSettings(const char * pszFileName = nullptr) const
         { gen_TraceSaveSettings(pszFileName);}*/

         //map < uptr,uptr,category,category > m_map;


      };



      //CLASS_DECL_AURA void __cdecl TRACE(const char * pszFormat,...);
      //CLASS_DECL_AURA void __cdecl TRACE(const unichar * pszFormat,...);
      //CLASS_DECL_AURA void __cdecl TRACE(uptr dwCategory,::u32 nLevel,const char * pszFormat,...);
      //CLASS_DECL_AURA void __cdecl TRACE(uptr dwCategory,::u32 nLevel,const unichar * pszFormat,...);

   } // namespace trace


};  // namespace aura


CLASS_DECL_AURA const char * get_windows_message_name(::u32 nMsg);



//struct CLASS_DECL_AURA log_context :
//   virtual public ::object
//{
//
//   e_trace_category     m_ecategory;
//   string               m_strContext;
//
//};


