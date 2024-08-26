#include "Framework.h"
#include "InputLayout.h"

InputLayout::~InputLayout()
{   
    SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* desc, uint count, ID3DBlob* blob)
{
    // �Ű� ������ �ϳ��� ���ٸ� ����
    if (!desc || !count || !blob)
        CHECK(false);

    // blob = ���̴� �ڵ峪 ������ ������ ���� �����ϴ� �޸�

    HRESULT hr = DEVICE->CreateInputLayout
    (
        desc,                    // InputLayout�� Desc
        count,                   // InputLayout�� ����
        blob->GetBufferPointer(),// ���̴� �ڵ带 �����ϴ� ��� ������
        blob->GetBufferSize(),   // ���̴� �ڵ带 �����ϴ� ��� ũ��
        &inputLayout
    );
}

void InputLayout::SetIA()
{
    DC->IASetInputLayout(inputLayout);
}
