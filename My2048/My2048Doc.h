
// My2048Doc.h : CMy2048Doc ��Ľӿ�
//


#pragma once
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "GUIsettings.h"


class CMy2048Doc : public CDocument
{
protected: // �������л�����
	CMy2048Doc();
	DECLARE_DYNCREATE(CMy2048Doc)
	bool isWin;
	bool isLose;
	int data[4][4];
	int score;
	int ratio_2to4;
	FILE *fp;
	GUIsettings gui;

// ����
public:
	int random(int max);
	void GenerateNewLattice();
	void GenerateNewGame();
	int JudgeCurrentStatus();
	bool MoveUp();
	bool MoveDown();
	bool MoveLeft();
	bool MoveRight();
	void MoveLattice(int x1, int y1, int x2, int y2, int value);
	void AddScore(int score);

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMy2048Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
