//
// Created by camilo on 2025-08-30 10:27 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/filesystem/file/memory_file.h"

class protocol_file :
virtual public ::memory_file
{

public:


   protocol_file();
   ~protocol_file() override;


   void open(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * ppfileexception) override;


   void close() override;


};



