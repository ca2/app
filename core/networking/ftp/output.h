#pragma once


#include "client_socket.h"


namespace ftp
{


   class CLASS_DECL_CORE output :
      virtual public client_socket::notification
   {
   public:


      output();
      virtual ~output();

      virtual void OnInternalError(const ::scoped_string & scopedstrErrorMsg, const ::scoped_string & scopedstrFileName, unsigned int dwLineNr);
      virtual void OnSendCommand(const command& strComamnd, const string_array_base& straArguments);
      virtual void OnResponse(const reply & Reply);

      virtual void WriteLine(const ::scoped_string & scopedstrLine, const ::scoped_string & scopedstrStatus);

   };



} //  namespace ftp

