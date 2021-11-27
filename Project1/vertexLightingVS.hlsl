/*-----------------------------------------
        
    [vertexLightingVS.hlsl]
    Author : �o���đ�

------------------------------------------*/
#include "common.hlsli"

void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;
	wvp = mul(_World, _View);
	wvp = mul(wvp, _Projection);
	
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, _World);
	worldNormal = normalize(worldNormal);

	float light = -dot(_Light.Direction.xyz, worldNormal.xyz);
	light = saturate(light);

	Out.Diffuse = In.Diffuse * _Material.Diffuse * light * _Light.Diffuse;
	Out.Diffuse += In.Diffuse * _Material.Ambient * _Light.Ambient;
	Out.Diffuse += _Material.Emission;
	Out.Diffuse.a = In.Diffuse.a * _Material.Diffuse.a;

	Out.Position = mul( In.Position, wvp );
	Out.TexCoord = In.TexCoord;
}

