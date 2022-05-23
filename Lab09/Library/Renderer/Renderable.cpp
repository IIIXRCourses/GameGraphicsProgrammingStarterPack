#include "Renderer/Renderable.h"

#include "assimp/Importer.hpp"	// C++ importer interface
#include "assimp/scene.h"		// output data structure
#include "assimp/postprocess.h"	// post processing flags

#include "Texture/DDSTextureLoader.h"

namespace library
{

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::Renderable

      Summary:  Constructor

      Args:     const XMFLOAT4& outputColor
                  Default color to shader the renderable

      Modifies: [m_vertexBuffer, m_indexBuffer, m_constantBuffer,
                 m_normalBuffer, m_aMeshes, m_aMaterials, m_vertexShader,
                 m_pixelShader, m_outputColor, m_world, m_bHasNormalMap
                 m_aNormalData].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::Renderable definition (remove the comment)
    --------------------------------------------------------------------*/


    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::initialize

      Summary:  Initializes the buffers and the world matrix

      Args:     ID3D11Device* pDevice
                  The Direct3D device to create the buffers
                ID3D11DeviceContext* pImmediateContext
                  The Direct3D context to set buffers
                PCWSTR pszTextureFileName
                  File name of the texture to usen

      Modifies: [m_vertexBuffer, m_normalBuffer, m_indexBuffer
                 m_constantBuffer].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::initialize definition (remove the comment)
    --------------------------------------------------------------------*/


    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::calculateNormalMapVectors

      Summary:  Calculate tangent and bitangent vectors of every vertex

      Modifies: [m_aNormalData].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::calculateNormalMapVectors definition (remove the comment)
    --------------------------------------------------------------------*/


    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::calculateTangentBitangent

      Summary:  Calculate tangent/bitangent vectors of the given face

      Args:     SimpleVertex& v1
                  The first vertex of the face
                SimpleVertex& v2
                  The second vertex of the face
                SimpleVertex& v3
                  The third vertex of the face
                XMFLOAT3& tangent
                  Calculated tangent vector
                XMFLOAT3& bitangent
                  Calculated bitangent vector
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    void Renderable::calculateTangentBitangent(_In_ const SimpleVertex& v1, _In_ const SimpleVertex& v2, _In_ const SimpleVertex& v3, _Out_ XMFLOAT3& tangent, _Out_ XMFLOAT3& bitangent)
    {
        XMFLOAT3 vector1, vector2;
        XMFLOAT2 tuVector, tvVector;

        // Calculate the two vectors for this face.
        vector1.x = v2.Position.x - v1.Position.x;
        vector1.y = v2.Position.y - v1.Position.y;
        vector1.z = v2.Position.z - v1.Position.z;

        vector2.x = v3.Position.x - v1.Position.x;
        vector2.y = v3.Position.y - v1.Position.y;
        vector2.z = v3.Position.z - v1.Position.z;

        // Calculate the tu and tv texture space vectors.
        tuVector.x = v2.TexCoord.x - v1.TexCoord.x;
        tvVector.x = v2.TexCoord.y - v1.TexCoord.y;

        tuVector.y = v3.TexCoord.x - v1.TexCoord.x;
        tvVector.y = v3.TexCoord.y - v1.TexCoord.y;

        // Calculate the denominator of the tangent/binormal equation.
        float den = 1.0f / (tuVector.x * tvVector.y - tuVector.y * tvVector.x);

        // Calculate the cross products and multiply by the coefficient to get the tangent and binormal.
        tangent.x = (tvVector.y * vector1.x - tvVector.x * vector2.x) * den;
        tangent.y = (tvVector.y * vector1.y - tvVector.x * vector2.y) * den;
        tangent.z = (tvVector.y * vector1.z - tvVector.x * vector2.z) * den;

        bitangent.x = (tuVector.x * vector2.x - tuVector.y * vector1.x) * den;
        bitangent.y = (tuVector.x * vector2.y - tuVector.y * vector1.y) * den;
        bitangent.z = (tuVector.x * vector2.z - tuVector.y * vector1.z) * den;

        // Calculate the length of this normal.
        float length = sqrt((tangent.x * tangent.x) + (tangent.y * tangent.y) + (tangent.z * tangent.z));

        // Normalize the normal and then store it
        tangent.x = tangent.x / length;
        tangent.y = tangent.y / length;
        tangent.z = tangent.z / length;

        // Calculate the length of this normal.
        length = sqrt((bitangent.x * bitangent.x) + (bitangent.y * bitangent.y) + (bitangent.z * bitangent.z));

        // Normalize the normal and then store it
        bitangent.x = bitangent.x / length;
        bitangent.y = bitangent.y / length;
        bitangent.z = bitangent.z / length;
    }


    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::AddMaterial

      Summary:  Add material to this renderable

      Args:     std::shared_ptr<Material>& material
                  Material to add

      Modifies: [m_aMaterials]
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    void Renderable::AddMaterial(_In_ const std::shared_ptr<Material>& material)
    {
        m_aMaterials.push_back(material);
    }


    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::SetMaterialOfMesh

      Summary:  Set the material of the mesh

      Args:     const UINT uMeshIndex
                  Index of the mesh
                 const UINT uMaterialIndex
                  Index of the material

      Modifies: [m_aMeshes, m_bHasNormalMap]

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Renderable::SetMaterialOfMesh(_In_ const UINT uMeshIndex, _In_ const UINT uMaterialIndex)
    {
        if (uMeshIndex >= m_aMeshes.size() || uMaterialIndex >= m_aMaterials.size())
        {
            return E_FAIL;
        }

        m_aMeshes[uMeshIndex].uMaterialIndex = uMaterialIndex;

        if (m_aMaterials[uMeshIndex]->pNormal)
        {
            m_bHasNormalMap = true;
        }

        return S_OK;
    }


    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetNormalBuffer

      Summary:  Return the normal buffer

      Returns:  ComPtr<ID3D11Buffer>&
                  Normal buffer
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::GetNormalBuffer definition (remove the comment)
    --------------------------------------------------------------------*/


    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetMaterial

      Summary:  Return the material of the given index

      Args:     UINT uIndex
                  Index of the material

      Returns:  std::shared_ptr<Material>&
                  Material
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::GetMaterial definition (remove the comment)
    --------------------------------------------------------------------*/


    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::HasNormalMap

      Summary:  Return whether the renderable has normal map

      Returns:  BOOL
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::HasNormalMap definition (remove the comment)
    --------------------------------------------------------------------*/

}
