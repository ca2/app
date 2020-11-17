#pragma once


/// Base class for implementing the notification stuff.
/// @remarks Inherit public (instead of private) because it wouldn't compile under Dev-C++
template < typename T, typename T2 > class observer :
   virtual public address_array < T * >
{
public:


   typedef address_array < T * > base_type;


   T2 *   m_point2This;

   virtual ~observer()
   {

      for (auto point : *this)
      {

         try
         {

            point->detach_observer(m_point2This);

         }
         catch (...)
         {


         }

      }

   }

   bool attach_observer(T * point)
   {
      if (this->contains(point))
         return false;
      this->add(point);
      m_point2This = dynamic_cast <T2 *>(this);
      point->attach_observer(m_point2This);
      return true;
   }
   bool detach_observer(T * point)
   {
      if (!this->contains(point))
         return false;
      this->remove(point);
      point->detach_observer(m_point2This);
      return true;
   }
};


/// @brief Calculates elapsed CPU time.
/// Is useful for calculating transfer rates.
class CTimer
{
public:

   millis     m_tick;

   CTimer() { Restart(); }

   /// Restarts the timer.
   void Restart() { m_tick.Now(); }

   /// Get the elapsed time in seconds.
   double GetElapsedTime() const
   {
      return __double(m_tick.elapsed()) / 1000.0;
   }

};



