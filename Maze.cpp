#include "Maze.h"
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool Maze::can_move_to_tile(Position pos)
{
  // implement this function
  if (pos.row >= 0 && pos.col >= 0 && pos.row < get_tiles().size() && pos.col < get_tiles()[0].size()) {
	  if (get_tiles()[pos.row][pos.col]->try_walk())
		  return true;
  }
  else {
	  return false;
  }
}

bool Maze::is_tile_end(Position pos)
{
  return tiles[pos.row][pos.col]->is_end();
}

// print a maze
ostream & operator << (ostream &out, Maze &m)
{
  for(auto row : m.get_tiles()) {
    for(auto t : row)
      out << *t;
    
    out << endl;
  }

  return out;
}

// read in a maze from input
istream & operator >> (istream &in,  Maze &m)
{
  string row; 
  while(getline(in, row)) {
    
    //stringstream ss(row);
    vector<Tile*> tile_row;
    Tile* t;
    //while(ss >> t) tile_row.push_back(t);
	cout << row << endl;
	for (int i = 0; i < row.length(); i++) {
		switch (row[i]) {
		case 'W': t = new WallTile(); break;
		case 'S': t = new StartingTile(); break;
		case 'X': t = new EmptyTile(); break;
		case 'E': t = new EndingTile(); break;
		}
		tile_row.push_back(t);
		i++;
	}
    m.get_tiles().push_back(tile_row);
  }

  
  return in;
}
