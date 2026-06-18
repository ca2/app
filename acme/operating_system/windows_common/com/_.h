// Created by camilo on 2026-05-22 17:14 <3ThomasBorregaardSørensen!!
#pragma once

#include "comptr.h"
#include "hresult_exception.h"

#define øDECL_INTERFACE_MAP()                                                                                          \
   HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppv);                                                  \
   ULONG STDMETHODCALLTYPE AddRef() { return InternalAddRef(); }                                      \
   ULONG STDMETHODCALLTYPE Release() { return InternalRelease(); }

#define øBEGIN_INTERFACE_MAP(class_name, default_interface) \
HRESULT STDMETHODCALLTYPE class_name::QueryInterface(REFIID riid, void **ppv)                                       \
   { \
   if (!ppv) \
      return E_POINTER; \
 \
   *ppv = nullptr; \
   if (riid == IID_IUnknown) \
   { \
 \
      *ppv = (IUnknown *)(default_interface *)this; \
      this->AddRef(); \
return S_OK; \
   }


#define øINTERFACE_MAP_ITEM(interface)                                                                                 \
   else if (riid == __uuidof(interface))                                                                                  \
   {                                                                                                                   \
      *ppv = (interface *)this;                                                                                        \
      AddRef();                                                                                                        \
      return S_OK;                                                                                                     \
   }

#define øEND_INTERFACE_MAP()                                                                                      \
   return E_NOINTERFACE;                                                                                               \
   }
