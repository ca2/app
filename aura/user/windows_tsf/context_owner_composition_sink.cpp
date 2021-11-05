#include "framework.h"
#include "aura/user/_user.h"
#include "edit_window.h"


namespace tsf
{


   STDMETHODIMP edit_window::OnStartComposition(ITfCompositionView * pComposition, BOOL * pfOk)
   {
      OutputDebugString(TEXT("edit_window::OnStartComposition\n"));

      *pfOk = true;

      if (m_cCompositions >= MAX_COMPOSITIONS)
      {
         //can't handle any more compositions
         *pfOk = false;
         return S_OK;
      }

      m_cCompositions++;

      //increment the object count
      pComposition->AddRef();

      //find an empty slot to put the composition pointer in
      ULONG i;
      for (i = 0; i < MAX_COMPOSITIONS; i++)
      {
         if (!m_rgCompositions[i])
         {
            m_rgCompositions[i] = pComposition;
            break;
         }
      }

      _UpdateStatusBar();

      return S_OK;
   }

   /**************************************************************************

      edit_window::OnUpdateComposition()

   **************************************************************************/

   STDMETHODIMP edit_window::OnUpdateComposition(ITfCompositionView * pComposition, ITfRange * pRangeNew)
   {
      OutputDebugString(TEXT("edit_window::OnUpdateComposition\n"));

      _UpdateStatusBar();

      return S_OK;
   }

   /**************************************************************************

      edit_window::OnEndComposition()

   **************************************************************************/

   STDMETHODIMP edit_window::OnEndComposition(ITfCompositionView * pComposition)
   {
      OutputDebugString(TEXT("edit_window::OnEndComposition\n"));

      //find the composition pointer in the array
      ULONG i;
      for (i = 0; i < MAX_COMPOSITIONS; i++)
      {
         if (pComposition == m_rgCompositions[i])
         {
            m_rgCompositions[i]->Release();
            m_rgCompositions[i] = NULL;

            m_cCompositions--;
            break;
         }
      }

      _UpdateStatusBar();

      return S_OK;
   }


   /**************************************************************************

      edit_window::_TerminateAllCompositions()

   **************************************************************************/

   HRESULT edit_window::_TerminateAllCompositions(void)
   {
      HRESULT hr;
      ITfContextOwnerCompositionServices * pCompServices;

      //get the ITfContextOwnerCompositionServices interface pointer
      hr = m_pContext->QueryInterface(IID_ITfContextOwnerCompositionServices, (LPVOID *)& pCompServices);
      if (SUCCEEDED(hr))
      {
         //passing NULL terminates all compositions
         hr = pCompServices->TerminateComposition(NULL);

         pCompServices->Release();
      }

      return hr;
   }


} // namespace tsf



