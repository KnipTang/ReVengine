cbuffer MatrixBuffer
{
    matrix orthoMatrix;
};

struct VertexInputType
{
    float4 position : POSITION;
    float2 uv : UV;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 uv : UV;
};

PixelInputType main(VertexInputType input)
{
    PixelInputType output;
    output.position = mul(input.position, orthoMatrix);
    output.uv = input.uv;
    return output;
}