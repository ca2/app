// From impact_host::exception by camilo on 2022-11-13 02:49 <3ThomasBorregaardSorensen!!
#pragma once


////#include "acme/exception/exception.h"


namespace user
{


   class CLASS_DECL_BASE impact_exception :
      virtual public ::exception
   {
   public:


      ::atom       m_atom;


      impact_exception(const ::atom & atom) : m_atom(atom) {}


   };



} // namespace user



