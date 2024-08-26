#pragma once

class IndexBuffer
{
public:
    ~IndexBuffer();

    void Create(const vector<uint>& vertices,
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
