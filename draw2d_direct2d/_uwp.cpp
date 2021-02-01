#include "framework.h"
#include "CustomRenderer.h"

#undef new
#ifdef _UWP
#include <wrl/module.h>
#endif


#ifdef _UWP


//
// Copyright (C) Microsoft Corporation
// All rights reserved.
//

#pragma warning( disable: 4073 )  // initializers put in library initialization area
#pragma init_seg( lib )

extern int __abi___threading_model;
//__abi_Module* __abi_module = nullptr;

#undef Platform

namespace Platform {
	namespace Details {

		//class InProcModule :
		//	public Microsoft::WRL::Module<Microsoft::WRL::InProcDisableCaching, InProcModule>,
		//	public __abi_Module
		//{
		//public:
		//	InProcModule()
		//	{
		//		__abi_module = this;
		//	}

		//	virtual ~InProcModule()
		//	{
		//		__abi_module = nullptr;
		//	}

		//	virtual unsigned long __stdcall __abi_IncrementObjectCount()
		//	{
		//		return Module::IncrementObjectCount();
		//	}

		//	virtual unsigned long __stdcall __abi_DecrementObjectCount()
		//	{
		//		return Module::DecrementObjectCount();
		//	}
		//};

		//auto &module_ = InProcModule::Create();


		// Forward declarations from vccorlib DLL
		HRESULT InitializeData(int __threading_model);
		void UninitializeData(int __threading_model);

		//Initializaton forwarders
		void __cdecl Cleanup();

		// Initialize MoCOM data and clean up handlers
//		int __cdecl Initialize()
//		{
//			//Global initialization
///*			HRESULT hr = InitializeData(__abi___threading_model);
//			if (FAILED(hr))
//			{
//				Cleanup();
//				return hr;
//			}*/
//
//			// Register cleaning handler
//			atexit(Cleanup);
//			return 0;
//		}
//
//		// Global clean up
//		void __cdecl Cleanup()
//		{
//			UninitializeData(__abi___threading_model);
//		}

	} } // namespace Details

//Put initialization data into the department that we can return failure
//#pragma section(".CRT$XIY",long,read)
//extern "C" __declspec(allocate(".CRT$XIY")) void* __abi__initialize = Details::Initialize;

// All required libraries must be pulled in in init.cpp file because it always referenced
// The librairies should not be pulled in vccorlib.h unless it's vccorlib*.lib


#endif










/************************************************************************
*
* File: CustomTextRenderer.cpp
*
* Description:
*
*
*  This file is part of the Microsoft Windows SDK Code Samples.
*
*  Copyright (C) Microsoft Corporation.  All rights reserved.
*
* This source code is intended only as a supplement to Microsoft
* Development Tools and/or on-line documentation.  See these other
* materials for detailed information regarding Microsoft code samples.
*
* THIS CODE AND INFORMATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
************************************************************************/

//#include "DWriteHelloWorld.h"

/******************************************************************
*                                                                 *
*  CustomTextRenderer::CustomTextRenderer                         *
*                                                                 *
*  The constructor stores the Direct2D factory, the render        *
*  target, and the outline and fill brushes used for drawing the  *
*  glyphs, underlines, and strikethroughs.                        *
*                                                                 *
******************************************************************/

