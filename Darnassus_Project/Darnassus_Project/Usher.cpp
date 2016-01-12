#include "stdafx.h"
#include "Usher.h"
#include <iostream>
#include <limits>
#include "DatabaseManager.h"
#include <string>
#include <sstream>
#undef max
using namespace std;

Usher::Usher()
{
	m_dm.Initialize(&m_hEnv, &m_hDbc);
	m_dm.Connect(m_hDbc, (SQLWCHAR*)L"local", (SQLWCHAR*)L"taewoo", (SQLWCHAR*)L"xodn**26");
	m_dm.ProcessStatement(m_hEnv, m_hDbc, (SQLWCHAR*)L"USE darnassus");
}

void Usher::Play()
{
	int input;
	while (true)
	{
		system("cls");
		cout << "1. user" << endl;
		cout << "2. admin" << endl;
		cout << "3. exit" << endl;
		cout << "In which mode do you want to login? ";
		cin >> input;
		switch (input)
		{
		case 1:
			UserProcess();
			break;
		case 2:
			AdminProcess();
			break;
		case 3:
			exit(1);
			break;
		default:
			break;
		}
	}
}

void Usher::UserProcess()
{
	system("cls");
	cout << "User mode\n" << endl;
	int input;
	while (true)
	{
		cout << "Welcome To Darnassus Usher!" << endl;
		
		cout << "1. item" << endl;
		cout << "2. npc" << endl;
		cout << "3. guest" << endl;
		cout << "4. quit" << endl;
		cout << "Which one do you want to search? ";
		cin >> input;
		switch (input)
		{
		case 1:
			SearchItem();
			break;
		case 2:
			SearchNPC();
			break;
		case 3:
			SearchGuest();
			break;
		case 4:
			return;
		default:
			break;
		}

		cout << "\n\n" << endl;
	}
}

void Usher::SearchItem()
{
	system("cls");
	cout << "Item searching\n" << endl;
	wstring temp;
	wchar_t input[50];
	wchar_t* ptr;

	cout << "item name (* for all item): ";
	wcin.getline(input, 50);
	wcin.clear();
	getline(wcin, temp);

	printf(" Column | %30s%30s%30s%30s", "아이템", "상인", "건물", "지역");
	printf("\n===============================================================================================================================================\n");
	wstring item_name = L"call search_item('" + temp + L"')";

	m_dm.ProcessStatement(m_hEnv, m_hDbc, (SQLWCHAR*)item_name.c_str());
}

void Usher::SearchNPC()
{
	system("cls");
	cout << "NPC searching\n" << endl;
	wstring temp;
	int way;
	wchar_t input[50];
	wchar_t* ptr;
	while (true)
	{
		cout << "0. all npc" << endl;
		cout << "1. search by name" << endl;
		cout << "2. search by role" << endl;
		cout << "3. search by building" << endl;
		cout << "4. search by region" << endl;
		cout << "5. quit" << endl;
		cout << "which way do you want? ";

		cin >> way;

		switch (way)
		{
		case 0:
			break;
		case 1:
			cout << "name : ";
			break;
		case 2:
			cout << "role : ";
			break;
		case 3:
			cout << "building : ";
			break;
		case 4:
			cout << "region : ";
			break;
		case 5:
			return;
		default:
			break;
		}

		if (way != 0)
		{
			wcin.getline(input, 50);
			wcin.clear();
			getline(wcin, temp);
		}

		wstring data = L"call search_npc(" + std::to_wstring(way) + L", '" + temp + L"')";

		printf(" Column | %30s%30s%30s%30s", "npc", "역할", "건물", "지역");
		printf("\n===============================================================================================================================================\n");

		wcout << data << endl;

		m_dm.ProcessStatement(m_hEnv, m_hDbc, (SQLWCHAR*)data.c_str());
	}
}

void Usher::SearchGuest()
{
	cout << "Guest searching\n" << endl;
	printf(" Column | %30s%30s%30s%30s", "id", "여관");
	printf("\n===============================================================================================================================================\n");
	m_dm.ProcessStatement(m_hEnv, m_hDbc, (SQLWCHAR*)L"select g.id, b.name from guest as g, building as b where g.Building_id = b.id");
}

void Usher::AdminProcess()
{
	system("cls");
	cout << "Admin mode\n" << endl;
	int input;
	while (true)
	{
		cout << "Welcome" << endl;
		cout << "1. item search" << endl;
		cout << "2. npc search" << endl;
		cout << "3. edit data" << endl;
		cout << "4. quit" << endl;
		cout << "What do you want to do? ";
		cin >> input;
		switch (input)
		{
		case 1:
			SearchItem();
			break;
		case 2:
			SearchNPC();
			break;
		case 3:
			EditData();
			break;
		case 4:
			return;
			break;
		default:
			break;
		}

		cout << "\n\n" << endl;
	}
}

