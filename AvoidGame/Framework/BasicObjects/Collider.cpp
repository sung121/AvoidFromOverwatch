#include "Framework.h"
#include "Collider.h"

#include "Geomatries/Rect.h"
#include "Utilities/Transform.h"

Collider::Collider(Vector3 position, Vector3 size, float rotation) 
	: Rect(position, size, rotation)
{
	MakeCollider();
}

Collider::Collider(const Transform& transform)
	:Rect(transform)
{
	MakeCollider();
}


Collider::~Collider()
{
	Rect::~Rect();

	SAFE_DELETE(collider);
	SAFE_DELETE(edge);

}

void Collider::MakeCollider()
{
	edge = new RectEdge();
	collider = new BoundingBox();

	verticesPosition[0] = vertices[0].position;
	verticesPosition[1] = vertices[1].position;
	verticesPosition[2] = vertices[2].position;
	verticesPosition[3] = vertices[3].position;

	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

		// CullMode : �׸��� ���� �� ���� (CULL_BACK = �޸��� �׸��� ����)
		desc.CullMode = D3D11_CULL_BACK;
		// FillMode : ä��� ��� ���� (SOLID�� ���� ä���)
		desc.FillMode = D3D11_FILL_WIREFRAME;
		// �ݽð� �׸��� ����(false�� �ð�������� �����Ѵ�)
		desc.FrontCounterClockwise = false;

		HRESULT hr = DEVICE->CreateRasterizerState(&desc, &rs);
		CHECK(hr);
	}
}

void Collider::Update()
{
	__super::Update();
	collider->UpdateCollisionData(world, verticesPosition);
}

void Collider::Render()
{
	if (renders)
	{
	__super::Render();
	}
}
