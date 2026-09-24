// Created by camilo on 2026-07-29 16:00 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "osdata_array.h"


osdata_array::osdata_array()
{


}


osdata_array::osdata_array(const osdata_array& a) :
   m_osdata(a.m_osdata)
{


}


osdata_array::osdata_array(osdata_array&& a) :
   m_osdata(::transfer(a.m_osdata))
{


}


osdata_array::~osdata_array()
{


}
