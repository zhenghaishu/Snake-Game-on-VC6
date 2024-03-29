// SnakeView.cpp : implementation of the CSnakeView class
//

#include "stdafx.h"
#include "Snake.h"

#include "SnakeDoc.h"
#include "SnakeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSnakeView

IMPLEMENT_DYNCREATE(CSnakeView, CView)

BEGIN_MESSAGE_MAP(CSnakeView, CView)
	//{{AFX_MSG_MAP(CSnakeView)
	ON_COMMAND(IDC_START, OnStart)
	ON_COMMAND(IDC_DIFFICULTY_EASY, OnDifficultyEasy)
	ON_COMMAND(IDC_DIFFICULTY_HARD, OnDifficultyHard)
	ON_COMMAND(IDC_DIFFICULTY_HARDER, OnDifficultyHarder)
	ON_COMMAND(IDC_DIFFICULTY_NORMAL, OnDifficultyNormal)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_COMMAND(IDC_PAUSE, OnPause)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnakeView construction/destruction

CSnakeView::CSnakeView()
{
	// TODO: add construction code here
	gameStart = 0;
	difficulty = 10; //10为简单的等级，6为一般的等级，3为难的等级，2为很难的等级
	snakeLength = 4; //蛇的初始长度为4个节点
	pauseOrContinue = 1; //游戏初始设为运行状态
}

CSnakeView::~CSnakeView()
{
}

BOOL CSnakeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSnakeView drawing

void CSnakeView::OnDraw(CDC* pDC)
{
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSnakeView printing

BOOL CSnakeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSnakeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSnakeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSnakeView diagnostics

#ifdef _DEBUG
void CSnakeView::AssertValid() const
{
	CView::AssertValid();
}

void CSnakeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSnakeDoc* CSnakeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSnakeDoc)));
	return (CSnakeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSnakeView message handlers

void CSnakeView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
//	KillTimer(1);

	CString score;
	score.Format("分数： %d", snakeLength-4); //游戏分数为蛇的节点数-蛇出生时的节点数
	AliveOrDie();
	
	//创建设备描述表
	CDC *pDC, hDC;
	pDC = GetDC();	
	hDC.CreateCompatibleDC(NULL);
	CBitmap hBitmap, *pOldBitmap ;
	hBitmap.CreateCompatibleBitmap(pDC, 1000, 1000);
	pOldBitmap = hDC.SelectObject(&hBitmap);

	hDC.FillSolidRect(0, 0, 1000, 1000, RGB(255, 255, 255)); //设定白色区域范围
	hDC.TextOut(550, 200, score);  //在坐标(500,200)处输出游戏分数
	hDC.Rectangle(CRect(90, 90, 520, 520)); //设定外矩形框
	hDC.Rectangle(CRect(100, 100, 510, 510)); //设定内矩形框

	if(gameStart == 1)  //游戏处于运行状态
	{
		b.x = a[0].x;
		b.y = a[0].y;

		//第0个节点的变化
		if (move == right)		//向右移动
		{
			a[0].x = a[0].x + 10;
		}
		else if (move == up)	//向上移动
		{
			a[0].y = a[0].y - 10;
		}
		else if (move == left)	//向左移动
		{
			a[0].x = a[0].x - 10;
		}
		else if (move == down)	//向下移动
		{
			a[0].y = a[0].y + 10;
		}

		//除第0、1个节点之外其它所有节点的变化
		for (int i = 1; i < snakeLength - 1; i++)
		{
			a[snakeLength - i].x = a[snakeLength - 1 - i ].x;
			a[snakeLength - i].y = a[snakeLength - 1 - i ].y;
		}

		//第1个节点的变化
		a[1].x = b.x;
		a[1].y = b.y;
		

		CBrush head(RGB(255, 0, 0));  //将蛇的头节点设置成红色
		hDC.SelectObject(head);
		rect = new CRect(a[0].x, a[0].y, a[0].x+10, a[0].y+10); //头节点的边框
		hDC.Rectangle(rect);
		for(i = 1; i < snakeLength; i++)
		{
			CBrush body(RGB(255, 255, 0)); //将蛇的身体节点设置成黄色
			hDC.SelectObject(body);
			rect = new CRect(a[i].x, a[i].y, a[i].x+10, a[i].y+10); //身体各节点的边框
			hDC.Rectangle(rect);
		}

		if(a[0].x == xfood && a[0].y == yfood) //蛇吃了食物
		{
			snakeLength++; //蛇的长度加1
			foodOrNot = 1; //产生新食物
			//蛇新增加的尾节点与原先的尾节点（现在的倒数第二个节点）的位置重合
			//再移动一下才能看到蛇的节点加1
			a[snakeLength-1].x = a[snakeLength-2].x;
			a[snakeLength-1].y = a[snakeLength-2].y;
		}

		if(foodOrNot == 1)
		{
			int x1 = int(Random(10,50));  // 产生的随机值在11~51之间
			int y1 = int(Random(10,50));
			xfood = x1*10;
			yfood = y1*10;
			for(int i=0; i<snakeLength; i++)
			{
				if(xfood==a[i].x && yfood==a[i].y)
				{
					//如果食物的位置恰好在蛇的某个节点的位置，重新设置食物的位置
					int x2 = int(Random(10,50));
					int y2 = int(Random(10,50));
					xfood = x2*10;
					yfood = y2*10;
				}
			}
			foodOrNot = 0;
		}
		CBrush food(RGB(0,255,0)); //食物的颜色设置为绿色
		hDC.SelectObject(food);
		hDC.Rectangle(xfood, yfood, xfood+10, yfood+10);  //设置食物的边框
	}

	pDC->BitBlt(0, 0, 1000, 1000, &hDC, 0, 0, SRCCOPY);
	hBitmap.DeleteObject();
	hDC.DeleteDC();
	OnDraw(pDC);

	SetTimer(1, difficulty*30, NULL); //将游戏难度与移动时间相关

	CView::OnTimer(nIDEvent);
}

