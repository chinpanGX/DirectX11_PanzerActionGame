/*-----------------------------------------
        
    [ToonAnimationPS.hlsl]
    Author : �o���đ�

------------------------------------------*/
#include "Common.hlsli"

Texture2D g_texture : register(t0);
Texture2D g_textureToon : register(t1);
SamplerState g_samplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_TARGET)
{
    float4 normal = normalize(In.Normal);
   
    outDiffuse = g_texture.Sample(g_samplerState, In.TexCoord);
    outDiffuse.a *= In.Diffuse.a;
  
    // �����v�Z
    float light = -dot(normal.xyz, _Light.Direction.xyz);
    
    // �A�j���[�V����
    float2 uv = light;
    float3 color;
    
    // Cpu�����瑗�M����ė���p�����[�^������UV�l��ύX����
    uv.x += _Parameter.x;
    uv.y = _Parameter.y;
    
    color = g_textureToon.Sample(g_samplerState, uv); //���邳���擾
    outDiffuse.rgb *= saturate(In.Diffuse.rgb * color * 1.5f); //�e�N�X�`�� * ���_�F * ���邳
}