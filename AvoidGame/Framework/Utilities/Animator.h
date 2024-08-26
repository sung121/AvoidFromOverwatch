#pragma once

class AnimationClip
{
public:
    // Animator�� AnimationClip�� ��� �����Ϳ� �����ϴ°��� ����ϰڴ�.
    friend class Animator;

    AnimationClip(wstring clipName,
        Texture2D* srcTex, UINT frameCount,
        Vector2 startUV, Vector2 endUV,
        bool bReversed = false);

protected:
    wstring clipName = L"";
    vector<Vector2> keyFrames;
    UINT frameCount = 0;
    ID3D11ShaderResourceView* srv = nullptr;
    Vector2 texelFrameSize = Values::ZeroVec2;
    bool bReversed = false;

};

class Animator
{
public:
    Animator();
    ~Animator();

    void Update();

    Vector2 GetCurrentFrame() { return currentFrame; }
    Vector2 GetTexelFrameSize() 
    { return currentClip->texelFrameSize; }
    ID3D11ShaderResourceView* GetCurrentSRV()
    { return currentClip->srv; }

    void AddAnimClip(AnimationClip* animClip);
    void SetCurrentAnimClip(wstring clipName);
	wstring GetCurrentAnimClipName() { return currentClip->clipName; };

	void StopUpdating() { stop = true; play = false; }
	void StartUpdating() { play = true; stop = false; }

	bool CheckExist(wstring clipName)
	{
		return animClips.find(clipName) != animClips.end();
	}

	void SetPlayRate(float playRate) { this->playRate = playRate; }
	float GetPlayRate(float playRate) { return this->playRate; }

	
private:
    // �ִϸ��̼� �̸��� �ִϸ��̼��� ���� ����
    unordered_map<wstring, AnimationClip*> animClips;
    // �ִϸ��̼��� �ߺ����� Ȯ���ϰ�
    
    // ���� �������� �ִϸ��̼ǰ� �� �����͵�
    AnimationClip* currentClip = nullptr;
    UINT currentFrameIndex = 0;
    Vector2 currentFrame = Values::ZeroVec2;

	bool stop = false;
	bool play = true;

    float deltaTime = 0.0f;
    float playRate = 1.0f / 15.0f;
};