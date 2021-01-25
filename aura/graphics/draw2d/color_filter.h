#pragma once


class color_filter :
   virtual public ::matter
{
public:


   virtual bool is_identity() const { return false; }
   virtual bool is_opacity_filter() const { return false; }
   virtual bool is_color_matrix_filter() const { return false; }

   virtual double opacity() const { return 1.0; }
   virtual bool get_color_matrix(color_matrix & colormatrix) const { return false; }

};


using color_filter_pointer = __pointer(color_filter);


inline double get_opacity(const color_filter * pfilter)
{

   if (::is_null(pfilter))
   {

      return 1.0;

   }

   return pfilter->opacity();

}


class identiy_color_filter :
   virtual public ::color_filter
{
public:


   virtual bool is_identity() const { return true; }


};


class opacity_color_filter :
   virtual public ::color_filter
{
public:


   double m_dOpacity;


   opacity_color_filter(double dOpacity)
   {

      m_dOpacity = dOpacity;

   }

   virtual bool is_opacity_filter() const { return true; }



   virtual double opacity() const { return m_dOpacity; }

   virtual bool get_color_matrix(color_matrix & colormatrix) const
   {

      colormatrix.clear();

      colormatrix.opacity(m_dOpacity);

      return true;

   }

};


class color_matrix_filter :
   virtual public ::color_filter
{
public:


   color_matrix         m_colormatrix;


   color_matrix_filter(const color_matrix & matrix) :
      m_colormatrix(matrix)
   {
   }

   virtual bool is_color_matrix_filter() const { return true; }


   virtual bool get_color_matrix(color_matrix & colormatrix) const
   {

      colormatrix = m_colormatrix;

      return true;

   }

};

