#include "WareHouse.h"
#include <algorithm>

/*bool operator<(Cell c1, Cell c2) {
	return c1.empty < c2.empty;
}*/
CompleteFuncElem::CompleteFuncElem(std::string InUuid, bool Incomplete, std::string InNamePosition, std::string InNameCell)
	: uuid(InUuid), complete(Incomplete), NamePosition(InNamePosition), NameCell(InNameCell) {};

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
		//while (!CheckInt(i[0])) {
		//	i.erase(0, 1);
		//}
		//if (int(i) < r.he) {

		//}
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
WareHouse::WareHouse(std::string InDBName) {
	db.ConnectToDB(InDBName);
}
/*{"size": {"size_x": 6, "size_y" : 3, "size_z" : 1},
"merged" : [["A1", "A2"], ["B2", "B3"], ["C1", "C2"], ["D2", "D3"], ["E2", "E3", "F2", "F3"]] }*/
WareHouse::WareHouse(POSTJSON data, string InNameDB) : db(DataBase(InNameDB)), widthWH(data.size_x), heightWH(data.size_y), depthWH(data.size_z), vecCellNotSmall(data.vecAssociations) {
	CreateDBTable(data);
}
DataBase& WareHouse::GetDB() {
	return db;
}
vector<CompleteFuncElem> WareHouse::AddElements(std::vector<Position> InVecCell) {
	vector<CompleteFuncElem> RetVecComplete;
	 vector<Position> BigElem(InVecCell.size()), MidlElem(InVecCell.size()),
		SmallElem(InVecCell.size()), RemoteElem(InVecCell.size());
	//ƒелим элементы из одного типа вектора в разные
	auto i = copy_if(InVecCell.begin(), InVecCell.end(), BigElem.begin(), [](Position c) {
		return c.GetTypePosition() == TypePosition::Big;
		});
	BigElem.erase(i, BigElem.end());
	i = copy_if(InVecCell.begin(), InVecCell.end(), MidlElem.begin(), [](Position c) {
		return c.GetTypePosition() == TypePosition::Medium;
		});
	MidlElem.erase(i, MidlElem.end());
	i = copy_if(InVecCell.begin(), InVecCell.end(), SmallElem.begin(), [](Position c) {
		return c.GetTypePosition() == TypePosition::Small;
		});
	SmallElem.erase(i, SmallElem.end());
	i = copy_if(InVecCell.begin(), InVecCell.end(), RemoteElem.begin(), [](Position c) {
		return c.GetTypePosition() == TypePosition::RemoteWarehouse;
		});
	RemoteElem.erase(i, RemoteElem.end());

	//—ортируем векторы, первый элемент - самый т€жЄлый.
	sort(BigElem.begin(), BigElem.end(), [](Position c1, Position c2) {
		return c1.GetWeigt() < c2.GetWeigt(); });
	sort(MidlElem.begin(), MidlElem.end(), [](Position c1, Position c2) {
		return c1.GetWeigt() < c2.GetWeigt(); });
	sort(SmallElem.begin(), SmallElem.end(), [](Position c1, Position c2) {
		return c1.GetWeigt() < c2.GetWeigt(); });
	for (auto& El : BigElem) {
		if (!InsertDB(El, "" + El.GetTypePosition())) {
			std::string TypePP = "" + El.GetTypePosition();
			bool flag = false;
			while (!flag and TypePP != "RemoteWarehouse") {
				if (TypePP == "Small") { TypePP = "Medium"; }
				else if (TypePP == "Medium") { TypePP = "Big"; }
				else if (TypePP == "Big") { TypePP = "RemoteWarehouse"; }
				flag = InsertDB(El, TypePP);
			}
			if (!flag) {
				cout << "[SQL Error](WareHouse::AddElements): " << db.GeSsqlError() << endl;
				RetVecComplete.push_back(CompleteFuncElem(El.GetUUid(), false, El.GetName(), "Error"));
			}
			else { //delete continion...
				cout << "[SQL OK](WareHouse::AddElements)" << endl; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
		}
	}
	for (auto& El : MidlElem) {
		if (!InsertDB(El, "" + El.GetTypePosition())) {
			std::string TypePP = "" + El.GetTypePosition();
			bool flag = false;
			while (!flag and TypePP != "RemoteWarehouse") {
				if (TypePP == "Small") { TypePP = "Medium"; }
				else if (TypePP == "Medium") { TypePP = "Big"; }
				else if (TypePP == "Big") { TypePP = "RemoteWarehouse"; }
				flag = InsertDB(El, TypePP);
			}
			if (!flag) {
				cout << "[SQL Error](WareHouse::AddElements): " << db.GeSsqlError() << endl;
				RetVecComplete.push_back(CompleteFuncElem(El.GetUUid(), false, El.GetName(), "Error"));
			}
			else { //delete continion...
				cout << "[SQL OK](WareHouse::AddElements)" << endl; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
		}
	}
	for (auto& El : SmallElem) {
		if (!InsertDB(El, "" + El.GetTypePosition())) {
			std::string TypePP = "" + El.GetTypePosition();
			bool flag = false;
			while (!flag and TypePP != "RemoteWarehouse") {
				if (TypePP == "Small") { TypePP = "Medium"; }
				else if (TypePP == "Medium") { TypePP = "Big"; }
				else if (TypePP == "Big") { TypePP = "RemoteWarehouse"; }
				flag = InsertDB(El, TypePP);
			}
			if (!flag) {
				cout << "[SQL Error](WareHouse::AddElements): " << db.GeSsqlError() << endl;
				RetVecComplete.push_back(CompleteFuncElem(El.GetUUid(), false, El.GetName(), "Error"));
			}
			else { //delete continion...
				cout << "[SQL OK](WareHouse::AddElements)" << endl; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
		}
	}
	for (auto& El : RemoteElem) {
		if (!InsertDB(El, "" + El.GetTypePosition())) {
			std::string TypePP = "" + El.GetTypePosition();
			bool flag = false;
			while (!flag and TypePP != "RemoteWarehouse") {
				if (TypePP == "Small") { TypePP = "Medium"; }
				else if (TypePP == "Medium") { TypePP = "Big"; }
				else if (TypePP == "Big") { TypePP = "RemoteWarehouse"; }
				flag = InsertDB(El, TypePP);
			}
			if (!flag) {
				cout << "[SQL Error](WareHouse::AddElements): " << db.GeSsqlError() << endl;
				RetVecComplete.push_back(CompleteFuncElem(El.GetUUid(), false, El.GetName(), "Error"));
			}
			else { //delete continion...
				cout << "[SQL OK](WareHouse::AddElements)" << endl; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
		}
	}
	return RetVecComplete;
}
bool WareHouse::InsertDB(Position& pos, std::string type) {
	std::string dbstr, Val;
	if (type != "RemoteWarehouse") {
		if (pos.GetComment() == "") {
			dbstr = "INSERT INTO Positions( Position, UUID, Name, Height, Width, Depth, Weight) VALUES (";
			Val = "( SELECT t1.PositionCell FROM WareHouse t1, Positions t2 WHERE NOT (t1.PositionCell IN ( \
			SELECT t1.PositionCell FROM WareHouse t1, WareHouse t2 WHERE(t1.PositionCell = t2.Position))) \
			AND t1.TypeCell = \'" + type + "\' ORDER BY t1.HeightCell LIMIT 1), ";
			Val += pos.GetUUid() + "\'" + ", "
				+ "\'" + pos.GetName() + "\'" + ", " + to_string(pos.GetHeight()) + ", "
				+ to_string(pos.GetWidth()) + ", " + to_string(pos.GetDepth()) + ", "
				+ to_string(pos.GetWeigt()) + ')';
			dbstr += Val;
		}
		else {
			dbstr = "INSERT INTO Positions( Position, UUID, Name, Height, Width, Depth, Weight, Comments) VALUES (";
			Val = "( SELECT t1.PositionCell FROM WareHouse t1, Positions t2 WHERE NOT (t1.PositionCell IN ( \
			SELECT t1.PositionCell FROM WareHouse t1, Positions t2 WHERE(t1.PositionCell = t2.Position))) \
			AND t1.TypeCell = \'" + type + "\' ORDER BY t1.HeightCell LIMIT 1), ";
			Val += "\'" + pos.GetUUid() + "\'" + ", "
				+ "\'" + pos.GetName() + "\'" + ", " + to_string(pos.GetHeight()) + ", "
				+ to_string(pos.GetWidth()) + ", " + to_string(pos.GetDepth()) + ", "
				+ to_string(pos.GetWeigt()) + ", " + "\'" + pos.GetComment() + "\'" + ')';
			//+ to_string(ce.height) + ')';
			dbstr += Val;
		}
	}
	else {
		if (pos.GetComment() == "") {
			dbstr = "INSERT INTO Positions( Position, UUID, Name, Height, Width, Depth, Weight) VALUES (";
			Val = "( SELECT PositionCell FROM WareHouse WHERE TypeCell = 'RemoteWarehouse' LIMIT 1), ";
			Val += "\'" + pos.GetUUid() + "\'" + ", "
				+ "\'" + pos.GetName() + "\'" + ", " + to_string(pos.GetHeight()) + ", "
				+ to_string(pos.GetWidth()) + ", " + to_string(pos.GetDepth()) + ", "
				+ to_string(pos.GetWeigt()) + ')';
			dbstr += Val;
		}
		else {
			dbstr = "INSERT INTO Positions( Position, UUID, Name, Height, Width, Depth, Weight, Comments) VALUES (";
			Val = "( SELECT PositionCell FROM WareHouse WHERE TypeCell = 'RemoteWarehouse' LIMIT 1), ";
			Val += "\'" + pos.GetUUid() + "\'" + ", "
				+ "\'" + pos.GetName() + "\'" + ", " + to_string(pos.GetHeight()) + ", "
				+ to_string(pos.GetWidth()) + ", " + to_string(pos.GetDepth()) + ", "
				+ to_string(pos.GetWeigt()) + ", " + "\'" + pos.GetComment() + "\'" + ')';
			//+ to_string(ce.height) + ')';
			dbstr += Val;
		}
	}
	if (!db.InsertDBData(dbstr)) {
		return false;
	}
	return true;
}
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
/*
void WareHouse::CreateDBTable(std::vector<Cell> InVecCell) { // пойдЄт под insert позиций.
	for (const auto& ce : InVecCell) {
		std::string dbstr = "INSERT INTO WareHouse(TypeCell, PositionCell, HeightCell) VALUES (";
		std::string Val = " \'" + ce.type + "\'" + ", " + "\'" + ce.NameCell + "\'" + ", "
			+ to_string(ce.height) + ')';
		dbstr += Val;
		db.InsertDBData(dbstr);
	}

}*/
bool WareHouse::CreateDBTable(POSTJSON data) { // пойдЄт под insert позиций.
	widthWH = data.size_x;  
	heightWH = data.size_y; 
	depthWH = data.size_z;
	vecCellNotSmall = data.vecAssociations;
	vector<Cell> VecCell;
	int x = 1, y = 1;
	while (x <= widthWH) {
		char n = char(x + 64);
		while (y <= heightWH) {
			Cell vc;
			vc.type = TypePosition::Small;
			vc.NameCell = n + to_string(y);
			vc.height = heightWH - y + 1;
			VecCell.push_back(vc);
			y++;
		}
		y = 1;
		x++;
	}
	for (auto vec : vecCellNotSmall) {
		Cell cell;
		if (vec.size() == 2) {
			cell.type = TypePosition::Medium;
		}
		else if (vec.size() == 4) {
			cell.type = TypePosition::Big;
		}
		auto Ccell = CreateCell(vec);
		/*
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
		}*/
		string VName = "";
		for (const auto& i : vec) {
			VName += i;
		}
		//cell.NameCell = stri + integ;
		cell.NameCell = VName;
		cell.height = heightWH - Ccell.he + 1;
		/*cout << "Height: " << cell.height << endl
			<< "NameCell: " << cell.NameCell << endl;*/
		VecCell.push_back(cell);
		
	}
	bool AddSuccesful = true;
	for (const auto& ce : VecCell) {
		std::string dbstr = "INSERT INTO WareHouse(TypeCell, PositionCell, HeightCell) VALUES (";
		std::string Val = " \'" + ce.type + "\'" + ", " + "\'" + ce.NameCell + "\'" + ", "
			+ to_string(ce.height) + ')';
		dbstr += Val;
		if (!db.InsertDBData(dbstr)) {
			AddSuccesful = false;
		}
	}
	return AddSuccesful;

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

vector<CompleteFuncElem> WareHouse::IssuePositions(vector<string> Vec) {
	string Body = "";
}
