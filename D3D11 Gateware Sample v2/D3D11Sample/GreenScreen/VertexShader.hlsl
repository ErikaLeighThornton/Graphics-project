//rule of three
//states that three things HAVE to match
//1. c++ vertex struct
//2.input layout
//3. hlsl vertex struct

#pragma pack_matrix(row_major)

//needs and input
struct InputVertex
{
	float4 xyzw : POSITION;
	float4 rgba : COLOR;
};

//needs an output
struct OutputVertex
{
	float4 xyzw : SV_POSITION; //system values
	float4 rgba : OCOLOR;
};

//constant buffer
cbuffer ShaderVariables : register(b0)
{
	float4x4 wMatrix;
	float4x4 vMatrix;
	float4x4 pMatrix;
};

OutputVertex main(InputVertex input)
{
	OutputVertex output = (OutputVertex)0;
	output.xyzw = input.xyzw;
	output.rgba = input.rgba;
	
	//do math(Shader intrices
	output.xyzw = mul(output.xyzw, wMatrix);
	output.xyzw = mul(output.xyzw, vMatrix);
	output.xyzw = mul(output.xyzw, pMatrix);

	//DO NOT DO PERSPECTIVE DIVIDE
	return output;
}
