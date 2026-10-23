#include "platform.h"
#include "not_implemented.h"


not_implemented::not_implemented(const ::scoped_string & scopedstrMessage, const ::e_status & estatus) :
   ::exception(estatus, scopedstrMessage)
{
   log_constructor("not_implemented");



}


not_implemented::~not_implemented()
{

}





