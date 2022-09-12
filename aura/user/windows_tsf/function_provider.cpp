#include "framework.h"
////#include "aura/user/user/_component.h"
#include "edit_window.h"
#include "globals.h"


namespace tsf
{


   STDMETHODIMP edit_window::GetType(GUID * pguid)
   {
      *pguid = GUID_NULL;

      return S_OK;
   }


   STDMETHODIMP edit_window::GetDescription(BSTR * pbstrDesc)
   {
      *pbstrDesc = SysAllocString(L"TSFApp Function Provider");

      return *pbstrDesc ? S_OK : E_OUTOFMEMORY;
   }


   STDMETHODIMP edit_window::GetFunction(REFGUID rguid, REFIID riid, IUnknown ** ppunk)
   {
      HRESULT hr = E_NOINTERFACE;

      *ppunk = NULL;

      if (IsEqualGUID(rguid, GUID_NULL))
      {
      }

      return hr;
   }


   BOOL edit_window::_InitFunctionProvider()
   {
      HRESULT hr = E_FAIL;
      ITfSourceSingle * pSourceSingle;

      hr = m_pthreadmgr->QueryInterface(&pSourceSingle);
      if (SUCCEEDED(hr))
      {
         hr = pSourceSingle->AdviseSingleSink(m_tfClientID, IID_ITfFunctionProvider, (ITfFunctionProvider *)this);

         pSourceSingle->Release();
      }

      return SUCCEEDED(hr);
   }


   void edit_window::_UninitFunctionProvider()
   {
      HRESULT hr;
      ITfSourceSingle * pSourceSingle;

      hr = m_pthreadmgr->QueryInterface(&pSourceSingle);
      if (SUCCEEDED(hr))
      {
         hr = pSourceSingle->UnadviseSingleSink(m_tfClientID, IID_ITfFunctionProvider);

         pSourceSingle->Release();
      }
   }


} // namespace tsf



