#pragma once

class keep_true
{
public:
   bool * m_pb;
   keep_true(bool & b) { m_pb = &b; b = true;}
   ~keep_true(){*m_pb = false;}
};
