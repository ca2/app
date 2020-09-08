#pragma once


#ifdef _UWP
#define CREATE_STRUCT_P_CREATE_PARAMS pCreateParams
#else
#define CREATE_STRUCT_P_CREATE_PARAMS lpCreateParams
#endif

class CLASS_DECL_ACME create :
   virtual public ::generic
{
public:

   
   bool                                                        m_bNew;
   string                                                      m_strDescription;
   enum_command                                                m_ecommand;
   string                                                      m_strAppId;
   var                                                         m_varFile;
   var                                                         m_varArgs;
   var                                                         m_varOptions;
   string                                                      m_strExtra;
   ::estatus                                                   m_estatus;

   bool                                                        m_bMakeVisible;
   bool                                                        m_bTransparentBackground;
   bool                                                        m_bClientOnly;
   bool                                                        m_bOuterPopupAlertLike;
   bool                                                        m_bHold;
   ::user::primitive *                                         m_puserinteractionParent;
   ::user::primitive *                                         m_puiAlloc;
   __pointer(command_line)                                     m_pcommandline;
   __pointer(::user::create)                                   m_pusercreate;
   ewindowflag                                                 m_ewindowflag;
   ::id                                                        m_id;

   create();
   create(::generic * pobject, arguments arguments);
   create(::generic * pobject);
   create(::generic * pobject, string strAppId, var varFile, const var & varOptions = __visible(true), ::user::primitive * puiParent = nullptr, ewindowflag eflag = window_flag_none, ::id = ::id());
   virtual ~create();


   void create_common_construct(const var & varOptions, ::user::primitive * puiParent);


   void defer_initialize();

   virtual string get_description();
   virtual void set_description(string strDescription);

   virtual index get_edge();
   //virtual ::application_bias * get_application_bias();


   //create & operator = (const create & create);




};





