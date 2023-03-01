#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include <ctime>

using namespace std;

#define WHITE_SQUARE 0xDB;

struct Player {
	string name;
	string color;
	int score;
	vector<string> player_words;
};

struct Letter {
	char letter;
	int quantity;
};

const int rows = 13; //Global variable
const int columns = 13; //Global variable
vector<string> words;
char board[rows][columns];
vector<char> bag;
vector<char> rack;

string string_rows_index = "ABCDEFGHIJKLM";
string string_columns_index = "abcdefghijklm";

vector<Player> players;
vector<Letter> letters;





// FUNCTION THAT READS THE CONTENT OF A TEXT FILE TO A STRING VECTOR
vector<string> readFile(string file_name)
{
	ifstream f_in_2;
	f_in_2.open(file_name);

	if (!f_in_2.is_open())
	{
		cerr << "\nERROR: file not found!" << endl;
		exit(1);
	}

	vector<string> file_content;
	string aux;

	while (getline(f_in_2, aux))
		file_content.push_back(aux);

	f_in_2.close();

	return file_content;
}
//-------------------------------------------------------------------------------------------------------------------------------



//FUNCTION THAT READS AND SEPARATES THE CONTENT OF THE CONFIG TEXT FILE
int config()
{
	int score;
	string config_filename = "CONFIG.txt";
	string words_filename, score_aux, read_row;
	Letter L;

	vector<string> CONFIGcontent = readFile(config_filename);

	score_aux = CONFIGcontent.at(0);
	score = stoi(score_aux.substr(score_aux.find(":") + 2));
	//cout << score;

	words_filename = CONFIGcontent.at(1);
	words_filename = words_filename.substr(words_filename.find(":") + 2);
	words = readFile(words_filename);

	for (int i = 0; i < words.size(); i++) {
		for (int k = 0; k < words[i].length(); k++) {
			words[i][k] = toupper(words[i][k]);
		}
	}

	for (int i = 3; i < CONFIGcontent.size(); i++)
	{

		for (int j = 0; j < CONFIGcontent.at(i).size(); j++)
		{
			L.letter = CONFIGcontent.at(i).at(0);

			read_row = CONFIGcontent.at(i);
			L.quantity = stoi(read_row.substr(read_row.find(" ") + 2));
			letters.push_back(L);

			i++;
		}
	}

	return score;
}
//-------------------------------------------------------------------------------------------------------------------------------



//FUNCTION THAT CREATES THE BAG VECTOR AND MIXES THE LETTERS INSIDE IT --> FALTA O ZZZZZZ ATENÇÃOOOO
void fillBag()
{
	for (int i = 0; i < letters.size(); i++)
	{
		char c;
		int number;

		c = letters[i].letter;
		number = letters[i].quantity;

		for (int j = 0; j < number; j++)
			bag.push_back(c);
	}
	random_shuffle(bag.begin(), bag.end());
}
//-------------------------------------------------------------------------------------------------------------------------------



//FUNCTION THAT CREATES THE RACK VECTOR WITH 7 LETTERS RANDOM EXTRACTED OF THE BAG DEPOIS ORGANIZA POR ORDEM ALFABÉTICA, 
void fillRack() //retorna um vetor do tipo char que tem como input o vetor bag
{
	int count = 0;

	for (int k = 0; k < rack.size(); k++) //conta quantas letras tem a prateleira
		count++;

	if (bag.size() < 7 - count) { //se a quant de letras da bag for menor a 7-a quantidade de letras da prateleira
		for (int i = 0; i < bag.size(); i++)
			rack.push_back(bag[i]); // tem que preencher a rack com o que a bag tem 
	}
	else
	{
		for (int i = 0; i < 7 - count; i++) //ou entao preenche com numeros aleatórios 
		{
			int c = rand() % bag.size();
			rack.push_back(bag[c]);
			bag.erase(bag.begin() + c);
		}

	}

	sort(rack.begin(), rack.end()); //para colocar as letras por ordem alfabética na rack
}
//-----------------------------------------------------------------------------------------



void printRack() 
{
	cout << "\bRack: ";
	for (int i = 0; i < rack.size(); i++) {
		cout << rack[i] << " ";
	}
	cout << endl;
}
//-----------------------------------------------------------------------------------------------------------------------



