#pragma once


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


   class CLASS_DECL_CA2_MATH scanner :
      virtual public ::object
   {
   public:


      const char * input;
      const char * next_input;
      class token * m_ptoken;


      scanner(::particle * pparticle);
      virtual ~scanner();



      void initialize(const ::scoped_string & scopedstr);
      void peek();
      void next();
      token * look_ahead();


   };


} // namespace calculator






