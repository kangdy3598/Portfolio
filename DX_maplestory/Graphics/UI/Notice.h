#pragma once

class NoticeClass : public UIClass
{

public:
	NoticeClass();
	NoticeClass(const NoticeClass&);
	~NoticeClass();

	bool Initialize(ID3D11Device*);
	void DrawNotice(int type = 0);

	static NoticeClass* Instance();

	const TCHAR* textMsg = nullptr;
	float m_frameTime = 0;
};