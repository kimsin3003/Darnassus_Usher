#pragma once
#include "DatabaseManager.h"

class Usher
{
public:
	void Play();


	Usher();
	~Usher();

private:

	SQLHENV m_hEnv;
	SQLHDBC m_hDbc;
	SQLHSTMT m_hStmt;

	DatabaseManager m_dm;
};

