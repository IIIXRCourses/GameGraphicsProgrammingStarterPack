/*+===================================================================
  File:      ROTATINGCUBE.H

  Summary:  RotatingCube header file contains declarations of 
            RotatingCube class used for the lab samples of Game 
            Graphics Programming course.

  Classes: RotatingCube

  © 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Cube/BaseCube.h"

class RotatingCube : public BaseCube
{
public:
    RotatingCube(const std::filesystem::path& textureFilePath);
    RotatingCube(const XMFLOAT4& outputColor);
    RotatingCube(const RotatingCube& other) = delete;
    RotatingCube(RotatingCube&& other) = delete;
    RotatingCube& operator=(const RotatingCube& other) = delete;
    RotatingCube& operator=(RotatingCube&& other) = delete;
    ~RotatingCube() = default;

    virtual void Update(_In_ FLOAT deltaTime) override;
};