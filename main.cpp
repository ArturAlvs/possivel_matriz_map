/* 

Artur Alves

Sempre olhar por [to-do]


Mapa pra se guiar e saber onde falta olhar usando neuronios

*/ 
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include <stdlib.h>
#include <time.h>

using namespace std;

struct Neuron
{
	char name;
	// vector<Neuron *> synaps;
	int offset_x;
	int offset_y;
};

// tirar essa global depois
// quanto de divisao minima tem
int division;

vector<Neuron> navigation_brain;
char letra = 'a';

char objct_char = '?';
char car_char = 'c';

map<char, Neuron> map_neurons;
map<string, int> map_objcts;

// isso pode melhorr muito [to-do]
// espero
int* binario_roubado(int number){

	int *array_retorno = (int*) malloc(sizeof(int) * 2);

	if (number == 0)
	{
		array_retorno[0] = 0;
		array_retorno[1] = 0;
	}
	else if (number == 1)
	{
		array_retorno[0] = 0;
		array_retorno[1] = 1;
	}
	else if (number == 2)
	{
		array_retorno[0] = 1;
		array_retorno[1] = 0;
	}
	else if (number == 3)
	{
		array_retorno[0] = 1;
		array_retorno[1] = 1;
	}

	return array_retorno;
}

void add_object_found(vector<Neuron> n){

	string s = "";

	for (int i = 0; i < n.size(); ++i)
	{
		s += n.at(i).name;
	}

	map_objcts[s] = 1;

}

int find_number_of_neurons(int size){



	int neurons_number = 0;
	for (int i = size; i > 0;)
	{
		if (i % 2 == 0){
			neurons_number += 4;

			for (int j = 0; j < 4; j++)
			{
				Neuron n;
				n.name =  letra;

				int *array_binario = binario_roubado(j);

				// cout << array_binario[0] << " ";
				// cout << array_binario[1] << endl;

				int offX = array_binario[0] * i/2;
				int offY = array_binario[1] * i/2;

				// cout << offX << " ";
				// cout << offY << endl;
				
				n.offset_x = offX;
				n.offset_y = offY;
				
				navigation_brain.push_back(n);

				// map_neurons.insert( pair<char, Neuron>(letra, n) );
				map_neurons[letra] = n;

				letra += 1;

			}

			i = i / 2;


		}
		else{
			neurons_number += i * i;
			division = i;

			cout << "teste dos menores" << endl;

			for (int j = 0; j < i*i; j++)
			{
				Neuron n;
				n.name = letra;
				n.offset_x = j/i;
				n.offset_y = j%i;

				// cout << j/i << " ";
				// cout << j%i << endl;
				

				navigation_brain.push_back(n);

				// map_neurons.insert( pair<char, Neuron>(letra, n) );
				map_neurons[letra] = n;

				letra += 1;
			}

			// cout << i << endl;
			break;
		}
	}

	cout << neurons_number << endl;

	return neurons_number;

}

int* find_XY_by_neuron(vector<Neuron> n){
	int *xy = (int*) malloc(sizeof(int) * 2);

	int x = 0, y = 0;
	for (int i = 0; i < n.size(); i++)
	{
		x += n.at(i).offset_x;
		y += n.at(i).offset_y;
		
	}

	xy[0] = x;
	xy[1] = y;

	return xy;

}

