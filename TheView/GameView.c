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
    int nstrings=(strlen(pastPlays))/8;
    int n = 0;
    for (n=0; n < nstrings; n++){
      //set i to be the first index in the 8-char string
      //i.e. 0, 8, 16..
      int i = 8*n;

//==================== Player info =================================
      //find which players' turn, from stringO8[0]
      //here inp is 0, 8, 16..
      PlayerID player;
      switch(pastPlays[i]){
        case 'G': player = PLAYER_LORD_GODALMING; break;
        case 'S': player = PLAYER_DR_SEWARD; break;
        case 'H': player = PLAYER_VAN_HELSING; break;
        case 'M': player = PLAYER_MINA_HARKER; break;
        case 'D': player = PLAYER_DRACULA; break;
      }

      gameView->currentTurn = player;
      //ensure that we are editing the correct player struct
      assert(gameView->players[player].playerId = player);
      
//==================== Location info =================================
      //find location and store as string
      //looking at stringO8[1..2]
      char tmp[3];
      tmp[0] = pastPlays[i+1]; //inp=1, 9, 17..//maybe increment?
      tmp[1] = pastPlays[i+2]; //inp=2, 10, 18..
      tmp[2] = '\0';
      //convert location string to a locationID or NOWHERE
      locationID loc = abbrevToID(tmp);
      
      //for hunter player 
      if (player != PLAYER_DRACULA){
        //check if they are resting, prev loc = curr loc
        if (loc == gameView->players[player].location){
          gameView->players[player].health += 3;
          //maximum hunter health is 9
          if (gameView->players[player].health > 9)
            gameView->players[player].health = 9;
        } else {
          gameView->players[player].location = loc;
        }
        //in either case trail is added to??
        addLocation(gameView->players[player].trail, loc);
      } else {
      //for dracula 
        //if location is not a given/known, places.c returns NOWHERE
        if (loc == NOWHERE){
          //checking only the first index of the location string
          switch(tmp[0]){
            case 'S': //in an unknown sea, loses life
              gameView->players[player].health -= LIFE_LOSS_SEA;
              gameView->players[player].location = SEA_UNKNOWN;
              addLocation(gameView->players[player].trail, SEA_UNKNOWN);
              break;
            case 'T'://teleports to castle dracula, gain life
              gameView->players[player].health += LIFE_GAIN_CASTLE_DRACULA;
              gameView->players[player].location = CASTLE_DRACULA;
              addLocation(gameView->players[player].trail, CASTLE_DRACULA);
              break;
            case 'C'://in an unknown city
              gameView->players[player].location = CITY_UNKNOWN;
              addLocation(gameView->players[player].trail, CITY_UNKNOWN);
              break;
            case 'H'://staying in the same spot 
              gameView->players[player].location = HIDE;
              // not sure addLocation(gameView->players[player].trail, loc);
              break;
            case 'D'://stuff for double back
              //change loc to spot in trail
              //tmp[1] holds n, n=1..5
              //curr loc has not been added to trail yet
              loc=findLocation(gameView->players[player].trail,((int *)tmp[1]-1));
              addLocation(gameView->players[player].trail, loc);
              //needs stuff for sea and his location may now be revealed
              //check this
              break;
          }
        } else {
        //location is valid/known 
          if (isSea(loc) == TRUE){
            gameView->players[player].health -= LIFE_LOSS_SEA;
          }
          gameView->players[player].location = loc;
        }
      }
//==================== Hunter Actions =================================
      if(player!=PLAYER_DRACULA){
         int k;
         for(k=3; k<7;k++){
            switch(pastPlays[i]){
               case 'T':
                  //encountered trap -> changes stats
                  break;
               case 'V':
                  //Immature Vampire encountered
                  break;
               case 'D': 
                  //Dracula confronted 
                  gameView->players[PLAYER_DRACULA].health-=LIFE_LOSS_HUNTER_ENCOUNTER;
                  gameView->players[player].health-=LIFE_LOSS_DRACULA_ENCOUNTER;
                  //does the score change??
                  break;
               case '.':
                  break;
            }
         }
      }else{
//==================== Dracula Actions =================================
      }
      //at end of each round, the score decreases by 1
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
