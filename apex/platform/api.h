// Created by camilo on 2021-11-05 16:10 PM <3ThomasBorregaardS�rensen!!
#pragma once


class CLASS_DECL_APEX api :
   virtual public ::object
{
public:


   api();
   ~api() override;

   
   ::e_status initialize(::object* pobject) override;


   virtual ::e_status api_login(const ::string & strConfig);


   virtual ::e_status api_get(string strGet, ::payload& payload, property_set & set);


   virtual ::e_status api_download(string strGet, const ::file::path& path, property_set& set);


   virtual string api_token(bool bForce);


};



