// Class-DesignDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Class-Design.h"
#include "Class-DesignDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include <string>
#include <algorithm>
#include <windows.h>// sleep()

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define RED   0
#define GREEN 1
#define BLUE  3

#define QUICK_SORT     0
#define BUBBLE_SORT    1
#define INSERT_SORT    2
#define HEAP_SORT      3
#define SELECTION_SORT 4
#define MERGE_SORT     5
#define SHELL_SORT     6
#define RADIX_SORT     7


// CClassDesignDlg dialog


CClassDesignDlg::CClassDesignDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLASSDESIGN_DIALOG, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClassDesignDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_combo);
}

BEGIN_MESSAGE_MAP(CClassDesignDlg, CDialogEx)
		ON_WM_PAINT()
		ON_WM_QUERYDRAGICON()
		ON_BN_CLICKED(IDC_BUTTON1, &CClassDesignDlg::OnBnClickedButton1)
		ON_BN_CLICKED(IDC_BUTTON2, &CClassDesignDlg::OnBnClickedButton2)
		ON_CBN_SELCHANGE(IDC_COMBO2, &CClassDesignDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CClassDesignDlg message handlers

BOOL CClassDesignDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	//--------------add elements to combo------------------------------------------//
	m_combo.AddString(L"快速排序");
	m_combo.AddString(L"冒泡排序");
	m_combo.AddString(L"插入排序");
	m_combo.AddString(L"堆排序");
	m_combo.AddString(L"选择排序");
	m_combo.AddString(L"归并排序");
	m_combo.AddString(L"希尔排序");
	m_combo.AddString(L"基数排序");
	m_combo.SetCurSel(0);
	//--------------limit the position and size of the Dialog----------------------//
	MoveWindow(200, 200, 1280, 720, FALSE);
	//--------------modify the title of the Dialog--------------------------------//
	SetWindowText(L"快速排序可视化");
	//--------------modify the tittle of the button------------------------------//
	SetDlgItemText(IDC_BUTTON1, L"生成随机数");
	SetDlgItemText(IDC_BUTTON2, L"开始排序");
	//--------------line settings----------------------------------------------//
	m_pen[0].CreatePen(PS_SOLID, 10, RGB(128, 0, 0)); //red real line,10 pixel width
	m_pen[1].CreatePen(PS_SOLID, 10, RGB(0, 128, 0)); //green real line
	m_pen[2].CreatePen(PS_SOLID, 600, RGB(255,255,255)); //background color real line
	m_pen[3].CreatePen(PS_SOLID, 10, RGB(0, 0, 128)); //blue real line
	//-----------------------initialize the array-------------------------------//
	srand((unsigned)time(NULL));
	for (int i = 0; i < 20; i++) {
		array.push_back(rand() % 200 + 1);
	}
	//-----------------------Set Buttons' picture--------------------------------//
	HBITMAP hBitmap;
	hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));
	((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap);
	hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2));
	((CButton *)GetDlgItem(IDC_BUTTON2))->SetBitmap(hBitmap);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	// TODO: Add extra initialization here

	return TRUE; // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClassDesignDlg::OnPaint() {
	//-----------draw rect----------------------//
	CPaintDC dc(this); // device context for painting
	CBrush brush(RGB(255, 255, 255));//brush
	dc.SelectObject(&brush);//make brush to DC
	DrawRect(&dc);

	if (IsIconic()) {
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClassDesignDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

//-----------generate random array-------------------//
void CClassDesignDlg::OnBnClickedButton1() {
	srand((unsigned)time(NULL));
	for (int i = 0; i < 20; i++) {
		array[i] = rand() % 200 + 1;
	}
	this->Invalidate();// current window is invalid, rePaint it.
}

void CClassDesignDlg::DrawRect(CDC* pDC) {
	//-----------------cover the most area.----------------------------------//
	CDC* pDc2 = GetDC();
	CRect rect2(0, 400, 1280, 720);
	pDc2->SelectObject(&m_pen[2]);
	pDc2->Rectangle(&rect2);//draw rect2
	//-----------Upper left angle coordinate, right lower corner coordinate---//
	CRect rect(100, 100, 110, 600);
	CPen* oldPen = pDC->SelectObject(&m_pen[GREEN]);
	//-----------number text settings-----------------------------------------//
	CDC* pDc = GetDC();
	CFont font;
	VERIFY(font.CreatePointFont(20, L"黑体", pDC));
	pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(60,63,65));
	pDC->SetBkColor(RGB(255, 255, 255));
	pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);

	for (int i = 0; i < ARRAY_SIZE; i++) {
		rect.OffsetRect(50, 0);//move to right 80 pixel
		rect.SetRect(rect.TopLeft().x, 600 - array[i] * 2, rect.BottomRight().x, rect.BottomRight().y);
		pDc->SelectObject(&m_pen[(i == pivotValue || i == now) ? RED : GREEN]);
		pDc->Rectangle(&rect);//draw rect
		wstring s = to_wstring(array[i]);
		//rect.TopLeft().x - len to make the number at the center.
		int len = 0;
		if (s.size() == 3)len = 10;
		else if (s.size() == 2)len = 5;
		else len = 0;
		pDc->DrawText(
			s.c_str(), CRect(rect.TopLeft().x - len, rect.TopLeft().y - 50, rect.TopLeft().x + 50, rect.TopLeft().y),
			DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	}
	pDC->SelectObject(oldPen);
}

