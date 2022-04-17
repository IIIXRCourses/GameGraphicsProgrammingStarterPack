#include "Light/PointLight.h"

#include "Renderer/DataTypes.h"

namespace library
{
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   PointLight::PointLight

      Summary:  Constructor

      Args:     const XMFLOAT4& position
                  Position of the light
                const XMFLOAT4& color
                  Position of the color

      Modifies: [m_position, m_color].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: PointLight::PointLight definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   PointLight::GetPosition

      Summary:  Returns the position of the light

      Returns:  const XMFLOAT4&
                  Position of the light
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: PointLight::GetPosition definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   PointLight::GetColor

      Summary:  Returns the color of the light

      Returns:  const XMFLOAT4&
                  Color of the light
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: PointLight::GetColor definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   PointLight::Update

      Summary:  Updates the light every frame

      Args:     FLOAT deltaTime
                  Elapsed time
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    void PointLight::Update(_In_ FLOAT deltaTime)
    {
        UNREFERENCED_PARAMETER(deltaTime);
    }
}