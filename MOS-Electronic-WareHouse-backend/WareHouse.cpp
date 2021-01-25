#include "WareHouse.h"

bool operator<(Cell c1, Cell c2) {
	return c1.empty < c2.empty;
}

WareHouse::WareHouse() {}
void WareHouse::AddElement(Cell ce) {
	setWareHouse.insert(ce);
}

Cell WareHouse::GetElementToUUID(const string& uuid) { // выдача элемента по позиции.
	auto it = find_if(setWareHouse.begin(), setWareHouse.end(), [uuid](Cell c) {
		return c.posit.GetUUid() == uuid;
		});
	if (it != setWareHouse.end()) {
		return *it;
	}
	else {
		return Cell(true); // если элемент не найден, то возвращаем пустой Cell с флажком Error.
	}
}
