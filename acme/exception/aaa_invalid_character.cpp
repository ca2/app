#include "framework.h"


invalid_character::invalid_character(const char * pszMessage):
   ::exception(pszMessage)
{


}


invalid_character::~invalid_character()
{

}

