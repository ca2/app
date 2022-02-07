//*****************************************************************************
//
//      Class:          LocalMemory
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Provides automatic cleanup of local memory objects.
//
//*****************************************************************************

#pragma once

namespace Kerr
{
    template <typename T>
    class LocalMemory
    {
    public:

        explicit LocalMemory(T* pBuffer) :
            m_pBuffer(pBuffer)
        {
            // Do nothing
        }

        virtual ~LocalMemory()
        {
            Free();
        }

        void Free()
        {
            if (0 != m_pBuffer)
            {
                ::LocalFree(m_pBuffer);
                m_pBuffer = 0;
            }
        }

        T* m_pBuffer;
    };
}
