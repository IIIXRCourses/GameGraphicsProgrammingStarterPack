#include "RenderTexture.h"

namespace library
{
	/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
	  Method:   RenderTexture::RenderTexture

	  Summary:  Constructor

	  Modifies: [m_uWidth, m_uHeight, m_texture2D, m_renderTargetView,
				 m_shaderResourceView, m_samplerClamp].
	M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
	/*--------------------------------------------------------------------
	  TODO: RenderTexture::RenderTexture definition (remove the comment)
	--------------------------------------------------------------------*/


	/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
	  Method:   RenderTexture::Initialize

	  Summary:  Initialize

	  Args:     ID3D11Device* pDevice
				ID3D11DeviceContext* pImmediateContext

	  Modifies: [m_texture2D, m_renderTargetView, m_shaderResourceView,
				 m_samplerClamp].

	  Returns:  HRESULT
				  Status code
	M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
	/*--------------------------------------------------------------------
	  TODO: RenderTexture::Initialize definition (remove the comment)
	--------------------------------------------------------------------*/


	ComPtr<ID3D11Texture2D>& RenderTexture::GetTexture2D()
	{
		return m_texture2D;
	}

	ComPtr<ID3D11RenderTargetView>& RenderTexture::GetRenderTargetView()
	{
		return m_renderTargetView;
	}

	ComPtr<ID3D11ShaderResourceView>& RenderTexture::GetShaderResourceView()
	{
		return m_shaderResourceView;
	}

	ComPtr<ID3D11SamplerState>& RenderTexture::GetSamplerState()
	{
		return m_samplerClamp;
	}

}