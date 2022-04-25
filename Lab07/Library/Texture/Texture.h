/*+===================================================================
  File:      TEXTURE.H

  Summary:   Texture header file contains declaration of class
			 Texture used to abstract texture data.

  Classes:  Texture

  © 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

namespace library
{
    class Texture
    {
    public:
        Texture() = delete;
        Texture(_In_ const std::filesystem::path& filePath);
        Texture(const Texture& other) = delete;
        Texture(Texture&& other) = delete;
        Texture& operator=(const Texture& other) = delete;
        Texture& operator=(Texture&& other) = delete;
        virtual ~Texture() = default;

        // Should be called once to load the texture
        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext);

        ComPtr<ID3D11ShaderResourceView>& GetTextureResourceView();
        ComPtr<ID3D11SamplerState>& GetSamplerState();

    private:
        std::filesystem::path m_filePath;
        ComPtr<ID3D11ShaderResourceView> m_textureRV;
        ComPtr<ID3D11SamplerState> m_samplerLinear;
    };
}