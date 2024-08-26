#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;
vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
    : filePath(filePath)
{
    Textures::Load(this);
}

void Texture2D::ReadPixel(vector<Color>* pixels)
{
    ID3D11Texture2D* texture;
    srv->GetResource((ID3D11Resource**)&texture);

    ReadPixel(texture, pixels);
    SAFE_RELEASE(texture);
}

void Texture2D::ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels)
{
    // ������ �����͸� �����ص� ���赵
    D3D11_TEXTURE2D_DESC srcDesc;
    // �ŰԺ��� ���� ������ �����͸� �̾� ���赵�� ����
    texture->GetDesc(&srcDesc);

    // ����� ����� ���赵
    D3D11_TEXTURE2D_DESC destDesc;
    ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));

    // ��� �ؽ��� ���赵 ����
    {
        // ��� ����
        destDesc.Usage = D3D11_USAGE_STAGING;
        // CPU ���� ����
        destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        // ���ο� ���δ� ������ ���� �ִ´�.
        destDesc.Width = srcDesc.Width;
        destDesc.Height = srcDesc.Height;
        // mipmap ������ 1�� ����
        // mipmap�� �׸��� ����Ƽ ����
        // �츮�� ������� �ʱ⿡ 1�� ���� 
        destDesc.MipLevels = 1;
        // �迭 ũ��� 1�� ����
        destDesc.ArraySize = 1;
        // ���䰪�� ������ ���䰪����
        destDesc.Format = srcDesc.Format;
        // ���ø� ����� ������ �������
        destDesc.SampleDesc = srcDesc.SampleDesc;
    }

    ID3D11Texture2D* destTex = nullptr;
    HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr,
        &destTex);
    CHECK(hr);
    // �����׸��� �����͸� destTex�� ������ ����
    D3DX11LoadTextureFromTexture(DC, texture, nullptr,
        destTex);

    // �ȼ� ����
    int pixelNum = destDesc.Width * destDesc.Height;

    // �ȼ� ���� ��ŭ�� ���� Ȯ��
    UINT* colors = new UINT[pixelNum];

    D3D11_MAPPED_SUBRESOURCE subResoucre;
    DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subResoucre);
    {
        memcpy(colors, subResoucre.pData,
            sizeof(UINT) * pixelNum);
    }
    DC->Unmap(destTex, 0);

    UINT* alpha = new UINT[pixelNum];
    UINT* red   = new UINT[pixelNum];
    UINT* green = new UINT[pixelNum];
    UINT* blue  = new UINT[pixelNum];

    for (int i = 0; i < pixelNum; i++)
    {
        // colors���� ARGB ������ ����
        alpha[i] = (colors[i] & 0xFF000000);
        red[i]   = (colors[i] & 0x00FF0000);
        green[i] = (colors[i] & 0x0000FF00);
        blue[i]  = (colors[i] & 0x000000FF);

        // OpenGL�� �ڵ�� ȣ�ϵǱ� ����
        red[i]  = colors[i] >> 16;
        blue[i] = colors[i] << 16;

        // �÷� ���ġ
        colors[i] = alpha[i] | red[i] | green[i] | blue[i];
    }

    // pixels�� colors �Ҵ�
    pixels->assign(&colors[0], &colors[pixelNum - 1]);

    SAFE_DELETE_ARRAY(colors);
    SAFE_RELEASE(destTex);
}

void Textures::Delete()
{
    for (TextureDesc desc : descs)
        SAFE_RELEASE(desc.srv);
}

void Textures::Load(Texture2D* texture)
{
    HRESULT hr;
    TexMetadata metaData;

    // texture�� �������ִ� ���� �����
    // ���� Ȯ���ڶ�� ����.
    wstring ext = Path::GetExtension(texture->filePath);
    if (ext == L"tga")
    {
        hr = GetMetadataFromTGAFile(texture->filePath.c_str(),
            metaData);
        CHECK(hr);
    }
    else if (ext == L"dds")
    {
        hr = GetMetadataFromDDSFile(texture->filePath.c_str(),
            DDS_FLAGS_NONE, metaData);
        CHECK(hr);
    }
    else
    {
        hr = GetMetadataFromWICFile(texture->filePath.c_str(),
            WIC_FLAGS_NONE, metaData);
        CHECK(hr);
    }

    // ��Ÿ �����Ϳ��� �ʺ�� ���̸� ����
    UINT width = metaData.width;
    UINT height = metaData.height;

    TextureDesc desc;
    desc.filePath = texture->filePath;
    desc.width = width;
    desc.height = height;

    // �ߺ� �˻縦 ���� desc�� bool��
    TextureDesc exist;
    bool bExist = false;

    for (TextureDesc temp : descs)
    {
        if (desc == temp) // �̰� �ҷ��� ����ü�� ���۷��̴� ����
        {
            bExist = true;
            exist = temp;

            break;
        }
    }

    // �ߺ� �ƴٸ�
    if (bExist)
    {
        texture->srv = exist.srv;
        texture->metaData = metaData;
    }
    else // �������� �ʴ´ٸ�
    {
        // �̹��� ���� �����͸� �а� ���� ���ִ� Ŭ����
        ScratchImage image;

        if (ext == L"tga")
        {
            hr = LoadFromTGAFile(texture->filePath.c_str(),
                &metaData, image);
            CHECK(hr);
        }
        else if (ext == L"dds")
        {
            hr = LoadFromDDSFile(texture->filePath.c_str(),
                DDS_FLAGS_NONE, &metaData, image);
            CHECK(hr);
        }
        else
        {
            hr = LoadFromWICFile(texture->filePath.c_str(),
                WIC_FLAGS_NONE, &metaData, image);
            CHECK(hr);
        }

        ID3D11ShaderResourceView* srv = nullptr;
        hr = CreateShaderResourceView(DEVICE, image.GetImages(),
            image.GetImageCount(), metaData, &srv);
        CHECK(hr);

        desc.srv = srv;
        texture->srv = srv;
        texture->metaData = metaData;

        descs.push_back(desc);
    }
}

/*
DirectTex
- �׸� ���� ������ �����Ҽ� �ִ� ����� ���� ���̺귯��

Metadata
- �׸��� �ʺ�,����,����,�迭 ũ��, ���� �� �� ��
�׸��� ������ �ִ� �����͵��� �����ϴ� ����ü
*/