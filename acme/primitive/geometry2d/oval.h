#pragma once


class CLASS_DECL_ACME oval :
   public ::rect
{
public:
   oval() : rect() {}
   oval(const ::rect& r) : rect(r) {}
};


class CLASS_DECL_ACME ovald :
   public ::rectd
{
public:
   ovald() : rectd() {}
   ovald(const ::rectd& r) : rectd(r) {}

};