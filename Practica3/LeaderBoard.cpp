#include "LeaderBoard.h"

#include "SDLApp.h"
#include "Texture.h"

LeaderBoard::LeaderBoard(SDLApp* app, const std::string& filename) : GameObject(), app_(app)
{
	load(filename);
}

LeaderBoard::~LeaderBoard()
{
}

void LeaderBoard::render() const
{
	int i = 0;
	for (auto& s : scores_)
	{
		if (i == 10)
			break;

		std::string output;

		output = s.second.nick + ' ' + std::to_string(s.second.score);

		Texture* t = new Texture(app_->getRenderer());
		t->loadFont(output, app_->getFont("PAINT22"), { 0, 0, 0, 255 });
		int w, h;
		app_->getFont("PAINT22")->getSizeOfText(output, w, h);
		t->render({ (WIN_WIDTH - w) / 2, 130 + (h * i), w, h });

		delete t;
		t = nullptr;
		i++;
	}
}

void LeaderBoard::update()
{
}

void LeaderBoard::load(const std::string& filename)
{
	std::string name;
	int points; time_t t;

	std::ifstream file;

	file.open(filename);

	while (!file.fail())
	{
		file >> name >> t >> points;

		scores_[ScoreKey{ points,t }] = Score{ name,t,points };
	}
	file.close();
}

void LeaderBoard::addScore(const std::string& nombre, int points)
{
	time_t currentTime = time(nullptr);
	scores_[ScoreKey{ points, currentTime }] = Score{ nombre, currentTime, points };
}

void LeaderBoard::save(const std::string& filename)
{
	std::ofstream file;
	file.open(filename);

	if (file.is_open())
	{
		for (auto& s : scores_)
			file << s.second.nick << " "
			<< s.second.time << " " << s.second.score << "\n";
	}
	file.close();
}
