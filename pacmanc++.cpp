#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

# define MAP_WIDTH 40
# define MAP_HEIGHT 20
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
bool GameOver = false;
bool Win = false;
bool Quit = false;
char request{};
int level{1};

int score{0};
int x_pos{ 21 };
int y_pos{ 17 };

char map[MAP_HEIGHT][MAP_WIDTH]; 
int reward[MAP_HEIGHT][MAP_WIDTH];

int current_input{};
string input_mapchoice{};
int map_choice{};

int Leaderboard_print_request{0};


string player_name;
vector<string>player_bucket;
int player_number{ 1 };
size_t player_id{ 1 };
vector<int>player_score;
vector<int>player_playtime;
vector<int>player_bestscore;
void player_arrow_image();

void pacman_intro() {
	
	cout << "_________________\t_________________\t_________________\t_________________\t_________________" << endl;
	cout << "|\t\t|\t|\t\t|\t|\t\t\t|\t|\t|\t|\t\t|" << endl;
	cout << "|\t\t|\t|\t\t|\t|\t\t\t|\t|\t|\t|\t\t|" << endl;
	cout << "|\t\t|\t|\t\t|\t|\t\t\t|\t|\t|\t|\t\t|" << endl;
	cout << "|\t\t|\t|\t\t|\t|\t\t\t|\t|\t|\t|\t\t|" << endl;
	cout << "|\t\t|\t|\t\t|\t|\t\t\t|\t|\t|\t|\t\t|" << endl;
	cout << "-----------------\t|---------------|\t|\t\t\t|\t|\t|\t|---------------|" << endl;
	cout << "|\t\t\t|\t\t|\t|\t\t\t|\t|\t|\t|\t\t|" << endl;
	cout << "|\t\t\t|\t\t|\t|\t\t\t|\t|\t|\t|\t\t|" << endl;
	cout << "|\t\t\t|\t\t|\t|\t\t\t|\t|\t|\t|\t\t|" << endl;
	cout << "|\t\t\t|\t\t|\t|\t\t\t|\t|\t|\t|\t\t|" << endl;
	cout << "|\t\t\t|\t\t|\t|\t\t\t|\t|\t|\t|\t\t|" << endl;
	cout<<"\t\t\t\t\t\t-----------------" << endl;
	cout << endl;
	cout << "***Please maximize the game window for optimum game experience,tq.***"<<endl;
	cout << endl;
	cout << "Welcome to the PACMAN HEHEHE gameee...." << endl<<endl;
	cout << "Here is the rule....." << endl;
	cout << "------------------------------------<" << endl;
	cout << fixed << setw(10) << "Rule" << endl;
	cout << "------------------------------------<" << endl;
	cout << "Remember to eat all of the N to win the game!" << endl<<endl;
	Sleep(800);
	cout << "eat N = 20 marks , eat . = 1 mark, eat all of the N to win the game..." << endl<<endl;
	Sleep(800);
	cout << "level 1 have 2 ghost ,level 2 will increase by 1 ghost and level 3 will increase by 2 ghost..." << endl<<endl;
	Sleep(800);
	cout << "And you can choose 3 map later with different map difficulty hehehe" << endl<<endl;
	Sleep(800);
	cout << "Good Luck at all,please enjoy PACMA *N* game. " << endl<<endl;
	Sleep(800);
	cout << "Please enter your name: ";
	getline(cin,player_name);
	cout << endl;
	cout << player_name << " has been registered..." << endl << endl;
	player_bucket.push_back(player_name);
	player_score.push_back(0);
	player_playtime.push_back(0);
	player_bestscore.push_back(0);

	while (true) {
		cout << "Please pick your map level: easy (1) , intermediate (2) , hardcore (3)" << endl;
		getline(std::cin, input_mapchoice);
		stringstream ss(input_mapchoice);     //convert input string to integer
		if (ss >> map_choice && (map_choice ==1 ||map_choice ==2 || map_choice ==3)) {    //ss>>map_choice extract an integer and strore into map_choice
			break;
		}
		else {
			cout << "Please retry again...." << endl;
		}
	}  
	
}