// agora com o offset em neuronio da pra achar isso de uma forma melhor [to-do]
vector<Neuron> find_neurons_by_XY(int x, int y, int neurons_number){

	vector<Neuron> neurons_return;

	// cout << "linha " << x/division << endl;
	// cout << "coluna" << y/division << endl;

	int qtsX = x/division;
	int qtsY = y/division;

	// acho que da pra diminuir os IF tipo o dos menores
	// tambem acho que da pra melhorar, tenho que olhar depois
	// [to-do]

	int qtX = 0, qtY = 0;

	Neuron n_add;

	char l = 'a';
	for (int i = 0; i < neurons_number; ++i)
	{
		Neuron n = map_neurons.find(l)->second;
		
		if ( (n.offset_x == 0 && n.offset_y == 0) && i > 0  )
		{
			// cout << n_add.offset_x << "-----" << endl;
			// cout << i << endl;
			cout << n_add.name << " ";

			neurons_return.push_back(n_add);

			qtX += n_add.offset_x;
			qtY += n_add.offset_y;
		}

		if ( (n.offset_x + qtX <= x) && (n.offset_y + qtY <= y) )
		{
			n_add = n;
		}


		// cout << "[" <<i<<"] " << n.name << " -> x:" << n.offset_x << " y:" << n.offset_y << endl;
		l += 1;
	}
	cout << n_add.name << endl;
	neurons_return.push_back(n_add);




	// if ( (qtsX >= 0 && qtsX <= 3) && (qtsY >= 0 && qtsY <= 3) )
	// {
	// 	Neuron n = map_neurons.find('a')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "A" << endl;
	// }
	// else if ( (qtsX >= 0 && qtsX <= 3) && (qtsY >= 4 && qtsY <= 7) )
	// {
	// 	Neuron n = map_neurons.find('b')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "B" << endl;
	// }
	// else if ( (qtsX >= 4 && qtsX <= 7) && (qtsY >= 0 && qtsY <= 3) )
	// {
	// 	Neuron n = map_neurons.find('c')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "C" << endl;
	// }
	// else if ( (qtsX >= 4 && qtsX <= 7) && (qtsY >= 4 && qtsY <= 7) )
	// {
	// 	Neuron n = map_neurons.find('d')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "D" << endl;
	// }

	// if ( (qtsX == 0 || qtsX == 1 || qtsX == 4 || qtsX == 5) && (qtsY == 0 || qtsY == 1 || qtsY == 4 || qtsY == 5) )
	// {
	// 	Neuron n = map_neurons.find('e')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "E" << endl;
	// }
	// else if ( (qtsX == 0 || qtsX == 1 || qtsX == 4 || qtsX == 5) && (qtsY == 2 || qtsY == 3 || qtsY == 6 || qtsY == 7) )
	// {
	// 	Neuron n = map_neurons.find('f')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "F" << endl;
	// }
	// else if ( (qtsX == 2 || qtsX == 3 || qtsX == 6 || qtsX == 7) && (qtsY == 0 || qtsY == 1 || qtsY == 4 || qtsY == 5) )
	// {
	// 	Neuron n = map_neurons.find('g')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "G" << endl;
	// }
	// else if ( (qtsX == 2 || qtsX == 3 || qtsX == 6 || qtsX == 7) && (qtsY == 2 || qtsY == 3 || qtsY == 6 || qtsY == 7) )
	// {
	// 	Neuron n = map_neurons.find('h')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "H" << endl;
	// }

	// if ( (qtsX == 0 || qtsX == 2 || qtsX == 4 || qtsX == 6) && (qtsY == 0 || qtsY == 2 || qtsY == 4 || qtsY == 6) )
	// {
	// 	Neuron n = map_neurons.find('i')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "I" << endl;
	// }
	// else if ( (qtsX == 0 || qtsX == 2 || qtsX == 4 || qtsX == 6) && (qtsY == 1 || qtsY == 3 || qtsY == 5 || qtsY == 7) )
	// {
	// 	Neuron n = map_neurons.find('j')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "J" << endl;
	// }
	// else if ( (qtsX == 1 || qtsX == 3 || qtsX == 5 || qtsX == 7) && (qtsY == 0 || qtsY == 2 || qtsY == 4 || qtsY == 6) )
	// {
	// 	Neuron n = map_neurons.find('k')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "K" << endl;
	// }
	// else if ( (qtsX == 1 || qtsX == 3 || qtsX == 5 || qtsX == 7) && (qtsY == 1 || qtsY == 3 || qtsY == 5 || qtsY == 7) )
	// {
	// 	Neuron n = map_neurons.find('l')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "L" << endl;
	// }

	// // os menores
	// if (x % 3 == 0 && y % 3 == 0)
	// {
	// 	Neuron n = map_neurons.find('m')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "M" << endl;
	// }
	// else if (x % 3 == 1 && y % 3 == 0)
	// {
	// 	Neuron n = map_neurons.find('p')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "P" << endl;
	// }
	// else if (x % 3 == 2 && y % 3 == 0)
	// {
	// 	Neuron n = map_neurons.find('s')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "S" << endl;
	// }
	// else if (x % 3 == 0 && y % 3 == 1)
	// {
	// 	Neuron n = map_neurons.find('n')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "N" << endl;
	// }
	// else if (x % 3 == 1 && y % 3 == 1)
	// {
	// 	Neuron n = map_neurons.find('q')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "Q" << endl;
	// }
	// else if (x % 3 == 2 && y % 3 == 1)
	// {
	// 	Neuron n = map_neurons.find('t')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "T" << endl;
	// }
	// else if (x % 3 == 0 && y % 3 == 2)
	// {
	// 	Neuron n = map_neurons.find('o')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "O" << endl;
	// }
	// else if (x % 3 == 1 && y % 3 == 2)
	// {
	// 	Neuron n = map_neurons.find('r')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "R" << endl;
	// }
	// else if (x % 3 == 2 && y % 3 == 2)
	// {
	// 	Neuron n = map_neurons.find('u')->second;
	// 	neurons_return.push_back(n);
	// 	// cout << "U" << endl;
	// }

	return neurons_return;
}

