#include "framework.h"


invalid_character::invalid_character(const scoped_string & strMessage):
   ::exception(pszMessage)
{


}


invalid_character::~invalid_character()
{

}

