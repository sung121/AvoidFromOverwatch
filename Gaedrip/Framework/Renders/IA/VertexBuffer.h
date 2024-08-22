#pragma once

class VertexBuffer
{
public:
    ~VertexBuffer();

    template<typename T>
    void Create(const vector<T>& vertices,
        const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

    ID3D11Buffer* GetResource() { return buffer; }

    uint GetStride() { return stride; }
    uint GetOffset() { return offset; }
    uint GetCount() { return count; }

    void SetIA();

private:
    ID3D11Buffer* buffer = nullptr;

    uint stride = 0;    // ���� ���ۿ��� �� ������ ũ��
    uint offset = 0;    // ���� ���ۿ��� ���� ���� ��ġ
    uint count = 0;     // ���� ���ۿ��� ���� ���� ����
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
    stride = sizeof(T);             // ������ ũ��
    count = vertices.size();        // ������ ����

    D3D11_BUFFER_DESC desc;         // ���� ������ ���� ����ü (���赵) 
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC)); // ����ü �ʱ�ȭ

    // desc ����
    {
        // ������ ��� �뵵
        desc.Usage = usage;
        // ������ ���� ���� (���� ���۷� ��� ����)
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
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
