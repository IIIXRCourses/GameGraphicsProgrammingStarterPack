#include "Scene/Voxel.h"

#include "Texture/Material.h"

namespace library
{

    HRESULT Voxel::Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext)
    {
        BasicMeshEntry basicMeshEntry;
        basicMeshEntry.uNumIndices = NUM_INDICES;

        m_aMeshes.push_back(basicMeshEntry);

        HRESULT hr = initialize(pDevice, pImmediateContext);
        if (FAILED(hr))
        {
            return hr;
        }

        hr = initializeInstance(pDevice);
        if (FAILED(hr))
        {
            return hr;
        }

        if (HasTexture() > 0)
        {
            hr = SetMaterialOfMesh(0, 0);
            if (FAILED(hr))
            {
                return hr;
            }
        }

        return S_OK;
    }

}