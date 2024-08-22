#include "Framework.h"
#include "IShader.h"

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob)
{
    // �����Ϸ� ���� �޼����� ������ Blob ������
    ID3DBlob* error = nullptr;
    
    // ���̴� ������ �������ϰ� ����� �ŰԺ����� ���� Blob�� ����
    HRESULT hr = D3DCompileFromFile
    (
        // ���̴� ���
        path.c_str(),
        // ���̴� ������ ��� ��ġ
        nullptr,
        // Include �������̽��� ������ Ŭ������ ����� ���̴� ���Ͽ���
        // �ٸ� ������ include �� �� ����� �� �ִ� ���ý�Ʈ
        nullptr,
        // ���̴� ������ ���� ������
        entryName.c_str(),
        // ���̴� ������ ������ �̸�
        profile.c_str(),
        // ������ ��� �ɼ�
        D3DCOMPILE_ENABLE_STRICTNESS,
        // ����� ������ ���Ե� ������ ����� �����ϱ� ���� �ɼ�
        0,
        // ������ ����� ������ blob ������
        blob,
        // �����Ϸ� ���� �޼����� ������ blob ������ �ּҰ�
        &error
    );
    // �����Ϸ� ������ �߻��ϸ� �޼����� ����� �Լ�
    CheckShaderError(hr, error);
    SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob* error)
{
    if (FAILED(hr))
    {
        if (error)
        {
            string str = (const char*)error->GetBufferPointer();
            MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
        }
        // ���α׷� �ߴ�
        CHECK(false);
    }
}

/*
ID3DBlob
- �޸𸮿� �Ҵ�� ������ ���
- ��ǥ������ ���̴� �ڵ峪 ���� ������ ���� �����Ѵ�. 
- �޸𸮿� �Ҵ�� ������ ����� ������ ������ ������ �� �ִ�.
*/