// AI
// This is where you build your AI

#include "ai.hpp"


float calc_score(Gameboard board);
void pawn(int i, int j, Gameboard board);
void rook(int i, int j, Gameboard board);
void knight(int i, int j, Gameboard board);
void bishop(int i, int j,Gameboard board);
void queen(int i, int j, Gameboard board);
void king(int i, int j, Gameboard board);
vector<string> move_piece(string move, vector<string> old_board);
bool king_threat(string move, Gameboard board);
void calc_moves(Gameboard board);
bool under_threat(int i, int j);
string TL_ID(Gameboard initial, double timeleft);
string maxChoice(Gameboard initial, int depth);
float min_value(Gameboard initial, int depth);
float max_value(Gameboard initial, int depth);
bool check_mate(Gameboard initial);
vector<string> pos_moves;
vector<string> threat;


vector<string> h{"a","b","c","d","e","f","g","h"};
vector<string> r{"8","7","6","5","4","3","2","1"};
string fen;
Gameboard gameboard;
void get_gameboard(string str);

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add #includes here for your AI.
// <<-- /Creer-Merge: includes -->>

namespace cpp_client
{

namespace chess
{

/// <summary>
/// This returns your AI's name to the game server.
/// Replace the string name.
/// </summary>
/// <returns>The name of your AI.</returns>
std::string AI::get_name() const
{
    // <<-- Creer-Merge: get-name -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // REPLACE WITH YOUR TEAM NAME!
    return "Gorman Pate";
    // <<-- /Creer-Merge: get-name -->>
}

/// <summary>
/// This is automatically called when the game first starts, once the game objects are created
/// </summary>
void AI::start()
{
    // <<-- Creer-Merge: start -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // This is a good place to initialize any variables
    // <<-- /Creer-Merge: start -->>
}

/// <summary>
/// This is automatically called the game (or anything in it) updates
/// </summary>
void AI::game_updated()
{
    // <<-- Creer-Merge: game-updated -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // If a function you call triggers an update this will be called before it returns.
    // <<-- /Creer-Merge: game-updated -->>
}

/// <summary>
/// This is automatically called when the game ends.
/// </summary>
/// <param name="won">true if you won, false otherwise</param>
/// <param name="reason">An explanation for why you either won or lost</param>
void AI::ended(bool won, const std::string& reason)
{
    //<<-- Creer-Merge: ended -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // You can do any cleanup of your AI here.  The program ends when this function returns.
    //<<-- /Creer-Merge: ended -->>
}

/// <summary>
/// This is called every time it is this AI.player's turn to make a move.
/// </summary>
/// <returns>A string in Universal Chess Interface (UCI) or Standard Algebraic Notation (SAN) formatting for the move you want to make. If the move is invalid or not properly formatted you will lose the game.</returns>
std::string AI::make_move()
{
  pos_moves.clear();
  string s = game->fen;
  for(int i =0;i<8;i++)
    gameboard.board[i] = "........";
  get_gameboard(s);
  gameboard.print();

  string best_move = "";
  vector<string> temp = pos_moves;
  vector<string> true_moves;
  char hold = gameboard.team;



  srand((unsigned) time(NULL));


    // <<-- Creer-Merge: makeMove -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // Put your game logic here for make_move here
    // <<-- /Creer-Merge: makeMove -->>


  best_move = TL_ID(gameboard, (player->time_remaining));
  pos_moves.clear();
  calc_moves(gameboard);
  temp = pos_moves;
  int random = rand() % temp.size();
  if((best_move == "") || king_threat(best_move, gameboard) == true)//If the algorithm returns no move then submits a random move
  {
   for(int i =0; i < temp.size();i++)
   {
      pos_moves.clear();
      if((king_threat(temp[i], gameboard) == false))
        true_moves.push_back(temp[i]);
      gameboard.team = hold;

    }


    random = rand() % true_moves.size();
    gameboard.team = hold;
    sort(true_moves.begin(), true_moves.end());
    best_move = true_moves[random];
  }
  cout << "My move = " << best_move << endl;
  pos_moves.clear();
  return best_move;
}



//<<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add additional methods here for your AI to call
//<<-- /Creer-Merge: methods -->>

} // chess

} // cpp_client

