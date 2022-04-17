/*+===================================================================
  File:      ROTATINGPOINTLIGHT.H

  Summary:   RotatingPointLight header file contains 
             declarations of the rotating point light.

  Classes: RotatingPointLight

  © 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Light/PointLight.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    RotatingPointLight

  Summary:  Point light that rotates around the y axis

  Methods:  Update
              Rotates every frame by y-axis
            RotatingPointLight
              Constructor.
            ~RotatingPointLight
              Destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class RotatingPointLight final : public library::PointLight
{
public:
    RotatingPointLight() = delete;
    RotatingPointLight(_In_ const XMFLOAT4& position, _In_ const XMFLOAT4& color);
    RotatingPointLight(const RotatingPointLight& other) = default;
    RotatingPointLight(RotatingPointLight&& other) = default;
    RotatingPointLight& operator=(const RotatingPointLight & other) = default;
    RotatingPointLight& operator=(RotatingPointLight && other) = default;
    virtual ~RotatingPointLight() = default;

    virtual void Update(_In_ FLOAT deltaTime) override;
};