#include "framework.h"


class CLASS_DECL_AURA what_exclamation_exclamation :
   public ::exception::exception
{
public:

   what_exclamation_exclamation(const char * payload) :
      ::exception::exception(payload)
   {

   }
   virtual ~what_exclamation_exclamation()
   {

   }

};







CLASS_DECL_AURA void throw_what_exclamation_exclamation(const char * psz)
{

   throw what_exclamation_exclamation(psz);

}






