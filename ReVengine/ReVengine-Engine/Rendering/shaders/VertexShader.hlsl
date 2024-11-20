struct vs_input
{
    float4 position : POSITION;
    float2 uv : UV;
};

struct vs_output
{
    float4 position : SV_POSITION;
    float2 uv : UV;
};

cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
    matrix transform;
};

vs_output vs_main(vs_input input)
{
    vs_output output = (vs_output) 0;
    
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
   // output.position.y = -output.position.y;
    //output.position.z -= 10;
    //output.position = mul(output.position, transform);
    //output.position = mul(float4(input.position.x, input.position.y, -input.position.z, 1.0f), transform);
    output.uv = input.uv;
    //output.color = input.color;
    
    return output;
}