void calc_moves(Gameboard board)//Checks board and calls each piece when it gets to that picece that add the next possible moves from the piece
{
  pos_moves.clear();
  char temp;
  for(int i = 0; i <= 7; i++)
  {
    for(int j = 0; j <= 7; j++)
    {
      temp = board.board[i][j];
      temp = toupper(temp);
      switch(temp)
      {
        case 'P':
          pawn(i,j, board);
          break;
        case 'R':
          rook(i,j, board);
          break;
        case 'N':
          knight(i,j, board);
          break;
        case 'B':
          bishop(i,j, board);
          break;
        case 'Q':
          rook(i,j, board);
          bishop(i,j, board);
          break;
        case 'K':
          king(i,j, board);
          break;

      }
    }

  }
}


void get_gameboard(string hold)//Gets all the values froms the fen string and puts them into a game board class
{
  string temp = "";
  int num = 0;
  int str_num = 0;
  int size = hold.size();
  int count = 0;
  char ch;
  while(num < 8)
  {
    ch = hold[str_num];
    if(ch == '/' || ch == ' ')
    {
      num++;
      count = 0;
    }
    else if(isalpha(ch))
    {
      gameboard.board[num][count] = ch;
      count++;
    }
    else
      count = (ch - '0') + count;

    str_num++;
  }
  gameboard.team = hold[str_num];
  str_num = str_num +2;
  while(hold[str_num] != ' ')
  {
    temp = temp + hold[str_num];
    str_num++;
  }
  gameboard.castle = temp;
  temp = "";
  str_num++;
  while(hold[str_num] != ' ')
  {
    temp = temp + hold[str_num];
    str_num++;
  }
  gameboard.enpas = temp;
  str_num++;
  gameboard.halfmove = hold[str_num] - '0';
  str_num = str_num + 2;
  gameboard.fullmove = hold[str_num] - '0';


}

void pawn(int i, int j, Gameboard game_board)//Adds all possible pawn moves to vector string pos_moves
{
  vector<string> board = game_board.board;
  int num = 0;
  vector<string> enpa;

  if(game_board.enpas.length() > 2)
  {
    for(int w = 0; w < (game_board.enpas.length()/2);w++)
    {
      enpa.push_back("");
      for(int n = 0; n< 2;n++)
      {
        enpa[w] = enpa[w] + game_board.enpas[num];
        num++;
      }

    }
  }
  if(game_board.team == 'w' && board[i][j] == 'P')
  {
    if(!(i-1 < 0))
    {
        if(game_board.board[i-1][j] == '.' && (i-1 > 0))
        {
          pos_moves.push_back(h[j]+r[i]+h[j]+r[i-1] );
        }

        else if((game_board.board[i-1][j] == '.') && ((i-1) == 0))
        {
          pos_moves.push_back(h[j]+r[i]+h[j]+r[i-1]+"Q");
          pos_moves.push_back(h[j]+r[i]+h[j]+r[i-1]+"N");
          pos_moves.push_back(h[j]+r[i]+h[j]+r[i-1]+"R");
          pos_moves.push_back(h[j]+r[i]+h[j]+r[i-1]+"B");
        }
        if(!(j-1 < 0))
        {
          if(islower(game_board.board[i-1][j-1]  && ((i-1) == 0)))
          {
            pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i-1]+"Q");
            pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i-1]+"N");
            pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i-1]+"R");
            pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i-1]+"B");
          }
          else if(islower(game_board.board[i-1][j-1]))
            pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i-1]);
        }
        if(!((j+1)>7))
        {
          if(islower(game_board.board[i-1][j+1]  && (i-1) == 0))
          {
            pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i-1]+"Q");
            pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i-1]+"N");
            pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i-1]+"R");
            pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i-1]+"B");
          }
          else if(islower(game_board.board[i-1][j+1]))
            pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i-1]);
        }
        if(i == 6 && board[i-2][j] == '.')
          pos_moves.push_back(h[j]+r[i]+h[j]+r[i-2]);
        for(int w =0; w< enpa.size(); w++)
        {
          if((j+1)<8)
          {
            if((h[j+1]+r[i-1] == enpa[w]))
              pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i-1]);
          }
          if((j-1)>(-1))
          {
            if((h[j-1]+r[i-1] == enpa[w]))
              pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i-1]);
          }
        }
    }

  }
  else if(game_board.team == 'b' && board[i][j] == 'p')
  {
    if(game_board.board[i+1][j] == '.' && (i+1) == 7)
    {
      pos_moves.push_back(h[j]+r[i]+h[j]+r[i+1]+"q");
      pos_moves.push_back(h[j]+r[i]+h[j]+r[i+1]+"n");
      pos_moves.push_back(h[j]+r[i]+h[j]+r[i+1]+"r");
      pos_moves.push_back(h[j]+r[i]+h[j]+r[i+1]+"b");
    }
    else if(game_board.board[i+1][j] == '.')
      pos_moves.push_back(h[j]+r[i]+h[j]+r[i+1]);
    if((j-1) >(-1))
    {
      if(isupper(game_board.board[i+1][j-1]  && (i+1) == 7))
      {
        pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i+1]+"q");
        pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i+1]+"n");
        pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i+1]+"r");
        pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i+1]+"b");
      }
      else if(isupper(game_board.board[i+1][j-1]))
        pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i+1]);
    }
    if((j+1) < 8)
    {
      if(isupper(game_board.board[i+1][j+1]  && (i+1) == 7))
      {
        pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i+1]+"q");
        pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i+1]+"n");
        pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i+1]+"r");
        pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i+1]+"b");
      }
      else if(isupper(game_board.board[i+1][j+1]))
        pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i+1]);
    }
    if(i == 1 && board[i+2][j] == '.')
      pos_moves.push_back(h[j]+r[i]+h[j]+r[i+2]);
    for(int w =0; w< enpa.size(); w++)
    {
      if((j+1)<8)
      {
        if((h[j+1]+r[i+1] == enpa[w]))
          pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i+1]);
      }
      if((j-1)>(-1))
      {
        if((h[j-1]+r[i+1] == enpa[w]))
          pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i+1]);
      }
    }
  }

}

