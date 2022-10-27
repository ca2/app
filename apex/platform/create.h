#pragma once


#include "acme/primitive/string/string.h"
#include "acme/primitive/primitive/payload.h"
#include "acme/parallelization/manual_reset_event.h"


#ifdef _UWP
#define CREATE_STRUCT_P_CREATE_PARAMS pCreateParams
#else
#define CREATE_STRUCT_P_CREATE_PARAMS lpCreateParams
#endif


class CLASS_DECL_APEX create :
   virtual public ::object
{
public:

   
   bool                                                        m_bNew;
   string                                                      m_strDescription;
   enum_command                                                m_ecommand;
   string                                                      m_strAppId;
   ::payload                                                   m_payloadFile;
   ::payload                                                   m_payloadArgs;
   ::payload                                                   m_payloadOptions;
   string                                                      m_strExtra;
   ::e_status                                                 m_estatus;

   bool                                                        m_bMakeVisible;
   bool                                                        m_bTransparentBackground;
   bool                                                        m_bExperienceMainFrame;
   bool                                                        m_bOuterPopupAlertLike;
   bool                                                        m_bHold;
   ::pointer<::user::primitive>                               m_puserprimitiveParent;
   ::pointer<::user::primitive>                               m_puserprimitiveAlloc;
   //::pointer<command_line>                                    m_pcommandline;
   ::pointer<::matter>                                        m_pmatterUserPayload;
   ewindowflag                                                 m_ewindowflag;
   ::atom                                                        m_atom;
   //enum_command                     m_ecommand;
   bool                             m_bShowSplash;
   bool                             m_bRunEmbedded;
   bool                             m_bRunAutomated;
   i32                              m_nCmdShow;

   // not ok for file_new
   //::payload                        m_payloadFile;

   // ok only for file_print_to
   string                           m_strPrinterName;
   string                           m_strDriverName;
   string                           m_strPortName;

   ::file::item_array* m_pitema;

   ::pointer<::acme::context>      m_pcontextFork;
   string                           m_strExe;
   string                           m_strApp;
   string                           m_strAppType;
   ::user::primitive* m_puserinteractionParent;
   index                            m_iEdge;
   manual_reset_event               m_eventReady;
   ::create* m_pcreate;
   string                           m_strCommandLine;



   create();
   ~create() override;

  
   //command_line();
   //~command_line() override;


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
   virtual void initialize_create(string strAppId, ::payload payloadFile, const ::payload& varOptions = __visible(true), ::user::primitive* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::atom = ::atom());


   void create_common_construct(const ::payload & varOptions, ::user::primitive * puiParent);


   ::acme::application * create_get_app(::acme::application * pappFallback = nullptr);


   void finish_initialization();

   virtual string get_description();
   virtual void set_description(string strDescription);

   virtual index get_edge();
   //virtual ::application_bias * get_application_bias();

   virtual bool has_file() const;
   virtual ::payload get_file() const;
   virtual void set_file_path(const ::payload & payload);
   //create & operator = (const create & create);


   //inline ::user::system * get_user_create() { return __user_system2(m_pusersystem); }


};





