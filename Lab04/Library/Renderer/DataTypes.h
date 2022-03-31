#pragma once

#include "Common.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Struct:    SimpleVertex

      Summary:  Simple vertex structure containing a single field of the
                type XMFLOAT3
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    struct SimpleVertex
    {
        XMFLOAT3 Position;
    };

    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Struct:   ConstantBuffer

      Summary:  Simple constant buffer structure containing world, view, 
                projection matrices
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    struct ConstantBuffer
    {
        XMMATRIX World;
        XMMATRIX View;
        XMMATRIX Projection;
    };
}
