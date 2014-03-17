//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MyAdo.cpp: implementation of the CConnection and CRecordset class.                                        +                                                                                                     +
//                                                                                                 +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "MyAdo.h"

#define ADO_HRESULT2WCODE(hr) (0x0000ffff&hr)
#define adErrIdleTimeout 0x4005
////////////////////////////////////////////////////////////////////////////////
// Connection method
///////////////////////////////////////////////////////////////////////////////
CConnection::CConnection()
{
	m_pConn.CreateInstance("ADODB.Connection");
}

CConnection::~CConnection()
{
	Close();
}

//
bool CConnection::Init(LPCTSTR lpConnectString, LPCTSTR lpUserName, LPCTSTR lpPasswd)
{
	m_sConnectString = lpConnectString;
	m_sUserName = lpUserName;
	m_sPasswd = lpPasswd;
	return true;
}

void CConnection::Open()
{
	m_pConn->Open((_bstr_t)m_sConnectString, (_bstr_t)m_sUserName, (_bstr_t)m_sPasswd, adCmdUnspecified);
}


//Close
void CConnection::Close()
{
	if(m_pConn->State & adStateOpen)
	{
		m_pConn->Close();
	}
}

//BeginTrans
void CConnection::BeginTrans()
{
	m_pConn->BeginTrans();
}


//CommitTrans
void CConnection::Commit()
{
	m_pConn->CommitTrans();
}


//RollbackTrans
void CConnection::Rollback()
{
	m_pConn->RollbackTrans();
}

void CConnection::ExecUpdate(LPCTSTR lpSql)
{
	VARIANT varAffect;
	varAffect.vt = VT_INT;
	try
	{
		m_pConn->Execute(lpSql, &varAffect, adCmdText);
	}
	catch(const _com_error &e)
	{
		if(NeedReopen(e))
		{
			// �������ӣ���ִ��
			Close();
			Open();
			m_pConn->Execute(lpSql, &varAffect, adCmdText);
		}
		else
		{
			throw e; // �׳���������
		}
	}
}

RecordsetPtr CConnection::ExecQuery(LPCTSTR lpSql)
{
	VARIANT varAffect;
	varAffect.vt = VT_INT;
	_RecordsetPtr rsPtr;

	try
	{
		rsPtr = m_pConn->Execute(lpSql, &varAffect, adCmdText);
	}
	catch(const _com_error &e)
	{
		if(NeedReopen(e))
		{
			// �������ӣ���ִ��
			Close();
			Open();
			rsPtr = m_pConn->Execute(lpSql, &varAffect, adCmdText);
		}
		else
		{
			throw e; // �׳���������
		}
	}

	return RecordsetPtr(new CRecordset(rsPtr));
}

bool CConnection::NeedReopen(const _com_error &e)
{
	WORD wCode = ADO_HRESULT2WCODE(e.Error());
	
	if(adErrObjectClosed == wCode  //����δ��
		|| adErrIdleTimeout == wCode)  // ����������ʱ�䣬���ȶϿ�
	{
		return true;
	}
	else
	{
		return false;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Recordset method
///////////////////////////////////////////////////////////////////////////////

CRecordset::CRecordset(_RecordsetPtr rsPtr)
	: m_rsPtr (rsPtr)
{
}

CRecordset::~CRecordset()
{
}

void CRecordset::MoveNext()
{
	m_rsPtr->MoveNext();
}

bool CRecordset::IsEOF()
{
	return (bool)m_rsPtr->adoEOF;
}

int CRecordset::GetInt(LPCTSTR lpFieldName)
{
	return (int)m_rsPtr->GetCollect(lpFieldName);
}

CString CRecordset::GetString(LPCTSTR lpFieldName)
{
	return (CString)m_rsPtr->GetCollect(lpFieldName);
}
