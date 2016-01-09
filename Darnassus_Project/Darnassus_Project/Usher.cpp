#include "stdafx.h"
#include "Usher.h"
#include <iostream>
#include "DatabaseManager.h"

using namespace std;

Usher::Usher()
{

	m_dm.Initialize(&m_hEnv, &m_hDbc);
	m_dm.Connect(m_hDbc, (SQLWCHAR*)L"taewoo", (SQLWCHAR*)L"xodn**26");
}

void Usher::Play()
{
	int ret;

	cout << "Welcome" << endl;
	m_dm.ProcessStatement(m_hEnv, m_hDbc, (SQLWCHAR*)L"USE 131021_library");
	m_dm.ProcessStatement(m_hEnv, m_hDbc, (SQLWCHAR*)L"select * from books");


}


Usher::~Usher()
{
}