void rook(int i, int j, Gameboard game_board)//Adds all possible rook moves to vector string pos_moves
{
  vector<string> board = game_board.board;
  int n = i+1;
  int s = i-1;
  int e = j+1;
  int l = j-1;


  if(game_board.team == 'w' && ((game_board.board[i][j] == 'R') || board[i][j] == 'Q'))
  {

    for(int w = 0; w < 7;w++)
    {
      if(n+w > 7)
        w=w;
      else if(game_board.board[n+w][j] == '.')
        pos_moves.push_back(h[j]+r[i]+h[j]+r[n+w]);
      else if(islower(game_board.board[n+w][j]))
      {
        pos_moves.push_back(h[j]+r[i]+h[j]+r[n+w]);
        break;
      }
      else
        break;
    }
    for(int w = 0; w < 7;w++)
    {
      if(s-w < 0)
        w=w;
      else if(game_board.board[s-w][j] == '.')
        pos_moves.push_back(h[j]+r[i]+h[j]+r[s-w]);
      else if(islower(game_board.board[s-w][j]))
      {
        pos_moves.push_back(h[j]+r[i]+h[j]+r[s-w]);
        break;
      }
      else
        break;
    }
    for(int w = 0; w < 7;w++)
    {
      if(e+w < 0)
        w=w;
      else if(game_board.board[i][e+w] == '.')
        pos_moves.push_back(h[j]+r[i]+h[e+w]+r[i]);
      else if(islower(game_board.board[i][e+w]))
      {
        pos_moves.push_back(h[j]+r[i]+h[e+w]+r[i]);
        break;
      }
      else
        break;
    }
    for(int w = 0; w < 7;w++)
    {
      if(l-w < 0)
        w=w;
      else if(game_board.board[i][l-w] == '.')
        pos_moves.push_back(h[j]+r[i]+h[l-w]+r[i]);
      else if(islower(game_board.board[i][l-w]))
      {
        pos_moves.push_back(h[j]+r[i]+h[l-w]+r[i]);
        break;
      }
      else
        break;
    }
  }
  else if(game_board.team == 'b' && ((game_board.board[i][j] == 'r') || board[i][j] == 'q'))
  {
    for(int w = 0; w < 7;w++)
    {
      if(n+w > 7)
        w=w;
      else if(game_board.board[n+w][j] == '.')
        pos_moves.push_back(h[j]+r[i]+h[j]+r[n+w]);
      else if(isupper(game_board.board[n+w][j]))
      {
        pos_moves.push_back(h[j]+r[i]+h[j]+r[n+w]);
        break;
      }
      else
        break;
    }
    for(int w = 0; w < 7;w++)
    {
      if(s-w < 0)
        w=w;
      else if(game_board.board[s-w][j] == '.')
        pos_moves.push_back(h[j]+r[i]+h[j]+r[s-w]);
      else if(isupper(game_board.board[s-w][j]))
      {
        pos_moves.push_back(h[j]+r[i]+h[j]+r[s-w]);
        break;
      }
      else
        break;
    }
    for(int w = 0; w < 7;w++)
    {
      if(e+w > 7)
        w=w;
      else if(game_board.board[i][e+w] == '.')
        pos_moves.push_back(h[j]+r[i]+h[e+w]+r[i]);
      else if(isupper(game_board.board[i][e+w]))
      {
        pos_moves.push_back(h[j]+r[i]+h[e+w]+r[i]);
        break;
      }
      else
        break;
    }
    for(int w = 0; w < 7;w++)
    {
      if(l-w < 0)
        w=w;
      else if(game_board.board[i][l-w] == '.')
        pos_moves.push_back(h[j]+r[i]+h[l-w]+r[i]);
      else if(isupper(game_board.board[i][l-w]))
      {
        pos_moves.push_back(h[j]+r[i]+h[l-w]+r[i]);
        break;
      }
      else
        break;
    }
  }
}
void knight(int i, int j, Gameboard game_board)//Adds all possible knight moves to vector string pos_moves
{
  vector<string> board = game_board.board;
  if(game_board.team == 'w' && board[i][j] == 'N')
  {

    if(i-2 < 0 || j-1 < 0)
      i=i;
    else if((game_board.board[i-2][j-1] == '.') || (islower(game_board.board[i-2][j-1])))
      pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i-2]);

    if(i-2 < 0 || j+1 > 7)
      i=i;
    else if(game_board.board[i-2][j+1] == '.' || islower(game_board.board[i-2][j+1]))
      pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i-2]);

    if(i+2 > 7 || j-1 < 0)
      i=i;
    else if(game_board.board[i+2][j-1] == '.' || islower(game_board.board[i+2][j-1]))
      pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i+2]);

    if(i+2 > 7 || j+1 > 7)
      i=i;
    else if(game_board.board[i+2][j+1] == '.' || islower(game_board.board[i+2][j+1]))
      pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i+2]);

    if(i+1 > 7 || j-2 < 0)
      i=i;
    else if(game_board.board[i+1][j-2] == '.' || islower(game_board.board[i+1][j-2]))
      pos_moves.push_back(h[j]+r[i]+h[j-2]+r[i+1]);

    if(i+1 > 7 || j+2 > 7)
      i=i;
    else if(game_board.board[i+1][j+2] == '.' || islower(game_board.board[i+1][j+2]))
      pos_moves.push_back(h[j]+r[i]+h[j+2]+r[i+1]);

    if(i-1 < 0 || j-2 < 0)
      i=i;
    else if(game_board.board[i-1][j-2] == '.' || islower(game_board.board[i-1][j-2]))
      pos_moves.push_back(h[j]+r[i]+h[j-2]+r[i-1]);

    if(i-1 < 0 || j+2 > 7)
      i=i;
    else if(game_board.board[i-1][j+2] == '.' || islower(game_board.board[i-1][j+2]))
      pos_moves.push_back(h[j]+r[i]+h[j+2]+r[i-1]);

  }
  else if(game_board.team == 'b' && board[i][j] == 'n')
  {
    if(i-2 < 0 || j-1 < 0)
      i=i;
    else if(game_board.board[i-2][j-1] == '.' || isupper(game_board.board[i-2][j-1]))
      pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i-2]);

    if(i-2 < 0 || j+1 > 7)
      i=i;
    else if(game_board.board[i-2][j+1] == '.' || isupper(game_board.board[i-2][j+1]))
      pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i-2]);

    if(i+2 > 7 || j-1 < 0)
      i=i;
    else if(game_board.board[i+2][j-1] == '.' || isupper(game_board.board[i+2][j-1]))
      pos_moves.push_back(h[j]+r[i]+h[j-1]+r[i+2]);

    if(i+2 > 7 || j+1 > 7)
      i=i;
    else if(game_board.board[i+2][j+1] == '.' || isupper(game_board.board[i+2][j+1]))
      pos_moves.push_back(h[j]+r[i]+h[j+1]+r[i+2]);

    if(i+1 > 7 || j-2 < 0)
      i=i;
    else if(game_board.board[i+1][j-2] == '.' || isupper(game_board.board[i+1][j-2]))
      pos_moves.push_back(h[j]+r[i]+h[j-2]+r[i+1]);

    if(i+1 > 7 || j+2 > 7)
      i=i;
    else if(game_board.board[i+1][j+2] == '.' || isupper(game_board.board[i+1][j+2]))
      pos_moves.push_back(h[j]+r[i]+h[j+2]+r[i+1]);

    if(i-1 < 0 || j-2 < 0)
      i=i;
    else if(game_board.board[i-1][j-2] == '.' || isupper(game_board.board[i-1][j-2]))
      pos_moves.push_back(h[j]+r[i]+h[j-2]+r[i-1]);

    if(i-1 < 0 || j+2 > 7)
      i=i;
    else if(game_board.board[i-1][j+2] == '.' || isupper(game_board.board[i-1][j+2]))
      pos_moves.push_back(h[j]+r[i]+h[j+2]+r[i-1]);


  }
}
void bishop(int i, int j, Gameboard game_board)//Adds all possible bishop moves to vector string pos_moves
{
  int n = i+1;
  int s = i-1;
  int e = j+1;
  int l = j-1;
  vector<string> board = game_board.board;

  if(game_board.team == 'w' && ((game_board.board[i][j] == 'B') || board[i][j] == 'Q'))
  {

    for(int w = 0; w < 7;w++)
    {
      if(n+w > 7 || e+w > 7)
        w=w;
      else if(game_board.board[n+w][e+w] == '.')
        pos_moves.push_back(h[j]+r[i]+h[e+w]+r[n+w]);
      else if(islower(game_board.board[n+w][e+w]))
      {
        pos_moves.push_back(h[j]+r[i]+h[e+w]+r[n+w]);
        break;
      }
      else
        break;
    }
    for(int w = 0; w < 7;w++)
    {
      if(s-w < 0 || l-w < 0)
        w=w;
      else if(game_board.board[s-w][l-w] == '.')
        pos_moves.push_back(h[j]+r[i]+h[l-w]+r[s-w]);
      else if(islower(game_board.board[s-w][l-w]))
      {
        pos_moves.push_back(h[j]+r[i]+h[l-w]+r[s-w]);
        break;
      }
      else
        break;
    }
    for(int w = 0; w < 7;w++)
    {
      if(e+w > 7 || s-w < 0)
        w=w;
      else if(game_board.board[s-w][e+w] == '.')
        pos_moves.push_back(h[j]+r[i]+h[e+w]+r[s-w]);
      else if(islower(game_board.board[s-w][e+w]))
      {
        pos_moves.push_back(h[j]+r[i]+h[e+w]+r[s-w]);
        break;
      }
      else
        break;
    }
    for(int w = 0; w < 7;w++)
    {
      if(l-w < 0 || n+w > 7)
        w=w;
      else if(game_board.board[n+w][l-w] == '.')
        pos_moves.push_back(h[j]+r[i]+h[l-w]+r[n+w]);
      else if(islower(game_board.board[n+w][l-w]))
      {
        pos_moves.push_back(h[j]+r[i]+h[l-w]+r[n+w]);
        break;
      }
      else
        break;
    }
  }

  else if(game_board.team == 'b' && ((game_board.board[i][j] == 'b') || board[i][j] == 'q'))
  {
    for(int w = 0; w < 7;w++)
    {
      if(n+w > 7 || e+w > 7)
        w=w;
      else if(game_board.board[n+w][e+w] == '.')
        pos_moves.push_back(h[j]+r[i]+h[e+w]+r[n+w]);
      else if(isupper(game_board.board[n+w][e+w]))
      {
        pos_moves.push_back(h[j]+r[i]+h[e+w]+r[n+w]);
        break;
      }
      else
        break;
    }
    for(int w = 0; w < 7;w++)
    {
      if(s-w < 0 || l-w < 0)
        w=w;
      else if(game_board.board[s-w][l-w] == '.')
        pos_moves.push_back(h[j]+r[i]+h[l-w]+r[s-w]);
      else if(isupper(game_board.board[s-w][l-w]))
      {
        pos_moves.push_back(h[j]+r[i]+h[l-w]+r[s-w]);
        break;
      }
      else
        break;
    }
    for(int w = 0; w < 7;w++)
    {
      if(e+w > 7 || s-w < 0)
        w=w;
      else if(game_board.board[s-w][e+w] == '.')
        pos_moves.push_back(h[j]+r[i]+h[e+w]+r[s-w]);
      else if(isupper(game_board.board[s-w][e+w]))
      {
        pos_moves.push_back(h[j]+r[i]+h[e+w]+r[s-w]);
        break;
      }
      else
        break;
    }
    for(int w = 0; w < 7;w++)
    {
      if(l-w < 0 || n+w > 7)
        w=w;
      else if(game_board.board[n+w][l-w] == '.')
        pos_moves.push_back(h[j]+r[i]+h[l-w]+r[n+w]);
      else if(isupper(game_board.board[n+w][l-w]))
      {
        pos_moves.push_back(h[j]+r[i]+h[l-w]+r[n+w]);
        break;
      }
      else
        break;
    }
  }
}

