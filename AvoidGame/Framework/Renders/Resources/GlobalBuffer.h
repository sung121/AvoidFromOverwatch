#pragma once

#include "Framework.h"

class WorldBuffer : public ShaderBuffer
{
public:
    WorldBuffer() : ShaderBuffer(&data, sizeof(Data))
    {
        // ����� �ʱ�ȭ   
        D3DXMatrixIdentity(&data.world);
    }

    void SetWorld(Matrix world)
    {
        // ��� ��ġ (���� ���� �ٲ� �ִ´�)
        D3DXMatrixTranspose(&data.world, &world);
    }

    struct Data
    {
        Matrix world;
    };
private:
    Data data;
};

class VPBuffer : public ShaderBuffer
{
public:
    VPBuffer() : ShaderBuffer(&data, sizeof(Data))
    {
        // ����� �ʱ�ȭ   
        D3DXMatrixIdentity(&data.view);
        D3DXMatrixIdentity(&data.projection);
    }

    void SetView(Matrix view)
    {
        // ��� ��ġ (���� ���� �ٲ� �ִ´�)
        D3DXMatrixTranspose(&data.view, &view);
    }
    void SetProjection(Matrix projection)
    {
        // ��� ��ġ (���� ���� �ٲ� �ִ´�)
        D3DXMatrixTranspose(&data.projection, &projection);
    }

    struct Data
    {
        Matrix view;
        Matrix projection;
    };
private:
    Data data;
};

/*
WVP : World, View, Projection
- 3D ���� 2D ��ũ�� ��ǥ�� ��ȯ�ϴ� ���� �� �ϳ�
- 3D ���� ������ ȭ�鿡 ���̴� �׸��� 2D�̱� ������ ���� ��� ���ӿ���
���Ǵ� �����̶� �����ϸ� �ȴ�.

1. World
- ���� ������ ���� ��ǥ�迡�� ���� ��ǥ��� ��ȯ�ϴ� ���� �ǹ�
- ���� ��ġ, ȸ�� �� ũ�⸦ ����

2. View
- ī�޶��� ��ġ, ����, �þ߸� ��Ÿ���� ���
- ���� ��ǥ�迡�� ī�޶� �ٶ󺸴� ������ ��Ÿ��
- ī�޶��� ��ġ�� ������ ����

3. Projection
- 3D������ 2D ��ũ�� ��ǥ�� ��ȯ�ϴ� ���� �ǹ�
- �þ߰�, ��Ⱦ��, ũ���� ��� ���� ����Ͽ� ����

*/