bool verification()
{

	bool error;
	char peek;

	if (cin.fail())
	{
		error = true;

		if (cin.eof()) {
			cin.clear();
			exit(2);
		}
		else
		{
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}
	else {
		peek = cin.peek();

		if (peek != '\n') {
			error = true;
			cin.ignore(10000, '\n');
		}
		else
			error = false;
	}
		

	return error;
}
//-----------------------------------------------------------------------------------------------------------------------


int finalIndex(string word, int index)
{
	int final_index = index + (word.length() - 1);

	return final_index;
}
//-----------------------------------------------------------------------------------------------------------------------



//FUNCTION THAT CREATES A PLAYER AND ASSIGN A COLOR TO HIM/HER
void createPlayer(int n_players)
{

	vector<string> color = { "red", "blue", "green", "magenta" };
	Player P;
	string name;
	bool error_state;

	error_state = verification();

	while (n_players < 2 || n_players > 4 || error_state == true)
	{
		
		cout << "\033[31m\n----- TRY AGAIN: Invalid number of players! -----\033[0m" << endl;
		cout << "\nHow many players want to play (2-4)? ";
		cin >> n_players;
		error_state = verification();
	
	}


	for (int i = 0; i < n_players; i++)
	{
		cout << "\nPLAYER " << i + 1 << endl;
		cout << "Name: ";
		cin >> P.name;
		//getline(cin,);
		P.color = color[i];
		P.score = 0;

		players.push_back(P);
	}

}
//-----------------------------------------------------------------------------------------------------------------------



void inputOrientation(char& ori)
{
	cout << "Orientation: ";
	cin >> ori;
	ori = toupper(ori);
}
//-----------------------------------------------------------------------------------------------------------------------



void checkOrientation(char& ori)
{
	bool error;

	error = verification();

	while (ori != 'H' && ori != 'V')
	{
		cout << "\033[31m\n----- ATTENTION: Invalid orientation! -----\033[0m\n" << endl;
		inputOrientation(ori);

		error = verification();
	}


	while (error == true)
	{
		cout << "\033[31m\n------ ATTENTION: Invalid orientation! -----\033[0m\n" << endl;
		inputOrientation(ori);

		error = verification();
	}
}
//-----------------------------------------------------------------------------------------------------------------------



void inputWord(string& word)
{
	cout << "\nWord: ";
	cin >> word;
	
	for (int k = 0; k < word.length(); k++) {
		word[k] = toupper(word[k]);
	}

}
//-----------------------------------------------------------------------------------------------------------------------



void checkWord(string& word)
{
	bool error;

	error = verification();

	int value = find(words.begin(), words.end(), word) != words.end();

	while (value == 0)
	{
		cout << "\033[31m\n----- ATTENTION: Invalid word! -----\033[0m" << endl;
		cout << "Note: This word does not exist!" << endl;
		inputWord(word);

		value = find(words.begin(), words.end(), word) != words.end();

		error = verification();
	}

	while(error == true)
	{
		cout << "\033[31m\n----- ATTENTION: Invalid word! -----\033[0m" << endl;
		cout << "Note: This word does not exist!" << endl;
		inputWord(word);

		value = find(words.begin(), words.end(), word) != words.end();

		error = verification();
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void erasefromWords(string word) //vai apagar a palavra do ficheiro das words 
{
	for (int i = 0; i < words.size(); i++)
	{
			if (word == words[i])
			{
				words.erase(words.begin() + i);
				break;
			}
	}
}

//----------------------------------------------------------------------------------------------------------------

void inputIndexes(string word, char& row_index, char& col_index, int& r_index, int& c_index, int& final_index, char ori)
{
	cout << "\nIndexes ";
	cout << "\n        Row: ";
	cin >> row_index;
	row_index = toupper(row_index);
	
	cout << "        Column: ";
	cin >> col_index;
	col_index = tolower(col_index);

	r_index = string_rows_index.find(row_index);
	c_index = string_columns_index.find(col_index);

	if (ori == 'H')
		final_index = finalIndex(word, c_index);
	else
		final_index = finalIndex(word, r_index);
}
//-----------------------------------------------------------------------------------------------------------------------



void checkIndexes(string word, char& row_index, char& col_index, int& r_index, int& c_index, int& final_index, char ori)
{
	bool error;

	error = verification();

	while (r_index == string::npos || c_index == string::npos) 
	{

		cout << "\033[31m\n----- ATTENTION: Invalid index! -----\033[0m" << endl;
		inputIndexes(word, row_index, col_index, r_index, c_index, final_index, ori);
		
		error = verification();
	}

	while (error == true) 
	{

		cout << "\033[31m\n----- ATTENTION: Invalid index! -----\033[0m" << endl;
		inputIndexes(word, row_index, col_index, r_index, c_index, final_index, ori);

		error = verification();
	}
}
//-----------------------------------------------------------------------------------------------------------------------



void checkFit(string word, char& row_index, char& col_index, int& r_index, int& c_index, int& final_index, char ori)
{
	while (final_index > (13 - 1)) {
		cout << "\033[31m\n----- TRY AGAIN: The word does not fit! -----\033[0m" << endl;

		inputIndexes(word, row_index, col_index, r_index, c_index, final_index, ori);

		checkIndexes(word, row_index, col_index, r_index, c_index, final_index, ori);
	}
}
//-----------------------------------------------------------------------------------------------------------------------



int flagLettersforWord(string& word, int& r_index, int& c_index, char ori, int final_index, vector<char> &word_aux, string &intercepted_word)
{
	int flag = 0;
	int r_index_aux = r_index;
	int c_index_aux = c_index;

	for (int k = 0; k < word.length(); k++) {
		if (ori == 'V')
		{
			for (int i = r_index_aux; i <= final_index; i++)
			{
				if (word[k] == board[i][c_index])
				{
					for (int m = 0; m < (13 - 1); m++)
					{
						if (board[i][m] != '\0')
							intercepted_word.push_back(board[i][m]);
					}

					flag++;
					break;
				}
				else
				{
					word_aux.push_back(word[k]);
					break;
				}
			}

			r_index_aux++;
		}
		else
		{
			for (int j = c_index_aux; j <= final_index; j++)
			{
				if (word[k] == board[r_index][j])
				{
					for (int m = 0; m < (13 - 1); m++)
					{
						if (board[m][j] != '\0')
							intercepted_word.push_back(board[m][j]);
					}

					flag++;
					break;
				}
				else
				{
					word_aux.push_back(word[k]);
					break;
				}
			}

			c_index_aux++;
		}
	}

	return flag;
}
//-----------------------------------------------------------------------------------------



void checkInvalidInput(int& flag, string& word, char& row_index, char& col_index, int& r_index, int& c_index, int& final_index, char& ori, vector<char> &word_aux, string &intercepted_word)
{
	while ((flag == 0))
	{
		cout << "\033[31m\n----- TRY AGAIN: Indexes not allowed! -----\033[0m" << endl;
		inputWord(word);
		checkWord(word);

		inputIndexes(word, row_index, col_index, r_index, c_index, final_index, ori);
		checkIndexes(word, row_index, col_index, r_index, c_index, final_index, ori);

		inputOrientation(ori);
		checkOrientation(ori);

		if (ori == 'H')
			final_index = finalIndex(word, c_index);
		else
			final_index = finalIndex(word, r_index);

		checkFit(word, row_index, col_index, r_index, c_index, final_index, ori);

		flag = flagLettersforWord(word, r_index, c_index, ori, final_index, word_aux, intercepted_word);
	}
}
//-----------------------------------------------------------------------------------------------------------------------



bool checkRack(vector<char> word_aux)
{
	bool error_rack = true;

	for (int k = 0; k < word_aux.size(); k++)
	{
		for (int j = 0; j < rack.size(); j++)
		{
			if (word_aux[k] == rack[j])
			{
				error_rack = false;
				break;
			}
			else
				error_rack = true;
		}
	}

	return error_rack;
}
//-----------------------------------------------------------------------------------------------------------------------



void erasefromRack(vector<char> word_aux)
{
	for (int k = 0; k < word_aux.size(); k++)
	{
		for (int j = 0; j < rack.size(); j++)
		{
			if (word_aux[k] == rack[j])
			{
				rack.erase(rack.begin() + j);
				break;
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------



void errorRack(bool error, string& word, char& row_index, char& col_index, int& r_index, int& c_index, int& final_index, char& ori, int &flag, vector<char> &word_aux, string &intercepted_word)
{
	
	while (error==true)
	{
		cout << "\033[31m\n----- TRY AGAIN: Letters not in the rack! -----\033[0m" << endl;
		inputWord(word);
		checkWord(word);

		inputIndexes(word, row_index, col_index, r_index, c_index, final_index, ori);
		checkIndexes(word, row_index, col_index, r_index, c_index, final_index, ori);

		inputOrientation(ori);
		checkOrientation(ori);

		if (ori == 'H')
			final_index = finalIndex(word, c_index);
		else
			final_index = finalIndex(word, r_index);

		checkFit(word, row_index, col_index, r_index, c_index, final_index, ori);

		flag = flagLettersforWord(word, r_index, c_index, ori, final_index, word_aux, intercepted_word);

	}
}
//-------------------------------------------------------------------------------------------------------------------------------



void saveCharBoard(char c, int r_index, int c_index) 
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == r_index && j == c_index) {
				board[i][j] = c;
			}
			else
				continue;
		}
	}
}
//-----------------------------------------------------------------------------------------



void writeVertical(string word, int r_index, int c_index) 
{
	vector<int> ro_indexes;

	int final_index = finalIndex(word, r_index);

	for (int k = r_index; k <= final_index; k++) {
		ro_indexes.push_back(k);
	}

	for (int h = 0; h < ro_indexes.size(); h++) {
		for (int i = 0; i < rows; i++) {
			if (i == ro_indexes[h])
				saveCharBoard(word[h], i, c_index);
			else
				continue;
		}
	}
}
//-----------------------------------------------------------------------------------------



void writeHorizontal(string word, int r_index, int c_index) 
{
	vector<int> co_indexes;

	int final_index = finalIndex(word, c_index);;

	
	for (int k = c_index; k <= final_index; k++) {
		co_indexes.push_back(k);
	}

	for (int h = 0; h < co_indexes.size(); h++) {
		for (int j = 0; j < columns; j++) {
			if (j == co_indexes[h])
				saveCharBoard(word[h], r_index, j);
			else
				continue;
		}
	}
}
//-----------------------------------------------------------------------------------------



//Red Color
void writeCharPlayer1(char c) 
{
	cout << "\033[47m\033[31m" << c << " \033[0m\033[0m";
}
//-----------------------------------------------------------------------------------------



//Blue Color
void writeCharPlayer2(char c) 
{
	cout << "\033[47m\033[34m" << c << " \033[0m\033[0m";
}
//-----------------------------------------------------------------------------------------



//Green Color
void writeCharPlayer3(char c) 
{
	cout << "\033[47m\033[32m" << c << " \033[0m\033[0m";
}
//-----------------------------------------------------------------------------------------



//Magenta Color
void writeCharPlayer4(char c) 
{
	cout << "\033[47m\033[35m" << c << " \033[0m\033[0m";
}
//-----------------------------------------------------------------------------------------



void updateBoardAux(char c, int r_index, int c_index, int i) 
{
	if (c_index % (13 - 1) != 0)
	{
		if (i == 0)
			writeCharPlayer1(c);

		else if(i == 1)
			writeCharPlayer2(c);

		else if(i == 2)
			writeCharPlayer3(c);
		else
			writeCharPlayer4(c);
	}
	else {
		if (c_index == 0) {
			cout << ' ' << string_rows_index[r_index] << ' ';
			if (i == 0)
				writeCharPlayer1(c);

			else if (i == 1)
				writeCharPlayer2(c);

			else if (i == 2)
				writeCharPlayer3(c);
			else
				writeCharPlayer4(c);
		}
		else {
			if (i == 0)
				writeCharPlayer1(c);

			else if (i == 1)
				writeCharPlayer2(c);

			else if (i == 2)
				writeCharPlayer3(c);
			else
				writeCharPlayer4(c);
			cout << endl;
		}
	}
}
//-----------------------------------------------------------------------------------------



void fillBackground(int r_index, int c_index)
{
	if (c_index % (13 - 1) != 0)
		cout << "\033[47m  \033[0m";
	else {
		if (c_index == 0) {
			cout << ' ' << string_rows_index[r_index] << ' ';
			cout << "\033[47m  \033[0m";
		}
		else {
			cout << "\033[47m  \033[0m" << endl;
		}
	}
}
//-----------------------------------------------------------------------------------------



void updateBoard(int player_index) 
{
	cout << endl << "   a b c d e f g h i j k l m " << endl;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (board[i][j] != '\0')
				updateBoardAux(board[i][j], i, j, player_index);
			else
				fillBackground(i, j);
		}
	}
	cout << endl;
}
//-----------------------------------------------------------------------------------------



void initializeBoard() 
{

	int rand_number = rand() % words.size();
	string init_word = words[rand_number];
	char init_row_index = 'C';
	char init_col_index = 'd';

	int r_index_init_word = string_rows_index.find(init_row_index);
	int c_index_init_word = string_columns_index.find(init_col_index);

	writeHorizontal(init_word, r_index_init_word, c_index_init_word);

}
//-----------------------------------------------------------------------------------------------------------------------



int initializeGame() 
{
	int max_score = config();
	fillBag();
	fillRack();
	initializeBoard();

	return max_score;
}
//-----------------------------------------------------------------------------------------------------------------------



int updateScore(string word, int player_index, string intercepted_word)
{
	int score = word.size();

	players[player_index].score += score;
	players[player_index].player_words.push_back(word);

		
	for (int p = 0; p < players.size(); p++)
	{
		for (int i = 0; i <= players[p].player_words.size(); i++)
		{
			if (player_index == p)
				continue;
			else
			{
				if (word.compare(intercepted_word) == 0)
				{
					players[p].score -= 1;
				}
				else
					continue;
			}
		}
	}
	
	return score;
}
//-------------------------------------------------------------------------------------------------------------------------------



bool anotherRoundConditions(int score, int max_score, int pass_counter)
{
	if (pass_counter < players.size() * 3 && score < max_score)
		return true;
	else
		return false;
}
//-------------------------------------------------------------------------------------------------------------------------------



void endGame()
{
	int score_winner = 0;

	cout << "\n______________________________________" << endl;
	cout << "SCORES: " << endl;

	for (int p = 0; p < players.size(); p++)
	{
		cout << endl << players[p].name << ": " << players[p].score << endl;

		/*if (players[p].score > players[p++].score)
			score_winner = players[p].score;
		else if (players[p].score < players[p++].score)
			score_winner = players[p++].score;
		else
			score_winner = players[p].score;*/
	}

	/*for (int p = 0; p < players.size(); p++)
	{
		if (players[p].score == score_winner)
		{
			cout << "WINNER: " << players[p].name << endl;
			cout << "\033[47m\033[32mCONGRATULATION! :-D\033[0m\033[0m" << endl;
		}
	}*/
}
//-------------------------------------------------------------------------------------------------------------------------------



void play(string &word, char &row_index, char &col_index, int &r_index, int &c_index, int &final_index, char &ori, int max_score) 
{
	int flag;
	int score = 0;
	int pass_counter = 0;
	bool error_rack;
	bool validInput = true;
	bool invalidInput = false;
	bool another_round = false;
	vector<char> word_aux;
	string intercepted_word;


	do
	{
		for (int i = 0; i < players.size(); i++)
		{
			cout << endl << "\nPLAYER " << i + 1 << ": " << players[i].name << " | Score: " << players[i].score << endl;

			printRack();

			updateBoard(i);

			do
			{
				invalidInput = false;
				validInput = true;
				char input;
				cout << "Play(P) || Pass(p) || Give Up(G): ";
				cin >> input;

				invalidInput = verification();
				if (invalidInput == true)
					input = 'x';

				switch (input)
				{
				case('P'):

					inputWord(word);
					checkWord(word);
					

					inputOrientation(ori);
					checkOrientation(ori);

					inputIndexes(word, row_index, col_index, r_index, c_index, final_index, ori);
					checkIndexes(word, row_index, col_index, r_index, c_index, final_index, ori);

					checkFit(word, row_index, col_index, r_index, c_index, final_index, ori);

					flag = flagLettersforWord(word, r_index, c_index, ori, final_index, word_aux, intercepted_word);
					checkInvalidInput(flag, word, row_index, col_index, r_index, c_index, final_index, ori, word_aux, intercepted_word);

					error_rack = checkRack(word_aux);
					errorRack(error_rack, word, row_index, col_index, r_index, c_index, final_index, ori, flag, word_aux, intercepted_word);
					erasefromRack(word_aux);
					fillRack();
					erasefromWords(word);

					score = updateScore(word, i, intercepted_word);

					if (ori == 'H')
						writeHorizontal(word, r_index, c_index);
					else
						writeVertical(word, r_index, c_index);

					break;

				case('p'):
					pass_counter += 1;
					break;

				case('G'):
					players.erase(players.begin() + i);
					break;

				default:
					cout << endl << "\033[31m\n----- ATTENTION: Invalid! -----\033[0m" << endl;

					validInput = false;
				}

			} while (validInput == false || invalidInput == true);

			another_round = anotherRoundConditions(score, max_score, pass_counter);
		}
	} while (another_round == true);

	endGame();
	
}
//-------------------------------------------------------------------------------------------------------------------------------



int main() 
{
	srand((unsigned)time(0));
	string word;
	char row_index, col_index, ori;

	int n_players, r_index, c_index, final_index;
	int score, max_score;

	vector<char> word_aux;

	

	cout << "        SCRABBLE GAME " << endl;



	cin.ignore(10000, '\n');
	cin.clear();
	cout << "How many players want to play (2-4)? ";
	cin >> n_players;

	createPlayer(n_players);
	max_score = initializeGame();
	play(word, row_index, col_index, r_index, c_index, final_index, ori, max_score);



	return 0;
}