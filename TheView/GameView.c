// GameView.c ... GameView ADT implementation
//Hi
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h" //if you decide to use the Map ADT
#include "TrailLinkedList.h"
  
typedef struct _Player {
   PlayerID playerId;
   //can be used for extra check
   //making sure we are in the correct player info
   int health;
   int location;
   List trail;
} Player;  

typedef struct gameView {
    PlayerID currentTurn;
    Round roundNumber;
    int score;
    Player players[NUM_PLAYERS];
    Map europe;
} gameView;
  
static void initialiseGameView(GameView newView)
{
    //set up general information
    newView->currentTurn=0;//Check this
    newView->roundNumber=0;//Check this
    newView->score=GAME_START_SCORE;
    newView->europe=newMap();
    //set up player information
    PlayerID user;
    for (user=PLAYER_LORD_GODALMING; user<NUM_PLAYERS;user++){
        newView->players[user].playerId=user;
        if(user==PLAYER_DRACULA){
           newView->players[user].health=GAME_START_BLOOD_POINTS;
        }else{
           newView->players[user].health=GAME_START_HUNTER_LIFE_POINTS;
        }
        newView->players[user].location=0;//Check this - i think 0 means they're in the Adriatic Sea
        newView->players[user].trail=newTrail();//fills list with UNKNOWN
    }
}
// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    GameView gameView = malloc(sizeof(struct gameView));
    //define initial state
    initialiseGameView(gameView);
    //go through string 8 characters at a time
    int nstrings=(strlen(pastPlays) - 1)/8;
    int n = 0;
    for (n=0; n < nstrings; n++){
      int i = 8*n;

      //find which players' turn
      PlayerID player;
      switch(pastPlays[i]){
        case 'G': player = PLAYER_LORD_GODALMING; break;
        case 'S': player = PLAYER_DR_SEWARD; break;
        case 'H': player = PLAYER_VAN_HELSING; break;
        case 'M': player = PLAYER_MINA_HARKER; break;
        case 'D': player = PLAYER_DRACULA; break;
      }

      gameView->currentTurn = player;
      gameView->players[player].playerId = player;

      //find location
      char tmp[3];
      tmp[0] = pastPlays[i+1]; //maybe increment?
      tmp[1] = pastPlays[i+2];
      tmp[2] = '\0';
      locationID loc = abbrevToID(tmp);
      
      //addLocation(gameView->players[player].trail, loc);
      
      if (player != PLAYER_DRACULA){
        if (loc == gameView->players[player].location){
          gameView->players[player].health += 3;
          if (gameView->players[player].health > 9)
            gameView->players[player].health = 9;
        } else {
          gameView->players[player].location = loc;
        }
      } else {
        //stuff for dracula
        //if location is not a city
        if (loc == NOWHERE){
          switch(tmp[0]){
            case 'S':
              gameView->players[player].health -= LIFE_LOSS_SEA;
              gameView->players[player].location = SEA_UNKNOWN;
              break;
            case 'T':
              gameView->players[player].health += LIFE_GAIN_CASTLE_DRACULA;
              gameView->players[player].location = CASTLE_DRACULA;
              break;
            case 'C':
              gameView->players[player].location = CITY_UNKNOWN;
            case 'H':
              gameView->players[player].location = HIDE;
            case 'D':
              //stuff for double back
          }
        } else {
          if (isSea(loc) == TRUE)
            gameView->players[player].health -= LIFE_LOSS_SEA;
          gameView->players[player].location = loc;
        }
      }

      if (player == PLAYER_DRACULA){
        gameView->score--;
        gameView->roundNumber++;
      }
    }
}
     
     
// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted)
{
    //COMPLETE THIS IMPLEMENTATION
    free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round getRound(GameView currentView)
{
    assert(currentView!=NULL);
    return currentView->roundNumber;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
    assert(currentView!=NULL);
    return currentView->currentTurn;
}

// Get the current score
int getScore(GameView currentView)
{
    assert(currentView!=NULL);
    return currentView->score;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
    assert(currentView!=NULL);
    return currentView->players[player].health;
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
    assert(currentView!=NULL);
    //could use findLocation(currentView->players[player].trail, 0);
    return currentView->players[player].location;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    Link myTrail=currentView->players[player].trail;
    int i;
    for(i=0;i<TRAIL_SIZE;i++){
        trail[i]=findLocation(myTrail,i);
    }
}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

LocationID *connectedLocations(GameView currentView, int *numLocations,
                               LocationID from, PlayerID player, Round round,
                               int road, int rail, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return NULL;
}
