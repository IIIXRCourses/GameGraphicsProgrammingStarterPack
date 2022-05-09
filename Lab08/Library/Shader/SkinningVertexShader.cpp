#include "Shader/SkinningVertexShader.h"

namespace library
{
    SkinningVertexShader::SkinningVertexShader(_In_ PCWSTR pszFileName, _In_ PCSTR pszEntryPoint, _In_ PCSTR pszShaderModel)
        : VertexShader(pszFileName, pszEntryPoint, pszShaderModel)
    {
    }

    HRESULT SkinningVertexShader::Initialize(_In_ ID3D11Device* pDevice)
    {
        ComPtr<ID3DBlob> vsBlob;
        HRESULT hr = compile(vsBlob.GetAddressOf());
        if (FAILED(hr))
        {
            WCHAR szMessage[256];
            swprintf_s(
                szMessage,
                L"The FX file %s cannot be compiled. Please run this executable from the directory that contains the FX file.",
                m_pszFileName
            );
            MessageBox(
                nullptr,
                szMessage,
                L"Error",
                MB_OK
            );
            return hr;
        }

        hr = pDevice->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, m_vertexShader.GetAddressOf());
        if (FAILED(hr))
        {
            return hr;
        }

        // Define the input layout
        D3D11_INPUT_ELEMENT_DESC aLayouts[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },

            { "BONEINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };
        UINT uNumElements = ARRAYSIZE(aLayouts);

        // Create the input layout
        hr = pDevice->CreateInputLayout(aLayouts, uNumElements, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), m_vertexLayout.GetAddressOf());

        return hr;
    }
}