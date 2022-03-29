#pragma once

namespace library
{
    /*S+S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S
      Struct:    SimpleVertex

      Summary:  Simple vertex structure containing a single field of the
                type XMFLOAT3
    S---S---S---S---S---S---S---S---S---S---S---S---S---S---S---S---S-S*/
    struct SimpleVertex
    {
        XMFLOAT3 Position;
    };

    /*S+S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S
      Struct:   ConstantBuffer

      Summary:  Simple constant buffer structure containing world, view,
                projection matrices
    S---S---S---S---S---S---S---S---S---S---S---S---S---S---S---S---S-S*/
    struct ConstantBuffer
    {
        XMMATRIX World;
        XMMATRIX View;
        XMMATRIX Projection;
    };
}
