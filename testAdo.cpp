// testAdo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DBJwzdc.h"
#include <string>
#include <time.h>

using namespace std;

void testQuery()
{
	CDBJwzdc db;
	try
	{
		int count = 0;
		db.Init(_T("192.168.5.62/test"), _T("system"), _T("orcl"));
		db.Open();
		RecordsetPtr rs = db.ExecQuery("select * from t_user_info");
		while(!rs->IsEOF())
		{
			string name = rs->GetString(_T("f_uname"));
			string pwd = rs->GetString(_T("f_password"));
			cout << count++ << ": " <<  name << " :" << pwd << endl;
			rs->MoveNext();
		}
		db.Close();
	}
	catch(_com_error &e)
	{
		cout << e.Description() << endl;
	}
	catch(...)
	{
		cout << "unknow exception" << endl;
	}
}

void testInsert()
{
	CDBJwzdc db;
	int imax = 100;
	time_t tStart = time(NULL);
	try
	{
		db.Init(_T("192.168.5.62/test"), _T("system"), _T("orcl"));
		db.Open();
		char sql[1024];
		for(int i = 0; i < imax; i++)
		{
			sprintf(sql, _T("insert into t_user_info(f_uname,f_password) values('name%d','pd%d')"), i, i+2);
			db.ExecUpdate(sql);
		}
		db.Close();
	}
	catch(_com_error &e)
	{
		cout << e.Description() << endl;
	}
	catch(...)
	{
		cout << "unknow exception" << endl;
	}
	cout << "insert " << imax << " costs " << time(NULL) - tStart << "s" << endl;
}


void testTrans()
{
	CDBJwzdc db;
	int imax = 100;
	time_t tStart = time(NULL);
	try
	{
		db.Init(_T("test"), _T("system"), _T("orcl"));
		db.Open();
		char sql[1024];
		db.BeginTrans();
		db.ExecUpdate( _T("insert into t_user_info(f_uname,f_password) values('tname1','hhaa')"));
		db.ExecUpdate( _T("insert into t_user_info(f_uname,f_password) values('tname2','hhaa')"));
		db.ExecUpdate( _T("insert into t_user_info(f_uname,f_password) values('tname3','hasfasffffhaa')")); // passwd too long! it will cause an exception
		db.ExecUpdate( _T("insert into t_user_info(f_uname,f_password) values('tname4','1233')"));
		db.Commit();
		db.Close();
	}
	catch(_com_error &e)
	{
		db.Rollback();
		cout << e.Description() << endl;
	}
	catch(...)
	{
		cout << "unknow exception" << endl;
	}
	cout << "ttans insert " << imax << " costs " << time(NULL) - tStart << "s" << endl;
}

void testInput()
{
	CDBJwzdc db;
	try
	{
		db.Init(_T("192.168.5.62/test"), _T("system"), _T("orcl"));
	//	db.Open();
		char sql[1024];
		string name, pwd;
		while(cin >> name >> pwd)
		{
			sprintf(sql, _T("insert into t_user_info(f_uname,f_password) values('%s','%s')"), name.c_str(), pwd.c_str());
			db.ExecUpdate(sql);
		}
		db.Close();	
	}
	catch(_com_error &e)
	{
		cout << e.Description() << endl;
	}
	catch(...)
	{
		cout << "unknow exception" << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(NULL);
	testInsert();
	testTrans();
	testQuery();
	testInput();
	CoUninitialize();
	return 0;
}

