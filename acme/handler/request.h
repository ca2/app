// From apex (create -> request) by camilo on 2022-12-01 00:59 <3ThomasBorregaardSorensen!!
#pragma once


////#include "acme/prototype/prototype/object.h"
//#include "acme/prototype/prototype/payload.h"
#include "acme/user/user/e_window_flag.h"

#include "acme/parallelization/manual_reset_event.h"


#ifdef UNIVERSAL_WINDOWS
#define CREATE_STRUCT_P_CREATE_PARAMS pCreateParams
#else
#define CREATE_STRUCT_P_CREATE_PARAMS lpCreateParams
#endif


#include "acme/graphics/graphics/output_purpose.h"


class CLASS_DECL_ACME request :
   virtual public ::object,
   virtual public ::graphics::output_purpose
{
public:

   
   bool                             m_bNew;
   string                           m_strDescription;
   enum_command                     m_ecommand;
   string                           m_strAppId;
   ::payload                        m_payloadFile;
   ::payload                        m_payloadArguments;
   ::payload                        m_payloadOptions;
   string                           m_strExtra;
   ::e_status                       m_estatus;
   //::particle_pointer         m_pparticleTopic;

   bool                             m_bDocumentAndFrameCreated = false;
   bool                             m_bDocumentWasModified = false;

   //bool                             m_bMakeVisible;
   bool                             m_bTransparentBackground;
   bool                             m_bExperienceMainFrame;
   bool                             m_bOuterPopupAlertLike;
   bool                             m_bHold;
   ::pointer<::user::element>       m_puserelementParent;
   ::pointer<::user::element>       m_puserelementAlloc;
   //::pointer<command_line>        m_pcommandline;
   ::pointer<::matter>              m_pmatterUserPayload;
   e_window_flag                    m_ewindowflag;
   ::atom                           m_atom;
   //enum_command                   m_ecommand;
   bool                             m_bShowSplash;
   bool                             m_bRunEmbedded;
   bool                             m_bRunAutomated;
   int                              m_nCmdShow;
   ::interlocked_count              m_countStack;

   // not ok for file_new
   //::payload                        m_payloadFile;

   // ok only for file_print_to
   string                           m_strPrinterName;
   string                           m_strDriverName;
   string                           m_strPortName;

   ::file::item_array *             m_pitema;

   ::pointer<::platform::context>       m_pcontextFork;
   string                           m_strExe;
   string                           m_strApp;
   string                           m_strAppType;
   ::collection::index                            m_iEdge;
   manual_reset_event               m_eventReady;
   ::request *                      m_prequest;
   string                           m_strCommandLine;
   ::pointer < ::data::data >       m_pdata;
   ::procedure_array                m_procedureaOnFinishRequest;


   request();
   ~request() override;

  
   //command_line();
   //~command_line() override;


   huge_integer increment_reference_count() override;
   huge_integer decrement_reference_count() override;


   void common_construct();


   virtual void initialize_command_line2(const string& strCommandLine);

   virtual void initialize_arguments(::string_array& straArguments);


   //command_line & operator = (const command_line & commandline);


   virtual void ParseParam(const ::string& strParam, bool bFlag, bool bLast);
   virtual void ParseParamFlag(const ::string& strParam);
   virtual void ParseParamNotFlag(const ::string& strParam);
   virtual void ParseLast(bool bLast);


   virtual void _001ParseCommandLine(const ::string& strCommandLine);
   virtual void _001ParseCommandLineUri(const ::string& strCommandLine);

   virtual void _001ParseCommandFork(const ::string& strCommandFork);
   virtual void _001ParseCommandForkUri(const ::string& strCommandFork);


   virtual void _001ParseCommandArguments(::string_array& straArguments);

   
   virtual void initialize_create(arguments arguments);
   virtual void initialize_create(string strAppId, ::payload payloadFile, const ::payload& varOptions = __visible(true), ::user::element * puiParent = nullptr, e_window_flag eflag = e_window_flag_none, ::atom = ::atom());
   virtual void initialize_create(::data::data * pdata, const ::payload & varOptions = __visible(true), ::user::element * puiParent = nullptr, e_window_flag eflag = e_window_flag_none, ::atom = ::atom());


   void create_common_construct(const ::payload & varOptions, ::user::element * puiParent);


   ::platform::application * create_get_app(::platform::application * pappFallback = nullptr);


   void finish_initialization();

   virtual string get_description();
   virtual void set_description(string strDescription);

   virtual ::collection::index get_edge();
   //virtual ::application_bias * get_application_bias();

   virtual bool has_file() const;
   virtual ::payload get_file() const;
   virtual void set_file_path(const ::payload & payload);
   //request & operator = (const request & request);


   //inline ::user::system * get_user_create() { return __user_system2(m_pusersystem); }

   void destroy() override;

};





