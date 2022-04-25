/*+===================================================================
  File:      MATERIAL.H

  Summary:   Material header file contains declaration of class
			 Material used to abstract multiple texture data.

  Classes:  Material

  © 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Texture/Texture.h"

namespace library
{
    class Material
    {
    public:
        Material();
        Material(const Material& other) = default;
        Material(Material&& other) = default;
        Material& operator=(const Material& other) = default;
        Material& operator=(Material&& other) = default;
        virtual ~Material() = default;

    public:
        std::shared_ptr<Texture> pDiffuse;
        std::shared_ptr<Texture> pSpecular;
    };
}