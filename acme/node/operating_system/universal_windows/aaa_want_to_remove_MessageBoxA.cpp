#include "framework.h"

#undef new

using namespace ::winrt::Windows::UI::Popups;
using namespace ::winrt::Windows::UI::Xaml;
using namespace ::winrt::Windows::UI::Xaml::Controls;
using namespace ::winrt::Windows::UI::Xaml::Navigation;

class message_box_a
{
public:

   message_box_a();

   int do_modal(String ^ text, String ^ caption, unsigned int uFlags);

   
};

message_box_a::message_box_a()
{
 
}

#define create_a_button(id,text) \
   msg->Commands->Append(ref new UICommand(text,nullptr,id));

int message_box_a::do_modal(String ^ text,String ^ caption,unsigned int uFlags)
{

   MessageDialog^ msg = ref new MessageDialog(text, caption);

   u32 uiType = uFlags & MB_TYPEMASK;

   switch(uiType)
   {
   case MB_OKCANCEL:
      create_a_button("ok","OK");
      create_a_button("cancel","Cancel");
      break;
   case MB_ABORTRETRYIGNORE:
      create_a_button("abort","Abort");
      create_a_button("retry","Retry");
      create_a_button("ignore","Ignore");
      break;
   case MB_YESNOCANCEL:
      create_a_button("yes","Yes");
      create_a_button("no","No");
      create_a_button("cancel","Cancel");
      break;
   case MB_YESNO:
      create_a_button("yes","Yes");
      create_a_button("no","No");
      break;
   case MB_RETRYCANCEL:
      create_a_button("retry","Retry");
      create_a_button("cancel","Cancel");
      break;
   case MB_CANCELTRYCONTINUE:
      create_a_button("cancel","Cancel");
      create_a_button("try","Try");
      create_a_button("continue","Continue");
      break;
   default:
      create_a_button("ok","OK");
      break;
   }


   // Set the command that will be invoked by default 
   msg->DefaultCommandIndex = 0;

   // Set the command to be invoked when escape is pressed 
   msg->CancelCommandIndex = 1;

   // Show the message dialog 
   IUICommand ^ cmd = ::wait(msg->ShowAsync());

   int iResult = e_dialog_result_cancel;

   if(cmd->Id == "ok")
   {

      iResult =  e_dialog_result_ok;





   }
   else if(cmd->Id == "yes")
   {

      iResult =  e_dialog_result_yes;





   }
   else if(cmd->Id == "no")
   {

      iResult =  e_dialog_result_no;





   }
   else if(cmd->Id == "cancel")
   {

      iResult =  e_dialog_result_cancel;





   }
   else if(cmd->Id == "abort")
   {

      iResult =  IDABORT;





   }
   else if(cmd->Id == "retry")
   {

      iResult =  IDRETRY;





   }
   else if(cmd->Id == "ignore")
   {

      iResult =  IDIGNORE;





   }
   else if(cmd->Id == "try")
   {

      iResult =  IDTRYAGAIN;





   }
   else if(cmd->Id == "continue")
   {

      iResult =  IDCONTINUE;





   }

   return iResult;

}




i32 WINAPI MessageBoxA(oswindow interaction_impl,const char * lpText,const char * lpCaption,u32 uFlags)
{

   __UNREFERENCED_PARAMETER(interaction_impl);

   message_box_a a;

   int iResult = a.do_modal(string(lpText),string(lpCaption),uFlags);


   return iResult;


}






