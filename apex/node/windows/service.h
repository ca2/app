#pragma once


namespace windows
{


   class CLASS_DECL_APEX service :
      public service_base
   {
   public:


      SERVICE_STATUS             m_status;

      SERVICE_STATUS_HANDLE      m_handle;

      static service *           s_pservice;
      

      service(u32 controlsAccepted = SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN);
      virtual ~service();


      virtual void Start(u32);

      virtual void Stop(u32);

      virtual void _server();

      virtual void SetServiceStatus();

      virtual void UpdateState(u32 state, HRESULT errorCode = S_OK);

      //virtual void _main_server(::u32 argumentCount, wchar_t * arguments);

      static void WINAPI ServiceMain(DWORD argumentCount, PWSTR * arguments);

      static void WINAPI ServiceHandler(DWORD control);
      
      virtual ::e_status queue_user_work_item(WINULONG flags = WT_EXECUTELONGFUNCTION);

      static DWORD WINAPI thread_proc(void * pcontext);
      
      static void serve(service * pservice);

      virtual void _main_server(::u32 argumentCount, PWSTR * arguments);


   };


} // namespace windows



