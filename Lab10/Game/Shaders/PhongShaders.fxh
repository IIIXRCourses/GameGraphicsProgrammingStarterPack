//--------------------------------------------------------------------------------------
// File: PhongShaders.fx
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License (MIT).
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
#define NUM_LIGHTS (1)
#define NEAR_PLANE (0.01f)
#define FAR_PLANE (1000.0f)

Texture2D shadowMapTexture : register(t2);
SamplerState shadowMapSampler : register(s2);

cbuffer cbLights : register(b3)
{
    float4 LightPositions[NUM_LIGHTS];
    float4 LightColors[NUM_LIGHTS];
	matrix LightViews[NUM_LIGHTS];
	matrix LightProjections[NUM_LIGHTS];
};

struct PS_PHONG_INPUT
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD0;
    float3 Normal : NORMAL;
    float3 WorldPosition : WORLDPOS;
    float3 Tangent : TANGENT;
    float3 Bitangent : BITANGENT;
    float4 LightViewPosition : TEXCOORD1;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_PHONG_INPUT VSPhong(VS_INPUT input)
{
	/*--------------------------------------------------------------------
	  TODO: Vertex shader code (remove the comment)
	--------------------------------------------------------------------*/
}

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return ((2.0 * NEAR_PLANE * FAR_PLANE) / (FAR_PLANE + NEAR_PLANE - z * (FAR_PLANE - NEAR_PLANE))) / FAR_PLANE;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PSPhong(PS_PHONG_INPUT input) : SV_Target
{
	/*--------------------------------------------------------------------
	  TODO: Pixel shader code (remove the comment)
	--------------------------------------------------------------------*/
}