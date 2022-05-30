/*+===================================================================
  File:      RENDERTEXTURE.H

  Summary:   RenderTexture header file contains declaration of class
			 RenderTexture used to create a Render-To-Texture

  Classes:  RenderTexture

  ?2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

namespace library
{
	class RenderTexture
	{
	public:
		RenderTexture() = delete;
		RenderTexture(_In_ UINT uWidth, _In_ UINT uHeight);
		RenderTexture(const RenderTexture& other) = delete;
		RenderTexture(RenderTexture&& other) = delete;
		RenderTexture& operator=(const RenderTexture& other) = delete;
		RenderTexture& operator=(RenderTexture&& other) = delete;
		~RenderTexture() = default;

		HRESULT Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext);

		ComPtr<ID3D11Texture2D>& GetTexture2D();
		ComPtr<ID3D11RenderTargetView>& GetRenderTargetView();
		ComPtr<ID3D11ShaderResourceView>& GetShaderResourceView();
		ComPtr<ID3D11SamplerState>& GetSamplerState();

	private:
		UINT m_uWidth;
		UINT m_uHeight;

		ComPtr<ID3D11Texture2D> m_texture2D;
		ComPtr<ID3D11RenderTargetView> m_renderTargetView;
		ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;
		ComPtr<ID3D11SamplerState> m_samplerClamp;
	};
}