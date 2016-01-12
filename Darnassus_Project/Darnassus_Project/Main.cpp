// Darnassus_Info.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <clocale>
#include "Usher.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "");

	Usher usher;
	usher.Play();


	return 0;
}