void king(int i, int j, Gameboard game_board)//Adds all possible king moves to pos_moves
{
  vector<string> board = game_board.board;
  if(game_board.team == 'w' && board[i][j] == 'K')
  {
    for(int w =0; w < game_board.castle.length(); w++)
    {
      if(game_board.castle[w] == 'K' && board[7][4] == 'K' && board[7][0] == 'R' && board[7][3] == '.' && board[7][2] == '.')
        pos_moves.push_back("e1b1");
      if(game_board.castle[w] == 'Q' && board[7][4] == 'K' && board[7][7] == 'R' && board[7][5] == '.' && board[7][6] == '.')
        pos_moves.push_back("e1g1");
    }

    for(int n = -1; n < 2; n++)
    {
      for(int w = -1; w < 2; w++)
      {
        if(i+n < 0 || i+n > 7 || j+w<0 || j+w>7)
          w=w;
        else if(game_board.board[i+n][j+w] == '.')
          pos_moves.push_back(h[j]+r[i]+h[j+w]+r[i+n]);
        else if(islower(game_board.board[i+n][j+w]))
          pos_moves.push_back(h[j]+r[i]+h[j+w]+r[i+n]);
      }
    }
  }
  else if(game_board.team == 'b' && board[i][j] == 'k')
  {
    for(int w =0; w < game_board.castle.length(); w++)
    {
      if(game_board.castle[w] == 'k' && board[0][4] == 'k' && board[0][7] == 'r' && board[0][6] == '.' && board[0][5] == '.')
        pos_moves.push_back("e8g1");
      if(game_board.castle[w] == 'q' && board[0][4] == 'k' && board[0][0] == 'r' && board[0][2] == '.' && board[0][3] == '.')
        pos_moves.push_back("e8b1");
    }
    for(int n = -1; n < 2; n++)
    {
      for(int w = -1; w < 2; w++)
      {
        if(i+n < 0 || i+n > 7 || j+w<0 || j+w>7)
          w=w;
        else if(game_board.board[i+n][j+w] == '.')
          pos_moves.push_back(h[j]+r[i]+h[j+w]+r[i+n]);
        else if(isupper(game_board.board[i+n][j+w]))
          pos_moves.push_back(h[j]+r[i]+h[j+w]+r[i+n]);
      }
    }
  }
}

