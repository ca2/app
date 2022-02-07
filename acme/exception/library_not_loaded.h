// Created by camilo on 2022-02-05 21:31 <3ThomasBorregaardSørensen!! (Thomas likes number 5 : day 5)
#pragma once


class CLASS_DECL_ACME library_not_loaded :
   public ::exception
{
public:


   library_not_loaded(const char * pszMessage = nullptr, const char * pszDetails = nullptr, const ::e_status & estatus = error_library_not_loaded);
   ~library_not_loaded() override;


};
