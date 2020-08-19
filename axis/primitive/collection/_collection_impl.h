#pragma once
















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
      bool CopySafeArray(array < TYPE, ARG_TYPE > & ar, VARIANT * var)
      {
         //    AFX_MANAGE_STATE(AfxGetStaticModuleState())
         ASSERT(pvar->vt == (VT_ARRAY | VT_I4));
         ar.remove_all();
         UINT uiDim;

         if(1 != (uiDim = SafeArrayGetDim(pvar->parray)))
         {
            ASSERT(FALSE);
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

         DWORD dw;
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












//template < typename Type, typename RawType >
//void string_array_base < Type, RawType >::add(const var & var)
//{
//   if(var.is_empty())
//   {
//   }
//   else if(var.get_type() == ::type_stra)
//   {
//      ::papaya::array::add(*this, var.stra());
//   }
//   else if(var.cast < string_array_base < Type, RawType > >() != nullptr)
//   {
//      ::papaya::array::add(*this, *var.cast < string_array_base < Type,RawType > >());
//   }
//   else if(var.get_type() == ::type_vara)
//   {
//      for(i32 i = 0; i < var.vara().get_count(); i++)
//      {
//         ::papaya::array::add(*this,var.vara()[i].get_string());
//      }
//   }
//   else if(var.get_type() == ::type_inta)
//   {
//      for(i32 i = 0; i < var.inta().get_count(); i++)
//      {
//         ::papaya::array::add(*this,__str(var.inta()[i]));
//      }
//   }
//   else if(var.get_type() == ::type_propset)
//   {
//      for(auto assoc : var.propset())
//      {
//         ::papaya::array::add(*this, assoc.get_string());
//      }
//   }
//   else
//   {
//      ::papaya::array::add(*this, var.get_string());
//   }
//}
//
//
//template < typename Type, typename RawType >
//void string_array_base < Type, RawType >::add(const property & prop)
//{
//   add(prop.get_value());
//}
//
//
//template < class Type, class RawType >
//string_array_base < Type, RawType >  & string_array_base < Type, RawType > ::operator = (var varSrc)
//{
//   this->remove_all();
//   if(varSrc.get_type() == ::type_stra)
//   {
//      varSrc.get_array(*this);
//   }
//   else
//   {
//      if(varSrc.get_count() == 1)
//      {
//         add((Type)varSrc.get_string());
//      }
//      else if(varSrc.get_count() > 1)
//      {
//         varSrc.get_array(*this);
//      }
//   }
//   return *this;
//}






//template < typename POINT_TYPE >
//void point_array_base < POINT_TYPE >::offset(UNIT_TYPE x,UNIT_TYPE y)
//{
//   for(i32 i = 0; i < this->get_size(); i++)
//   {
//      this->element_at(i).x += x;
//      this->element_at(i).y += y;
//   }
//}
//

//
//template < typename POINT_TYPE >
//void point_array_base < POINT_TYPE >::rotate(double dAngle)
//{
//
//   UNIT_TYPE x;
//   UNIT_TYPE y;
//   double dCos = cos(dAngle);
//   double dSin = sin(dAngle);
//
//   for(i32 i = 0; i < this->get_count(); i++)
//   {
//      x = this->element_at(i).x;
//      y = this->element_at(i).y;
//      this->element_at(i).x = (LONG)(x * dCos - y * dSin);
//      this->element_at(i).y = (LONG)(x * dSin + y * dCos);
//   }
//
//}



//template < typename POINT_TYPE >
//void point_array_base < POINT_TYPE >::get_bounding_rect(RECT_BASE_TYPE * prect) const
//{
//
//   this->get_bounding_rect(prect,this->get_data(),this->get_count());
//
//
//}
//
//
//template < typename POINT_TYPE >
//void point_array_base < POINT_TYPE >::get_bounding_rect(RECT_BASE_TYPE * prect, const POINT_BASE_TYPE * ppoint, ::count count)
//{
//
//   if(count <= 0)
//   {
//
//      prect->left      = 0;
//
//      prect->top       = 0;
//
//      prect->right     = 0;
//
//      prect->bottom    = 0;
//
//
//   }
//   else
//   {
//      prect->left      = ppoint[0].x;
//
//      prect->top       = ppoint[0].y;
//
//      prect->right     = ppoint[0].x;
//
//      prect->bottom    = ppoint[0].y;
//
//      for(i32 i = 1; i < count; i++)
//      {
//
//         if(ppoint[i].x < prect->left)
//         {
//
//            prect->left = ppoint[i].x;
//
//         }
//         else if(ppoint[i].x > prect->right)
//         {
//
//            prect->right = ppoint[i].x;
//
//         }
//
//         if(ppoint[i].y < prect->top)
//         {
//
//            prect->top = ppoint[i].y;
//
//         }
//         else if(ppoint[i].y > prect->bottom)
//         {
//
//            prect->bottom = ppoint[i].y;
//
//         }
//
//      }
//
//   }
//
//}
//
//
//template < typename POINT_TYPE >
//bool point_array_base < POINT_TYPE >::bounding_rect_contains_pt(const POINT_TYPE & point) const
//{
//   typename POINT_TYPE::RECT_TYPE rect;
//   this->get_bounding_rect(&rect);
//   return rect.contains(point);
//}


//template < typename POINT_TYPE >
//bool point_array_base < POINT_TYPE >::polygon_contains(const POINT_TYPE & point) const
//{
//
//   return ::polygon_contains_point(this->get_data(),(int)this->get_size(), point);
//
//}


//template < typename POINT_TYPE >
//::count point_array_base < POINT_TYPE >::add_unique_range(const POINT_TYPE & pBeg,const POINT_TYPE & pointEnd, const SIZE_TYPE & s)
//{
//
//   UNIT_TYPE x1 = pBeg.x;
//
//   UNIT_TYPE x2 = pointEnd.x;
//
//   UNIT_TYPE y1 = pBeg.y;
//
//   UNIT_TYPE y2 = pointEnd.y;
//
//   __sort(x1,x2);
//
//   __sort(y1,y2);
//
//   ::count c = 0;
//
//   for(UNIT_TYPE x = x1; x <= x2; x+= s.cx)
//   {
//
//      for(UNIT_TYPE y = y1; y <= y2; y+= s.cy)
//      {
//
//         if(this->add_unique(POINT_TYPE(x,y)))
//         {
//
//            c++;
//
//         }
//
//      }
//
//   }
//
//   return c;
//
//}


