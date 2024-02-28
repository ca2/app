#pragma once


#include "acme/primitive/data/data.h"


class CLASS_DECL_AXIS form_data :
   virtual public ::data::data
{
public:


   form_data * m_pimpl;


   form_data();
   ~form_data() override;


};
