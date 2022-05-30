/*+===================================================================
  File:      CUBE1.H

  Summary:   Cube header file contains declarations of Cube class
             used for the lab samples of Game Graphics Programming
             course.

  Classes: Cube

  ?2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Cube/BaseCube.h"

class Cube : public BaseCube
{
public:
    Cube(_In_ const XMFLOAT4& outputColor);
    Cube(const Cube& other) = delete;
    Cube(Cube&& other) = delete;
    Cube& operator=(const Cube& other) = delete;
    Cube& operator=(Cube&& other) = delete;
    ~Cube() = default;

    virtual HRESULT Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext) override;
    virtual void Update(_In_ FLOAT deltaTime) override;
};

