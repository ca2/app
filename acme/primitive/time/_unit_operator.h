//
//  _unit_operator.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 15/10/21 09:27 BRT.
//  Copyright © 2021 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once
//template < a_enum ENUM >
//inline int operator -(UniChar ush, ENUM e) { return ush - (int) e; }

//template < primitive_integral INTEGRAL >
//inline integral_nanosecond operator %(const integral_nanosecond & time, INTEGRAL integral) { return integral_nanosecond((::i64)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline integral_nanosecond operator /(const integral_nanosecond & time, INTEGRAL integral) { return integral_nanosecond((::i64)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline integral_nanosecond operator *(const integral_nanosecond & time, INTEGRAL integral) { return integral_nanosecond((::i64)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_nanosecond operator +(const integral_nanosecond & time, INTEGRAL integral) { return integral_nanosecond((::i64)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_nanosecond operator -(const integral_nanosecond & time, INTEGRAL integral) { return integral_nanosecond((::i64)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline integral_microsecond operator %(const integral_microsecond & time, INTEGRAL integral) { return integral_microsecond((::i64)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline integral_microsecond operator /(const integral_microsecond & time, INTEGRAL integral) { return integral_microsecond((::i64)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline integral_microsecond operator *(const integral_microsecond & time, INTEGRAL integral) { return integral_microsecond((::i64)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_microsecond operator +(const integral_microsecond & time, INTEGRAL integral) { return integral_microsecond((::i64)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_microsecond operator -(const integral_microsecond & time, INTEGRAL integral) { return integral_microsecond((::i64)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline integral_millisecond operator %(const integral_millisecond & time, INTEGRAL integral) { return integral_millisecond((::i64)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline integral_millisecond operator /(const integral_millisecond & time, INTEGRAL integral) { return integral_millisecond((::i64)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline integral_millisecond operator *(const integral_millisecond & time, INTEGRAL integral) { return integral_millisecond((::i64)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_millisecond operator +(const integral_millisecond & time, INTEGRAL integral) { return integral_millisecond((::i64)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_millisecond operator -(const integral_millisecond & time, INTEGRAL integral) { return integral_millisecond((::i64)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline integral_second operator %(const integral_second & time, INTEGRAL integral) { return integral_second((::i64)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline integral_second operator /(const integral_second & time, INTEGRAL integral) { return integral_second((::i64)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline integral_second operator *(const integral_second & time, INTEGRAL integral) { return integral_second((::i64)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_second operator +(const integral_second & time, INTEGRAL integral) { return integral_second((::i64)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_second operator -(const integral_second & time, INTEGRAL integral) { return integral_second((::i64)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline integral_minute operator %(const integral_minute & time, INTEGRAL integral) { return integral_minute((::i64)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline integral_minute operator /(const integral_minute & time, INTEGRAL integral) { return integral_minute((::i64)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline integral_minute operator *(const integral_minute & time, INTEGRAL integral) { return integral_minute((::i64)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_minute operator +(const integral_minute & time, INTEGRAL integral) { return integral_minute((::i64)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_minute operator -(const integral_minute & time, INTEGRAL integral) { return integral_minute((::i64)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline integral_hour operator %(const integral_hour & time, INTEGRAL integral) { return integral_hour((::i64)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline integral_hour operator /(const integral_hour & time, INTEGRAL integral) { return integral_hour((::i64)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline integral_hour operator *(const integral_hour & time, INTEGRAL integral) { return integral_hour((::i64)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_hour operator +(const integral_hour & time, INTEGRAL integral) { return integral_hour((::i64)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_hour operator -(const integral_hour & time, INTEGRAL integral) { return integral_hour((::i64)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline integral_day operator %(const integral_day & time, INTEGRAL integral) { return integral_day(time.m_i % integral); }
template < primitive_integral INTEGRAL >
inline integral_day operator /(const integral_day & time, INTEGRAL integral) { return integral_day(time.m_i / integral); }
template < primitive_integral INTEGRAL >
inline integral_day operator *(const integral_day & time, INTEGRAL integral) { return integral_day(time.m_i * integral); }
//template < primitive_integral INTEGRAL >
//inline integral_day operator +(const integral_day & time, INTEGRAL integral) { return integral_day(time.m_i + integral); }
//template < primitive_integral INTEGRAL >
//inline integral_day operator -(const integral_day & time, INTEGRAL integral) { return integral_day(time.m_i - integral); }


