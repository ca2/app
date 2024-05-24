//
// Created by camilo on Jul/4/2023. ~23:30 <3ThomasBorregaardSoresen!!
//
#pragma once


#include <stdio.h>


CLASS_DECL_ACID FILE * trace_level_FILE(enum_trace_level etracelevel, enum_trace_level etracelevelInformation = e_trace_level_information);
//{
//
//    return etracelevel <= etracelevelInformation ? stdout : stderr;
//
//}

CLASS_DECL_ACID void __clearerr_s(FILE *stream);


//CLASS_DECL_ACID void write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten);



//CLASS_DECL_ACID filesize get_size(FILE * pfile);


//CLASS_DECL_ACID void set_size(FILE * pfile, filesize iSize);


