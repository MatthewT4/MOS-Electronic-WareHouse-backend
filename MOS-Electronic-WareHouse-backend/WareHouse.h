#pragma once
#include <iostream>
#include "Position.h"
#include <vector>
#include <set>
#include <algorithm>

struct Cell {
	Cell() {}
	Cell(bool Er) : Error(Er){}
	Cell(TypePosition Intype, Position Inposit, vector<std::string> InVecCell) : type(Intype),
								posit(Inposit), includeCell(InVecCell), empty(false) {}
	bool empty = true;
	TypePosition type;
	Position posit = Position("000");
	vector<std::string> includeCell;
	bool Error = false;
};

bool operator<(Cell c1, Cell c2);

class WareHouse {
public:
	WareHouse(); /*{}*/
	void AddElement(Cell ce);
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
private:
	set<Cell> setWareHouse;
};