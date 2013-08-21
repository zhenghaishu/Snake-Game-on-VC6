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
	difficulty = 10; //10Ϊ�򵥵ĵȼ���6Ϊһ��ĵȼ���3Ϊ�ѵĵȼ���2Ϊ���ѵĵȼ�
	snakeLength = 4; //�ߵĳ�ʼ����Ϊ4���ڵ�
	pauseOrContinue = 1; //��Ϸ��ʼ��Ϊ����״̬
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
	score.Format("������ %d", snakeLength-4); //��Ϸ����Ϊ�ߵĽڵ���-�߳���ʱ�Ľڵ���
	AliveOrDie();
	
	//�����豸������
	CDC *pDC, hDC;
	pDC = GetDC();	
	hDC.CreateCompatibleDC(NULL);
	CBitmap hBitmap, *pOldBitmap ;
	hBitmap.CreateCompatibleBitmap(pDC, 1000, 1000);
	pOldBitmap = hDC.SelectObject(&hBitmap);

	hDC.FillSolidRect(0, 0, 1000, 1000, RGB(255, 255, 255)); //�趨��ɫ����Χ
	hDC.TextOut(550, 200, score);  //������(500,200)�������Ϸ����
	hDC.Rectangle(CRect(90, 90, 520, 520)); //�趨����ο�
	hDC.Rectangle(CRect(100, 100, 510, 510)); //�趨�ھ��ο�

	if(gameStart == 1)  //��Ϸ��������״̬
	{
		b.x = a[0].x;
		b.y = a[0].y;

		//��0���ڵ�ı仯
		if (move == right)		//�����ƶ�
		{
			a[0].x = a[0].x + 10;
		}
		else if (move == up)	//�����ƶ�
		{
			a[0].y = a[0].y - 10;
		}
		else if (move == left)	//�����ƶ�
		{
			a[0].x = a[0].x - 10;
		}
		else if (move == down)	//�����ƶ�
		{
			a[0].y = a[0].y + 10;
		}

		//����0��1���ڵ�֮���������нڵ�ı仯
		for (int i = 1; i < snakeLength - 1; i++)
		{
			a[snakeLength - i].x = a[snakeLength - 1 - i ].x;
			a[snakeLength - i].y = a[snakeLength - 1 - i ].y;
		}

		//��1���ڵ�ı仯
		a[1].x = b.x;
		a[1].y = b.y;
		

		CBrush head(RGB(255, 0, 0));  //���ߵ�ͷ�ڵ����óɺ�ɫ
		hDC.SelectObject(head);
		rect = new CRect(a[0].x, a[0].y, a[0].x+10, a[0].y+10); //ͷ�ڵ�ı߿�
		hDC.Rectangle(rect);
		for(i = 1; i < snakeLength; i++)
		{
			CBrush body(RGB(255, 255, 0)); //���ߵ�����ڵ����óɻ�ɫ
			hDC.SelectObject(body);
			rect = new CRect(a[i].x, a[i].y, a[i].x+10, a[i].y+10); //������ڵ�ı߿�
			hDC.Rectangle(rect);
		}

		if(a[0].x == xfood && a[0].y == yfood) //�߳���ʳ��
		{
			snakeLength++; //�ߵĳ��ȼ�1
			foodOrNot = 1; //������ʳ��
			//�������ӵ�β�ڵ���ԭ�ȵ�β�ڵ㣨���ڵĵ����ڶ����ڵ㣩��λ���غ�
			//���ƶ�һ�²��ܿ����ߵĽڵ��1
			a[snakeLength-1].x = a[snakeLength-2].x;
			a[snakeLength-1].y = a[snakeLength-2].y;
		}

		if(foodOrNot == 1)
		{
			int x1 = int(Random(10,50));  // ���������ֵ��11~51֮��
			int y1 = int(Random(10,50));
			xfood = x1*10;
			yfood = y1*10;
			for(int i=0; i<snakeLength; i++)
			{
				if(xfood==a[i].x && yfood==a[i].y)
				{
					//���ʳ���λ��ǡ�����ߵ�ĳ���ڵ��λ�ã���������ʳ���λ��
					int x2 = int(Random(10,50));
					int y2 = int(Random(10,50));
					xfood = x2*10;
					yfood = y2*10;
				}
			}
			foodOrNot = 0;
		}
		CBrush food(RGB(0,255,0)); //ʳ�����ɫ����Ϊ��ɫ
		hDC.SelectObject(food);
		hDC.Rectangle(xfood, yfood, xfood+10, yfood+10);  //����ʳ��ı߿�
	}

	pDC->BitBlt(0, 0, 1000, 1000, &hDC, 0, 0, SRCCOPY);
	hBitmap.DeleteObject();
	hDC.DeleteDC();
	OnDraw(pDC);

	SetTimer(1, difficulty*30, NULL); //����Ϸ�Ѷ����ƶ�ʱ�����

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
	if(nChar==37 && lastMove!=right) //���������ƶ�����֮ǰ���ƶ�����������
	{
		move = left;
	}
	else if(nChar==38 && lastMove!=down) //���������ƶ�����֮ǰ���ƶ�����������
	{
		move = up;
	}
	else if(nChar==39 && lastMove!=left) //���������ƶ�����֮ǰ���ƶ�����������
	{
		move = right;
	}
	else if(nChar==40 && lastMove!=up) //���������ƶ�����֮ǰ���ƶ�����������
	{
		move = down;
	}
	OnTimer(1); //���������Լ���
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

double CSnakeView::Random(double start, double end) //���������������ֵ��start~end֮��
{
	return start+(end-start)*rand()/(RAND_MAX+1.0);
}

void CSnakeView::AliveOrDie()
{
	for(int i=1; i<snakeLength; i++)
	{
		//�ߵ�ͷ�ڵ���������ĳ�ڵ�
		if(a[0].x==a[i].x && a[0].y==a[i].y)
		{
			gameStart=0;
		}
		//�ߵ�ͷ�ڵ������߽�
		else if(a[0].x<100 || a[0].x>500 || a[0].y<100 || a[0].y>500)
		{
			gameStart=0;
		}		
	}
}

void CSnakeView::Initialize()
{
	//��Ϸ�տ�ʼʱ��״̬
	move = right;
	lastMove = right;
	snakeLength = 4;
	foodOrNot = 1;
	//�ߵĳ���λ��
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
		// ��ͣ��Ϸ
		pauseOrContinue = 0;
		KillTimer(1);
	}
	else if(pauseOrContinue == 0)
	{
		// ������Ϸ
		pauseOrContinue = 1;
		OnTimer(1);
	}
}