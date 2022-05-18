#pragma once


namespace fs
{


   class item_array;


} // namespace fs


//class CLASS_DECL_APEX command_line :
//   virtual public ::object
//{
//public:
//
//   
//   enum_command                     m_ecommand;
//   bool                             m_bShowSplash;
//   bool                             m_bRunEmbedded;
//   bool                             m_bRunAutomated;
//   i32                              m_nCmdShow;
//
//   // not ok for file_new
//   ::payload                        m_payloadFile;
//
//   // ok only for file_print_to
//   string                           m_strPrinterName;
//   string                           m_strDriverName;
//   string                           m_strPortName;
//
//   ::file::item_array *             m_pitema;
//
//   __pointer(::acme::context)       m_pcontextFork;
//   string                           m_strExe;
//   string                           m_strApp;
//   string                           m_strAppType;
//   ::user::primitive *              m_puserinteractionParent;
//   index                            m_iEdge;
//   manual_reset_event               m_eventReady;
//   ::create *                       m_pcreate;
//   string                           m_strCommandLine;
//
//
//   command_line();
//   ~command_line() override;
//
//
//   void common_construct();
//
//
//   virtual void initialize_command_line2(const string& strCommandLine);
//
//   virtual void initialize_arguments(const ::string_array & straArguments);
//
//
//   //command_line & operator = (const command_line & commandline);
//
//
//   virtual void ParseParam(const ::string & strParam,bool bFlag,bool bLast);
//   virtual void ParseParamFlag(const ::string & strParam);
//   virtual void ParseParamNotFlag(const ::string & strParam);
//   virtual void ParseLast(bool bLast);
//
//
//   virtual void _001ParseCommandLine(const ::string & strCommandLine);
//   virtual void _001ParseCommandLineUri(const ::string & strCommandLine);
//
//   virtual void _001ParseCommandFork(const ::string & strCommandFork);
//   virtual void _001ParseCommandForkUri(const ::string & strCommandFork);
//
//
//   virtual void _001ParseCommandArguments(const ::string_array & straArguments);
//
//
//};
//


