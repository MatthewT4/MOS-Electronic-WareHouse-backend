#pragma once
#include <iostream>
#include "Position.h"
#include <vector>
#include <set>
#include <algorithm>
#include "JSON.h"
#include "DataBase.h"

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

struct CompleteAddElem {
	CompleteAddElem(std::string InUuid, bool Incomplete, std::string InNamePosition, std::string InNameCell);
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
	vector<CompleteAddElem> AddElements(std::vector<Position> ce);
	/*{
		setWareHouse.insert(ce);
	}*/
	Cell GetElementToUUID(const string& uuid); 
	/*{ // выдача элемента по позиции.
		auto it = find_if(setWareHouse.begin(), setWareHouse.end(), [uuid] (Cell c) {
			return c.posit.GetUUid() == uuid;
			});
		if (it != setWareHouse.end()) {
			return *it;
		}
		else {
			return Cell(true); // если элемент не найден, то возвращаем пустой Cell с флажком Error.
		}
	}*/
	DataBase& GetDB();
	bool CreateDBTable(POSTJSON data);
private:
	bool InsertDB(Position& pos, std::string type);
	int heightWH = 0,
		widthWH = 0,
		depthWH = 0;
	std::vector<std::vector<std::string>> vecCellNotSmall;
	DataBase db;
};