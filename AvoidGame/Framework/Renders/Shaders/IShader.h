#pragma once

// ����� �ϱ����� ��ü�� �����佺��� �Ѵ�.
class IShader
{
public:
    // ����
    virtual void Create(const wstring path, const string entryName) = 0;
    // ��ü �ʱ�ȭ
    virtual void Clear() = 0;
    // ���̴� ����
    virtual void SetShader() = 0;

protected:
    void CompileShader(wstring path, string entryName, string profile,
        ID3DBlob** blob);

    wstring path = L"";
    string entryName = "";

private:
    void CheckShaderError(HRESULT hr, ID3DBlob* error);
};