void CSnakeView::OnStart() 
{
	// TODO: Add your command handler code here
	gameStart = 1;
	Initialize();
    OnTimer(1);
	
}

void CSnakeView::OnDifficultyEasy() 
{
	// TODO: Add your command handler code here
	difficulty = 10;
}

void CSnakeView::OnDifficultyHard() 
{
	// TODO: Add your command handler code here
	difficulty = 3;
}

void CSnakeView::OnDifficultyHarder() 
{
	// TODO: Add your command handler code here
	difficulty = 2;
}

void CSnakeView::OnDifficultyNormal() 
{
	// TODO: Add your command handler code here
	difficulty = 6;
}

int CSnakeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetTimer(1, 10, NULL);
	srand(unsigned(time(0)));

	return 0;
}

void CSnakeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	lastMove = move;
	if(nChar==37 && lastMove!=right) //按下向左移动键且之前的移动方向不是向右
	{
		move = left;
	}
	else if(nChar==38 && lastMove!=down) //按下向上移动键且之前的移动方向不是向下
	{
		move = up;
	}
	else if(nChar==39 && lastMove!=left) //按下向右移动键且之前的移动方向不是向左
	{
		move = right;
	}
	else if(nChar==40 && lastMove!=up) //按下向下移动键且之前的移动方向不是向上
	{
		move = down;
	}
	OnTimer(1); //连续按可以加速
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

double CSnakeView::Random(double start, double end) //产生随机数，且其值在start~end之间
{
	return start+(end-start)*rand()/(RAND_MAX+1.0);
}

void CSnakeView::AliveOrDie()
{
	for(int i=1; i<snakeLength; i++)
	{
		//蛇的头节点碰到身体某节点
		if(a[0].x==a[i].x && a[0].y==a[i].y)
		{
			gameStart=0;
		}
		//蛇的头节点碰到边界
		else if(a[0].x<100 || a[0].x>500 || a[0].y<100 || a[0].y>500)
		{
			gameStart=0;
		}		
	}
}

void CSnakeView::Initialize()
{
	//游戏刚开始时的状态
	move = right;
	lastMove = right;
	snakeLength = 4;
	foodOrNot = 1;
	//蛇的出生位置
	a[0].x = 180;
	a[0].y = 170;
	a[1].x = 170;
	a[1].y = 170;
	a[2].x = 160;
	a[2].y = 170;
	a[3].x = 150;
	a[3].y = 170;	
}

void CSnakeView::OnPause() 
{
	// TODO: Add your command handler code here
	if(pauseOrContinue == 1)
	{
		// 暂停游戏
		pauseOrContinue = 0;
		KillTimer(1);
	}
	else if(pauseOrContinue == 0)
	{
		// 继续游戏
		pauseOrContinue = 1;
		OnTimer(1);
	}
}