CustomTextRenderer::CustomTextRenderer(
   ID2D1Factory* pfactory,
   ID2D1RenderTarget* prendertarget,
   ID2D1Brush* pbrushOutline,
   ID2D1Brush* pbrushFill
   )
   :
   m_cReference(0),
   m_pfactory(pfactory),
   m_prendertarget(prendertarget),
   m_pbrushOutline(pbrushOutline),
   m_pbrushFill(pbrushFill)
{
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::~CustomTextRenderer                        *
*                                                                 *
*  The destructor releases the member variables                   *
*                                                                 *
******************************************************************/

CustomTextRenderer::~CustomTextRenderer()
{
   //m_pfactory->Release();
   //if(m_pbrushOutline != nullptr)
   //{
   //   m_pbrushOutline->Release();
   //}
   //if(m_pbrushFill != nullptr)
   //{
   //   m_pbrushFill->Release();
   //}
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::DrawGlyphRun                               *
*                                                                 *
*  Gets GlyphRun outlines via IDWriteFontFace::GetGlyphRunOutline *
*  and then draws and fills them using Direct2D path geometries   *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::DrawGlyphRun(
   __maybenull void* clientDrawingContext,
   FLOAT baselineOriginX,
   FLOAT baselineOriginY,
   DWRITE_MEASURING_MODE measuringMode,
   __in DWRITE_GLYPH_RUN const* glyphRun,
   __in DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
   IUnknown* clientDrawingEffect
   )
{
   
   HRESULT hr = S_OK;

   Microsoft::WRL::ComPtr<ID2D1PathGeometry>        pPathGeometry;

   Microsoft::WRL::ComPtr<ID2D1GeometrySink>        pSink;

   hr = m_pfactory->CreatePathGeometry(&pPathGeometry);

   if(SUCCEEDED(hr))
   {

      hr = pPathGeometry->Open(&pSink);

   }

   // Get the glyph run outline geometries back from DirectWrite and place them within the
   // geometry sink.
   if(SUCCEEDED(hr))
   {

      hr = glyphRun->fontFace->GetGlyphRunOutline(
         glyphRun->fontEmSize,
         glyphRun->glyphIndices,
         glyphRun->glyphAdvances,
         glyphRun->glyphOffsets,
         glyphRun->glyphCount,
         glyphRun->isSideways,
         glyphRun->bidiLevel % 2,
         pSink.Get()
         );

   }

   // Close the geometry sink
   if(SUCCEEDED(hr))
   {

      hr = pSink->Close();

   }

   // Initialize a matrix to translate the origin of the glyph run.
   D2D1::Matrix3x2F const matrix = D2D1::Matrix3x2F(
      1.0f,0.0f,
      0.0f,1.0f,
      baselineOriginX,baselineOriginY
      );

   // Create the transformed geometry
   Microsoft::WRL::ComPtr<ID2D1TransformedGeometry> pTransformedGeometry;
   if (SUCCEEDED(hr))
   {

      hr = m_pfactory->CreateTransformedGeometry(pPathGeometry.Get(), &matrix, &pTransformedGeometry);

   }

   if (SUCCEEDED(hr))
   {
      
      // Draw the outline of the glyph run
      if (m_pbrushOutline != nullptr)
      {
         
         m_prendertarget->DrawGeometry(pTransformedGeometry.Get(), m_pbrushOutline.Get());

      }

   }

   if (SUCCEEDED(hr))
   {

      if (m_pbrushFill != nullptr)
      {

         m_prendertarget->FillGeometry(pTransformedGeometry.Get(), m_pbrushFill.Get());

      }

   }

   return hr;

}


/******************************************************************
*                                                                 *
*  CustomTextRenderer::DrawUnderline                              *
*                                                                 *
*  Draws underlines below the text using a Direct2D recatangle    *
*  geometry                                                       *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::DrawUnderline(
   __maybenull void* clientDrawingContext,
   FLOAT baselineOriginX,
   FLOAT baselineOriginY,
   __in DWRITE_UNDERLINE const* underline,
   IUnknown* clientDrawingEffect
   )
{
   /*HRESULT hr;

   D2D1_RECT_F rectangle_i32 = D2D1::RectF(
      0,
      underline->offset,
      underline->width,
      underline->offset + underline->thickness
      );

   ID2D1RectangleGeometry* pRectangleGeometry = nullptr;
   hr = m_pfactory->CreateRectangleGeometry(
      &rectangle,
      &pRectangleGeometry
      );

   // Initialize a matrix to translate the origin of the underline
   D2D1::Matrix3x2F const matrix = D2D1::Matrix3x2F(
      1.0f,0.0f,
      0.0f,1.0f,
      baselineOriginX,baselineOriginY
      );

   ID2D1TransformedGeometry* pTransformedGeometry = nullptr;
   if(SUCCEEDED(hr))
   {
      hr = m_pfactory->CreateTransformedGeometry(
         pRectangleGeometry,
         &matrix,
         &pTransformedGeometry
         );
   }

   // Draw the outline of the rectangle_i32
   m_prendertarget->DrawGeometry(
      pTransformedGeometry,
      m_pbrushOutline
      );

   // Fill in the rectangle_i32
   m_prendertarget->FillGeometry(
      pTransformedGeometry,
      m_pbrushFill
      );

      */
   return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::DrawStrikethrough                          *
*                                                                 *
*  Draws strikethroughs below the text using a Direct2D           *
*  recatangle geometry                                            *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::DrawStrikethrough(
   __maybenull void* clientDrawingContext,
   FLOAT baselineOriginX,
   FLOAT baselineOriginY,
   __in DWRITE_STRIKETHROUGH const* strikethrough,
   IUnknown* clientDrawingEffect
   )
{
   /*HRESULT hr;

   D2D1_RECT_F rectangle_i32 = D2D1::RectF(
      0,
      strikethrough->offset,
      strikethrough->width,
      strikethrough->offset + strikethrough->thickness
      );

   ID2D1RectangleGeometry* pRectangleGeometry = nullptr;
   hr = m_pfactory->CreateRectangleGeometry(
      &rectangle,
      &pRectangleGeometry
      );

   // Initialize a matrix to translate the origin of the strikethrough
   D2D1::Matrix3x2F const matrix = D2D1::Matrix3x2F(
      1.0f,0.0f,
      0.0f,1.0f,
      baselineOriginX,baselineOriginY
      );

   ID2D1TransformedGeometry* pTransformedGeometry = nullptr;
   if(SUCCEEDED(hr))
   {
      hr = m_pfactory->CreateTransformedGeometry(
         pRectangleGeometry,
         &matrix,
         &pTransformedGeometry
         );
   }

   // Draw the outline of the rectangle_i32
   m_prendertarget->DrawGeometry(
      pTransformedGeometry,
      m_pbrushOutline
      );

   // Fill in the rectangle_i32
   m_prendertarget->FillGeometry(
      pTransformedGeometry,
      m_pbrushFill
      );

   SafeRelease(&pRectangleGeometry);
   SafeRelease(&pTransformedGeometry);*/

   return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::DrawInlineObject                           *
*                                                                 *
*  This function is not implemented for the purposes of this      *
*  sample.                                                        *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::DrawInlineObject(
   __maybenull void* clientDrawingContext,
   FLOAT originX,
   FLOAT originY,
   IDWriteInlineObject* inlineObject,
   BOOL isSideways,
   BOOL isRightToLeft,
   IUnknown* clientDrawingEffect
   )
{
   // Not implemented
   return E_NOTIMPL;
}

IFACEMETHODIMP_(unsigned long) CustomTextRenderer::AddRef()
{
   return InterlockedIncrement(&m_cReference);
}

IFACEMETHODIMP_(unsigned long) CustomTextRenderer::Release()
{
   unsigned long newCount = InterlockedDecrement(&m_cReference);
   if(newCount == 0)
   {
      delete this;
      return 0;
   }

   return newCount;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::IsPixelSnappingDisabled                    *
*                                                                 *
*  Determines whether pixel snapping is disabled. The recommended *
*  default is FALSE, unless doing animation that requires         *
*  subpixel vertical placement.                                   *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::IsPixelSnappingDisabled(
   __maybenull void* clientDrawingContext,
   __out BOOL* isDisabled
   )
{
   *isDisabled = FALSE;
   return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::GetCurrentTransform                        *
*                                                                 *
*  Returns the current transform applied to the render target..   *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::GetCurrentTransform(
   __maybenull void* clientDrawingContext,
   __out DWRITE_MATRIX* transform
   )
{
   //forward the render target's transform
   m_prendertarget->GetTransform(reinterpret_cast<D2D1_MATRIX_3X2_F*>(transform));
   return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::GetPixelsPerDip                            *
*                                                                 *
*  This returns the number of pixels per DIP.                     *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::GetPixelsPerDip(
   __maybenull void* clientDrawingContext,
   __out FLOAT* pixelsPerDip
   )
{
   float x,yUnused;

   m_prendertarget->GetDpi(&x,&yUnused);
   *pixelsPerDip = x / 96;

   return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::QueryInterface                             *
*                                                                 *
*  Query interface implementation                                 *
*                                                                 *
******************************************************************/

IFACEMETHODIMP CustomTextRenderer::QueryInterface(
   IID const& riid,
   void** ppvObject
   )
{
   if(__uuidof(IDWriteTextRenderer) == riid)
   {
      *ppvObject = this;
   }
   else if(__uuidof(IDWritePixelSnapping) == riid)
   {
      *ppvObject = this;
   }
   else if(__uuidof(IUnknown) == riid)
   {
      *ppvObject = this;
   }
   else
   {
      *ppvObject = nullptr;
      return E_FAIL;
   }

   this->AddRef();

   return S_OK;
}

