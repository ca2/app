// Created by camilo on 2022-05-08 19:00:00 <3ThomasBorregaardSørensen!!
#include "framework.h"


void conversation::do_message_box(const ::string& strMessage, const string& strTitle, const ::e_message_box& emessagebox, const ::string & strDetails)
{


}


::string conversation::get_message_box_message()
{

   return "";

}


::string conversation::get_message_box_title()
{

   return "";

}


::e_message_box conversation::get_message_box_flags()
{

   return e_message_box_ok;

}


::string conversation::get_message_box_details()
{

   return "";

}


::atom conversation::do_synchronously()
{
   
   return e_message_box_ok;
   
}



