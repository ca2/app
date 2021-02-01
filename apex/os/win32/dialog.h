#pragma once


namespace win32
{


   class CLASS_DECL_APEX dialog :
      virtual public window
   {
   public:

      bool m_bCreated;
      bool  m_bNew;
      const widechar * m_pszResource;


      dialog();
      dialog(::layered* pobjectContext, const widechar * pszResource);
      virtual ~dialog();


      virtual ::e_status initialize_dialog(::layered * pobjectContext, const widechar * pszResource);

      bool create_dialog(window * pwindow = nullptr);

      static INT_PTR CALLBACK DialogProc(HWND h, UINT u, WPARAM, LPARAM);
      virtual INT_PTR on_dialog_message(const ::id & id, wparam wparam, lparam lparam);

      virtual bool on_init_dialog();
      virtual void on_close();
      virtual void on_notify(NMHDR * p);
      virtual void on_notify(int iCode, int iId);


   };



} // namespace win32



