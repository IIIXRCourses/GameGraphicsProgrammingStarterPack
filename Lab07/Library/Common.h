/*+===================================================================
  File:      COMMON.H

  Summary:   Common header file that contains common header files and 
			 macros used for the Library project of Game Graphics
			 Programming course.

  Functions:

  � 2022 Kyung Hee University
===================================================================+*/
#pragma once

#ifndef  UNICODE
#define UNICODE
#endif // ! UNICODE

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // ! WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <wincodec.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <directxcolors.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <cassert>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Resource.h"

constexpr LPCWSTR PSZ_COURSE_TITLE = L"Game Graphics Programming";

using namespace Microsoft::WRL;
using namespace DirectX;

namespace library
{
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_ConvertToLeftHanded)

    /*S+S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S
      Class:    DirectionsInput

      Summary:  Data structure that stores keyboard movement data
    S---S---S---S---S---S---S---S---S---S---S---S---S---S---S---S---S-S*/
    struct DirectionsInput
    {
        BOOL bFront;
        BOOL bLeft;
        BOOL bBack;
        BOOL bRight;
        BOOL bUp;
        BOOL bDown;
    };

    /*S+S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S+++S
      Class:    MouseRelativeMovement

      Summary:  Data structure that stores mouse relative movement data
    S---S---S---S---S---S---S---S---S---S---S---S---S---S---S---S---S-S*/
    struct MouseRelativeMovement
    {
        LONG X;
        LONG Y;
    };
}