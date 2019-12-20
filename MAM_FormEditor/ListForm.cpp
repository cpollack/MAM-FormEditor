#include "ListForm.h"

using namespace MAM_FormEditor;

void ListForm::fillList(List<String^> ^strings) {
	for each (String^ s in strings) {
		listBoxItems->Items->Add(s);
	}
}

void ListForm::listMoveUp() {
	int idx = listBoxItems->SelectedIndex;
	if (idx <= 0 || listBoxItems->Items->Count == 1 || idx > listBoxItems->Items->Count - 1) return;

	String^ s = listBoxItems->Items[idx-1]->ToString();
	listBoxItems->Items[idx - 1] = listBoxItems->Items[idx];
	listBoxItems->Items[idx] = s;
}

void ListForm::listMoveDown() {
	int idx = listBoxItems->SelectedIndex;
	if (idx < 0 || listBoxItems->Items->Count == 1 || idx >= listBoxItems->Items->Count - 1) return;

	String^ s = listBoxItems->Items[idx]->ToString();
	listBoxItems->Items[idx] = listBoxItems->Items[idx + 1];
	listBoxItems->Items[idx + 1] = s;
}

void ListForm::listDelete() {
	int idx = listBoxItems->SelectedIndex;
	if (idx < 0 || idx > listBoxItems->Items->Count - 1) return;
	listBoxItems->Items->RemoveAt(idx);
}

void ListForm::listAdd(String^ s) {
	if (s->Length == 0) return;
	listBoxItems->Items->Add(s);
}

void ListForm::listSave() {
	returnStrings->Clear();
	for each (Object^ o in listBoxItems->Items) {
		returnStrings->Add(o->ToString());
	}
}