#include "framework.h"
#include "box.h"


namespace user
{


   namespace rich_text
   {


      box::box(span* pspan) :
         m_pspan(pspan)
      {

      }

      
      box::~box()
      {

      }

      
      double box::get_dev_pos_left(::collection::index iPos) const 
      { 
         
         if (m_iPosBeg > m_pspan->m_iPosBeg)
         {

            if (iPos - m_pspan->m_iPosBeg >= m_pspan->m_daPositionDeviceLeft.length())
            {

               return 0.;

            }

            return m_pspan->m_daPositionDeviceLeft[iPos - m_pspan->m_iPosBeg] - m_pspan->m_daPositionDeviceLeft[m_iPosBeg - m_pspan->m_iPosBeg - 1] + m_rectangleBox.left();

         }
         else
         {

            if (iPos - m_iPosBeg >= m_pspan->m_daPositionDeviceLeft.length())
            {

               return 0.;

            }

            return m_pspan->m_daPositionDeviceLeft[iPos - m_iPosBeg] + m_rectangleDevice.left();

         }
      
      }


      double box::get_dev_pos_right(::collection::index iPos) const
      {
         
         if (m_iPosBeg > m_pspan->m_iPosBeg)
         {

            if (iPos - m_pspan->m_iPosBeg >= m_pspan->m_daPositionDeviceRight.length())
            {

               return 0.;

            }

            return m_pspan->m_daPositionDeviceRight[iPos - m_pspan->m_iPosBeg] - m_pspan->m_daPositionDeviceRight[m_iPosBeg - m_pspan->m_iPosBeg - 1] + m_rectangleBox.left();

         }
         else
         {

            if (iPos - m_iPosBeg >= m_pspan->m_daPositionDeviceRight.length())
            {

               return 0.;

            }

            return m_pspan->m_daPositionDeviceRight[iPos - m_iPosBeg] + m_rectangleDevice.left();

         }
      
      }


      double box::get_dev_pos(::collection::index iPos) const
      {

         if (iPos <= m_iPosBeg)
         {

            return m_rectangleDevice.left();

         }
         else if (iPos > m_iPosEnd)
         {

            return m_rectangleDevice.right();

         }
         else
         {

            return ((get_dev_pos_left(iPos) + get_dev_pos_right(iPos - 1)) / 2.0);

         }

      }


      string box::get_text() const
      {

         return m_pspan->m_str.substr(get_beg(), (int)(get_pos_count()));

      }


      double box::get_pos_left(::collection::index iPos) const
      {

         if (m_iPosBeg > m_pspan->m_iPosBeg)
         {

            return m_pspan->m_daPositionLeft[iPos - m_pspan->m_iPosBeg] - m_pspan->m_daPositionLeft[m_iPosBeg - m_pspan->m_iPosBeg - 1] + m_rectangleBox.left();

         }
         else
         {

            return m_pspan->m_daPositionLeft[iPos - m_pspan->m_iPosBeg] + m_rectangleBox.left();

         }

      }


      double box::get_pos_right(::collection::index iPos) const
      {

         if (m_iPosBeg > m_pspan->m_iPosBeg)
         {

            return m_pspan->m_daPositionRight[iPos - m_pspan->m_iPosBeg] - m_pspan->m_daPositionRight[m_iPosBeg - m_pspan->m_iPosBeg - 1] + m_rectangleBox.left();

         }
         else
         {

            return m_pspan->m_daPositionRight[iPos - m_pspan->m_iPosBeg] + m_rectangleBox.left();

         }

      }


      double box::get_pos(::collection::index iPos) const
      {

         if (iPos <= m_iPosBeg)
         {

            return m_rectangleBox.left();

         }
         else if (iPos > m_iPosEnd)
         {

            return m_rectangleBox.right();

         }
         else
         {

            double dPreviousRight = get_pos_right(iPos - 1);

            return dPreviousRight;

  //          double dThisLeft = get_pos_left(iPos);

//            return ((dPreviousRight + dThisLeft) / 2.0) + m_rectangleBox.left();

         }

      }


   } // namespace rich_text


} // namespace user