void Usher::EditData()
{
	system("cls");
	cout << "Data editing\n" << endl;

	int input;
	while (true)
	{
		cout << "1. guest" << endl;
		cout << "2. item" << endl;
		cout << "3. npc" << endl;
		cout << "Which table do you want to edit? ";
		cin >> input;
		switch (input)
		{
		case 1:
			EditGuest();
			break;
		case 2:
			EditItem();
			break;
		case 3:
			EditNpc();
			break;
		case 4:
			return;
			break;
		default:
			break;
		}

		cout << "\n\n" << endl;
	}
}

void Usher::EditGuest()
{
	system("cls");
	cout << "Guest editing\n" << endl;


	wstring id;
	int building_id;
	int input;
	wchar_t temp[50];
	wchar_t* ptr;

	while (true)
	{
		cout << "1. insert" << endl;
		cout << "2. delete" << endl;
		cout << "3. quit" << endl;
		cout << "Which way do you want? ";
		cin >> input;

		if (input == 1)
		{

			cout << "guest id: ";
			wcin.getline(temp, 50);
			wcin.clear();
			getline(wcin, id);

			cout << "building id: ";
			cin >> building_id;

			wstring query = L"insert into guest set id = '" + id + L"', Building_id = " + std::to_wstring(building_id) + L"";
			m_dm.ProcessStatement(m_hEnv, m_hDbc, (SQLWCHAR*)query.c_str());

		}
		else if (input == 2)
		{

			cout << "guest id: ";
			wcin.getline(temp, 50);
			wcin.clear();
			getline(wcin, id);

			wstring query = L"delete from guest where id like '%" + id + L"%'";
			m_dm.ProcessStatement(m_hEnv, m_hDbc, (SQLWCHAR*)query.c_str());

		}
		else
			return;

		cout << "\n\n" << endl;
	}
}

void Usher::EditItem()
{
	system("cls");
	cout << "Item editing\n" << endl;

	int input;
	while (true)
	{
		cout << "1. insert" << endl;
		cout << "2. delete" << endl;
		cout << "3. quit" << endl;
		cout << "Which way do you want? ";
		cin >> input;

		if (input == 1)
		{

			wstring name;
			wstring price;
			int npc_id;

			cout << " name: ";
			wcin >> name;

			cout << "price: ";
			wcin >> price;

			cout << "npc_id: ";
			cin >> npc_id;


			wstring query = L"insert into item set name = '" + name + L"', price = '" + price + L"', NPC_id = " + std::to_wstring(npc_id);
			wcout << query;
			m_dm.ProcessStatement(m_hEnv, m_hDbc, (SQLWCHAR*)query.c_str());

		}
		else if (input == 2)
		{
			wstring name;
			cout << " name: ";
			wcin >> name;

			wstring query = L"delete from item where name like '%" + name + L"%'";
			m_dm.ProcessStatement(m_hEnv, m_hDbc, (SQLWCHAR*)query.c_str());
		}
		else
		{
			return;
		}

		cout << "\n\n" << endl;
	}
}

void Usher::EditNpc()
{
	system("cls");
	cout << "Npc editing\n" << endl;

	int input;
	while (true)
	{
		cout << "1. insert" << endl;
		cout << "2. delete" << endl;
		cout << "3. quit" << endl;
		cout << "Which way do you want? ";
		cin >> input;

		if (input == 1)
		{

			wstring name;
			wstring role;
			int building_id;
			int Region_id;
			wchar_t* ptr;
			cout << "npc name: ";
			wcin >> name;

			cout << "npc role: ";
			wcin >> role;

			cout << "building id: ";
			cin >> building_id;

			wstring query = L"call insert_npc('" + name + L"', '" + role + L"', " + std::to_wstring(building_id) + L");";
			wcout << query << endl;
			m_dm.ProcessStatement(m_hEnv, m_hDbc, (SQLWCHAR*)query.c_str());

		}
		else if (input == 2)
		{
			wstring name;
			cout << "npc name: ";
			wcin >> name;

			wstring query = L"delete from npc where name like '%" + name + L"%'";
			m_dm.ProcessStatement(m_hEnv, m_hDbc, (SQLWCHAR*)query.c_str());

		}
		else
		{
			return;
		}

		cout << "\n\n" << endl;
	}
}

Usher::~Usher()
{
}
