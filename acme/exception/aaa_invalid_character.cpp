#include "framework.h"


invalid_character::invalid_character(const ::scoped_string & scopedstrMessage):
   ::exception(scopedstrMessage)
{


}


invalid_character::~invalid_character()
{

}