//--------------quick sort main function---------------//
void CClassDesignDlg::QuickSort(int start, int end) {
	if (start < end) {
		int p = Partition(start, end);////p is partitioning index,array[p] is now at correct place
		QuickSort(start, p - 1);//before index p.
		QuickSort(p + 1, end);//after index p.
	}
}

/*This function takes last element as pivot, places
*the pivot element at its correct position in sorted
*array, and places all smaller(smaller than pivot)
*to left of pivot and all greater elements to right
*of pivot.
*/
int CClassDesignDlg::Partition(int start, int end) {
	int p = array[end];
	int i = start - 1;//index of smaller element.
	CPaintDC dc(this); // device context for painting
	CBrush brush(RGB(255, 255, 255));//brush
	dc.SelectObject(&brush);//make brush to DC
	for (int j = start; j <= end - 1; j++) {
		if (i != j) {
			pivotValue = i;
			now = j;
			DrawRect(&dc);
			Sleep(time_span);
		}
		if (array[j] <= p) {
			//if current element is smaller than or equal to pivot.
			i++;
			swap(array[i], array[j]);
			if (i != j) {
				pivotValue = i;
				now = j;
				DrawRect(&dc);
				Sleep(time_span);
			}
		}
	}
	swap(array[i + 1], array[end]);
	return i + 1;
}

//-------------bubble sort---------------------------//
void CClassDesignDlg::bubbleSort() {
	for (int i = 0; i < ARRAY_SIZE - 1; i++) {
		for (int j = 0; j < ARRAY_SIZE - i - 1; j++) {
			pivotValue = j;
			now = j + 1;
			CPaintDC dc(this); // device context for painting
			CBrush brush(RGB(255, 255, 255));//brush
			dc.SelectObject(&brush);//make brush to DC
			DrawRect(&dc);
			Sleep(time_span);
			if (array[j] > array[j + 1]) {
				swap(array[j], array[j + 1]);
				DrawRect(&dc);
				Sleep(time_span);
			}
		}

	}
}

//-----------insert sort----------------//
void CClassDesignDlg::insertSort() {
	CPaintDC dc(this); // device context for painting
	CBrush brush(RGB(255, 255, 255));//brush
	dc.SelectObject(&brush);//make brush to DC

	for (int i = 1; i < ARRAY_SIZE; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (array[j] > array[j + 1]) {
				swap(array[j], array[j + 1]);
			}
			else {
				break;
			}
			pivotValue = j;
			DrawRect(&dc);
			Sleep(time_span);
		}
	}
}

