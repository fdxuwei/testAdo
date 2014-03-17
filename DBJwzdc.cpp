#include "DBJwzdc.h"


CDBJwzdc::CDBJwzdc(void)
{
}


CDBJwzdc::~CDBJwzdc(void)
{
}

bool CDBJwzdc::Init(const std::string& sDBName, const std::string& sUserName, const std::string& sPasswd)
{
	m_sDBName = sDBName;
	m_sUserName = sUserName;
	m_sPasswd = sPasswd;
	CString csConnectString;
	csConnectString.Format(_T("Provider=MSDAORA.1;Data Source=%s;User Id=%s;"
		"Password=%s;"), sDBName.c_str(), sUserName.c_str(), sPasswd.c_str());
	return m_Conn.Init(csConnectString, sUserName.c_str(), sPasswd.c_str());
}

void CDBJwzdc::ExecUpdate(const std::string& sSql)
{
	m_Conn.ExecUpdate(sSql.c_str());
}

RecordsetPtr CDBJwzdc::ExecQuery(const std::string& sSql)
{
	return m_Conn.ExecQuery(sSql.c_str());
}

void CDBJwzdc::Open()
{
	m_Conn.Open();
}

void CDBJwzdc::Close()
{
	m_Conn.Close();
}

//BeginTrans
void CDBJwzdc::BeginTrans()
{
	m_Conn.BeginTrans();
}


//CommitTrans
void CDBJwzdc::Commit()
{
	m_Conn.Commit();
}


//RollbackTrans
void CDBJwzdc::Rollback()
{
	m_Conn.Rollback();
}