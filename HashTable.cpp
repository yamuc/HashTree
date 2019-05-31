#include "HashTable.h"
#include <iostream>

using namespace std;

HashTable::HashTable()
{
	data = new HashEntry*[100];

	for (int i = 0; i < length; i++) {
		data[i] = nullptr;
	}
}


HashTable::~HashTable()
{
}

void HashTable::add(Student* in)
{
	int index = hashFunc(in);
	if (data[index] != nullptr) {//if there is an entry in the one im trying to add to
		if (data[index] && data[index]->next) {//if theres already 2 of them
			resizeData(length*2);
			cout << endl;
			add(in);//add it recursively
		}
		else {//add it to the next
			data[index]->next = new HashEntry(in);
		}
	}
	else {//put it in the array
		data[index] = new HashEntry(in);
	}
	
}

void HashTable::remove(int index, bool chain)
{
	if (chain) {
		delete data[index]->next;
		data[index]->next = nullptr;
	}
	else {
		if (data[index]->next) {
			HashEntry* temp = data[index]->next;
			delete data[index];
			data[index] = temp;
		}
		else {
			delete data[index];
			data[index] = nullptr;
		}
		
	}
}

void HashTable::remove(int id)
{
	for (int i = 0; i < length; i++) {
		if (data[i] && data[i]->data->id == id) {
			if (data[i]->next) {
				HashEntry* temp = data[i]->next;
				delete data[i];
				data[i] = temp;
			}
			else {
				delete data[i];
				data[i] = nullptr;
			}
			break;
		}
		else if (data[i] && data[i]->next && data[i]->next->data->id == id) {
			delete data[i]->next;
			data[i]->next = nullptr;
			break;
		}
	}
}

void HashTable::resizeData(size_t newSize)
{
	size_t oldSize = length;
	HashEntry ** oldData = new HashEntry*[length];
	for (int i = 0; i < oldSize; i++)
		oldData[i] = data[i];
	
	
	length = newSize;
	delete[] data;
	data = new HashEntry*[newSize];
	for (int i = 0; i < newSize; i++)
		data[i] = nullptr;
	for (unsigned int i = 0; i < oldSize; i++) {//for all the old data
		if (oldData[i]) {//if it exists
			if (oldData[i]->next) {//if there are 2
				int index = hashFunc(oldData[i]->next->data);//get new hash
				if (data[index] != nullptr) {//if there is one in the new array already
					data[index]->next = oldData[i]->next;//add it
				}
				else {
					data[index] = oldData[i]->next;//add it
				}
				oldData[i]->next = nullptr;//just make sure nothing errors
			}
			int index = hashFunc(oldData[i]->data);
			if (data[index] != nullptr) {
				data[index]->next = oldData[i];
			}
			
			else {
				data[index] = oldData[i];
			}
		}
		
	}
	
}



int HashTable::hashFunc(Student * in)
{
	int f = 1; 
	for (unsigned int i = 0; i < strlen(in->firstName); i++)
		f += in->firstName[i]/3;
	int l = 1; 
	for (unsigned int i = 0; i < strlen(in->lastName); i++)
		l += in->lastName[i]/3;

	int total = (int)(in->gpa * (float)in->id/3 * abs(f-l));

	return total % length;
}




void HashTable::printStudents()
{
	for (int i = 0; i < length; i++) {
		if (data[i]) {
			cout << i << " " << data[i]->data->firstName << " " << data[i]->data->lastName 
				<< "(" << data[i]->data->id << ")";

			if (data[i]->next) {
				cout  << " -> " << data[i]->next->data->firstName << " " << data[i]->next->data->lastName 
					<< "(" << data[i]->next->data->id << ")";
			}
			cout << endl;
		}
	}
}
/*
int HashTable::countThings(HashEntry ** in, size_t size)
{
	int h = 0;
	for (int i = 0; i < size; i++) {
		if (in[i]) {
			if (in[i]->next) {
				h++;
			}
			h++;
		}
		
	}
	return h;
}
*/