//template < primitive_floating FLOATING >
//inline integral_nanosecond operator %(const integral_nanosecond & time, FLOATING floating) { return integral_nanosecond((::i64)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline integral_nanosecond operator /(const integral_nanosecond & time, FLOATING floating) { return integral_nanosecond((::i64)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline integral_nanosecond operator *(const integral_nanosecond & time, FLOATING floating) { return integral_nanosecond((::i64)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline integral_nanosecond operator +(const integral_nanosecond & time, FLOATING floating) { return integral_nanosecond((::i64)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline integral_nanosecond operator -(const integral_nanosecond & time, FLOATING floating) { return integral_nanosecond((::i64)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline integral_microsecond operator %(const integral_microsecond & time, FLOATING floating) { return integral_microsecond((::i64)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline integral_microsecond operator /(const integral_microsecond & time, FLOATING floating) { return integral_microsecond((::i64)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline integral_microsecond operator *(const integral_microsecond & time, FLOATING floating) { return integral_microsecond((::i64)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline integral_microsecond operator +(const integral_microsecond & time, FLOATING floating) { return integral_microsecond((::i64)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline integral_microsecond operator -(const integral_microsecond & time, FLOATING floating) { return integral_microsecond((::i64)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline integral_millisecond operator %(const integral_millisecond & time, FLOATING floating) { return integral_millisecond((::i64)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline integral_millisecond operator /(const integral_millisecond & time, FLOATING floating) { return integral_millisecond((::i64)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline integral_millisecond operator *(const integral_millisecond & time, FLOATING floating) { return integral_millisecond((::i64)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline integral_millisecond operator +(const integral_millisecond & time, FLOATING floating) { return integral_millisecond((::i64)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline integral_millisecond operator -(const integral_millisecond & time, FLOATING floating) { return integral_millisecond((::i64)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline integral_second operator %(const integral_second & time, FLOATING floating) { return integral_second((::i64)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline integral_second operator /(const integral_second & time, FLOATING floating) { return integral_second((::i64)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline integral_second operator *(const integral_second & time, FLOATING floating) { return integral_second((::i64)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline integral_second operator +(const integral_second & time, FLOATING floating) { return integral_second((::i64)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline integral_second operator -(const integral_second & time, FLOATING floating) { return integral_second((::i64)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline integral_minute operator %(const integral_minute & time, FLOATING floating) { return integral_minute((::i64)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline integral_minute operator /(const integral_minute & time, FLOATING floating) { return integral_minute((::i64)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline integral_minute operator *(const integral_minute & time, FLOATING floating) { return integral_minute((::i64)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline integral_minute operator +(const integral_minute & time, FLOATING floating) { return integral_minute((::i64)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline integral_minute operator -(const integral_minute & time, FLOATING floating) { return integral_minute((::i64)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline integral_hour operator %(const integral_hour & time, FLOATING floating) { return integral_hour((::i64)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline integral_hour operator /(const integral_hour & time, FLOATING floating) { return integral_hour((::i64)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline integral_hour operator *(const integral_hour & time, FLOATING floating) { return integral_hour((::i64)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline integral_hour operator +(const integral_hour & time, FLOATING floating) { return integral_hour((::i64)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline integral_hour operator -(const integral_hour & time, FLOATING floating) { return integral_hour((::i64)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline integral_day operator %(const integral_day & time, FLOATING floating) { return integral_day(time.m_i % floating); }
template < primitive_floating FLOATING >
inline integral_day operator /(const integral_day & time, FLOATING floating) { return integral_day(time.m_i / floating); }
template < primitive_floating FLOATING >
inline integral_day operator *(const integral_day & time, FLOATING floating) { return integral_day(time.m_i * floating); }
//template < primitive_floating FLOATING >
//inline integral_day operator +(const integral_day & time, FLOATING floating) { return integral_day(time.m_i + floating); }
//template < primitive_floating FLOATING >
//inline integral_day operator -(const integral_day & time, FLOATING floating) { return integral_day(time.m_i - floating); }


