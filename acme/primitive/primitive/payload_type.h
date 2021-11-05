// Created by camilo on 2021-08-31 17:44 BRT <3ThomasBS_!!
#pragma once


template<typename VAR>
class payload_type
{
public:

   using VAR_TYPE = VAR;


   VAR_TYPE * this_var() { return (VAR_TYPE *)this; }


   const VAR_TYPE * this_var() const { return (const VAR_TYPE *)this; }

};


struct voidarg : public payload_type < voidarg > { voidarg(); };



