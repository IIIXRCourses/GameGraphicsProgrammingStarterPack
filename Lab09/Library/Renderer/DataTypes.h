#pragma once

#include "Common.h"

namespace library
{
#define NUM_LIGHTS (2)
#define MAX_NUM_BONES (256)
#define MAX_NUM_BONES_PER_VERTEX (16)


    /*S+S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S
      Struct:   NormalData

      Summary:  NormalData structure containing tangent space vetors 
                of the vertex
    S---S---S---S---S---S---S---S---S---S---S---S---S---S---S---S---S-S*/
    struct NormalData
    {
        XMFLOAT3 Tangent;
        XMFLOAT3 Bitangent;
    };

    /*S+S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S
      Struct:   CBChangesEveryFrame

      Summary:  Constant buffer containing world matrix
    S---S---S---S---S---S---S---S---S---S---S---S---S---S---S---S---S-S*/
    struct CBChangesEveryFrame
    {
        XMMATRIX World;
        XMFLOAT4 OutputColor;
        BOOL HasNormalMap;
    };

}