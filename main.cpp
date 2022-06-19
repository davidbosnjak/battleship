#include <iostream>
#include <vector>

using namespace std;
void printGraphic(vector<vector<char>> &grid){
  for(int i =0; i<grid.size(); i++){
    for(int j=0; j<grid[0].size(); j++){
      cout<<grid[i][j]<<" ";
    }
    cout<<endl;
  }
}
void printGrid(vector<vector<int>> &grid){
  for(int i =0; i<grid.size();i++){
    for(int j=0; j<grid[0].size();j++){
      cout<<grid[i][j]<<" ";
    }
    cout<<endl;
  }
}

bool hitTarget(vector<vector<int>> &grid, int locationY, int locationX, vector<vector<char>> &graphic){
  if(grid[locationY][locationX] ==1){
    cout<<locationX<<","<<locationY<<" is a HIT"<<endl;
    grid[locationY][locationX]=0;
    graphic[locationY][locationX]='X';
    return true;
  }
  else{
    cout<<"MISS"<<endl;
    graphic[locationY][locationX]='O';
    return false;
  }
}
void clearScreen(){
  int numberOfLines =100;
  while(numberOfLines--){
    cout<<endl;
  }
}
bool addShip(vector<vector<int>> &grid, int locationX, int locationY,int length, char orientation){
  int gridSize = 8;
  if(orientation =='v'){
    if(locationX+length>gridSize-1){
      return false;
    }
    else{
      for(int i =0; i<length; i++){
        if(grid[locationX+i][locationY]==1){
          return false;
        }
        grid[locationX+i][locationY]=1;
      }
    }
  }
  else{
    if(locationY+length>gridSize-1){
      return false;
    }
    else{
      for(int i =0; i<length; i++){
        if(grid[locationX][locationY+i]==1){
          return false;
        }
        grid[locationX][locationY+i]=1;
      }
    }
  }
  
  return true;
}
int gameLoop(){
   //declaring both players grids
  int gameGridLength=8;
  vector<vector<int>> grid1(gameGridLength,vector<int>(gameGridLength,0));
  vector<vector<int>> grid2(gameGridLength,vector<int>(gameGridLength,0));
  vector<vector<char>> grid1Graphics(gameGridLength,vector<char>(gameGridLength,'?'));
  vector<vector<char>> grid2Graphics(gameGridLength,vector<char>(gameGridLength,'?'));
  //adding ships onto grid
  int shipAmount = 3;
  int tempShipAmount = shipAmount;
  int shipLength =2;
  while(tempShipAmount--){
    int ax,ay,bx,by;
    char ao, bo;
    cout<<"player 1 please add a ship of length: "<<shipLength<<endl<<"x cord y cord rotation (v for vertical h for horizontal)"<<endl;
    cin>>ax;
    cin>>ay;
    cin>>ao;
    bool check =addShip(grid1,ay,ax,shipLength,ao);

    if(!check){
      cout<<"ADD SHIP ERROR: dont put a ship where one already is"<<endl; 
      return 0;
      }
    clearScreen();
    cout<<"player 2 please add a ship of length "<<shipLength<<endl<<"x cord, y cord, rotation (v for vertical h for horizonal"<<endl;
    cin>>bx;
    cin>>by;
    
    cin>>bo;
    bool check2 =addShip(grid2, by,bx,shipLength,bo);
    if(!check2){
      cout<<"ADD SHIP ERROR: dont put a ship where one already is"<<endl;
      return 0;
      }
    clearScreen();
    shipLength++;
    
  }
  bool winner= false;
  cout<<"player 1's grid"<<endl;
  printGrid(grid1);
  cout<<endl<<"player 2's grid"<<endl;
  printGrid(grid2);

  int playerWinner;
  int playerOneCount = shipAmount*3;
  int playerTwoCount = shipAmount*3;
  //while no one has won yet keeping repeating turns until someone wins the game
  
  while(!winner){
      
    int guessAX, guessAY, guessBX, guessBY;
    cout<<"player 1 please guess cordinates"<<endl;
    cin>>guessAX;
    cin>>guessAY;
    bool isHit =hitTarget(grid2, guessAX, guessAY, grid1Graphics);
    if(isHit){cout<<"should be a hit "<<playerTwoCount<<" ships remaining"<<endl;playerTwoCount--;}
    if(playerTwoCount ==0) {
      playerWinner =1;
      break;
     }
    printGraphic(grid1Graphics);
    cout<<"player 2 please guess cordinates"<<endl;
    cin>>guessBX;
    cin>>guessBY;
    bool isHit2 = hitTarget(grid1, guessBX, guessBY, grid2Graphics);
    if(isHit2)playerOneCount--;
    if(playerOneCount ==0){
      playerWinner=2;
       break;
      }
    printGraphic(grid2Graphics);
  
}
//winner declaration
  cout<<"Player "<<playerWinner<<" wins! Congratulations!\nPress enter to continue"<<endl;
  
  return 0;
}
int main() {
  bool playAgain =true;
  char decision;
  while(playAgain){
    gameLoop();
    cout<<"Do you wish to play again? y/n"<<endl;
    cin>>decision;
    if(decision =='n') playAgain =false;
  }
  return 0;
}