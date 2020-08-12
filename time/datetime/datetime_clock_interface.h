#pragma once

class CLASS_DECL_CA2_TIME clock_interface :
   virtual public ::object
{
protected:


   ::datetime::time_span    m_timespan;


public:


   enum EElement
   {
      ElementNull,
      ElementPreviousHour,
      ElementPreviousMinute,
      ElementNextMinute,
      ElementNextHour,
      ElementHourTitle,
      ElementMinuteTitle,
      ElementClock,
   };


   clock_interface(::object * pobject);


   virtual void GetRect(LPRECT lprect, enum EElement eelement);


   virtual void set_time(const ::datetime::time & time);
   virtual void get_time(::datetime::time & time);

   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


   virtual void previous_minute();
   virtual void next_minute();
   virtual void next_hour();
   virtual void previous_hour();

   virtual EElement on_hit_test(::user::item & item);
   virtual bool hit_test(EElement eelement, const ::point & point);
  

};