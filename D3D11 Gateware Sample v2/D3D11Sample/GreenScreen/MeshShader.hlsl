#pragma pack_matrix(row_major)

struct InputVertex
{
	float4 xyz : POSITION;
	float uve : TEXCOORD;
	float4 norm: NORMAL;
};

struct OutputVertex
{
	float4 xyzw : SV_POSITION; 
	float4 rgba : OCOLOR;
};

cbuffer ShaderVariables : register(b0)
{
	float4x4 wMatrix;
	float4x4 vMatrix;
	float4x4 pMatrix;
};

OutputVertex main(InputVertex input)
{
	OutputVertex output = (OutputVertex)0;
	output.xyzw = float4(input.xyz.x, input.xyz.y, input.xyz.z, 1);
	output.rgba.rgb = float4(input.norm);

	//do math (Shader intrices)
	output.xyzw = mul(output.xyzw, wMatrix);
	output.xyzw = mul(output.xyzw, vMatrix);
	output.xyzw = mul(output.xyzw, pMatrix);

	//dont do perspective divide
	return output;
}
