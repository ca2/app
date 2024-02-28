#pragma once


class CLASS_DECL_CA2_MATH numeric_parsing_exception:
   virtual public ::exception
{
public:


   numeric_parsing_exception(::particle * pparticle, const ::string & strMessage);
   virtual ~numeric_parsing_exception();


};


CLASS_DECL_CA2_MATH bool get_avoid_numeric_parsing_exception();
CLASS_DECL_CA2_MATH bool throw_numeric_parsing_exception(const ::string & strMessage);


class CLASS_DECL_CA2_MATH avoid_numeric_parsing_exception
{
public:

   iptr m_iBefore;

   avoid_numeric_parsing_exception();
   virtual ~avoid_numeric_parsing_exception();

};
