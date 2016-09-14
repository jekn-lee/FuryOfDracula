//Implementation of Trail Linked List by Mahima Mandal

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h"
#include "TrailLinkedList.h"
#include "Places.h"

static void addUnknownNode(List myList);
static int trailSize(List myList);
/*//Simple Testing
int main(int argc, char *argv[]){
   List myTrail=newTrail();
   showTrail(myTrail);
   addLocation(myTrail, LONDON);
   addLocation(myTrail, MADRID);
   addLocation(myTrail, LIVERPOOL);
   showTrail(myTrail);
   int i;
   for(i=0;i<TRAIL_SIZE;i++){
      printf("%d ",findLocation(myTrail,i));
   }
   printf("\n");
   addLocation(myTrail, PARIS);
   addLocation(myTrail, SOFIA);
   addLocation(myTrail, VENICE);
   showTrail(myTrail);
   for(i=0;i<TRAIL_SIZE;i++){
      printf("%d ",findLocation(myTrail,i));
   }
   printf("\n");
   LocationID *trail=giveLocation(myTrail);
   for(i=0;i<TRAIL_SIZE;i++){
      printf("%d ",trail[i]);
   }
   addLocation(myTrail, PARIS);
   addLocation(myTrail, PARIS);
   addLocation(myTrail, PARIS);
   showTrail(myTrail);
   for(i=0;i<TRAIL_SIZE;i++){
      printf("%d ",findLocation(myTrail,i));
   }
   printf("\n");

   assert(lookUpTrail(myTrail,PARIS)==TRUE);
   assert(lookUpTrail(myTrail,SOFIA)==TRUE);
   assert(lookUpTrail(myTrail,VENICE)==TRUE);
   assert(lookUpTrail(myTrail,LONDON)==FALSE);
   assert(lookUpTrail(myTrail,MADRID)==FALSE);
   assert(lookUpTrail(myTrail,LIVERPOOL)==FALSE);
   freeTrailList(myTrail);
   return EXIT_SUCCESS;
}*/

static void addUnknownNode(List myList){
   //create UNKNOWN node
   Link myNode=malloc(sizeof(Node));
   assert(myList!=NULL && myNode!=NULL);
   myNode->loc=UNKNOWN_LOCATION;
   myNode->next=NULL;
   //Link to List/Trail
   //Case 1: Empty List
   if (myList->first==NULL){
      myList->first=myNode;
   }else{//Case 2: Generally non-emptyList
      myList->last->next=myNode;
   }
      myList->last=myNode;
   return;
}

static int trailSize(List myList){
   assert(myList!=NULL);
   Link curr=myList->first;
   int size=0;
   while(curr!=NULL){
      size++;
      curr=curr->next;
   }
   return size;
}

List newTrail(){
   List newList=malloc(sizeof(List));
   newList->first=NULL;
   newList->last=NULL;
   int i;
   //attach 6 UNKNOWN nodes
   for (i=0;i<TRAIL_SIZE;i++){
      addUnknownNode(newList);
   }
   assert(trailSize(newList)==TRAIL_SIZE);
   return newList;
}

void freeTrailList(List myList){
   if(myList==NULL)return;
   free(myList);
   return;
}

void addLocation(List myList,LocationID currLoc){
   assert(myList!=NULL);
   assert(trailSize(myList)==TRAIL_SIZE);
   //create node
   Link newNode=malloc(sizeof(Node));
   newNode->loc=currLoc;
   newNode->next=myList->first;
   //attach node
   myList->first=newNode;
   Link curr=myList->first;
   while(curr->next->next!=NULL){curr=curr->next;}
   //remove last node
   Link toDelete=curr->next;
   curr->next=NULL;
   myList->last=curr;
   free(toDelete);
   assert(trailSize(myList)==TRAIL_SIZE);
}

void showTrail(List myList){
   assert(myList!=NULL);
   assert(trailSize(myList)==TRAIL_SIZE);
   Link curr=myList->first;
   printf("X ->");
   while(curr!=NULL){
      printf(" %d",curr->loc);
      curr=curr->next;
   }
   printf("\n");
}

int lookUpTrail(List myList,LocationID loc){
   assert(myList!=NULL);
   assert(trailSize(myList)==TRAIL_SIZE);
   Link curr=myList->first;
   while(curr!=NULL){
      if(curr->loc==loc)return TRUE;//I have found loc in trail
      curr=curr->next;
   }
   return FALSE;//did not find loc
}

LocationID findLocation(List myList, int index){
   assert(myList!=NULL);
   assert(index<=TRAIL_SIZE);
   assert(trailSize(myList)==TRAIL_SIZE);
   Link curr=myList->first;
   //traverse to index
   int i;
   for (i=index;i!=0;i--){
      curr=curr->next;
   }
   return curr->loc;
}

LocationID *giveLocation(List myList){
   //create array of size 7 (6 for LocationID, 1 for NULL)
   LocationID *trail=malloc(sizeof(LocationID)*(TRAIL_SIZE+1));
   assert(trailSize(myList)==TRAIL_SIZE);
   //traverse trail and add to array
   LocationID i;
   Link curr=myList->first;
   for(i=0;i<TRAIL_SIZE;i++){
      trail[i]=curr->loc;
      curr=curr->next;
   }
   trail[i]=NULL;
   return trail;//return pointer to array
}

