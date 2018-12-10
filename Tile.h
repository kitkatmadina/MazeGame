#ifndef TILE_H
#define TILE_H

#include <iostream>

using namespace std;

class Tile
{
public:
  char tile_char = '_';

public:
  virtual bool try_walk() { return false;}

  virtual bool is_start() {return false;}

  virtual bool is_end() { return false; }
};

class WallTile : public Tile
{
public:
	WallTile() { tile_char = 'W'; }
};

class EmptyTile : public Tile
{
public:
	EmptyTile() { tile_char = 'X'; }

public:
	virtual bool try_walk() {return true;}	
};

class StartingTile : public EmptyTile
{
public:
	StartingTile() { tile_char = 'S'; }

public:

	virtual bool is_start() {return true;}
};

class EndingTile : public EmptyTile
{
public:
	EndingTile() { tile_char = 'E'; }

public:
	virtual bool try_walk() {return true;}

	virtual bool is_end() {return true;}
};

ostream & operator << (ostream &out, const Tile &t);
istream & operator >> (istream &in,  Tile *&t);

#endif
