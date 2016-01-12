#pragma once

#include <Windows.h>
#include "sql.h"
#include "sqlext.h"

class DatabaseManager
{
public:

	void Initialize(SQLHENV *henv, SQLHDBC *hdbc);
	void Connect(SQLHDBC hDbc, SQLWCHAR* connName, SQLWCHAR *username, SQLWCHAR *password);
	void Disconnect(SQLHDBC hDbc);
	bool SelectDB(SQLHSTMT hStmt);
	int ProcessStatement(SQLHENV henv, SQLHDBC hdbc, SQLWCHAR *sqlstr);
	DatabaseManager();
	~DatabaseManager(); 

private:
	int CheckError(SQLHENV henv, SQLHDBC hdbc, SQLHSTMT hstmt, SQLRETURN frc);
	void PrintError(SQLHENV henv, SQLHDBC hdbc, SQLHSTMT hstmt);
	void DisplayResults(SQLHSTMT hstmt,	SQLSMALLINT nresultcols);
};

