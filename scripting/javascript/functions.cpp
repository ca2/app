/*
 * TinyJS
 *
 * A single-file Javascript-alike engine
 *
 * Authored By Gordon Williams <gw@pur3.co.uk>
 *
 * Copyright (C) 2009 Pur3 Ltd
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "framework.h"
#include "tinyjs.h"
#include "functions.h"
////#include "aura/net/sockets/_.h"
//
//
////#include "net/_.h"


//#ifdef _DEBUG
//#	ifdef _MSC_VER
//#		define aaa_memory_new ACME_NEW
//#	endif
//#endif //__DEBUG



//void scIsInNet(CScriptVar *pvar, void *data);
bool is_only_digits(const ::scoped_string & scopedstr);
void scIsPlainHostName(CScriptVar *pvar, void *data);
void scMyIpAddress(CScriptVar *pvar, void *data);



//void scIsInNet(CScriptVar *pvar, void *data)
//{
////	tinyjs *tinyJS = (tinyjs *)data;
//	string host = pvar->getParameter("host")->getString();
//   string addr = pvar->getParameter("addr")->getString();
//   string mask = pvar->getParameter("mask")->getString();
//
//   auto pFind = host.rear_find(':');
//   if(::is_set(pFind))
//      host = host(0, pFind);
//
//
///*   ipaddr_t l_host;
//   if (!Sys(tinyJS->get_context_system()).net().u2ip(host, l_host))
//   {
//   	pvar->getReturnVar()->setInt(false);
//      return;
//   }
//   ipaddr_t l_addr;
//   if (!Sys(tinyJS->get_context_system()).net().u2ip(addr, l_addr))
//   {
//   	pvar->getReturnVar()->setInt(false);
//      return;
//   }
//   ipaddr_t l_mask;
//   if (!Sys(tinyJS->get_context_system()).net().u2ip(mask, l_mask))
//   {
//   	pvar->getReturnVar()->setInt(false);
//      return;
//   }*/
//
//   ::networking::address ad_host(host, 0);
//   ::networking::address ad_addr(addr, 0);
//   ::networking::address ad_mask(mask, 0);
//
//
//	pvar->getReturnVar()->setInt(ad_host.is_in_same_net(ad_addr, ad_mask));
//
//}


bool is_only_digits(const ::scoped_string & scopedstrParam)
{
   const_char_pointer psz = scopedstrParam;
   if(psz == nullptr || *psz == '\0')
      return false;
   while(true)
   {
      if(!ansi_char_isdigit(*psz))
         return false;
      psz++;
      if(*psz == '\0')
         return true;
   }
         
}

void scIsPlainHostName(CScriptVar *pvar, void *data)
{
//	tinyjs *tinyJS = (tinyjs *)data;

//   App(tinyJS->get_app());

   string str = pvar->getParameter("host")->getString();

   string_array stra;

   stra.explode(".", str);

   bool bIpv4 = true;

   if(stra.get_count() == 4)
   {
      for(int i = 0; i < stra.get_size(); i++)
      {
         if(!is_only_digits(stra[i]) || ansi_to_int(stra[i]) > 255)
         {
            bIpv4 = true;
         }
      }
   }

   if(bIpv4)
   {
      pvar->getReturnVar()->setInt(0);
      return;
   }

   
   pvar->getReturnVar()->setInt(str.find_index(".") > 0);

}


void scMyIpAddress(CScriptVar *pvar, void *data)
{
//	tinyjs *tinyJS = (tinyjs *)data;

//   App(tinyJS->get_app());


   pvar->getReturnVar()->setString("127.0.0.1");

}

// ----------------------------------------------- Register Functions
void registerJavascriptFunctions(tinyjs *tinyJS) {
//    tinyJS->addNative("function eval(jsCode)", scEval, tinyJS); // execute the given string and return the result
   //tinyJS->addNative("function isInNet(host, addr, mask)", scIsInNet, tinyJS); // convert to JSON. replacer is ignored at the moment
   tinyJS->addNative("function isPlainHostName(host)", scIsPlainHostName, tinyJS); // convert to JSON. replacer is ignored at the moment
   tinyJS->addNative("function myIpAddress()", scMyIpAddress, tinyJS); // convert to JSON. replacer is ignored at the moment
	// JSON.parse is left out as you can (unsafely!) use eval instead
}

