#pragma once
#include <iostream>
#include "Position.h"
#include <vector>
#include <set>
#include <algorithm>
#include "JSON.h"
#include "DataBase.h"
/*��������� ������*/
struct Cell {
	Cell() {}
	Cell(bool Er) : Error(Er){}
	Cell(TypePosition Intype, Position Inposit) : type(Intype), posit(Inposit) {}
	TypePosition type = TypePosition::RemoteWarehouse;
	Position posit = Position("000"); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	bool Error = false;
	int height = 0;
	string NameCell = "";
};

bool operator<(Cell c1, Cell c2);
/*��������� ������������� ������ ��� ��������� �������.*/
struct CompleteFuncElem {
	CompleteFuncElem(std::string InUuid, bool Incomplete, std::string InNamePosition, std::string InNameCell);
	std::string uuid;
	bool complete;
	std::string NamePosition;
	std::string NameCell;
};

class WareHouse {
public:
	WareHouse(); /*{}*/
	WareHouse(std::string InDBName);
	WareHouse(POSTJSON data, string DBName);
	/*���������� ��������� � ���� ������ �� ������� �������.*/
	vector<CompleteFuncElem> AddElements(std::vector<Position> ce);
	/*������ ��������� �� ���� ������ �� ������� �������.*/
	vector<CompleteFuncElem> IssuePositions(vector<string> Vec);
	/*��������� ���������� DataBace �� ������.*/
	DataBase& GetDB();
	/*���������� ����� ����� ������.*/
	bool CreateDBTable(POSTJSON data);


private:
	/*���������� ������� ��� ���������� � ��*/
	bool InsertDB(Position& pos, std::string type);
	int heightWH = 0,
		widthWH = 0,
		depthWH = 0;
	std::vector<std::vector<std::string>> vecCellNotSmall;
	DataBase db;
};