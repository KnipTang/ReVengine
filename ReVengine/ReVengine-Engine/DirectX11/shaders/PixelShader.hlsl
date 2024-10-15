struct ps_input
{

    float3 color : COLOR;
};

struct ps_output
{

};

float4 ps_main(ps_input input) : SV_TARGET
{
    return float4(input.color, 1.0f);
}