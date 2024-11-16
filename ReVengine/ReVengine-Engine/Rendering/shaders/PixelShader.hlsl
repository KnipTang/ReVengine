Texture2D Texture : register(t0);
SamplerState Sampler : register(s0);

struct ps_input
{
    float4 position : SV_POSITION;
    float2 uv : UV;
    //float3 color : COLOR;
};

struct ps_output
{
    float4 color : SV_TARGET;
};

ps_output ps_main(ps_input input)
{
    ps_output output;
    
    float4 textureColor;
    
    textureColor = Texture.Sample(Sampler, input.uv);
    
    output.color = float4(textureColor);
    //output.color = float4(input.color, 1);
    return output;
}