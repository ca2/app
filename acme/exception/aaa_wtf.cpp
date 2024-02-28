#include "framework.h"


class CLASS_DECL_ACME what_exclamation_exclamation :
   public ::exception
{
public:

   what_exclamation_exclamation(const char * payload) :
      ::exception(payload)
   {

   }
   virtual ~what_exclamation_exclamation()
   {

   }

};







CLASS_DECL_ACME void throw_what_exclamation_exclamation(const ::scoped_string & scopedstr)
{

   throw what_exclamation_exclamation(psz);

}






