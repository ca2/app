#include "framework.h"


class CLASS_DECL_AQUA what_exclamation_exclamation :
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







CLASS_DECL_AQUA void throw_what_exclamation_exclamation(const char * psz)
{

   throw what_exclamation_exclamation(psz);

}






