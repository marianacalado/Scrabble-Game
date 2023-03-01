#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<random>

using namespace std;

struct Player {
	string name;
	string color;
	int score;
};

struct Letter {
	char letter;
	int quantity;
};

const int COLLUMN = 13;	//Global variable
const int ROW = 13;
vector<string> words;
vector<Letter> letters;
vector<char> rack;

// FUNCTION THAT READS THE CONTENT OF A TEXT FILE TO A STRING VECTOR
vector<string> read_file(string file_name)
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
//------------------------------------------------------------------------------------------------------------------------------

//FUNCTION THAT READS AND SEPARATES THE CONTENT OF THE CONFIG TEXT FILE
void Config(string filename, string& score, string& words_filename, vector<Letter>& letter)
{
	string score_aux, read_row;
	Letter L;

	vector<string> CONFIGcontent = read_file(filename);

	score_aux = CONFIGcontent.at(0);
	score = score_aux.substr(score_aux.find(":") + 2);
	//cout << score;

	words_filename = CONFIGcontent.at(1);
	words_filename = words_filename.substr(words_filename.find(":") + 2);
	//cout << words_filename;

	for (int i = 3; i < CONFIGcontent.size(); i++)
	{

		for (int j = 0; j < CONFIGcontent.at(i).size(); j++)
		{
			L.letter = CONFIGcontent.at(i).at(0);

			read_row = CONFIGcontent.at(i);
			L.quantity = stoi(read_row.substr(read_row.find(" ") + 2));
			letter.push_back(L);

			i++;
		}
	}

	//Test
	/*for (int i = 0; i < letter.size(); i++)
	{
		cout << letter[i].letter << " " << letter[i].quantity << endl;
	}*/
}
//-------------------------------------------------------------------------------------------------------------------------------


////FUNCTION THAT CREATES THE BAG VECTOR AND MIXES THE LETTERS INSIDE IT --> FALTA O ZZZZZZ ATENÇÃOOOO
vector<char> FillBag(vector<Letter> bag_aux)
{
	vector<char> bag;

	for (int i = 0; i < bag_aux.size(); i++)
	{
		char c;
		int number;

		c = bag_aux[i].letter;
		number = bag_aux[i].quantity;

		for (int j = 0; j < number; j++)
			bag.push_back(c);
	}

	//Test
	/*for (int i = 0; i < bag.size(); i++)
	{
		cout << bag[i] << endl;
	}*/

	random_shuffle(bag.begin(), bag.end());

	//Test
	//int count;
	/*for (int i = 0; i < bag.size(); i++)
	{
		cout << bag[i];

		if(bag[i] == 'A')
		count++;
	}*/
	//cout << count;

	return bag;
}
//-------------------------------------------------------------------------------------------------------------------------------


//FUNCTION THAT CREATES THE RACK VECTOR WITH 7 LETTERS RANDOM EXTRACTED OF THE BAG DEPOIS ORGANIZA POR ORDEM ALFABÉTICA vector<char> rack
vector <char> FillRack(vector<char>& bag) //retorna um vetor do tipo char que tem como input o vetor bag
{
	vector<char> rack;

	for (int i = 0; i < 7; i++)
	{
		char c = bag[rand() % bag.size()]; //dentro da bag tiramos um numero aleatorio
		rack.push_back(c); //insere coisas no vetor o valor x na posição 1
	}

	sort(rack.begin(), rack.end()); //para colocar as letras por ordem alfabética na rack

	return rack;
}
//---------------------------------------------------------------------------------------

////FUNCTION THAT READS THE PLAYER INSERTED WORD AND VERIFIES IF IT EXISTS IN THE WORDS VECTOR
//void ReadWord(string& inserted_word)
//{
//	for (int i = 0; i < words.size(); i++)
//	{
//		if (inserted_word == words.at(i))
//		{
//			// Permite preencher a board FillBoard
//		}
//		else
//			cout << "INVALID WORD!";
//	}
//}
////-------------------------------------------------------------------------------------------------------------------------------
//
//
////FUNCTION THAT CREATES A PLAYER AND ASSIGN A COLOR TO HIM/HER
//void CreatePlayer(int n_players, vector<Player> players)
//{
//	vector<string> color = { "red", "blue", "green", "magenta" };
//	Player P;
//	string name;
//
//	if (n_players > 4)
//	{
//		cerr << "Invalid: Just 4 players are allowed!\n TRY AGAIN!" << endl;
//		cout << "How many players want to play (1-4)? "; cin >> n_players;
//	}
//
//	for (int i = 0; i < n_players; i++)
//	{
//		cout << "Name: " << endl; cin >> P.name;
//		P.color = color[i];
//
//		players.push_back(P);
//	}
//
//}
////-------------------------------------------------------------------------------------------------------------------------------


int main()
{

	vector<string> readfile;
	vector<char> BAG;
	vector<char> Rack;
	vector<Letter> letter1;
	string score_aux, score1, words_filename1, readfile_aux1;
	int quant = 0;
	Letter L;


	Config("CONFIG.txt", score1, words_filename1, letter1);


	BAG = FillBag(letter1);
	cout << rand();
	/*Rack = FillRack(BAG);
	for (int i = 0; i < Rack.size(); i++)
		cout << Rack[i] << endl;*/

	return 0;
}