//template < primitive_integral INTEGRAL >
//inline floating_nanosecond operator %(const floating_nanosecond & time, INTEGRAL integral) { return floating_nanosecond((::f64)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline floating_nanosecond operator /(const floating_nanosecond & time, INTEGRAL integral) { return floating_nanosecond((::f64)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline floating_nanosecond operator *(const floating_nanosecond & time, INTEGRAL integral) { return floating_nanosecond((::f64)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_nanosecond operator +(const floating_nanosecond & time, INTEGRAL integral) { return floating_nanosecond((::f64)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_nanosecond operator -(const floating_nanosecond & time, INTEGRAL integral) { return floating_nanosecond((::f64)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline floating_microsecond operator %(const floating_microsecond & time, INTEGRAL integral) { return floating_microsecond((::f64)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline floating_microsecond operator /(const floating_microsecond & time, INTEGRAL integral) { return floating_microsecond((::f64)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline floating_microsecond operator *(const floating_microsecond & time, INTEGRAL integral) { return floating_microsecond((::f64)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_microsecond operator +(const floating_microsecond & time, INTEGRAL integral) { return floating_microsecond((::f64)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_microsecond operator -(const floating_microsecond & time, INTEGRAL integral) { return floating_microsecond((::f64)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline floating_millisecond operator %(const floating_millisecond & time, INTEGRAL integral) { return floating_millisecond((::f64)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline floating_millisecond operator /(const floating_millisecond & time, INTEGRAL integral) { return floating_millisecond((::f64)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline floating_millisecond operator *(const floating_millisecond & time, INTEGRAL integral) { return floating_millisecond((::f64)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_millisecond operator +(const floating_millisecond & time, INTEGRAL integral) { return floating_millisecond((::f64)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_millisecond operator -(const floating_millisecond & time, INTEGRAL integral) { return floating_millisecond((::f64)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline floating_second operator %(const floating_second & time, INTEGRAL integral) { return floating_second((::f64)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline floating_second operator /(const floating_second & time, INTEGRAL integral) { return floating_second((::f64)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline floating_second operator *(const floating_second & time, INTEGRAL integral) { return floating_second((::f64)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_second operator +(const floating_second & time, INTEGRAL integral) { return floating_second((::f64)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_second operator -(const floating_second & time, INTEGRAL integral) { return floating_second((::f64)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline floating_minute operator %(const floating_minute & time, INTEGRAL integral) { return floating_minute((::f64)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline floating_minute operator /(const floating_minute & time, INTEGRAL integral) { return floating_minute((::f64)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline floating_minute operator *(const floating_minute & time, INTEGRAL integral) { return floating_minute((::f64)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_minute operator +(const floating_minute & time, INTEGRAL integral) { return floating_minute((::f64)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_minute operator -(const floating_minute & time, INTEGRAL integral) { return floating_minute((::f64)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline floating_hour operator %(const floating_hour & time, INTEGRAL integral) { return floating_hour((::f64)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline floating_hour operator /(const floating_hour & time, INTEGRAL integral) { return floating_hour((::f64)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline floating_hour operator *(const floating_hour & time, INTEGRAL integral) { return floating_hour((::f64)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_hour operator +(const floating_hour & time, INTEGRAL integral) { return floating_hour((::f64)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_hour operator -(const floating_hour & time, INTEGRAL integral) { return floating_hour((::f64)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline floating_day operator %(const floating_day & time, INTEGRAL integral) { return floating_day(time.m_d % integral); }
template < primitive_integral INTEGRAL >
inline floating_day operator /(const floating_day & time, INTEGRAL integral) { return floating_day(time.m_d / integral); }
template < primitive_integral INTEGRAL >
inline floating_day operator *(const floating_day & time, INTEGRAL integral) { return floating_day(time.m_d * integral); }
//template < primitive_integral INTEGRAL >
//inline floating_day operator +(const floating_day & time, INTEGRAL integral) { return floating_day(time.m_d + integral); }
//template < primitive_integral INTEGRAL >
//inline floating_day operator -(const floating_day & time, INTEGRAL integral) { return floating_day(time.m_d - integral); }


