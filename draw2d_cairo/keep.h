#pragma once


class CLASS_DECL_DRAW2D_CAIRO cairo_keep
{
public:


   cairo_t *         m_pdc;
   bool              m_bSave;


   cairo_keep(cairo_t * pdc, bool bSave = true);
   ~cairo_keep();


   void save();
   void restore();
   void pulse();


};


