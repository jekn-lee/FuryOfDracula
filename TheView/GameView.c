// GameView.c ... GameView ADT implementation
//Hi
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h" //if you decide to use the Map ADT
  
typedef struct _Player {
   //PlayerID playerId;
   int health;
   int location;
   int trail[TRAIL_SIZE];
} Player;  

typedef struct gameView {
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
        newView->players[user].location=0;//Check this - i think 0 means they're in the Adriatic Sea
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
    //go through string 8 characters at a time

    int nstrings=strlen(pastPlays)/8;
    int n = 0;
    for (n=0; n < nstrings; n++){
      printf("it is player %d turn\n", gameView->currentTurn);
      int i = 8*n;

      //find which player's turn
      PlayerID player;
      switch(pastPlays[i]){
        case 'G': player = PLAYER_LORD_GODALMING; break;
        case 'S': player = PLAYER_DR_SEWARD; break;
        case 'H': player = PLAYER_VAN_HELSING; break;
        case 'M': player = PLAYER_MINA_HARKER; break;
        case 'D': player = PLAYER_DRACULA; break;
      }

      //find location
      char tmp[3];
      tmp[0] = pastPlays[i+1]; //maybe increment?
      tmp[1] = pastPlays[i+2];
      tmp[2] = '\0';
      LocationID loc = abbrevToID(tmp);

      //stuff for hunters
      if (player != PLAYER_DRACULA){
        if (loc == gameView->players[player].location){
          //get health if they are in the same location
          //check that health doesn't exceed 9
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
              break;
            case 'H':
              gameView->players[player].location = HIDE;
              break;
            case 'D':
              //stuff for double back
              break;
          }
        } else {
          if (isSea(loc) == TRUE){
            gameView->players[player].health -= LIFE_LOSS_SEA;
          }
          gameView->players[player].location = loc;
        }
      }

      if (player == PLAYER_DRACULA){
        gameView->score--;
        gameView->roundNumber++;
        gameView->currentTurn = PLAYER_LORD_GODALMING;
      } else {
        gameView->currentTurn++;
      }

      printf("it is player %d turn\n", gameView->currentTurn);
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
