#include "stdafx.h"
#include <iostream>
#include <stdio.h>

#include <winsock2.h>

#include <errno.h>
#include <string>
#include <clocale>
#include "DatabaseManager.h"

using namespace std;

#define MAX_STMT_LEN 255
#define  MAXCOLS   100

#define  max(a,b) (a > b ? a : b)

void DatabaseManager::Initialize(SQLHENV *henv,
	SQLHDBC *hdbc)
{
	SQLRETURN   ret;

	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, henv);
	ret = SQLSetEnvAttr(*henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	ret = SQLAllocHandle(SQL_HANDLE_DBC, *henv, hdbc);
}

void DatabaseManager::Connect(SQLHDBC hDbc,SQLWCHAR *username, SQLWCHAR *password)
{
	int ret;

	ret = SQLConnect(hDbc, (SQLWCHAR*)L"local", SQL_NTS, username, SQL_NTS, password, SQL_NTS);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("SQL Connect Ok \n");
	else
		printf("SQL Connect Fail \n");
}

void DatabaseManager::Disconnect(SQLHDBC hDbc)
{
	SQLDisconnect(hDbc);
}

bool DatabaseManager::SelectDB(SQLHSTMT hStmt)
{

	int ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"USE company", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		cout << "USE Success\n" << endl;
		return true;
	}
	else{
		cout << "USE Fail\n" << endl;
		return false;
	}
}

int DatabaseManager::ProcessStatement(SQLHENV henv, SQLHDBC hdbc, SQLWCHAR *sqlstr)
{
	SQLHSTMT hstmt;
	SQLSMALLINT nresultcols;
	SQLRETURN rt;

	SQLLEN rowcount;

	SQLAllocStmt(hdbc, &hstmt);       /* allocate a statement handle */

	/* execute the SQL statement in "sqlstr"    */

	rt = SQLExecDirect(hstmt, sqlstr, SQL_NTS);
	if (rt != SQL_SUCCESS){
		if (rt == SQL_NO_DATA_FOUND) {
			printf("\nStatement executed without error, however,\n");
			printf("no data was found or modified\n");
			return (SQL_SUCCESS);
		}
		else
			CheckError(henv, hdbc, hstmt, rt);
	}

	SQLRowCount(hstmt, (SQLLEN*)&rowcount);
	rt = SQLNumResultCols(hstmt, &nresultcols);
	if (rt != SQL_SUCCESS)
		CheckError(henv, hdbc, hstmt, rt);

	/* determine statement type */
	if (nresultcols == 0) /* statement is not a select statement */
	{
		if (rowcount > 0) /* assume statement is UPDATE, INSERT, DELETE */
		{
			printf("Statement executed, %ld rows affected\n", rowcount);
		}
		else  /* assume statement is GRANT, REVOKE or a DLL statement */
		{
			printf("Statement completed successful\n");
		}
	}
	else /* display the result set */
	{
		DisplayResults(hstmt, nresultcols);
	} /* end determine statement type */

	SQLFreeStmt(hstmt, SQL_DROP);       /* free statement handle */

	return (0);
}

int DatabaseManager::CheckError(SQLHENV    henv,
	SQLHDBC        hdbc,
	SQLHSTMT   hstmt,
	SQLRETURN  frc)
{
	SQLRETURN   rc;

	PrintError(henv, hdbc, hstmt);

	switch (frc){
	case SQL_SUCCESS: break;
	case SQL_ERROR:
	case SQL_INVALID_HANDLE:
		printf("\n ** FATAL ERROR, Attempting to rollback transaction **\n");
		rc = SQLTransact(henv, hdbc, SQL_ROLLBACK);
		if (rc != SQL_SUCCESS)
			printf("Rollback Failed, Exiting application\n");
		else
			printf("Rollback Successful, Exiting application\n");
		terminate();
		exit(frc);
		break;
	case SQL_SUCCESS_WITH_INFO:
		printf("\n ** Warning Message, application continuing\n");
		break;
	case SQL_NO_DATA_FOUND:
		printf("\n ** No Data Found ** \n");
		break;
	default:
		printf("\n ** Invalid Return Code ** \n");
		printf(" ** Attempting to rollback transaction **\n");
		SQLTransact(henv, hdbc, SQL_ROLLBACK);
		terminate();
		exit(frc);
		break;
	}
	return (SQL_SUCCESS);

}

void DatabaseManager::DisplayResults(SQLHSTMT hstmt, SQLSMALLINT nresultcols)
{
	
	int ret;
	int iCount = 0;
	/* display result rows                                            */
	while ((ret = SQLFetch(hstmt)) != SQL_NO_DATA_FOUND)
	{
		SQLLEN iDataLen;
		char data[200];
		_tprintf(_T(" Row %d : "), iCount);
		if (ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO) {
			printf("An Fetch error occured\n");
			break;
		}
		if (ret == SQL_NO_DATA_FOUND) {
			break;
		}
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			for (int i = 1; i <= nresultcols; i++)
			{
				SQLGetData(hstmt, i, SQL_C_WCHAR, &data, 200, &iDataLen);
				/* Print the row of data */
				_tprintf(_T(" %ls"), data);
				fflush(stdout);
			} /* for all columns in this row  */

			printf("\n");
		}

		iCount++;
	} /* while rows to fetch */

}

void DatabaseManager::PrintError(SQLHENV henv,
	SQLHDBC hdbc,
	SQLHSTMT hstmt)
{
	SQLWCHAR     buffer[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLWCHAR     sqlstate[SQL_SQLSTATE_SIZE + 1];
	SQLINTEGER  sqlcode;
	SQLSMALLINT length;

	while (SQLError(henv, hdbc, hstmt, sqlstate, &sqlcode, buffer,
		SQL_MAX_MESSAGE_LENGTH + 1, &length) == SQL_SUCCESS)
	{
		printf("\n **** ERROR *****\n");
		printf("         SQLSTATE: %s\n", sqlstate);
		printf("Native Error Code: %ld\n", sqlcode);
		printf("%s \n", buffer);
	};
	return;
}


DatabaseManager::DatabaseManager()
{
}


DatabaseManager::~DatabaseManager()
{
}
