// VertexInput ����ü ����

struct VertexInput
{
    float4 position : POSITION0; // ������ ��ġ
    float4 color : COLOR0; // ������ ����
};

struct PixelInput
{
    float4 position : SV_POSITION0; // ������ ��ġ
    float4 color : COLOR0; // ������ ����   
};


cbuffer WorldBuffer : register(b0)
{
    matrix _world;
};

cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _projection;
};

// ���ؽ� ���̴�
PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    
    // �� ������� ���ؾ� ���ϴ� ��ġ�� ���� ���� �� �ִ�.
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
    output.color = input.color;
    
    return output;
};

float4 PS(PixelInput input) : SV_Target
{
    return input.color;
};

/*
Semantic : ����ƽ(��� �빮�� ���ڵ�)
- HLSL ���̴����� �������� �ǹ̸� �����ϴ� �� ���
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���� �� �ֵ��� ������
- ���� �̸� �ڿ� ':' ��ȣ�� �Բ� ����
- �ý��� �� ����ƽ�� 'SV_' ���λ�� �����ϸ� Directx3D���� ���ǵ� Ư���� �ǹ̸� ���Ѵ�.
- �ý��� �� ����ƽ�� ���̴� �������� ���� �����͸� �����ϴµ� ���ȴ�.

slot
- GPU���� ����ϴ� ��� ����, �ؽ�ó, ���÷� ���� �ڿ��� �ĺ��ϴ� �ε���
- �� ������ ������ ��ȣ�� ������, �ش� �ڿ��� ������ ���ҿ� ���� �ٸ��� �Ҵ��
- register��� Ű���带 ����Ͽ� ����
- �� �ڿ��� � ���Կ� �Ҵ�� ������ ��������� ������ �� ����
- �ֿ� ���� 
    1) ��� ���� ����
    - ��� �����͸� �����ϴµ� ���Ǹ�, VS�� PS���� ������ �� �ִ�.
    - ��� ���� ������ register(b#)�� ����Ͽ� �����Ѵ�.
    
    2) �ؽ�ó ����
    - �̹��� �����͸� �����ϴµ� ���
    - �ؽ�ó ������ register(t#)�� ����Ͽ� ����
    
    3) ���÷� ����
    - �ؽ�ó�� ���ø��ϴµ� ���
    - ���÷� ������ register(s#)�� ����Ͽ� ����

cbuffer = Contant Buffer : ��� ����
- ���̴����� ����ϴ� ���� ������ �����ϴµ� ���
- �� ��� ���� �������Ϳ��� �� ���� ��� ���۸� �Ҵ��� �� ����

- ��� ���� ���ο��� ���� ���� ������ ������ �� �ִ�.




*/



 