bool king_threat(string move, Gameboard board)//Checks if move makes king under threat
{
  Gameboard copy;
  copy.board = board.board;
  copy.team = board.team;
  copy.castle = board.castle;
  copy.enpas = board.enpas;
  copy.halfmove = board.halfmove;
  copy.fullmove = board.fullmove;
  copy.board = board.board;
  string str_x;
  string str_y;
  int x;
  int y;

  copy.board = move_piece(move, board.board);

  if(board.team == 'b')
    copy.team = 'w';
  else
    copy.team = 'b';
  pos_moves.clear();
  calc_moves(copy);
  for(int i = 0; i < pos_moves.size();i++)
  {

    str_x = pos_moves[i][2];
    str_y = pos_moves[i][3];
    for(int i =0; i < 8; i++)
    {
      if(str_x == h[i])
        x = i;
      if(str_y == r[i])
        y = i;
    }

    if(copy.board[y][x] == 'k' || copy.board[y][x] == 'K')
      return true;
  }
  pos_moves.clear();
  return false;




}



vector<string> move_piece(string move, vector<string> old_board)//Actually moves a piece using the old gameboard a new gameboard and the move
{
  vector<string> copy;
  char hold;
  string str_x;
  string str_y;
  int x;
  int y;
  int n;
  int m;
  bool king;

  copy = old_board;
  str_x = move[2];
  str_y = move[3];

  for(int i =0; i < 8; i++)
  {
    if(str_x == h[i])
      x = i;
    if(str_y == r[i])
      y = i;
  }
  str_x = move[0];
  str_y = move[1];

  for(int i =0; i < 8; i++)
  {
    if(str_x == h[i])
      n = i;
    if(str_y == r[i])
      m = i;
  }


  hold = old_board[m][n];
  copy[m][n] = '.';
  copy[y][x] = hold;
  return copy;


}

