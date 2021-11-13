
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{

	matrix wvp;
	wvp = mul(_World, _View);
	wvp = mul(wvp, _Projection);

	Out.Position = mul(In.Position, wvp);
	Out.TexCoord = In.TexCoord;
	Out.Diffuse = In.Diffuse;

}