/*
 * To heapify a subtree rooted with node i which is
 * an index in array[]. n is size of heap.
 */
void CClassDesignDlg::heapify(int n, int i) {
	CPaintDC dc(this); // device context for painting
	CBrush brush(RGB(255, 255, 255));//brush
	dc.SelectObject(&brush);//make brush to DC
	int largest = i;// Initialize largest as root
	int l = 2 * i + 1;// left = 2*i + 1
	int r = 2 * i + 2;// right = 2*i + 2
	// If left child is larger than root
	if (l < n && array[l] > array[largest])
		largest = l;
	// If right child is larger than largest so far
	if (r < n && array[r] > array[largest])
		largest = r;
	// If largest is not root
	if (largest != i) {
		pivotValue = i;
		now = largest;
		DrawRect(&dc);
		Sleep(time_span);
		swap(array[i], array[largest]);
		DrawRect(&dc);
		Sleep(time_span);
		// Recursively heapify the affected sub-tree
		heapify(n, largest);
	}
}

//----------heap sort-------------------//
//main function to do heap sort
void CClassDesignDlg::heapSort() {
	CPaintDC dc(this); // device context for painting
	CBrush brush(RGB(255, 255, 255));//brush
	dc.SelectObject(&brush);//make brush to DC
	// Build heap (rearrange array)
	for (int i = ARRAY_SIZE / 2 - 1; i >= 0; i--) {
		heapify(ARRAY_SIZE, i);
	}
	//One by one extract an element from heap
	for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
		//Move current root to end
		pivotValue = i;
		now = 0;
		DrawRect(&dc);
		Sleep(time_span);
		swap(array[0], array[i]);
		DrawRect(&dc);
		Sleep(time_span);
		//call max heapify on the reduced heap.
		heapify(i, 0);
	}
}

//-----------select sort-----------------//
void CClassDesignDlg::selectSort() {
	CPaintDC dc(this); // device context for painting
	CBrush brush(RGB(255, 255, 255));//brush
	dc.SelectObject(&brush);//make brush to DC

	for (int i = 0; i < ARRAY_SIZE - 1; i++) {
		int min_index = i;
		for (int j = i + 1; j < ARRAY_SIZE; j++) {
			if (array[j] < array[min_index]) {
				min_index = j;
			}
			pivotValue = min_index;
			now = j;
			DrawRect(&dc);
			Sleep(time_span);
		}
		pivotValue = i;
		now = min_index;
		DrawRect(&dc);
		Sleep(time_span);
		swap(array[i], array[min_index]);
		DrawRect(&dc);
		Sleep(time_span);
	}
}

//-----------merge sort-----------------//
//l is for left index and r is right index of the sub - array of arr to be sorted
void CClassDesignDlg::mergeSort(int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;//Same as (l+r)/2, but avoids overflow for large l and h.
		// Sort first and second halves
		mergeSort(l, m);
		mergeSort(m + 1, r);

		merge(l, m, r);
	}
}

void CClassDesignDlg::merge(int l, int m, int r) {
	CPaintDC dc(this); // device context for painting
	CBrush brush(RGB(255, 255, 255));//brush
	dc.SelectObject(&brush);//make brush to DC

	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	//create temp arrays
	vector<int> L(n1);
	vector<int> R(n2);
	//Copy data to temp arrays L[] and R[]
	for (i = 0; i < n1; i++)L[i] = array[l + i];
	for (j = 0; j < n2; j++)R[j] = array[m + 1 + j];
	//Merge the temp arrays back into arr[l..r]
	i = j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			array[k] = L[i];
			pivotValue = i;
			now = k;
			DrawRect(&dc);
			Sleep(time_span);
			i++;
		}
		else {
			array[k] = R[j];
			pivotValue = j;
			now = k;
			DrawRect(&dc);
			Sleep(time_span);
			j++;
		}
		k++;
	}
	//Copy the remaining elements of L[], if there are any.
	while (i < n1) {
		array[k] = L[i];
		pivotValue = i;
		now = k;
		DrawRect(&dc);
		Sleep(time_span);
		i++;
		k++;
	}
	//Copy the remaining elements of R[], if there are any.
	while (j < n2) {
		array[k] = R[j];
		pivotValue = j;
		now = k;
		DrawRect(&dc);
		Sleep(time_span);
		j++;
		k++;
	}
}

