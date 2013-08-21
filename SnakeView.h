/*++
��Ȩû�У���ӭ����
����: ֣����
����: 2009-09-04
�޸�: 2009-09-26
�ڶ����޸�: 2009-11-17
--*/

// SnakeView.h : interface of the CSnakeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAKEVIEW_H__9AA975BC_4C2B_44DE_8F46_B9A1CE6B4DCB__INCLUDED_)
#define AFX_SNAKEVIEW_H__9AA975BC_4C2B_44DE_8F46_B9A1CE6B4DCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct position
{
	int x; //̰ʳ��ÿ���ڵ����Ͻǵĺ�����
	int y; //̰ʳ��ÿ���ڵ����Ͻǵ�������
};

class CSnakeView : public CView
{
protected: // create from serialization only
	CSnakeView();
	DECLARE_DYNCREATE(CSnakeView)

// Attributes
public:
	CSnakeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSnakeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSnakeView();
	void	Initialize();						//��ʼ��̰ʳ�ߵ�״̬
	void	AliveOrDie();						//�����й�
	double	Random(double start, double end);	//�������ʳ���λ��

	int  gameStart;     //��Ϸ��ʼ��ֹͣ״̬��1Ϊ��ʼ��0Ϊֹͣ
	int  difficulty;	//��Ϸ�Ѷȼ���
	int  foodOrNot;		//�Ƿ������ʳ�1Ϊ��ӣ�0Ϊ�����	
	int  snakeLength;	//�ߵĽڵ���
	position a[200];	//�ߵ����ڵ�����Ϊ200
	position b;			//�����ߵ�ͷ���ı���
	int xfood;			//ʳ������Ͻ�����
	int yfood;			//ʳ������Ͻ�����
	CRect rect;
	enum Move{left, up, right, down}; //�ƶ����ĸ�����ö������
	enum Move move;         //�ƶ�����
	enum Move lastMove;		//����ǰ�ƶ��ķ��������жϷ�ֹ������
	int  pauseOrContinue;   //��Ϸ״̬��0Ϊ��ͣ��Ϸ��1Ϊ������Ϸ

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSnakeView)
	afx_msg void OnStart();
	afx_msg void OnDifficultyEasy();
	afx_msg void OnDifficultyHard();
	afx_msg void OnDifficultyHarder();
	afx_msg void OnDifficultyNormal();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPause();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SnakeView.cpp
inline CSnakeDoc* CSnakeView::GetDocument()
   { return (CSnakeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNAKEVIEW_H__9AA975BC_4C2B_44DE_8F46_B9A1CE6B4DCB__INCLUDED_)
