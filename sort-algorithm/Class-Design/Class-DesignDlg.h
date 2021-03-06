// Class-DesignDlg.h : header file
//

#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int ARRAY_SIZE = 20;


// CClassDesignDlg dialog
class CClassDesignDlg : public CDialogEx {
	// Construction
public:
	CClassDesignDlg(CWnd* pParent = nullptr); // standard constructor
	//--------------------pen and point-------------------------//
	CPen m_pen[4];
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLASSDESIGN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void DrawRect(CDC* pDC);
private:
	vector<int> array;
	int pivotValue = -1;
	int now = -1;
	void QuickSort(int start, int end);
	int Partition(int start, int end);
	void bubbleSort();
	void insertSort();
	void heapify(int n, int i);
	void heapSort();
	void selectSort();
	void mergeSort(int l, int r);
	void merge(int m, int l, int r);
	void shellSort();
	void countSort(int n, int exp);
	void radixSort();
	int whilh_sort = 0;//which sort selected.
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnCbnSelchangeCombo2();
private:
	// IDC_COMBO2
	CComboBox m_combo;
	int time_span = 300;//sleep time
};
