/*+===================================================================
  File:      MATERIAL.H

  Summary:   Material header file contains declaration of class
			 Material used to abstract multiple texture data.

  Classes:  Material

  ?2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Texture/Texture.h"

namespace library
{
	class Material
	{
	public:
		Material() = delete;
		Material(_In_ std::wstring szName);
		Material(const Material& other) = default;
		Material(Material&& other) = default;
		Material& operator=(const Material& other) = default;
		Material& operator=(Material&& other) = default;
		virtual ~Material() = default;

		virtual HRESULT Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext);

		std::wstring GetName() const;

	private:
		BYTE m_padding[4];
		std::wstring m_szName;

	public:
		std::shared_ptr<Texture> pDiffuse;
		std::shared_ptr<Texture> pSpecularExponent;
		std::shared_ptr<Texture> pNormal;
	};
}