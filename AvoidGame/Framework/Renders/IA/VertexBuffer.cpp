#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
    // I�� �����ϴ� DX�ڷ����� RELEASE�� ����� �����Ѵ�.
    SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
    // IA�� ���� ���۸� �ǳ��ִ� �Լ�
    DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
