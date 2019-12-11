#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#include "checkML.h"
#include "GameObject.h"
#include <fstream>
#include <vector>
#include <algorithm>

class SDLApp;

class ScoreBoard :
	public GameObject
{
private:
	SDLApp* app_;

	int score_;
	int numArrows_;

public:
	ScoreBoard();
	ScoreBoard(SDLApp* app);
	virtual ~ScoreBoard();

	virtual void render() const;
	virtual void update();

	int getScore() { return score_; }
	void setScore(int score) { score_ = score; }

	int getNumArrows() { return numArrows_; }
	void setNumArrows(int nArrows) { numArrows_ = nArrows; }
	void addArrow() { numArrows_++; }
	void useArrow() { numArrows_--; }

};

#endif // !_SCOREBOARD_H_