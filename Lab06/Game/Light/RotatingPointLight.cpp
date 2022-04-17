#include "Light/RotatingPointLight.h"

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   RotatingPointLight::RotatingPointLight

  Summary:  Constructor

  Args:     const XMFLOAT4& position
              Position of the light
            const XMFLOAT4& color
              Position of the color
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
/*--------------------------------------------------------------------
  TODO: RotatingPointLight::RotatingPointLight definition (remove the comment)
--------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   RotatingPointLight::Update

  Summary:  Rotates the light every frame

  Args:     FLOAT deltaTime
              Elapsed time
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void RotatingPointLight::Update(_In_ FLOAT deltaTime)
{
    XMMATRIX rotate = XMMatrixRotationY(-2.0f * deltaTime);
    XMVECTOR position = XMLoadFloat4(&m_position);
    position = XMVector3Transform(position, rotate);
    XMStoreFloat4(&m_position, position);
}
