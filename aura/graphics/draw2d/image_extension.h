#pragma once


//////////////////////////////////////////////////////////////////////
//   Creator : El Barto (ef00@luc.ac.be)
//   Location : http://www.luc.ac.be/~ef00/ebgfx
//   Date : 09-04-98
//////////////////////////////////////////////////////////////////////


class CLASS_DECL_AURA image_extension :
   virtual public ::object
{
public:


   ::image_pointer                  m_pimage;
   __pointer(image_frame_array)     m_pframea;
   __pointer(image_map)             m_pmap;
   double                           m_dSpeed;




   image_extension();
   virtual ~image_extension();


};