//------------shell sort-------------------//
void CClassDesignDlg::shellSort() {
	CPaintDC dc(this); // device context for painting
	CBrush brush(RGB(255, 255, 255));//brush
	dc.SelectObject(&brush);//make brush to DC

	// Start with a big gap, then reduce the gap
	for (int gap = ARRAY_SIZE / 2; gap > 0; gap /= 2) {
		// Do a gapped insertion sort for this gap size.
		// The first gap elements a[0..gap-1] are already in gapped order
		// keep adding one more element until the entire array is
		// gap sorted 
		for (int i = gap; i < ARRAY_SIZE; i += 1) {
			// add a[i] to the elements that have been gap sorted
			// save a[i] in temp and make a hole at position i
			int temp = array[i];

			// shift earlier gap-sorted elements up until the correct 
			// location for a[i] is found
			int j;
			for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
				pivotValue = j;
				now = j - gap;
				DrawRect(&dc);
				Sleep(time_span);
				array[j] = array[j - gap];
			}

			//  put temp (the original a[i]) in its correct location
			pivotValue = j;
			now = temp;
			DrawRect(&dc);
			Sleep(time_span);
			array[j] = temp;
		}
	}
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void CClassDesignDlg::countSort(int n, int exp) {
	CPaintDC dc(this); // device context for painting
	CBrush brush(RGB(255, 255, 255));//brush
	dc.SelectObject(&brush);//make brush to DC

	vector<int> output(n); // output array
	int i, count[10] = {0};

	// Store count of occurrences in count[]
	for (i = 0; i < n; i++)
		count[(array[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual
	//  position of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = n - 1; i >= 0; i--) {
		vector<int> temp = array;
		output[count[(array[i] / exp) % 10] - 1] = array[i];
		int t = count[(array[i] / exp) % 10] - 1;
		array[t] = array[i];
		pivotValue = t;
		now = i;
		DrawRect(&dc);
		Sleep(time_span);
		array = temp;
		count[(array[i] / exp) % 10]--;
	}

	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < n; i++) {
		array[i] = output[i];
		pivotValue = i;
		now = i;
		DrawRect(&dc);
		Sleep(time_span);
	}

}

//---------------radix sort-------------------//
void CClassDesignDlg::radixSort() {
	// Find the maximum number to know number of digits
	int m = *max_element(array.begin(), array.end());

	// Do counting sort for every digit. Note that instead
	// of passing digit number, exp is passed. exp is 10^i
	// where i is current digit number
	for (int exp = 1; m / exp > 0; exp *= 10) {
		countSort(ARRAY_SIZE, exp);
	}
}

//-----------start sorting---------------//
void CClassDesignDlg::OnBnClickedButton2() {
	int index = m_combo.GetCurSel();
	if (index == QUICK_SORT) {
		QuickSort(0, ARRAY_SIZE - 1);
	}
	else if (index == BUBBLE_SORT) {
		bubbleSort();
	}
	else if (index == INSERT_SORT) {
		insertSort();
	}
	else if (index == HEAP_SORT) {
		heapSort();
	}
	else if (index == SELECTION_SORT) {
		selectSort();
	}
	else if (index == MERGE_SORT) {
		mergeSort(0, ARRAY_SIZE - 1);
	}
	else if (index == SHELL_SORT) {
		shellSort();
	}
	else if (index == RADIX_SORT) {
		radixSort();
	}
	Sleep(1000);
	pivotValue = -1;
	now = -1;
	this->Invalidate();
}

//-----------select which sort---------//
void CClassDesignDlg::OnCbnSelchangeCombo2() {
}
