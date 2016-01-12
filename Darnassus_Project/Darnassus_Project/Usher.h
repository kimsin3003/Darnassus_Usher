#pragma once
#include <codecvt>
#include "DatabaseManager.h"

class Usher
{
public:
	void Play();


	Usher();
	~Usher();

private:

	void UserProcess();
	void SearchItem();
	void SearchNPC();
	void SearchGuest();
	void AdminProcess();
	void EditData();
	void EditGuest();
	void EditItem();
	void EditNpc();
	SQLHENV m_hEnv;
	SQLHDBC m_hDbc;
	SQLHSTMT m_hStmt;

	DatabaseManager m_dm;
};