//template < primitive_floating FLOATING >
//inline floating_nanosecond operator %(const floating_nanosecond & time, FLOATING floating) { return floating_nanosecond((::f64)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline floating_nanosecond operator /(const floating_nanosecond & time, FLOATING floating) { return floating_nanosecond((::f64)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline floating_nanosecond operator *(const floating_nanosecond & time, FLOATING floating) { return floating_nanosecond((::f64)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline floating_nanosecond operator +(const floating_nanosecond & time, FLOATING floating) { return floating_nanosecond((::f64)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline floating_nanosecond operator -(const floating_nanosecond & time, FLOATING floating) { return floating_nanosecond((::f64)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline floating_microsecond operator %(const floating_microsecond & time, FLOATING floating) { return floating_microsecond((::f64)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline floating_microsecond operator /(const floating_microsecond & time, FLOATING floating) { return floating_microsecond((::f64)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline floating_microsecond operator *(const floating_microsecond & time, FLOATING floating) { return floating_microsecond((::f64)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline floating_microsecond operator +(const floating_microsecond & time, FLOATING floating) { return floating_microsecond((::f64)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline floating_microsecond operator -(const floating_microsecond & time, FLOATING floating) { return floating_microsecond((::f64)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline floating_millisecond operator %(const floating_millisecond & time, FLOATING floating) { return floating_millisecond((::f64)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline floating_millisecond operator /(const floating_millisecond & time, FLOATING floating) { return floating_millisecond((::f64)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline floating_millisecond operator *(const floating_millisecond & time, FLOATING floating) { return floating_millisecond((::f64)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline floating_millisecond operator +(const floating_millisecond & time, FLOATING floating) { return floating_millisecond((::f64)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline floating_millisecond operator -(const floating_millisecond & time, FLOATING floating) { return floating_millisecond((::f64)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline floating_second operator %(const floating_second & time, FLOATING floating) { return floating_second((::f64)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline floating_second operator /(const floating_second & time, FLOATING floating) { return floating_second((::f64)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline floating_second operator *(const floating_second & time, FLOATING floating) { return floating_second((::f64)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline floating_second operator +(const floating_second & time, FLOATING floating) { return floating_second((::f64)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline floating_second operator -(const floating_second & time, FLOATING floating) { return floating_second((::f64)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline floating_minute operator %(const floating_minute & time, FLOATING floating) { return floating_minute((::f64)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline floating_minute operator /(const floating_minute & time, FLOATING floating) { return floating_minute((::f64)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline floating_minute operator *(const floating_minute & time, FLOATING floating) { return floating_minute((::f64)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline floating_minute operator +(const floating_minute & time, FLOATING floating) { return floating_minute((::f64)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline floating_minute operator -(const floating_minute & time, FLOATING floating) { return floating_minute((::f64)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline floating_hour operator %(const floating_hour & time, FLOATING floating) { return floating_hour((::f64)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline floating_hour operator /(const floating_hour & time, FLOATING floating) { return floating_hour((::f64)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline floating_hour operator *(const floating_hour & time, FLOATING floating) { return floating_hour((::f64)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline floating_hour operator +(const floating_hour & time, FLOATING floating) { return floating_hour((::f64)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline floating_hour operator -(const floating_hour & time, FLOATING floating) { return floating_hour((::f64)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline floating_day operator %(const floating_day & time, FLOATING floating) { return floating_day(time.m_d % floating); }
template < primitive_floating FLOATING >
inline floating_day operator /(const floating_day & time, FLOATING floating) { return floating_day(time.m_d / floating); }
template < primitive_floating FLOATING >
inline floating_day operator *(const floating_day & time, FLOATING floating) { return floating_day(time.m_d * floating); }
//template < primitive_floating FLOATING >
//inline floating_day operator +(const floating_day & time, FLOATING floating) { return floating_day(time.m_d + floating); }
//template < primitive_floating FLOATING >
//inline floating_day operator -(const floating_day & time, FLOATING floating) { return floating_day(time.m_d - floating); }

