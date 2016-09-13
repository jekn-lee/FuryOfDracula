// GameView.c ... GameView ADT implementation
//Hi
#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h" //if you decide to use the Map ADT
  
typedef struct _Player {
   PlayerID playerId;
   int health;
   int location;
   int trail[TRAIL_SIZE];
} Player;  

typedef struct _gameView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
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
        newView->players[user].location=0;//Check this
        int i;
        for(i=0; i<TRAIL_SIZE;i++){
            newView->players[user].trail[i]=UNKNOWN_LOCATION;
        }
    }
}
// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    GameView gameView = malloc(sizeof(struct gameView));
    //define initial state
    initialiseGameView(gameView);
    return gameView;
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
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->roundNumber;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->currentTurn;
}

// Get the current score
int getScore(GameView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->score;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->players[player].health;
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->players[player].location;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
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
