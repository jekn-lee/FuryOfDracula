// TrailLinkedList.h
// Designed by Mahima Mandal

#include "Globals.h"
#include "Game.h"
#include "Places.h"

typedef struct Node *Link;
typedef struct Node { LocationID loc; Link next; } Node;
typedef struct List { Link first; Link last; } *List;

List newTrail();//Create a LL trail with all UNKNOWN
void freeTrailList(List myList);//Free LL
void addLocation(List myList,LocationID currLoc);//Add new location to start
void showTrail(List myList);//Print out trail
int lookUpTrail(List myList,LocationID loc);//Search for loc in trail, 0 if FALSE, 1 if TRUE
LocationID findLocation(List myList, int index);//Gives location at index 0..5
LocationID *giveLocation(List myList);//returns pointer to array holding the trail and NULL terminator



