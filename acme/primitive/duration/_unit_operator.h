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
//inline INTEGRAL_NANOSECOND operator %(const INTEGRAL_NANOSECOND & duration, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_NANOSECOND operator /(const INTEGRAL_NANOSECOND & duration, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_NANOSECOND operator *(const INTEGRAL_NANOSECOND & duration, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_NANOSECOND operator +(const INTEGRAL_NANOSECOND & duration, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_NANOSECOND operator -(const INTEGRAL_NANOSECOND & duration, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MICROSECOND operator %(const INTEGRAL_MICROSECOND & duration, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MICROSECOND operator /(const INTEGRAL_MICROSECOND & duration, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MICROSECOND operator *(const INTEGRAL_MICROSECOND & duration, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MICROSECOND operator +(const INTEGRAL_MICROSECOND & duration, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MICROSECOND operator -(const INTEGRAL_MICROSECOND & duration, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MILLISECOND operator %(const INTEGRAL_MILLISECOND & duration, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MILLISECOND operator /(const INTEGRAL_MILLISECOND & duration, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MILLISECOND operator *(const INTEGRAL_MILLISECOND & duration, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MILLISECOND operator +(const INTEGRAL_MILLISECOND & duration, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MILLISECOND operator -(const INTEGRAL_MILLISECOND & duration, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline INTEGRAL_SECOND operator %(const INTEGRAL_SECOND & duration, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(duration.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_SECOND operator /(const INTEGRAL_SECOND & duration, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(duration.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_SECOND operator *(const INTEGRAL_SECOND & duration, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(duration.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_SECOND operator +(const INTEGRAL_SECOND & duration, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(duration.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_SECOND operator -(const INTEGRAL_SECOND & duration, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(duration.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MINUTE operator %(const INTEGRAL_MINUTE & duration, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(duration.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MINUTE operator /(const INTEGRAL_MINUTE & duration, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(duration.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MINUTE operator *(const INTEGRAL_MINUTE & duration, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(duration.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MINUTE operator +(const INTEGRAL_MINUTE & duration, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(duration.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MINUTE operator -(const INTEGRAL_MINUTE & duration, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(duration.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline INTEGRAL_HOUR operator %(const INTEGRAL_HOUR & duration, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(duration.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_HOUR operator /(const INTEGRAL_HOUR & duration, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(duration.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_HOUR operator *(const INTEGRAL_HOUR & duration, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(duration.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_HOUR operator +(const INTEGRAL_HOUR & duration, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(duration.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_HOUR operator -(const INTEGRAL_HOUR & duration, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(duration.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline INTEGRAL_DAY operator %(const INTEGRAL_DAY & duration, INTEGRAL integral) { return INTEGRAL_DAY(duration.m_i % integral); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_DAY operator /(const INTEGRAL_DAY & duration, INTEGRAL integral) { return INTEGRAL_DAY(duration.m_i / integral); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_DAY operator *(const INTEGRAL_DAY & duration, INTEGRAL integral) { return INTEGRAL_DAY(duration.m_i * integral); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_DAY operator +(const INTEGRAL_DAY & duration, INTEGRAL integral) { return INTEGRAL_DAY(duration.m_i + integral); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_DAY operator -(const INTEGRAL_DAY & duration, INTEGRAL integral) { return INTEGRAL_DAY(duration.m_i - integral); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_NANOSECOND operator %(const INTEGRAL_NANOSECOND & duration, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_NANOSECOND operator /(const INTEGRAL_NANOSECOND & duration, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_NANOSECOND operator *(const INTEGRAL_NANOSECOND & duration, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_NANOSECOND operator +(const INTEGRAL_NANOSECOND & duration, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_NANOSECOND operator -(const INTEGRAL_NANOSECOND & duration, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_MICROSECOND operator %(const INTEGRAL_MICROSECOND & duration, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MICROSECOND operator /(const INTEGRAL_MICROSECOND & duration, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MICROSECOND operator *(const INTEGRAL_MICROSECOND & duration, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_MICROSECOND operator +(const INTEGRAL_MICROSECOND & duration, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_MICROSECOND operator -(const INTEGRAL_MICROSECOND & duration, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_MILLISECOND operator %(const INTEGRAL_MILLISECOND & duration, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MILLISECOND operator /(const INTEGRAL_MILLISECOND & duration, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MILLISECOND operator *(const INTEGRAL_MILLISECOND & duration, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_MILLISECOND operator +(const INTEGRAL_MILLISECOND & duration, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_MILLISECOND operator -(const INTEGRAL_MILLISECOND & duration, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_SECOND operator %(const INTEGRAL_SECOND & duration, FLOATING floating) { return INTEGRAL_SECOND((::i64)(duration.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_SECOND operator /(const INTEGRAL_SECOND & duration, FLOATING floating) { return INTEGRAL_SECOND((::i64)(duration.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_SECOND operator *(const INTEGRAL_SECOND & duration, FLOATING floating) { return INTEGRAL_SECOND((::i64)(duration.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_SECOND operator +(const INTEGRAL_SECOND & duration, FLOATING floating) { return INTEGRAL_SECOND((::i64)(duration.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_SECOND operator -(const INTEGRAL_SECOND & duration, FLOATING floating) { return INTEGRAL_SECOND((::i64)(duration.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_MINUTE operator %(const INTEGRAL_MINUTE & duration, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(duration.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MINUTE operator /(const INTEGRAL_MINUTE & duration, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(duration.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MINUTE operator *(const INTEGRAL_MINUTE & duration, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(duration.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_MINUTE operator +(const INTEGRAL_MINUTE & duration, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(duration.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_MINUTE operator -(const INTEGRAL_MINUTE & duration, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(duration.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_HOUR operator %(const INTEGRAL_HOUR & duration, FLOATING floating) { return INTEGRAL_HOUR((::i64)(duration.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_HOUR operator /(const INTEGRAL_HOUR & duration, FLOATING floating) { return INTEGRAL_HOUR((::i64)(duration.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_HOUR operator *(const INTEGRAL_HOUR & duration, FLOATING floating) { return INTEGRAL_HOUR((::i64)(duration.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_HOUR operator +(const INTEGRAL_HOUR & duration, FLOATING floating) { return INTEGRAL_HOUR((::i64)(duration.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_HOUR operator -(const INTEGRAL_HOUR & duration, FLOATING floating) { return INTEGRAL_HOUR((::i64)(duration.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_DAY operator %(const INTEGRAL_DAY & duration, FLOATING floating) { return INTEGRAL_DAY(duration.m_i % floating); }
template < primitive_floating FLOATING >
inline INTEGRAL_DAY operator /(const INTEGRAL_DAY & duration, FLOATING floating) { return INTEGRAL_DAY(duration.m_i / floating); }
template < primitive_floating FLOATING >
inline INTEGRAL_DAY operator *(const INTEGRAL_DAY & duration, FLOATING floating) { return INTEGRAL_DAY(duration.m_i * floating); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_DAY operator +(const INTEGRAL_DAY & duration, FLOATING floating) { return INTEGRAL_DAY(duration.m_i + floating); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_DAY operator -(const INTEGRAL_DAY & duration, FLOATING floating) { return INTEGRAL_DAY(duration.m_i - floating); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_NANOSECOND operator %(const FLOATING_NANOSECOND & duration, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(duration.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_NANOSECOND operator /(const FLOATING_NANOSECOND & duration, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(duration.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_NANOSECOND operator *(const FLOATING_NANOSECOND & duration, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(duration.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_NANOSECOND operator +(const FLOATING_NANOSECOND & duration, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(duration.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_NANOSECOND operator -(const FLOATING_NANOSECOND & duration, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(duration.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_MICROSECOND operator %(const FLOATING_MICROSECOND & duration, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(duration.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MICROSECOND operator /(const FLOATING_MICROSECOND & duration, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(duration.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MICROSECOND operator *(const FLOATING_MICROSECOND & duration, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(duration.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_MICROSECOND operator +(const FLOATING_MICROSECOND & duration, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(duration.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_MICROSECOND operator -(const FLOATING_MICROSECOND & duration, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(duration.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_MILLISECOND operator %(const FLOATING_MILLISECOND & duration, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(duration.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MILLISECOND operator /(const FLOATING_MILLISECOND & duration, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(duration.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MILLISECOND operator *(const FLOATING_MILLISECOND & duration, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(duration.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_MILLISECOND operator +(const FLOATING_MILLISECOND & duration, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(duration.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_MILLISECOND operator -(const FLOATING_MILLISECOND & duration, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(duration.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_SECOND operator %(const FLOATING_SECOND & duration, INTEGRAL integral) { return FLOATING_SECOND((::f64)(duration.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_SECOND operator /(const FLOATING_SECOND & duration, INTEGRAL integral) { return FLOATING_SECOND((::f64)(duration.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_SECOND operator *(const FLOATING_SECOND & duration, INTEGRAL integral) { return FLOATING_SECOND((::f64)(duration.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_SECOND operator +(const FLOATING_SECOND & duration, INTEGRAL integral) { return FLOATING_SECOND((::f64)(duration.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_SECOND operator -(const FLOATING_SECOND & duration, INTEGRAL integral) { return FLOATING_SECOND((::f64)(duration.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_MINUTE operator %(const FLOATING_MINUTE & duration, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(duration.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MINUTE operator /(const FLOATING_MINUTE & duration, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(duration.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MINUTE operator *(const FLOATING_MINUTE & duration, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(duration.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_MINUTE operator +(const FLOATING_MINUTE & duration, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(duration.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_MINUTE operator -(const FLOATING_MINUTE & duration, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(duration.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_HOUR operator %(const FLOATING_HOUR & duration, INTEGRAL integral) { return FLOATING_HOUR((::f64)(duration.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_HOUR operator /(const FLOATING_HOUR & duration, INTEGRAL integral) { return FLOATING_HOUR((::f64)(duration.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_HOUR operator *(const FLOATING_HOUR & duration, INTEGRAL integral) { return FLOATING_HOUR((::f64)(duration.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_HOUR operator +(const FLOATING_HOUR & duration, INTEGRAL integral) { return FLOATING_HOUR((::f64)(duration.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_HOUR operator -(const FLOATING_HOUR & duration, INTEGRAL integral) { return FLOATING_HOUR((::f64)(duration.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_DAY operator %(const FLOATING_DAY & duration, INTEGRAL integral) { return FLOATING_DAY(duration.m_d % integral); }
template < primitive_integral INTEGRAL >
inline FLOATING_DAY operator /(const FLOATING_DAY & duration, INTEGRAL integral) { return FLOATING_DAY(duration.m_d / integral); }
template < primitive_integral INTEGRAL >
inline FLOATING_DAY operator *(const FLOATING_DAY & duration, INTEGRAL integral) { return FLOATING_DAY(duration.m_d * integral); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_DAY operator +(const FLOATING_DAY & duration, INTEGRAL integral) { return FLOATING_DAY(duration.m_d + integral); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_DAY operator -(const FLOATING_DAY & duration, INTEGRAL integral) { return FLOATING_DAY(duration.m_d - integral); }


//template < primitive_floating FLOATING >
//inline FLOATING_NANOSECOND operator %(const FLOATING_NANOSECOND & duration, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(duration.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_NANOSECOND operator /(const FLOATING_NANOSECOND & duration, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(duration.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_NANOSECOND operator *(const FLOATING_NANOSECOND & duration, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(duration.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_NANOSECOND operator +(const FLOATING_NANOSECOND & duration, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(duration.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_NANOSECOND operator -(const FLOATING_NANOSECOND & duration, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(duration.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline FLOATING_MICROSECOND operator %(const FLOATING_MICROSECOND & duration, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(duration.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MICROSECOND operator /(const FLOATING_MICROSECOND & duration, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(duration.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MICROSECOND operator *(const FLOATING_MICROSECOND & duration, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(duration.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_MICROSECOND operator +(const FLOATING_MICROSECOND & duration, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(duration.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_MICROSECOND operator -(const FLOATING_MICROSECOND & duration, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(duration.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline FLOATING_MILLISECOND operator %(const FLOATING_MILLISECOND & duration, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(duration.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MILLISECOND operator /(const FLOATING_MILLISECOND & duration, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(duration.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MILLISECOND operator *(const FLOATING_MILLISECOND & duration, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(duration.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_MILLISECOND operator +(const FLOATING_MILLISECOND & duration, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(duration.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_MILLISECOND operator -(const FLOATING_MILLISECOND & duration, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(duration.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline FLOATING_SECOND operator %(const FLOATING_SECOND & duration, FLOATING floating) { return FLOATING_SECOND((::f64)(duration.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_SECOND operator /(const FLOATING_SECOND & duration, FLOATING floating) { return FLOATING_SECOND((::f64)(duration.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_SECOND operator *(const FLOATING_SECOND & duration, FLOATING floating) { return FLOATING_SECOND((::f64)(duration.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_SECOND operator +(const FLOATING_SECOND & duration, FLOATING floating) { return FLOATING_SECOND((::f64)(duration.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_SECOND operator -(const FLOATING_SECOND & duration, FLOATING floating) { return FLOATING_SECOND((::f64)(duration.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline FLOATING_MINUTE operator %(const FLOATING_MINUTE & duration, FLOATING floating) { return FLOATING_MINUTE((::f64)(duration.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MINUTE operator /(const FLOATING_MINUTE & duration, FLOATING floating) { return FLOATING_MINUTE((::f64)(duration.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MINUTE operator *(const FLOATING_MINUTE & duration, FLOATING floating) { return FLOATING_MINUTE((::f64)(duration.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_MINUTE operator +(const FLOATING_MINUTE & duration, FLOATING floating) { return FLOATING_MINUTE((::f64)(duration.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_MINUTE operator -(const FLOATING_MINUTE & duration, FLOATING floating) { return FLOATING_MINUTE((::f64)(duration.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline FLOATING_HOUR operator %(const FLOATING_HOUR & duration, FLOATING floating) { return FLOATING_HOUR((::f64)(duration.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_HOUR operator /(const FLOATING_HOUR & duration, FLOATING floating) { return FLOATING_HOUR((::f64)(duration.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_HOUR operator *(const FLOATING_HOUR & duration, FLOATING floating) { return FLOATING_HOUR((::f64)(duration.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_HOUR operator +(const FLOATING_HOUR & duration, FLOATING floating) { return FLOATING_HOUR((::f64)(duration.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_HOUR operator -(const FLOATING_HOUR & duration, FLOATING floating) { return FLOATING_HOUR((::f64)(duration.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline FLOATING_DAY operator %(const FLOATING_DAY & duration, FLOATING floating) { return FLOATING_DAY(duration.m_d % floating); }
template < primitive_floating FLOATING >
inline FLOATING_DAY operator /(const FLOATING_DAY & duration, FLOATING floating) { return FLOATING_DAY(duration.m_d / floating); }
template < primitive_floating FLOATING >
inline FLOATING_DAY operator *(const FLOATING_DAY & duration, FLOATING floating) { return FLOATING_DAY(duration.m_d * floating); }
//template < primitive_floating FLOATING >
//inline FLOATING_DAY operator +(const FLOATING_DAY & duration, FLOATING floating) { return FLOATING_DAY(duration.m_d + floating); }
//template < primitive_floating FLOATING >
//inline FLOATING_DAY operator -(const FLOATING_DAY & duration, FLOATING floating) { return FLOATING_DAY(duration.m_d - floating); }

