#include "framework.h"


namespace draw2d_direct2d
{


   pen::pen()
   {

      m_pthis = this;
      m_bMetroColor     = false;
      m_crMetro         = 0;

   }


   pen::~pen()
   {

   }


   void pen::dump(dump_context & dumpcontext) const
   {

      ::draw2d::object::dump(dumpcontext);

   }


   bool pen::create(::draw2d::graphics* pgraphicsParam, ::i8 iCreate)
   {

      auto pgraphics = __graphics(pgraphicsParam);

      if((!m_bMetroColor || m_crMetro != m_color) || m_pbrush == nullptr)
      {

         D2D1_COLOR_F color;

         __copy(color, m_color);

         pgraphics->m_prendertarget->CreateSolidColorBrush(color, &m_pbrush);

         if(m_pbrush != nullptr)
         {

            m_osdata[0] = (ID2D1Brush *) m_pbrush.Get();
            
            m_crMetro       = m_color;

            m_bMetroColor   = true;
            
         }

      }

      return m_osdata[0] != nullptr;

   }


   void pen::destroy()
   {

      m_pbrush = nullptr;

      ::draw2d::pen::destroy();

   }


   HRESULT pen::s_RenderPatternToCommandList(ID2D1RenderTarget * pgraphics,D2D1_COLOR_F *pcr)
   {

      HRESULT hr = S_OK;

      //pgraphics->BeginDraw();

      pgraphics->Clear(pcr);

      ID2D1SolidColorBrush * pbr = nullptr;

      //hr = pgraphics->CreateSolidColorBrush(*pcr, &pbr);

      //pgraphics->DrawRectangle(D2D1::RectF(0.f, 0.f, 256.f, 256.f), pbr, 0.f);

      //pbr->Release();

      ///hr = pgraphics->EndDraw();

      return hr;

   }

   HRESULT pen::s_CreatePatternBrush(ID2D1DeviceContext *pDeviceContext, D2D1_COLOR_F * pcr, ID2D1ImageBrush **ppImageBrush)
   {

      HRESULT hrEndDraw = pDeviceContext->EndDraw();

      HRESULT hr = S_OK;
      ID2D1Image *pOldTarget = nullptr;
      pDeviceContext->GetTarget(&pOldTarget);

      ID2D1CommandList *pCommandList = nullptr;
      hr = pDeviceContext->CreateCommandList(&pCommandList);

      if(SUCCEEDED(hr))
      {
         pDeviceContext->SetTarget(pCommandList);
         hr = s_RenderPatternToCommandList(pDeviceContext,pcr);
      }

      pDeviceContext->SetTarget(pOldTarget);

      ID2D1ImageBrush *pImageBrush = nullptr;

      if(SUCCEEDED(hr))
      {
         hr = pCommandList->Close();
      }

      if(SUCCEEDED(hr))
      {

         D2D1_IMAGE_BRUSH_PROPERTIES props;

         props.sourceRectangle.left = 0.f;
         props.sourceRectangle.top = 0.f;
         props.sourceRectangle.right = 256.f;
         props.sourceRectangle.bottom = 256.f;

         props.extendModeX = D2D1_EXTEND_MODE_WRAP;
         props.extendModeY = D2D1_EXTEND_MODE_WRAP;

         props.interpolationMode = D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR;

         hr = pDeviceContext->CreateImageBrush(
              pCommandList,&props,nullptr,&pImageBrush);
      }

      // Fill a rectangle with the image brush.
      /*if (SUCCEEDED(hr))
      {
      pDeviceContext->fill_rect(
      D2D1::RectF(0, 0, 100, 100), pImageBrush);
      }*/

      //pImageBrush->Release();
      pCommandList->Release();
      pOldTarget->Release();

      if(hrEndDraw == S_OK)
      {
         pDeviceContext->BeginDraw();
      }

      if(SUCCEEDED(hr))
      {

         *ppImageBrush = pImageBrush;

      }
      else
      {

         *ppImageBrush = nullptr;
      }

      return hr;
   }

} // namespace draw2d_direct2d



