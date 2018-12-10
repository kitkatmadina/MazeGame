// implementation of MazeGame functions

#include "MazeGame.h"

MazeGame::MazeGame(string filename)
{
  save_out.open(out_name);
  ifstream in;
  in.open(filename);
  if (!in) {
    cerr << "Wrong maze tiles file: " + filename << endl;
    throw IncorrectFile();
  }
  save_out << "Maze tiles file: " << filename << endl << endl;
  in >> maze;
}

MazeGame::~MazeGame()
{
  save_out.close();
}

void MazeGame::start_game(istream & is)
{  // implement this function
  for (int i = 0; i < maze.get_tiles().size(); i++) { // for each row in the maze
	  for (int j = 0; j < maze.get_tiles()[i].size(); j++) { // for each tile in row
		if (maze.get_tiles()[i][j]->tile_char == 'S'){// if its a starting tile 
			Position pos = Position(i,j);
			MazePlayer* player = new MazePlayer(pos);
			this ->players.push_back(player);
		}
	}
  }
  print_maze();
  update_loop(is);
}

// Important: if you use cout << something
// do the same with save_out << something
// Otherwise, the file output.txt would be incorrect
void MazeGame::update_loop(istream & is)
{
  bool again = true;
  int pnum = 0; // player's number
  for(auto player : players) {
    pnum++;
	cout << "player " << pnum << " position: " << player->get_position()<<endl;
	save_out << player->get_position()<<endl;
	save_out << "Move #: " << player->move_number() <<endl;
	string s;
	cin >> s;
	if (maze.can_move_to_tile(player->take_turn(s))==true) {
		player->set_position(player->take_turn(s));
		if (maze.is_tile_end(player->get_position())==true) {
			again = false;
			cout << "Player " << pnum << " won!" << endl;
			return;
		}
	}
	else if (maze.can_move_to_tile(player->take_turn(s)) == false) {
		while (maze.can_move_to_tile(player->take_turn(s)) == false) {
			cout << "Oops! You cannot move in this direction! Please try again." << endl;
			cin >> s;
		}
		if (maze.can_move_to_tile(player->take_turn(s)) == true) {
			player->set_position(player->take_turn(s));
			if (maze.is_tile_end(player->get_position()) == true) {
				again = false;
				cout << "Player " << pnum << " won!" << endl;
				return;
			}
		}
	}
	
	print_maze();
  }
  update_loop(is);
}

void MazeGame::print_maze()
{
  vector<string> grid;
  for(auto row : maze.get_tiles()) {
    string tiles = "";
    for(auto t : row) 
      tiles += t->tile_char;

    grid.push_back(tiles);
  }

  for(auto player : players)
    grid[player->get_position().row][player->get_position().col] = 'P';

  cout << " ";
  save_out << " ";
  
  for(int i = 0; i < grid[0].size(); i++) {
    cout << i;
    save_out << i;
  }

  cout << endl;
  save_out << endl;
  
  for(int i = 0; i < grid.size(); i++) {
    cout << i << grid[i] << endl;
    save_out << i << grid[i] << endl;
  }
}

