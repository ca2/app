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

      for (auto p : *this)
      {

         try
         {

            p->detach_observer(m_point2This);

         }
         catch (...)
         {


         }

      }

   }

   bool attach_observer(T * p)
   {
      if (this->contains(p))
         return false;
      this->add(p);
      m_point2This = dynamic_cast <T2 *>(this);
      p->attach_observer(m_point2This);
      return true;
   }

   bool detach_observer(T * p)
   {
      if (!this->contains(p))
         return false;
      this->erase(p);
      p->detach_observer(m_point2This);
      return true;
   }

};


/// @brief Calculates elapsed CPU time.
/// Is useful for calculating transfer rates.
class CTimer
{
public:

   
   class ::time     m_time;


   CTimer() { Restart(); }

   /// Restarts the timer.
   void Restart() { m_time.Now(); }

   /// Get the elapsed time
   class ::time GetElapsedTime() const
   {

      return m_time.elapsed();

   }

};



