// Created by camilo on 2021-08-30 23:47 BRT <3ThomasBS__!!
#pragma once


#ifdef WINDOWS 
#define ARG_SEC_ATTRS_DEF , void * psaAttributes = nullptr
#define ARG_SEC_ATTRS , void * psaAttributes
#define PARAM_SEC_ATTRS (void *) psaAttributes
#define PASS_SEC_ATTRS psaAttributes
#define INSERT_PARAM_SEC_ATTRS(ATTRS) , ATTRS
#define ADD_PARAM_SEC_ATTRS , PARAM_SEC_ATTRS
#define ADD_PASS_SEC_ATTRS , PASS_SEC_ATTRS
#else
#define ARG_SEC_ATTRS_DEF 
#define ARG_SEC_ATTRS
#define PARAM_SEC_ATTRS
#define INSERT_PARAM_SEC_ATTRS(ATTRS) 
#define ADD_PARAM_SEC_ATTRS
#define ADD_PASS_SEC_ATTRS
#endif



