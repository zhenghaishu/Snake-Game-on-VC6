/*++
版权没有，欢迎共享
作者: 郑海树
日期: 2009-09-04
修改: 2009-09-26
第二次修改: 2009-11-17
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
	int x; //贪食蛇每个节点左上角的横坐标
	int y; //贪食蛇每个节点左上角的纵坐标
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
	void	Initialize();						//初始化贪食蛇的状态
	void	AliveOrDie();						//生死判官
	double	Random(double start, double end);	//随机产生食物的位置

	int  gameStart;     //游戏开始或停止状态，1为开始，0为停止
	int  difficulty;	//游戏难度级别
	int  foodOrNot;		//是否添加新食物，1为添加，0为不添加	
	int  snakeLength;	//蛇的节点数
	position a[200];	//蛇的最大节点数设为200
	position b;			//辅助蛇的头结点的变量
	int xfood;			//食物的左上角坐标
	int yfood;			//食物的右上角坐标
	CRect rect;
	enum Move{left, up, right, down}; //移动的四个方向，枚举类型
	enum Move move;         //移动方向
	enum Move lastMove;		//蛇先前移动的方向，用于判断防止蛇逆行
	int  pauseOrContinue;   //游戏状态，0为暂停游戏，1为继续游戏

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
