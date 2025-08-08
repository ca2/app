//
//  reference_count_debug.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 20/06/20.
//  More work on 2023-11-22 12:47 <3ThomasBorregaardSorensen
//
#pragma once


//#include "simple_array.h"


//#include "acme/prototype/collection/array.h"

#if REFERENCING_DEBUGGING




class reference_item_array;

class refdbg
{
public:

   static ::string new_line_quote(::string strRefrain)
   {

      ::string str;

      str.append("\n");
      str.append("\n");
      str.append(strRefrain);
      str.append("\n");
      str.append("\n");

      return str;


   }


   static ::string  dash_quote(::string strRefrain)
   {

      ::string str;

      str.append("---------------------------------------");
      str.append(strRefrain);
      str.append("-----------------------------------------------");

      return str;

   }

};


class CLASS_DECL_ACME referencing_debugging :
   public refdbg
{
public:


   ::critical_section                                             m_criticalsection;
   ::proto < comparable_array < reference_item_array * > >        m_item2a;
   bool                                                           m_bEnable = true;
   long long                                                          m_iCount = 0;


   referencing_debugging();
   ~referencing_debugging();


   virtual void add_item_array(reference_item_array * pitema);
   virtual bool erase_item_array(reference_item_array * pitema);



   virtual void dump_pending_releases();


};



#endif // REFERENCING_DEBUGGING




