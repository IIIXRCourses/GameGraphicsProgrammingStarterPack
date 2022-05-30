#include "Cube/Cube.h"


HRESULT Cube::Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext)
{
    BasicMeshEntry basicMeshEntry;
    basicMeshEntry.uNumIndices = NUM_INDICES;

    m_aMeshes.push_back(basicMeshEntry);

    if (HasTexture())
    {
        SetMaterialOfMesh(0, 0);
    }

    return initialize(pDevice, pImmediateContext);
}
