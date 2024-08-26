#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startUV, Vector2 endUV, bool bReversed)
    :clipName(clipName), frameCount(frameCount),
    bReversed(bReversed)
{
    srv = srcTex->GetSRV();

    float imageWidth = srcTex->GetWidth();
    float imageHeight = srcTex->GetHeight();

    // �ִϸ��̼��� �׸� �׸� �κ��� �� ����
    // ù��° Ŭ������ ������ Ŭ�������� ũ��
    Vector2 clipSize = endUV - startUV;

    // �ִϸ��̼� Ŭ�� 1���� ũ��
    Vector2 frameSize;
    frameSize.x = clipSize.x / frameCount;
    frameSize.y = clipSize.y;

    // uv��ǥ���� ����� Ŭ�� ũ��
    // uv�� 0 ~ 1 ���� �ֱ� ����
    texelFrameSize.x = frameSize.x / imageWidth;
    texelFrameSize.y = frameSize.y / imageHeight;

    // �׸� ������ ��ǥ
    Vector2 texelStartPos;
    texelStartPos.x = startUV.x / imageWidth;
    texelStartPos.y = startUV.y / imageHeight;

    // ���� ����� �������� ��ǥ
    Vector2 keyFrame;

    for (int i = 0; i < frameCount; i++)
    {
        keyFrame.x = 
            texelStartPos.x + (texelFrameSize.x * i);
        keyFrame.y = texelStartPos.y;

        keyFrames.push_back(keyFrame);
    }
}

Animator::Animator()
{
}

Animator::~Animator()
{
    for (auto clip : animClips)
        SAFE_DELETE(clip.second);
}

void Animator::Update()
{
	if (stop == true && play == false)
	{
		return;
	}
	else if (stop == false && play == true)
	{

		// �÷��� ����Ʈ���� ��ŸŸ���� ������ ���� ���������� ����
		if (deltaTime > playRate)
		{
			// ������� �ƴ϶��
			if (currentClip->bReversed == false)
			{
				//if (deltaTime > playRate * 2)
				//{
				//	// ��ŸŸ�� ������ �÷��̷���Ʈ�� ������ ������ ���� ����ؼ� �ε����� �߰����ֱ�
				//		
				//	float missedFramefloor = floor(deltaTime / playRate);

				//	currentFrameIndex += missedFramefloor;

				//	//������ ������ ������ŭ ���� �Ҵ��ϱ�
				//	if (currentFrameIndex > currentClip->frameCount)
				//		currentFrameIndex = currentFrameIndex - currentClip->frameCount;
				//	
				//
				//}
				//else
				
				currentFrameIndex++;

				// ����ؾ� �ϴ� �������� �ִ밪�̶��
				// �ٽ� 0���� ������ ������Ų��.
				if (currentFrameIndex == currentClip->frameCount)
					currentFrameIndex = 0;

				// ������ ����
				currentFrame =
					currentClip->keyFrames[currentFrameIndex];
			}
			else // ������̶��
			{
				currentFrameIndex--;

				// ����ؾ��ϴ� ��ȣ�� -1���� �۾����ٸ�
				if (currentFrameIndex <= -1)
					currentFrameIndex = currentClip->frameCount - 1;

				// ������ ����
				currentFrame =
					currentClip->keyFrames[currentFrameIndex];
			}
			deltaTime = 0.0f;
		}
		else // ���� �������� �ٲܶ��� �ƴ϶��
			deltaTime += Time::Delta();
	}
}

void Animator::AddAnimClip(AnimationClip* animClip)
{
    animClips.insert(make_pair(animClip->clipName,
        animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{   
    // ���� �������� �ִϸ��̼��� ����
    // �Ű������� ���� Ŭ���� �����Ѵٸ�
    // �ٷ� �����Ѵ�
    if (currentClip == nullptr &&
        CheckExist(clipName) == true)
    {
        currentClip = animClips.find(clipName)->second;
        return;
    }
    // �̹� �������� �ִϸ��̼��̶�� �ƹ��͵� ����
    else if (currentClip != nullptr &&
        currentClip->clipName == clipName)
    {
        return;
    }

    // �������� �ִϸ��̼��� �ְ�
    // ���� �������� ���ϸ��̼��� �ƴ϶��
    // ��, �ִϸ��̼��� �ٲܲ����

    // �ִϸ��̼��� �ִ��� Ȯ��
    if (CheckExist(clipName))
    {
        // �ִϸ��̼� �־��ְ� �ð� �ʱ�ȭ
        currentClip = animClips.find(clipName)->second;
        deltaTime = 0.0f;

        // ���� ���� ������ �ִϸ��̼���
        // ��������� �����ؾ� �ϴ� �ִϸ��̼��̸�
        if (currentClip->bReversed == true)
            currentFrameIndex = currentClip->frameCount - 1;
        else // ����� ���� �ʴ� �ٸ�
            currentFrameIndex = 0;

        // �ִϸ��̼� ����
        currentFrame = 
            currentClip->keyFrames[currentFrameIndex];
    }
}