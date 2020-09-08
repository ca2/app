#pragma once


namespace fs
{


   class item_array;


} // namespace fs


class CLASS_DECL_AQUA command_line :
   virtual public ::object
{
public:

   
   enum enum_command
   {
      command_none,
      command_application_start,
      command_file_new,
      command_file_open,
      command_file_print,
      command_file_print_to,
      command_file_dde,
      command_app_unregister,
      command_file_nothing = -1
   };


   enum_command                     m_ecommand;
   bool                          m_bShowSplash;
   bool                          m_bRunEmbedded;
   bool                          m_bRunAutomated;
   i32                       m_nCmdShow;

   // not valid for file_new
   var                           m_varFile;

   // valid only for file_print_to
   string                        m_strPrinterName;
   string                        m_strDriverName;
   string                        m_strPortName;

   var                           m_varQuery;
   ::file::item_array *            m_pitema;

   __pointer(::aqua::application)       m_pappFork;
   string                        m_strExe;
   string                        m_strApp;
   string                        m_strAppType;
   ::user::primitive *           m_puserinteractionParent;
   index                         m_iEdge;
   manual_reset_event            m_eventReady;
   //application_bias *            m_papplicationbias;
   __reference(::create)         m_pcreate;
   string                        m_strCommandLine;


   command_line();
   command_line(::object * pobject);
   command_line(::object * pobject, const string & strCommandLine);
   ~command_line();


   void common_construct();


   //command_line & operator = (const command_line & commandline);


   virtual void ParseParam(const string & strParam,bool bFlag,bool bLast);
   virtual void ParseParamFlag(const string & strParam);
   virtual void ParseParamNotFlag(const string & strParam);
   virtual void ParseLast(bool bLast);


   virtual void _001ParseCommandLine(const string & strCommandLine);
   virtual void _001ParseCommandLineUri(const string & strCommandLine);

   virtual void _001ParseCommandFork(const string & strCommandFork);
   virtual void _001ParseCommandForkUri(const string & strCommandFork);


};



