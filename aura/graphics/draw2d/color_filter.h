#pragma once


#include "color_matrix.h"


class CLASS_DECL_AURA color_filter
{
protected:
   
   color_matrix *          m_pcolormatrix;

public:

   
   class ::opacity         m_opacity;
   

   color_filter() { m_pcolormatrix = nullptr; }
   color_filter(::nullptr_t) { m_pcolormatrix = nullptr; }
   color_filter(const class ::opacity & opacity) : m_opacity(opacity), m_pcolormatrix(nullptr){}
   ~color_filter() { ::acme::del(m_pcolormatrix); }

   inline bool is_identity() const { return !m_pcolormatrix ? true : m_pcolormatrix->is_identity(); }
   inline bool is_opacity_filter() const { return m_opacity.is_translucent(); }
   inline bool is_matrix_filter() const { return ::is_set(m_pcolormatrix); }

   inline class ::opacity opacity() const { return m_opacity; }
   inline void opacity(const class ::opacity & opacity) { m_opacity = opacity; }
   bool get_matrix(color_matrix & colormatrix) const;

   color_matrix & matrix() { if (!m_pcolormatrix) m_pcolormatrix = new color_matrix; return *m_pcolormatrix; }

   color_filter & operator = (const color_filter & colorfilter)
   {

      m_opacity = colorfilter.m_opacity;

      if (colorfilter.m_pcolormatrix)
      {
         
         if (m_pcolormatrix)
         {

            *m_pcolormatrix = *colorfilter.m_pcolormatrix;

         }
         else
         {

            m_pcolormatrix = new color_matrix(*colorfilter.m_pcolormatrix);

         }

      }

      return *this;

   }


};

//
//using color_filter_pointer = __pointer(color_filter);
//
//
//inline class ::opacity get_opacity(const color_filter * pfilter)
//{
//
//   if (::is_null(pfilter))
//   {
//
//      return 1.0;
//
//   }
//
//   return pfilter->opacity();
//
//}
//
//
//class identiy_color_filter :
//   virtual public ::color_filter
//{
//public:
//
//
//   virtual bool is_identity() const { return true; }
//
//
//};
//
//
//class opacity_color_filter :
//   virtual public ::color_filter
//{
//public:
//
//
//   class ::opacity         m_opacity;
//
//
//   opacity_color_filter(class ::opacity opacity)
//   {
//
//      m_opacity = opacity;
//
//   }
//
//   virtual bool is_opacity_filter() const { return true; }
//
//
//
//   virtual class ::opacity opacity() const { return m_opacity; }
//
//   virtual bool get_color_matrix(color_matrix & colormatrix) const
//   {
//
//      colormatrix.clear();
//
//      colormatrix.opacity(m_opacity);
//
//      return true;
//
//   }
//
//};
//
//
//class color_matrix_filter :
//   virtual public ::color_filter
//{
//public:
//
//
//   
//
//
//   color_matrix_filter(const color_matrix & matrix) :
//      m_colormatrix(matrix)
//   {
//   }
//
//   virtual bool is_color_matrix_filter() const { return true; }
//
//
//   virtual bool get_color_matrix(color_matrix & colormatrix) const
//   {
//
//      colormatrix = m_colormatrix;
//
//      return true;
//
//   }
//
//};
//
