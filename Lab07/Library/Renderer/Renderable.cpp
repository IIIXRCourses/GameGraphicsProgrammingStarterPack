#include "Renderer/Renderable.h"

#include "assimp/Importer.hpp"	// C++ importer interface
#include "assimp/scene.h"		// output data structure
#include "assimp/postprocess.h"	// post processing flags

namespace library
{
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::Renderable

      Summary:  Constructor

      Args:     const XMFLOAT4& outputColor
                  Default color of the renderable

      Modifies: [m_vertexBuffer, m_indexBuffer, m_constantBuffer, 
                 m_textureRV, m_samplerLinear, m_vertexShader, 
                 m_pixelShader, m_textureFilePath, m_outputColor,
                 m_world].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::Renderable definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::initialize

      Summary:  Initializes the buffers, texture, and the world matrix

      Args:     ID3D11Device* pDevice
                  The Direct3D device to create the buffers
                ID3D11DeviceContext* pImmediateContext
                  The Direct3D context to set buffers

      Modifies: [m_vertexBuffer, m_indexBuffer, m_constantBuffer].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::initialize definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::SetVertexShader

      Summary:  Sets the vertex shader to be used for this renderable
                object

      Args:     const std::shared_ptr<VertexShader>& vertexShader
                  Vertex shader to set to

      Modifies: [m_vertexShader].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::SetVertexShader definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::SetPixelShader

      Summary:  Sets the pixel shader to be used for this renderable
                object

      Args:     const std::shared_ptr<PixelShader>& pixelShader
                  Pixel shader to set to

      Modifies: [m_pixelShader].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::SetPixelShader definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetVertexShader

      Summary:  Returns the vertex shader

      Returns:  ComPtr<ID3D11VertexShader>&
                  Vertex shader. Could be a nullptr
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::GetVertexShader definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetPixelShader

      Summary:  Returns the vertex shader

      Returns:  ComPtr<ID3D11PixelShader>&
                  Pixel shader. Could be a nullptr
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::GetPixelShader definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetVertexLayout

      Summary:  Returns the vertex input layout

      Returns:  ComPtr<ID3D11InputLayout>&
                  Vertex input layout
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::GetVertexLayout definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetVertexBuffer

      Summary:  Returns the vertex buffer

      Returns:  ComPtr<ID3D11Buffer>&
                  Vertex buffer
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::GetVertexBuffer definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetIndexBuffer

      Summary:  Returns the index buffer

      Returns:  ComPtr<ID3D11Buffer>&
                  Index buffer
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::GetIndexBuffer definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetConstantBuffer

      Summary:  Returns the constant buffer

      Returns:  ComPtr<ID3D11Buffer>&
                  Constant buffer
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::GetConstantBuffer definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetWorldMatrix

      Summary:  Returns the world matrix

      Returns:  const XMMATRIX&
                  World matrix
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::GetWorldMatrix definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetOutputColor

      Summary:  Returns the output color

      Returns:  const XMFLOAT4&
                  The output color
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::GetOutputColor definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::HasTexture

      Summary:  Returns whether the renderable has texture

      Returns:  BOOL
                  Whether the renderable has texture
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::HasTexture definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetMaterial

      Summary:  Returns a material at given index

      Returns:  const Material&
                  Material at given index
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    const Material& Renderable::GetMaterial(UINT uIndex) const
    {
        assert(uIndex < m_aMaterials.size());

        return m_aMaterials[uIndex];
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetMesh

      Summary:  Returns a basic mesh entry at given index

      Returns:  const Renderable::BasicMeshEntry&
                  Basic mesh entry at given index
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    const Renderable::BasicMeshEntry& Renderable::GetMesh(UINT uIndex) const
    {
        assert(uIndex < m_aMeshes.size());

        return m_aMeshes[uIndex];
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::RotateX

      Summary:  Rotates around the x-axis

      Args:     FLOAT angle
                  Angle of rotation around the x-axis, in radians

      Modifies: [m_world].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::RotateX definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::RotateY

      Summary:  Rotates around the y-axis

      Args:     FLOAT angle
                  Angle of rotation around the y-axis, in radians

      Modifies: [m_world].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::RotateY definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::RotateZ

      Summary:  Rotates around the z-axis

      Args:     FLOAT angle
                  Angle of rotation around the z-axis, in radians

      Modifies: [m_world].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::RotateZ definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::RotateRollPitchYaw

      Summary:  Rotates based on a given pitch, yaw, and roll (Euler angles)

      Args:     FLOAT pitch
                  Angle of rotation around the x-axis, in radians
                FLOAT yaw
                  Angle of rotation around the y-axis, in radians
                FLOAT roll
                  Angle of rotation around the z-axis, in radians

      Modifies: [m_world].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::RotateRollPitchYaw definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::Scale

      Summary:  Scales along the x-axis, y-axis, and z-axis

      Args:     FLOAT scaleX
                  Scaling factor along the x-axis.
                FLOAT scaleY
                  Scaling factor along the y-axis.
                FLOAT scaleZ
                  Scaling factor along the z-axis.

      Modifies: [m_world].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::Scale definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::Translate

      Summary:  Translates matrix from a vector

      Args:     const XMVECTOR& offset
                  3D vector describing the translations along the x-axis, y-axis, and z-axis

      Modifies: [m_world].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Renderable::Translate definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetNumMeshes

      Summary:  Returns the number of meshes

      Returns:  UINT
                  Number of meshes
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    UINT Renderable::GetNumMeshes() const
    {
        return static_cast<UINT>(m_aMeshes.size());
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Renderable::GetNumMaterials

      Summary:  Returns the number of materials

      Returns:  UINT
                  Number of materials
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    UINT Renderable::GetNumMaterials() const
    {
        return static_cast<UINT>(m_aMaterials.size());
    }
}