float calc_score(Gameboard board)// Calculates the Score of the gameboard
{
  bool alive = false;
  char temp;
  temp = board.team;
  float score = 0;
  string hold;
  threat.clear();
  pos_moves.clear();
  calc_moves(board);
  for(int i = 0; i < pos_moves.size(); i++)
  {
    hold = "";
    hold += pos_moves[i][2];
    hold += pos_moves[i][3];
    threat.push_back(hold);
  }

  if(temp == 'w')
    board.team ='b';
  else
    board.team = 'w';
  pos_moves.clear();
  calc_moves(board);

  board.team = temp;

  for(int i = 0; i < pos_moves.size(); i++)
  {
    hold = "";
    hold += pos_moves[i][2];
    hold += pos_moves[i][3];
    threat.push_back(hold);
  }



  for(int i = 0; i <= 7; i++)
  {
    for(int j = 0; j <= 7; j++)
    {
      temp = board.board[i][j];
      if(board.team == 'w')
      {
        if(((i == 3) || (i == 4)) && ((j >=3) &&  (j<=4)) && temp != 'K' && temp != 'k' && temp != '.')
          score+=0.5;
        else if((((i == 3) || (i == 4)) && ((j >=1) &&  (j<=6))) && temp != '.' && temp != 'K' && temp != 'k')
          score+=0.25;
        switch(temp)
        {
          case 'P':
            score++;
            if(under_threat(i, j))
              score-=0.5;
            break;
          case 'R':
            score+=5;
            if(under_threat(i, j))
              score-=2.5;
            break;
          case 'N':
            score+=3;
            if(under_threat(i, j))
              score-=1.5;
            break;
          case 'B':
            score+=3;
            if(under_threat(i, j))
              score-=1.5;
            break;
          case 'Q':
            score+=9;
            if(under_threat(i, j))
              score-=4.5;
            break;
          case 'K':
            alive = true;
            if(under_threat(i,j))
              score-=100;
              break;
          case 'p':
            score-=1;
            if(under_threat(i, j))
              score+=0.5;
            break;
          case 'r':
            score-=5;
            if(under_threat(i, j))
              score+=2.5;
            break;
          case 'n':
            score-=3;
            if(under_threat(i, j))
              score+=1.5;
            break;
          case 'b':
            score-=3;
            if(under_threat(i, j))
              score+=1.5;
            break;
          case 'q':
            score-=9;
            if(under_threat(i, j))
              score+=4.5;
            break;
          case 'k':
            if(under_threat(i,j))
              score+=0.5;
              break;

        }
      }
      else
      {
        if(((i == 3) || (i == 4)) && ((j >=3) &&  (j<=4)) && temp != 'K' && temp != 'k' && temp != '.')
          score+=0.5;
        else if((((i == 3) || (i == 4)) && ((j >=1) &&  (j<=6))) && temp != '.')
          score+=0.25;
        switch(temp)
        {
          case 'P':
            score-=1;
            if(under_threat(i, j))
              score+=0.5;
            break;
          case 'R':
            score-=5;
            if(under_threat(i, j))
              score+=2.5;
            break;
          case 'N':
            score-=3;
            if(under_threat(i, j))
              score+=1.5;
            break;
          case 'B':
            score-=3;
            if(under_threat(i, j))
              score+=1.5;
            break;
          case 'Q':
            score-=9;
            if(under_threat(i, j))
              score+=4.5;
            break;
          case 'K':
            if(under_threat(i,j))
              score+=0.5;
              break;
          case 'p':
            score+=1;
            if(under_threat(i, j))
              score-=0.5;
            break;
          case 'r':
            score+=5;
            if(under_threat(i, j))
              score-=2.5;
            break;
          case 'n':
            score+=3;
            if(under_threat(i, j))
              score-=1.5;
            break;
          case 'b':
            score+=3;
            if(under_threat(i, j))
              score-=1.5;
            break;
          case 'q':
            score+=9;
            if(under_threat(i, j))
              score-=4.5;
            break;
          case 'k':
            alive = true;
            if(under_threat(i,j))
              score-=100;
        }
      }

    }

  }
  if(alive == false)
    score-=100;

  return score;
}


