#pragma once


//#include "acme/prototype/prototype/pointer.h"


namespace calculator
{


#define INITIALIZE_TABLE(table, function) if(table[0] == 0) function(table)

/*
::payload:
a(ad)*
a = a-z, A-Z, _
d = 0-9
operators:
+ -
* /
=
numbers:
0-9
*/


   class CLASS_DECL_AXIS scanner :
      virtual public ::particle
   {
   public:


      //const_char_pointer input;
      ::ansi_range m_range;
      const_char_pointer next_input;
      ::pointer<class token> m_ptoken;


      scanner();
      virtual ~scanner();



      void initialize(const ::scoped_string & scopedstr);
      void peek();
      void next();
      token * look_ahead();


   };


} // namespace calculator






