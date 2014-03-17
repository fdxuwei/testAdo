#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include "MyAdo.h"

typedef boost::shared_ptr<CRecordset> RecordsetPtr;

class CDBJwzdc
{
public:
	CDBJwzdc(void);
	~CDBJwzdc(void);
	bool Init(const std::string& sDBName, const std::string& sUserName, const std::string& sPasswd);
	void Open();
	void Close();
	void ExecUpdate(const std::string& sSql);
	RecordsetPtr ExecQuery(const std::string& sSql);
	// transaction
	void Rollback();
	void Commit();
	void BeginTrans();

private:
	std::string m_sDBName;
	std::string m_sUserName;
	std::string m_sPasswd;

	CConnection m_Conn;
};

