#pragma once



template < typename ITERABLE >
inline ::count __iterable_count(const ITERABLE & iterable)
{

   return iterable.get_count();

}







#ifdef WINDOWS
namespace gen
{
   namespace win
   {
      template < class TYPE, class ARG_TYPE >
      bool CreateSafeArray(array < TYPE, ARG_TYPE > & ar, VARIANT * pvar, VARTYPE vt)
      {
          pvar->vt = VT_ARRAY | vt;
          SAFEARRAYBOUND rgsabound[1];
          rgsabound[0].lLbound = 0;
          rgsabound[0].cElements = get_size();
          pvar->parray = SafeArrayCreate(vt, 1, rgsabound);
          if(pvar->parray == nullptr)
              return false;
          for(i32 i = 0; i < get_size(); i++)
          {
              SafeArrayPutElement(pvar->parray, (long *) &i, &ar.element_at(i));
          }
      }

      template < class TYPE, class ARG_TYPE >
      bool CopySafeArray(array < TYPE, ARG_TYPE > & ar, VARIANT * ::payload)
      {
      //    WINDOWS_DEFINITION_MANAGE_STATE(::windows_definition::GetStaticModuleState())
          ASSERT(pvar->vt == (VT_ARRAY | VT_I4));
          ar.erase_all();
          ::u32 uDim;

          if(1 != (uiDim = SafeArrayGetDim(pvar->parray)))
          {
              ASSERT(false);
              return false;
          }

          HRESULT hr;
          long lLBound;
          long lUBound;

          if(FAILED(hr = SafeArrayGetLBound(pvar->parray, uiDim, &lLBound)))
          {
              return false;
          }

          if(FAILED(hr = SafeArrayGetUBound(pvar->parray, uiDim, &lUBound)))
          {
              return false;
          }

          ::u32 dw;
          for(i32 i = lLBound; i <= lUBound; i++)
          {
              SafeArrayGetElement(pvar->parray, (long *) &i, &dw);
              ar.add(dw);
          }
          return true;

      }
   }
}
#endif
















