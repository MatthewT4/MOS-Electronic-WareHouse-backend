#pragma once
#include <iostream>
#include "Position.h"
#include <vector>
#include <set>
#include <algorithm>
#include "JSON.h"
#include "DataBase.h"
/*Стркутура ячейки*/
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
/*структура возвращаемого значия для некоторых функций.*/
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
	/*Добавление элементов в базу данных из вектора позиций.*/
	vector<CompleteFuncElem> AddElements(std::vector<Position> ce);
	/*Выдача элементов из базы данных из вектора позиций.*/
	vector<CompleteFuncElem> IssuePositions(vector<string> Vec);
	/*Получение переменной DataBace по ссылке.*/
	DataBase& GetDB();
	/*Добавление новых ячеек склада.*/
	bool CreateDBTable(POSTJSON data);


private:
	/*подготовка запроса для добавления в БД*/
	bool InsertDB(Position& pos, std::string type);
	int heightWH = 0,
		widthWH = 0,
		depthWH = 0;
	std::vector<std::vector<std::string>> vecCellNotSmall;
	DataBase db;
};