bool under_threat(int x, int y)//Checks if the current piece can be taken
{
  string hold = "";
  hold = h[y] + r[x];
  for(int i =0; i < threat.size();i++)
  {

    if(hold == threat[i]){
      return true;

    }
  }
  return false;

}


string TL_ID(Gameboard initial, double timeleft )// TIME LIMITED INTERAIVE DEEPING---------------------------
{



  float systime = time(NULL);
  float timeSize = timeleft * 0.05;
  float timeTurn = systime + timeSize ;
  string best_move = "";

  int depth =0;
  float t = time(NULL);
  while(t < systime+(timeTurn *0.5) && depth < 5)
  {
    best_move = maxChoice(initial, depth);
    depth++;
    t = time(NULL);

  }
  return best_move;

}

string maxChoice(Gameboard initial, int depth) //Depth Limited MINI MAX
{
  int num = 0;
  Gameboard copy;
  vector<string> temp;
  string best_move = "";
  float score;
  int max = -100;

  copy.board = initial.board;
  copy.team = initial.team;
  copy.castle = initial.castle;
  copy.enpas = initial.enpas;
  copy.halfmove = initial.halfmove;
  copy.fullmove = initial.fullmove;
  copy.board = initial.board;
  pos_moves.clear();
  calc_moves(initial);
  temp = pos_moves;

  for(int i =0; i < temp.size();i++)
  {
    if(king_threat(temp[i], initial) == false)
    {
      copy.board = move_piece(temp[i], initial.board);
      score = min_value(copy, depth-1);
      if(score > max)
      {
        max = score;
        num = i;
      }

    }

  }
  best_move = temp[num];
  cout << best_move <<  " " << max << endl;
  return best_move;
}


