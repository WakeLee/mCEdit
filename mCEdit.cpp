#include "stdafx.h"
#include "mCEdit.h"

IMPLEMENT_DYNAMIC(mCEdit, mCWnd)

mCEdit::mCEdit()
{
}
mCEdit::~mCEdit()
{
	if(m_edit.m_hWnd != NULL) m_edit.DestroyWindow();
	if(m_font.m_hObject != NULL) m_font.DeleteObject();
}

BEGIN_MESSAGE_MAP(mCEdit, mCWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void mCEdit::PreSubclassWindow()
{
	ModifyStyle(0, SS_NOTIFY); // œÏ”¶ Û±Í

	mCWnd::PreSubclassWindow();
}

void mCEdit::OnPaint()
{
	CPaintDC dc(this);

	DrawBack();

	ShowMemoryDC(&dc);
}

void mCEdit::AddWindow(CWnd *pParent, UINT id, CRect &crect, Json::Value jUI)
{
	mCWnd::AddWindow(pParent, id, crect, jUI);

	crect.OffsetRect(-crect.left, -crect.top);
	crect.DeflateRect(
		jUI["back"]["border"]["left"]["size"].asInt(),
		jUI["back"]["border"]["top"]["size"].asInt(),
		jUI["back"]["border"]["right"]["size"].asInt(),
		jUI["back"]["border"]["bottom"]["size"].asInt()
		);
	crect.DeflateRect(
		jUI["back"]["padding"]["left"].asInt(),
		jUI["back"]["padding"]["top"].asInt(),
		jUI["back"]["padding"]["right"].asInt(),
		jUI["back"]["padding"]["bottom"].asInt()
		);

	m_edit.Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, crect, this, id + 5000);

	m_font.CreateFont(
		jUI["fore"]["FontSize"].asInt() + 10,
		0,
		0,
		0,
		jUI["fore"]["bold"].asBool() ? FW_BOLD : FW_NORMAL,
		FALSE,
		jUI["fore"]["underline"].asBool() ? TRUE : FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		L"Arial");
	m_edit.SetFont(&m_font);
}

CStringW mCEdit::GetText()
{
	CStringW sText;
	m_edit.GetWindowText(sText);

	return sText;
}

