// Created by camilo on Odense, DK Time 2026-11-07 02:32 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#include "platform.h"
#include "_trace_message.h"


::string _001Message(const ::scoped_string& scopedstrTitle, const ::string_array_base& stra)
{

   ::string strMessage;

   strMessage.append_format("\n\n{}:\n{{\n", scopedstrTitle);

   for (auto str : stra)
   {

      strMessage.append_format("   - {}\n", str);

   }

   strMessage.append("}\n\n");

   return ::transfer(strMessage);

}