float min_value(Gameboard initial, int depth)//MIN PART OF MINIMAX Gets the min value from the list of moves
{
  Gameboard copy;
  float min = 100;
  float score;
  vector<string> temp;

  copy.board = initial.board;
  copy.team = initial.team;
  copy.castle = initial.castle;
  copy.enpas = initial.enpas;
  copy.halfmove = initial.halfmove;
  copy.fullmove = initial.fullmove;
  copy.board = initial.board;
  if(check_mate(initial))
    return -100;


  if(depth <= 0)
  {
    return calc_score(initial);
  }
  pos_moves.clear();
  if(initial.team == 'w')
    initial.team ='b';
  else
    initial.team = 'w';
  calc_moves(initial);
  temp = pos_moves;

  for(int i =0; i < temp[i].size();i++)
  {
    copy.board = move_piece(temp[i], initial.board);
    score = max_value(copy, depth);
    if(score < min)
      min = score;
  }
  return min;
}

float max_value(Gameboard initial, int depth)
{

  Gameboard copy;
  float max = -100;
  float score =0;
  vector<string> temp;

  copy.board = initial.board;
  copy.team = initial.team;
  copy.castle = initial.castle;
  copy.enpas = initial.enpas;
  copy.halfmove = initial.halfmove;
  copy.fullmove = initial.fullmove;
  copy.board = initial.board;

  if(check_mate(initial))
    return 100;
  if(depth <= 0)
  {
    return calc_score(initial);
  }
  if(initial.team == 'w')
    initial.team ='b';
  else
    initial.team = 'w';
  pos_moves.clear();
  calc_moves(initial);
  temp = pos_moves;
  for(int i =0; i < temp[i].size();i++)
  {
    copy.board = move_piece(temp[i], initial.board);

    score = min_value(copy, depth-1);
    if(score > max)
      max = score;
  }
  return max;

}

bool check_mate(Gameboard board)
{

  vector<string> true_moves;
  vector<string> temp;
  string move;
  char team = board.team;


  calc_score(board);
  temp = pos_moves;



  for(int i =0; i < temp.size();i++)
  {
    if((king_threat(temp[i], board) == false))
      true_moves.push_back(temp[i]);
    board.team = team;

  }
  if(true_moves.empty())
    return true;
  return false;

}

