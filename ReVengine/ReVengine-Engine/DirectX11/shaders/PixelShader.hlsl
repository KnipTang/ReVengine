struct ps_input
{
    float3 position_local : POSITION;
};

struct ps_output
{
    float4 position_clip : SV_POSITION;
};

float4 ps_main(ps_input input) : SV_TARGET
{
    return float4(0.0, 0.0, 0.0, 1.0);
}