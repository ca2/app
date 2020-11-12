#pragma once


namespace ftp
{


   class CLASS_DECL_CORE output :
      virtual public client_socket::notification
   {
   public:


      output();
      virtual ~output();

      virtual void OnInternalError(const string& strErrorMsg, const string& strFileName, ::u32 dwLineNr);
      virtual void OnSendCommand(const command& strComamnd, const string_array& straArguments);
      virtual void OnResponse(const reply & Reply);

      virtual void WriteLine(const string & cszLine, const string & strStatus);

   };



} //  namespace ftp

