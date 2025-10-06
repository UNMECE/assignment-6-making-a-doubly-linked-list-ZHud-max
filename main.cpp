#include <iostream>
#include <ctime>
#include <cmath>
#include "coordinate.h"

using namespace std;

void add_coordinate(float x, float y, int coord_id, Coordinate *list_end) {

	Coordinate *new_coord = (Coordinate *) malloc(sizeof(Coordinate));

		new_coord->x = x;
		new_coord->y = y;
		new_coord->coord_id = coord_id;

		new_coord->next = NULL;

		new_coord->previous = list_end;
		list_end->next = new_coord;

}

void forward_display(Coordinate* list_beginning) {

	Coordinate *temp = list_beginning;

	while (temp != NULL) {
		cout << "Coordinate: " << temp->coord_id << endl;
		cout << "X: " << temp->x << endl;
		cout << "Y: " << temp->y << endl;

		temp = temp->next;
	}

}

void backwards_display(Coordinate* list_end) {

   Coordinate *temp = list_end;

   while (temp != NULL) {
     cout << "Coordinate: " << temp->coord_id << endl;
     cout << "X: " << temp->x << endl;
     cout << "Y: " << temp->y << endl;

     temp = temp->previous;
   }
}

int list_length(Coordinate* list_beginning) {

	Coordinate* temp = list_beginning;
	int length = 0;

	while (temp != NULL) {
		length++;
		temp = temp->next;
	}

	return length;

}

void delete_coordinate(Coordinate* list_beginning, int coord_id) {
	
	Coordinate *temp = list_beginning;

	while (temp != NULL) {

		if (temp->coord_id == coord_id) {
			if (temp->previous != NULL) {
				temp->previous->next = temp->next;
			}

			if (temp->next != NULL) {
				temp->next->previous = temp->previous;
			}

			delete temp;
			cout << "Coordinate Deleted: " << coord_id << endl;
			
			return;
		}

		temp = temp->next;

	}
	
	cout << "Coordinate not found" << endl;

}

void closest_to(Coordinate* list_beginning, int x, int y) {

	double distance;
	double min_distance;

	Coordinate *curr_coord = list_beginning;
	Coordinate *min_coord = list_beginning;

	min_distance = sqrt(pow(min_coord->x - x, 2) + pow(min_coord->y - y, 2));

	while (curr_coord != NULL) {

		distance = sqrt(pow(curr_coord->x - x, 2) + pow(curr_coord->y - y, 2));

		if (distance < min_distance) {
			min_distance = distance;
			min_coord = curr_coord;
		}

		curr_coord = curr_coord->next;
	
	}

	cout << "The shortest distance from coordinates X:" << x << " Y: " << y << " is:\n" 
	     << min_coord->coord_id << " at X: " << min_coord->x << " Y: " << min_coord->y << endl;

}


int main(int argc, char* argv[]) {

	Coordinate *list_beginning = (Coordinate *) malloc(sizeof(Coordinate));
	list_beginning->next = NULL;
	list_beginning->previous = NULL;
	list_beginning->coord_id = 0;

	Coordinate *list_end = list_beginning;

	srand(time(NULL));
	int num_coord = atoi(argv[1]);

	float x;
  float y;

	cout << "Generating coordinates..." << endl;
	for (int i = 1; i < num_coord; i++) {

		x = (float)(rand()%100);
    y = (float)(rand()%100);

		add_coordinate(x, y, i, list_end);
		list_end = list_end->next;

	}

	cout << "Coordinate list:" << endl;
	forward_display(list_beginning);
	cout << "List Length: " << list_length(list_beginning) << endl;

	int delete_id = (int)(rand()%num_coord);
	cout << "Deleting Coordinate " << delete_id << endl;
	delete_coordinate(list_beginning, delete_id);

	cout << "New coordinate list (in reverse):" << endl;
  backwards_display(list_end);
	cout << "List Length: " << list_length(list_beginning) << endl;

	x = (float)(rand()%100);
  y = (float)(rand()%100);

	cout << "Finding coordinate closest to X: " << x << " Y: " << y << endl;
	closest_to(list_beginning, x, y);


	Coordinate* temp;
	while ( list_beginning != NULL) {

		temp = list_beginning;
		list_beginning = list_beginning->next;
		delete temp; 

	}


	return 0;

}

