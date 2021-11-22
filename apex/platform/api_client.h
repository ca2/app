// Created by camilo on 2021-11-17 01:29 PM <3ThomasBorregaardS�rensen!! & Mummi!!
#pragma once


class CLASS_DECL_APEX api_client :
   virtual public ::object
{
public:


   __pointer(::api)     m_papi;


   api_client();
   ~api_client() override;


   virtual ::e_status defer_api();


   virtual ::e_status create_api(const ::string& strImplementation);


};









