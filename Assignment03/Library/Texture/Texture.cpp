#include "Texture.h"

#include "Texture/DDSTextureLoader.h"
#include "Texture/WICTextureLoader.h"

namespace library
{
    ComPtr<ID3D11SamplerState> Texture::s_samplers[static_cast<size_t>(eTextureSamplerType::COUNT)];

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Texture::Texture

      Summary:  Constructor

      Args:     const std::filesystem::path& textureFilePath
                  Path to the texture to use
                eTextureSamplerType textureSamplerType
                  Texture sampler type of this texture

      Modifies: [m_filePath, m_textureRV, m_textureSamplerType].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Texture::Texture definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Texture::Initialize

      Summary:  Initializes the texture and samplers if not initialized

      Args:     ID3D11Device* pDevice
                  The Direct3D device to create the buffers
                ID3D11DeviceContext* pImmediateContext
                  The Direct3D context to set buffers

      Modifies: [m_textureRV].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Texture::Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext)
		{
        HRESULT hr = CreateWICTextureFromFile(
            pDevice,
            pImmediateContext,
            m_filePath.c_str(),
            nullptr,
            m_textureRV.GetAddressOf()
        );
        if (FAILED(hr))
        {
            hr = CreateDDSTextureFromFile(pDevice, m_filePath.c_str(), nullptr, m_textureRV.GetAddressOf());
            if (FAILED(hr))
            {
                OutputDebugString(L"Can't load texture from \"");
                OutputDebugString(m_filePath.c_str());
                OutputDebugString(L"\n");
                return hr;
            }
        }

        // Create the sample state
        if (!s_samplers[static_cast<size_t>(eTextureSamplerType::TRILINEAR_WRAP)].Get())
        {
            D3D11_SAMPLER_DESC sampDesc =
            {
                /*--------------------------------------------------------------------
                  TODO: Initialize the trilinear wrap sampler (remove the comment)
                --------------------------------------------------------------------*/
            };
            hr = pDevice->CreateSamplerState(&sampDesc, s_samplers[static_cast<size_t>(eTextureSamplerType::TRILINEAR_WRAP)].GetAddressOf());
            if (FAILED(hr))
            {
                return hr;
            }
        }

        if (!s_samplers[static_cast<size_t>(eTextureSamplerType::TRILINEAR_CLAMP)].Get())
        {
          D3D11_SAMPLER_DESC sampDesc =
          {
              /*--------------------------------------------------------------------
                TODO: Initialize the trilinear clamp sampler (remove the comment)
              --------------------------------------------------------------------*/
          };
          hr = pDevice->CreateSamplerState(&sampDesc, s_samplers[static_cast<size_t>(eTextureSamplerType::TRILINEAR_CLAMP)].GetAddressOf());
          if (FAILED(hr))
          {
              return hr;
          }
        }
        
        return hr;
		}

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Texture::GetTextureResourceView

      Summary:  Returns the TRV

      Returns:  ComPtr<ID3D11ShaderResourceView>&
                  Shader resource view
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    ComPtr<ID3D11ShaderResourceView>& Texture::GetTextureResourceView()
    {
        return m_textureRV;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Texture::GetSamplerType

      Summary:  Returns the sampler type

      Returns:  eTextureSamplerType
                  Sampler type
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    eTextureSamplerType Texture::GetSamplerType() const
		{
			return m_textureSamplerType;
		}
}