class read_file {
private:
	string file_name;
public:
	read_file(string name )
		:file_name(name) {}

	void open_file() {
		string content;
		ifstream file(file_name);
		int rows{ 0 };
		int columns{ 0 };
		int columns_space{ 0 };

		if (file.is_open()) {
			while (getline(file, content)) {
				for (auto cont : content) {
					map[rows][columns] = cont;
					cout << map[rows][columns];
					++columns;
					cout << " ";
				}
				cout << "\n";
				columns = 0;
				++rows;
			}
		}
		else {
			cout << "File is not open or cannot be found." << '\n';
		}
	}
};

void draw_map() {
	COORD cursor_position;
	cursor_position.X = 0;
	cursor_position.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_position);

	for (int j = 0; j < MAP_HEIGHT; ++j) {
		for (int i = 0; i < MAP_WIDTH; ++i) {
			if (map[j][i] == 'X'||map[j][i] == '>' || map[j][i] == '<'|| map[j][i] == '^' || map[j][i] == 'V') {
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << map[j][i];
			cout << " ";
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else if (map[j][i] == 'A') {
			SetConsoleTextAttribute(hConsole,FOREGROUND_RED| FOREGROUND_INTENSITY);
			cout << map[j][i];
			cout << " ";
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else if (map[j][i] == 'N') {
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << map[j][i];
				cout << " ";
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else if (map[j][i] == '#') {
				SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN );
				cout << " ";
				cout << map[j][i];
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else {
				cout << map[j][i];
				cout << " ";
			}
		}
		cout << endl;
	}
	for (int j = 0; j <= MAP_HEIGHT; ++j) {
		for (int i = 0; i <= MAP_WIDTH; ++i) {
			if (map[j][i] == '#') {
				reward[j][i] = 0;
			}
			if (map[j][i] == ' ' || map[j][i] == '.' || map[j][i]=='N') {
				reward[j][i] = 1;
			}
		}
	}
	cout << "SCORE: " << score << endl;
	cout << "Current level: " << level << endl;
}

void Player_move_logic() {
	int newx_pos = x_pos;
	int newy_pos = y_pos;
	map[y_pos][x_pos] = 'X';

	if (_kbhit()) {
		int input = _getch();
		if (input == 224) {
			input = _getch();
			current_input = input;
		}
	}
	if (current_input == 72) {
		--newy_pos;
	}
	if (current_input == 77) {
		++newx_pos;
	}
	if (current_input == 80) {
		++newy_pos;
	}
	if (current_input == 75) {
		--newx_pos;
	}
	if (map[newy_pos][newx_pos] == '.') {
		map[y_pos][x_pos] = ' ';    // set the previous location to ' '
		y_pos = newy_pos;           //update the current position to new position
		x_pos = newx_pos;
		player_arrow_image();
		++score;
	}
	if (map[newy_pos][newx_pos] == ' ') {
		map[y_pos][x_pos] = ' ';
		y_pos = newy_pos;
		x_pos = newx_pos;
		player_arrow_image();
	}
	if (map[newy_pos][newx_pos] == 'N') {
		map[y_pos][x_pos] = ' ';
		y_pos = newy_pos;
		x_pos = newx_pos;
		score += 20;
		player_arrow_image();
	}
	if (map[newy_pos][newx_pos] == 'A') {
		GameOver = true;
	}
}
void player_arrow_image() {
	if (current_input == 72) {
		map[y_pos][x_pos] = '^';
	}
	if (current_input == 80) {
		map[y_pos][x_pos] = 'V';
	}
	if (current_input == 75) {
		map[y_pos][x_pos] = '<';
	}
	if (current_input == 77) {
		map[y_pos][x_pos] = '>';
	}
	
}
class ghost_class {
private:

	int sleep_time;
	int ghost1_ypos;
	int ghost1_xpos;
	int ghost1_dir;

public:

	ghost_class (int x,int y,int d,int t)
		:ghost1_xpos(x),ghost1_ypos(y),ghost1_dir(d),sleep_time(t){}

	void ghost_movelogic()
	{
		int newg1_x = ghost1_xpos;
		int newg1_y = ghost1_ypos;
		int marks{ 0 };
		int best_i{ 0 };
		int i_difference{ 0 };
		int shortest_idiff{ 999 };
		int path_total_marks{ 0 };
		int x_min{ 0 };
		int x_max{ 0 };

		Sleep(sleep_time);
		switch (ghost1_dir) {
		case 1:
			--newg1_x;
			break;

		case 2:
			++newg1_x;
			break;

		case 3:
			--newg1_y;
			break;

		case 4:
			++newg1_y;
			break;

		default:
			break;
		}
		if (map[newg1_y][newg1_x] == ' ') {
			map[ghost1_ypos][ghost1_xpos] = ' ';
			ghost1_ypos = newg1_y;
			ghost1_xpos = newg1_x;
			map[ghost1_ypos][ghost1_xpos] = 'A';
		}
		else if (map[newg1_y][newg1_x] == '.') {
			map[ghost1_ypos][ghost1_xpos] = '.';
			ghost1_ypos = newg1_y;
			ghost1_xpos = newg1_x;
			map[ghost1_ypos][ghost1_xpos] = 'A';
		}
		else if (map[newg1_y][newg1_x] == 'N') {
			map[ghost1_ypos][ghost1_xpos] = 'N';
			ghost1_ypos = newg1_y;
			ghost1_xpos = newg1_x;
			map[ghost1_ypos][ghost1_xpos] = 'A';
		}

		else if (map[newg1_y][newg1_x] == 'X') {
			GameOver = true;
		}
		for (int i = ghost1_xpos - 1; i >= 0; --i) {
			if (reward[ghost1_ypos][i] == 0) {
				x_min = i;
				break;
			}
		}
		for (int i = ghost1_xpos + 1; i < MAP_WIDTH; ++i) {
			if (reward[ghost1_ypos][i] == 0) {
				x_max = i;
				break;
			}
		}
		if (ghost1_ypos <= y_pos) {
			for (int i = x_min; i <= x_max; ++i) {
				for (int j = ghost1_ypos; j <= y_pos; ++j) {
					marks += reward[j][i];
				}

				if (i > x_min && marks >= path_total_marks) {
					path_total_marks = marks;
					i_difference = abs(i - x_pos);

					if (i_difference < shortest_idiff) {
						shortest_idiff = i_difference;
						best_i = i;
					}
				}
				marks = 0;
			}
		}
		if (ghost1_ypos > y_pos) {
			for (int i = x_min; i <= x_max; ++i) {
				for (int j = y_pos; j <= ghost1_ypos; ++j) {
					marks += reward[j][i];
				}

				if (i > x_min && marks >= path_total_marks) {
					path_total_marks = marks;
					i_difference = abs(i - x_pos);

					if (i_difference < shortest_idiff) {
						shortest_idiff = i_difference;
						best_i = i;
					}

				}
				marks = 0;
			}
		}
		if (best_i >= 0 && best_i < MAP_WIDTH) {
			if (best_i > ghost1_xpos) {
				ghost1_dir = 2;
			}
			if (best_i < ghost1_xpos) {
				ghost1_dir = 1;
			}
			if (best_i == ghost1_xpos && ghost1_ypos > y_pos) {
				ghost1_dir = 3;
			}
			if (best_i == ghost1_xpos && ghost1_ypos < y_pos) {
				ghost1_dir = 4;
			}
		}
	}
};

void Check_Nremaining() {
	bool Nremaining{false};
	for (int j = 0; j < MAP_HEIGHT; ++j) {
		for (int i = 0; i < MAP_WIDTH; ++i) {
			if (map[j][i] == 'N') {
				Nremaining = true;
				break;
			}
		}
		if (Nremaining) {
			break;
		}
	}
	if (!Nremaining) {
		Win = true;
	}
}
void ghostandplayer_reset_pos() {
	ghost_class ghost1(3,   1, 0, 40);
	ghost_class ghost2(33,  1, 0, 40);
	ghost_class ghost3(15, 10, 0, 20);
	ghost_class ghost4(38,  1, 0, 20);
	x_pos = 21;
	y_pos = 17;
}

void Reset_package() {
	Quit = false;
	current_input = 0;
	score = 0;
	ghostandplayer_reset_pos();
	Leaderboard_print_request = 0;
}


void Leaderboard() {
	int temp_score{ 0 };
	int best_score{ 0 };
	
	if (Leaderboard_print_request == 0) {
		cout << "\t\t\t\t\t\t\t\t\t\t\t_______ Leaderboard _______ (score,playtime(seconds))\n";
		++Leaderboard_print_request;
		
		vector<pair<size_t, pair<int, int>>> player_data;

		for (size_t i = 0; i < player_bucket.size(); ++i) {
			temp_score = player_score.at(i);
			if (i > 0 && temp_score > best_score) {
				best_score = temp_score;
			}
			player_data.push_back(make_pair(i, make_pair(player_score.at(i), player_playtime.at(i))));
		}
		sort(player_data.begin(), player_data.end(), [](const auto& p1, const auto& p2) {
			if (p1.second.first == p2.second.first) {
				return p1.second.second <= p2.second.second;
			}
			return p1.second.first > p2.second.first;
			});
		
		for (const auto& player : player_data) {
			size_t player_id = player.first;
			int player_score=player.second.first;
			int player_playtime = player.second.second;
			int player_previous_score;
		
			if (player_score > player_bestscore[player_id]) {
				player_bestscore[player_id] = player_score;
			}
		
			cout<<fixed<<setw(90)<< (player_id + 1) << ") " <<setw(20)<< player_bucket.at(player_id) <<setw(10)<<player_bestscore[player_id] << setw(17) << player_playtime << endl;
		}

	}
}
void change_player_map() {
		while (true) {
			cout << "Change Map or Change Player?(M/P)?" << endl;
			cout << "when you has finished your changed ,please enter E to exit." << endl;
			cin >> request;
			if (request == 'M' || request == 'm') {
				while (true) {
					cout << "Please pick your map level: easy (1) , intermediate (2) , hardcore (3)" << endl;
					cin.ignore();
					getline(cin, input_mapchoice);
					stringstream ss(input_mapchoice);     //convert input string to integer
					if (ss >> map_choice && (map_choice == 1 || map_choice == 2 || map_choice == 3)) {    //ss>>map_choice extract an integer and strore into map_choice
						break;
					}
					else {
						cout << "Please retry again...." << endl;
					}
					cout << "Map has been changed to " << "map " << map_choice << endl;
				}
			}
			if (request == 'P' || request == 'p') {
	
				cout << "If you want to add new player(A) or change existing player(X): ";
				cin >> request;
				if (request == 'A' || request == 'a') {
					for (size_t i = 0; i < player_bucket.size(); ++i) {
						cout << (i + 1) << ") " << player_bucket.at(i) << endl;
					}
					cout << "Please enter the new player name: ";
					cin >> player_name;
					player_bucket.push_back(player_name);
					player_score.push_back(0);
					player_playtime.push_back(0);
					player_bestscore.push_back(0);
					cout << "new player " << player_name << " has been registered\n\n";
					++player_id;
				}
				if (request == 'X' || request == 'x') {
					 
					for (size_t i = 0; i < player_bucket.size(); ++i) {
						cout << (i + 1) << ") " << player_bucket.at(i) << endl;
					}
					cout << "Current player is " << player_bucket.at(player_id-1) << endl<<endl;
					cout << "Please enter your player number to change with (1/2/3/...) : ";
					cin >> player_id;
					cout << "Current player is " << player_bucket.at(player_id - 1) << endl<<endl<<endl;	
				}
			}
			if (request == 'E' || request == 'e') {
				GameOver = false;
				Reset_package();
				break;
			}
		}
}

int main() {

	pacman_intro();
	time_t start_time = time(nullptr);
	while (Quit != true) {
		ghost_class ghost1( 3, 1,0,40);
		ghost_class ghost2(33, 1,0,40);
		ghost_class ghost3(15,10,0,20);
		ghost_class ghost4(38, 1,0,20);

		system("cls");
		if (map_choice == 1) {
			read_file file("pacman map 1.txt");
			file.open_file();
		}
		if (map_choice == 2) {
			read_file file("map_2.txt");
			file.open_file();
		}
		if (map_choice == 3) {
			read_file file("map_3.txt");
			file.open_file();
		}

		while (GameOver != true && Win != true) {
			Leaderboard();
			draw_map();
			ghost1.ghost_movelogic();
			ghost2.ghost_movelogic();
			if (level == 2) {
				ghost3.ghost_movelogic();
			}
			if (level >= 3) {
				ghost3.ghost_movelogic();
				ghost4.ghost_movelogic();
			}

			Player_move_logic();
			Check_Nremaining();
		}
		if (Win == true) {
			cout << "Congratulationss." << endl << endl;
			cout << "Your final score is: " << score << endl;
			time_t end_time = time(nullptr);
			int timeplay = difftime(end_time, start_time);
			cout << "Your timeplay is " << timeplay << " seconds...." << endl;
			player_score.at(player_id-1) = score;
			player_playtime.at(player_id-1) = timeplay;
			Leaderboard_print_request = 0;
			Leaderboard();
			++Leaderboard_print_request;
			cout << "Want to go for higher level? or Change player/Change map? or Same level or Quit? (Y/C/S/Q)" << endl;
			cin >> request;
			if (request == 'Q' || request == 'q') {
				Quit = true;
			}
			if (request == 'S' || request == 's') {
				Reset_package();
				Win = false;
				end_time = time(nullptr);
				timeplay = difftime(end_time, start_time);
				start_time += static_cast<time_t>(timeplay);
			}
			if (request == 'Y' || request == 'y') {
				Reset_package();
				Win = false;
				if (level >= 1 && level < 3) {
					++level;
				}
				end_time = time(nullptr);
				timeplay = difftime(end_time, start_time);
				start_time += static_cast<time_t>(timeplay);
			}
			if (request == 'C' || request == 'c') {
				change_player_map();
				end_time = time(nullptr);
				timeplay = difftime(end_time, start_time);
				start_time += static_cast<time_t>(timeplay);
			}
		}

		if (GameOver == true) {
			cout << "You have died......" << endl << endl;
			cout << "Not too surprised that you have lost...." << endl;
			time_t end_time = time(nullptr);
			int timeplay = difftime(end_time, start_time);
			cout << "Your final score is: " << score << endl;
			cout << "Your timeplay is " << timeplay << " seconds...." << endl;
			player_score.at(player_id - 1) = score;
			player_playtime.at(player_id - 1) = timeplay;
			Leaderboard_print_request = 0;
			Leaderboard();
			++Leaderboard_print_request;

			cout << "Want to go for higher level? or Change player/Change map? or Same level or Quit? (Y/C/S/Q)" << endl;
			cin >> request;
			if (request == 'Q' || request == 'q') {
				Quit = true;
			}
			if (request == 'S' || request == 's') {
				Reset_package();
				GameOver = false;
				end_time = time(nullptr);
				timeplay = difftime(end_time, start_time);
				start_time += static_cast<time_t>(timeplay);
			}
			if (request == 'Y' || request == 'y') {
				Reset_package();
				GameOver = false;
				if (level >= 1 && level < 3) {
					++level;
				}
				end_time = time(nullptr);
				timeplay = difftime(end_time, start_time);
				start_time += static_cast<time_t>(timeplay);
			}
			if (request == 'C' || request == 'c') {
				change_player_map();
				end_time = time(nullptr);
				timeplay = difftime(end_time, start_time);
				start_time += static_cast<time_t>(timeplay);
			}
		}
	}
	return 0;
}
