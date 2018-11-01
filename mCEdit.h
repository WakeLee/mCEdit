#pragma once

class mCEdit : public mCWnd
{
	DECLARE_DYNAMIC(mCEdit)

public:
	mCEdit();
	virtual ~mCEdit();

protected:
	DECLARE_MESSAGE_MAP()

	virtual void PreSubclassWindow();  
	afx_msg void OnPaint();

	CEdit m_edit;
	CFont m_font;

public:
	void AddWindow(CWnd *pParent, UINT id, CRect &crect, Json::Value jUI);

	CStringW GetText();
};


