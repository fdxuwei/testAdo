//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MyAdo.h:                                                                                   +                                                                  +
// 接口定义用异常处理代替返回值，调用时注意处理异常                                                                             +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _MYADO_H_
#define _MYADO_H_

#include <boost/shared_ptr.hpp>
#include "stdafx.h"

// class CRecordset
class CRecordset  
{
public:
	// 
	CRecordset(_RecordsetPtr rsPtr);
	virtual ~CRecordset();

	//
	void MoveNext();
	bool IsEOF();
	//     
	int GetInt(LPCTSTR lpFieldName);
	CString GetString(LPCTSTR lpFieldName);

private:
	_RecordsetPtr m_rsPtr;

};

//
typedef boost::shared_ptr<CRecordset> RecordsetPtr;

// class CConnection
class CConnection  
{
public:
	CConnection();
	virtual ~CConnection();

	// 
	bool Init(LPCTSTR lpConnectString, LPCTSTR lpUserName, LPCTSTR lpPasswd);
	void Open();
    void Close();

	// sql
	void ExecUpdate(LPCTSTR lpSql);
	RecordsetPtr ExecQuery(LPCTSTR lpSql);
	
	// transaction
	void Rollback();
	void Commit();
	void BeginTrans();

private:
	_ConnectionPtr  m_pConn; 
	CString m_sConnectString;
	CString m_sUserName;
	CString m_sPasswd;

	bool NeedReopen(const _com_error &e); // 检测是否需要重新打开， 用于自动重连

};

#endif 