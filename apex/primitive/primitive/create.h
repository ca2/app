#pragma once


#ifdef _UWP
#define CREATE_STRUCT_P_CREATE_PARAMS pCreateParams
#else
#define CREATE_STRUCT_P_CREATE_PARAMS lpCreateParams
#endif





class CLASS_DECL_APEX create :
   virtual public ::context_object
{
public:

   
   bool                                                        m_bNew;
   string                                                      m_strDescription;
   enum_command                                                m_ecommand;
   string                                                      m_strAppId;
   ::payload                                                   m_varFile;
   ::payload                                                   m_varArgs;
   ::payload                                                   m_varOptions;
   string                                                      m_strExtra;
   ::e_status                                                  m_estatus;

   bool                                                        m_bMakeVisible;
   bool                                                        m_bTransparentBackground;
   bool                                                        m_bClientOnly;
   bool                                                        m_bOuterPopupAlertLike;
   bool                                                        m_bHold;
   ::user::primitive *                                         m_puserinteractionParent;
   ::user::primitive *                                         m_puiAlloc;
   __pointer(command_line)                                     m_pcommandline;
   __pointer(::matter)                                         m_pmatterUserPayload;
   ewindowflag                                                 m_ewindowflag;
   ::id                                                        m_id;


   create();
   virtual ~create();


   
   virtual ::e_status initialize_create(arguments arguments);
   virtual ::e_status initialize_create(string strAppId, ::payload varFile, const ::payload& varOptions = __visible(true), ::user::primitive* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::id = ::id());


   void create_common_construct(const ::payload & varOptions, ::user::primitive * puiParent);


   ::apex::application* create_get_application(::apex::application* pappFallback = nullptr);

   ::e_status finish_initialization();

   virtual string get_description();
   virtual void set_description(string strDescription);

   virtual index get_edge();
   //virtual ::application_bias * get_application_bias();


   //create & operator = (const create & create);


   //inline ::user::system * get_user_create() { return __user_system2(m_pusersystem); }


};





