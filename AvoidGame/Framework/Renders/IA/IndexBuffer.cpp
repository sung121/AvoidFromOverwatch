#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::~IndexBuffer()
{
    SAFE_RELEASE(buffer);
}

void IndexBuffer::Create(const vector<uint>& vertices, const D3D11_USAGE& usage)
{
    stride = sizeof(uint);          // ������ ũ��
    count = vertices.size();        // ������ ����

    D3D11_BUFFER_DESC desc;         // ���� ������ ���� ����ü (���赵) 
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC)); // ����ü �ʱ�ȭ

    // desc ����
    {
        // ������ ��� �뵵
        desc.Usage = usage;
        // ������ ���� ���� (���� ���۷� ��� ����)
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        // ������ ũ��
        desc.ByteWidth = stride * count;

        // cpu ����
        switch (usage)
        {
            // CPU�� �а� ���°� �Ұ����ϴ�.
            // GPU�� �����Ҽ� �ִ�.
        case D3D11_USAGE_DEFAULT:
            // CPU�� �а� ���°� �Ұ����ϴ�.
            // GPU���� �б⸸ �����ϴ�.
        case D3D11_USAGE_IMMUTABLE:
            break;

            // CPU�� ���� �����ϰ� ������ �����ϴ�.
        case D3D11_USAGE_DYNAMIC:
            // cpu���� ���� �������� ����
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            break;

            // CPU�� ���� �����ϰ� GPU�� ���� �ֵ��� ��ȯ�Ҽ��ִ�.
        case D3D11_USAGE_STAGING:
            desc.CPUAccessFlags =
                D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
            break;
        }
    }

    // ����
    {
        D3D11_SUBRESOURCE_DATA subData; // ���� �����͸� ��Ƶ� ����ü
        ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA)); // �ʱ�ȭ

        subData.pSysMem = vertices.data();

        // HRESULT�� ���� �����Ͱ� �� ����� ������ �˻��ϴ� ����
        HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);
        CHECK(hr);
    }
}

void IndexBuffer::SetIA()
{
    // ������ ���� ����
    DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
