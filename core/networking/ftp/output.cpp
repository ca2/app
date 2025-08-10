#include "framework.h"
#include "output.h"
//#include "apex/networking/sockets/_sockets.h"


namespace ftp
{


   output::output()
   {
   }

   output::~output()
   {

   }


   void output::OnSendCommand(const command& command, const string_array_base& straArguments)
   {

      if (command.AsString().length() == 0)
         return;

      string strImplode = straArguments.implode(" ");

      if (command.AsString().case_insensitive_contains("PASS"))
      {
         if (strImplode.has_character())
         {
            WriteLine("< PASS **********", "S");
         }
         else
         {
            WriteLine("< PASS ", "S");
         }
      }
      else
      {

         WriteLine("> " + command.AsString() + " " + strImplode, "S");

      }

   }

   void output::OnResponse(const reply & Reply)
   {
      if (Reply.Value().length() == 0)
         return;

      string strStatus = "R"; // rgb(0, 150, 0);
      if (Reply.Code().IsPermanentNegativeCompletionReply())
         strStatus = "N"; // rgb(255, 0, 0);
      else if (Reply.Code().IsTransientNegativeCompletionReply())
         strStatus = "W"; // = rgb(200, 200, 0);

      WriteLine("< " + Reply.Value(), strStatus);

   }

   void output::OnInternalError(const ::scoped_string & scopedstrErrorMsg, const ::scoped_string & scopedstrFileName, unsigned int dwLineNr)
   {

      string strMessage;

      strMessage.formatf(("%s ==> File \"%s\" (%d)"),scopedstrErrorMsg.c_str(), scopedstrFileName.c_str(), dwLineNr);

      WriteLine(strMessage, "E");

   }

   void output::WriteLine(const ::scoped_string & scopedstrLine, const ::scoped_string & scopedstrStatus)
   {

      informationf("%s: %s", scopedstrStatus.c_str(), scopedstrLine.c_str());

   }




} // namespace ftp
