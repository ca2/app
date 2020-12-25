/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 2001 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/******************************************************************************

   File:          DataObj.h
   
   Description:   CTSFDataObject definitions.

******************************************************************************/

#ifndef DATAOBJ_H
#define DATAOBJ_H

#include <windows.h>

/**************************************************************************

   CTSFDataObject class definition

**************************************************************************/

class CTSFDataObject : public IDataObject
{
private:
    ::u32       m_ObjRefCount;
    FORMATETC   m_FormatEtc;
    LPWSTR      m_pwszText;
   
public:
    CTSFDataObject();
    ~CTSFDataObject();

    //IUnknown methods
    STDMETHODIMP QueryInterface(REFIID, LPVOID *);
    STDMETHODIMP_(::u32) AddRef();
    STDMETHODIMP_(::u32) Release();

    //IDataObject methods
    STDMETHODIMP GetData(LPFORMATETC, LPSTGMEDIUM);
    STDMETHODIMP GetDataHere(LPFORMATETC, LPSTGMEDIUM);
    STDMETHODIMP QueryGetData(LPFORMATETC);
    STDMETHODIMP GetCanonicalFormatEtc(LPFORMATETC, LPFORMATETC);
    STDMETHODIMP SetData(LPFORMATETC, LPSTGMEDIUM, BOOL);
    STDMETHODIMP EnumFormatEtc(::u32, IEnumFORMATETC**);
    STDMETHODIMP DAdvise(LPFORMATETC, ::u32, IAdviseSink*, LPDWORD);
    STDMETHODIMP DUnadvise(::u32 dwConnection);
    STDMETHODIMP EnumDAdvise(IEnumSTATDATA** ppEnumAdvise);

    //utility methods
    HRESULT _SetText(LPWSTR pwszText);

private:
};


#endif// DATAOBJ_H