char** criar_mapa(int size)
{

	// char *mapa = (char*) malloc(sizeof(char) * (size*size));
	char **mapa = new char*[size];

	for (int i = 0; i < size; ++i)
	{
		mapa[i] = new char[size];
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int rando = rand() % 20 +1;

			if (rando < 4)
			{
				mapa[i][j] = objct_char;
				
			}
			else{
				mapa[i][j] = ' ';

			}
		}
	}

	return mapa;

}

void printar_mapa(char **mapa, int size){

	cout << "______MAPA_______" << endl;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << mapa[i][j];
		}
		cout << endl;
	}
	cout << "______MAPA_______" << endl;


}

void car_move(char **mapa, int size, vector<Neuron> n){

	int *xy = find_XY_by_neuron(n);

	

}



int main(int argc, char const *argv[])
{	
	srand (time(NULL));

	int size = 24;

	// quadrada por enquanto
	// int mapa[size][size];
	char **mapa = criar_mapa(size);

	printar_mapa(mapa, size);



	// numero de neuronios necessario pra mapear
	int neurons_number = find_number_of_neurons(size);

	// int x,y;
	// do{
	// 	x = rand() % size;
	// 	y = rand() % size;

	// }while(mapa[x][y] == objct_char);
	// mapa[x][y] = car_char;
	
	// dado do carro
	// vector<Neuron> neurons_my_place = find_neurons_by_XY(x,y, neurons_number);



	// cout << x << " " << y << endl;

	// int sair = 1;

	// while(sair)
	// {
	// 	printar_mapa(mapa, size);

	// 	car_move(mapa, size, neurons_my_place);


	// 	cin >> sair;
	// }

	// testeee
	// int neurons[neurons_number];
	// for (int i = 0; i < neurons_number; ++i)
	// {
	// 	neurons[i] = 0;
	// }

	// A
	int x = 15;
	int y = 9;

	vector<Neuron> neurons_my_place = find_neurons_by_XY(x,y, neurons_number);

	for (int i = 0; i < neurons_my_place.size(); i++)
	{
		cout << neurons_my_place.at(i).name << endl;
	}

	// int *xy = find_XY_by_neuron(neurons_my_place);
	// cout << xy[0] << " " << xy[1] << endl;

	// // B
	// x = 9;
	// y = 20;
	// find_neurons_by_XY(x,y);
	// // C
	// x = 15;
	// y = 9;
	// find_neurons_by_XY(x,y);
	// // D
	// x = 19;
	// y = 16;	
	// find_neurons_by_XY(x,y);


	// cout << "Testes" << endl;
	// for (int i = 0; i < navigation_brain.size(); ++i)
	// {
	// 	cout << navigation_brain.at(i).name << endl;
	// }
	// cout << endl;

	char l = 'a';
	for (int i = 0; i < neurons_number; ++i)
	{
		Neuron n = map_neurons.find(l)->second;
		cout << "[" <<i<<"] " << n.name << " -> x:" << n.offset_x << " y:" << n.offset_y << endl;
		l += 1;
	}

	
	for (int i = 0; i < size; ++i)
	{
		delete [] mapa[i];
	}
	delete [] mapa;

	

	return 0;
}