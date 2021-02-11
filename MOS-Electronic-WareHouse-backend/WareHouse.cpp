#include "WareHouse.h"
#include <algorithm>

bool operator<(Cell c1, Cell c2) {
	return c1.empty < c2.empty;
}
struct ret {
	int he = 0;
	set<char> Posit;
};
static bool CheckInt(const char& ch) {
	string s = "0123456789";
	for (const auto& j : s) {
		if (ch == j) {
			return true;
		}
	}
	return false;
}
ret CreateCell(std::vector<std::string> Vec) {
	ret r;
	for (auto i : Vec) {
		/*while (!CheckInt(i[0])) {
			i.erase(0, 1);
		}
		if (int(i) < r.he) {

		}*/
		int val = 0;
		for (auto c : i) {
			if (CheckInt(c)) {
				val *= 10;
				val += int(c) - 48;
				r.Posit.insert(c);
			}
			else {
				r.Posit.insert(c);
			}
		}
		if (r.he < val) {
			r.he = val;
		}
	}
	return r;
}


WareHouse::WareHouse() {}
/*{"size": {"size_x": 6, "size_y" : 3, "size_z" : 1},
"merged" : [["A1", "A2"], ["B2", "B3"], ["C1", "C2"], ["D2", "D3"], ["E2", "E3", "F2", "F3"]] }*/
WareHouse::WareHouse(POSTJSON data, string InNameDB) : db(DataBase(InNameDB)), widthWH(data.size_x), heightWH(data.size_y), depthWH(data.size_z), vecCellNotSmall(data.vecAssociations) {
	vector<Cell> VecCell;
	for (auto vec : vecCellNotSmall) {
		Cell cell;
		if (vec.size() == 2) {
			cell.type = TypePosition::Medium;
		}
		auto Ccell = CreateCell(vec);
		for (const auto& NCh : Ccell.Posit) {
			cell.NameCell += NCh;
		}
		std::string stri = "", 
					integ = "";

		for (const auto& st : cell.NameCell) {
			if (CheckInt(st)) {
				integ += st;
			}
			else {
				stri += st;
			}
		}
		cell.NameCell = stri + integ;
		cell.height = Ccell.he;
		/*cout << "Height: " << cell.height << endl
			<< "NameCell: " << cell.NameCell << endl;*/
		VecCell.push_back(cell);
		
	}
}

void WareHouse::AddElement(Cell ce) {
	//setWareHouse.insert(ce);
}

void WareHouse::CreateDBTable(std::vector<Cell> InVecCell) { // пойдЄт под insert позиций.
	//—оздаЄм вектора дл€ разных типов €чеек
	/*vector<Cell> BigElem(InVecCell.size()), MidlElem(InVecCell.size()), 
				 SmallElem(InVecCell.size()), RemoteElem(InVecCell.size());
	//ƒелим элементы из одного типа вектора в разные
	{
		auto i = copy_if(InVecCell.begin(), InVecCell.end(), BigElem.begin(), [](Cell c) {
			return c.type == TypePosition::Big;
			});
		BigElem.erase(i, BigElem.end());
		i = copy_if(InVecCell.begin(), InVecCell.end(), MidlElem.begin(), [](Cell c) {
			return c.type == TypePosition::Medium;
			});
		MidlElem.erase(i, MidlElem.end());
		i = copy_if(InVecCell.begin(), InVecCell.end(), SmallElem.begin(), [](Cell c) {
			return c.type == TypePosition::Small;
			});
		SmallElem.erase(i, SmallElem.end());
		i = copy_if(InVecCell.begin(), InVecCell.end(), RemoteElem.begin(), [](Cell c) {
			return c.type == TypePosition::RemoteWarehouse;
			});
		RemoteElem.erase(i, RemoteElem.end());
	}*/
	for (const auto& ce : InVecCell) {
		db.InsertDBData("INSERT INTO WareHouse(TypeCell, PositionCell, HeightCell, Empty) VALUES" + (ce.type));
	}

}
Cell WareHouse::GetElementToUUID(const string& uuid) { // выдача элемента по позиции.
	/*auto it = find_if(setWareHouse.begin(), setWareHouse.end(), [uuid](Cell c) {
		return c.posit.GetUUid() == uuid;
		});
	if (it != setWareHouse.end()) {
		return *it;
	}
	else {*/
		return Cell(true); // если элемент не найден, то возвращаем пустой Cell с флажком Error.
	//}
}