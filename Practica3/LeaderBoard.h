#ifndef _LEADERBOARD_H_
#define _LEADERBOARD_H_

#include "checkML.h"
#include "GameObject.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class SDLApp;

struct Score
{
	std::string nick;
	time_t time;
	int score;
};

struct ScoreKey
{
	int score;
	time_t time;
};

struct ScoreComp {
	bool operator()(const ScoreKey& lhs, const ScoreKey& rhs) const
	{
		return (lhs.score > rhs.score || (lhs.score == rhs.score && lhs.time < rhs.time));
	}
};

class LeaderBoard :
	public GameObject
{
private:
	SDLApp* app_;
	std::map<ScoreKey, Score, ScoreComp> scores_;

public:
	LeaderBoard() : GameObject(), app_(nullptr) {}
	LeaderBoard(SDLApp* app, const std::string& filename);
	virtual ~LeaderBoard();

	virtual void render() const;
	virtual void update();

	void load(const std::string& filename);
	void addScore(const std::string& nombre, int points);
	void save(const std::string& filename);
};

#endif // !_LEADERBOARD_H_