#include "Renderer/Skybox.h"

#include "assimp/Importer.hpp"	// C++ importer interface
#include "assimp/scene.h"		// output data structure
#include "assimp/postprocess.h"	// post processing flags

namespace library
{
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Skybox::Skybox

      Summary:  Constructor

      Args:     const std::filesystem::path& cubeMapFilePath
                  Path to the cube map texture to use
                FLOAT scale
                  Scaling factor

      Modifies: [m_cubeMapFileName, m_scale].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Skybox::Skybox definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Skybox::Initialize

      Summary:  Initializes the skybox and cube map texture

      Args:     ID3D11Device* pDevice
                  The Direct3D device to create the buffers
                ID3D11DeviceContext* pImmediateContext
                  The Direct3D context to set buffers

      Modifies: [m_aMeshes, m_aMaterials].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Skybox::Initialize definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Skybox::GetSkyboxTexture

      Summary:  Returns the cube map texture

      Returns:  const std::shared_ptr<Texture>&
                  Cube map texture object
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Skybox::GetSkyboxTexture definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Skybox::initSingleMesh

      Summary:  Initialize single mesh from a given assimp mesh

      Args:     UINT uMeshIndex
                  Mesh index
                const aiMesh* pMesh
                  Point to an assimp mesh object
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Skybox::initSingleMesh definition (remove the comment)
    --------------------------------------------------------------------*/
}