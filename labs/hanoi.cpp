#include <iostream>

using namespace std;
void tower(int disk, int **b, int from, int to, int spare, int height);
int **create_array(int rows);
void move(int height, int **b, int from, int to);
void print(int height, int **b);
int main(int argc, char *argv[]){
	int disk, height;
	disk = argv[1][0] - '0';
	//cout << "How many disk do you want to use? ";
	//cin >> disk;
	int **b;
	b = create_array(disk);
	height = disk;
	for(int i = 0; i < disk; i++){
		for(int j = 0; j < 3; j++){
			b[i][j] = 0;
		}
	}
	for(int i = 0; i < disk; i++){
		b[i][0] = i + 1;
	}
	for(int i = 0; i < height; i++){
		cout << " " << b[i][0] << " " << b[i][1] << " " << b[i][2] <<endl;
	}
	cout << "-------" << endl;
	tower(disk, b, 1, 2, 3, height);
}

int **create_array(int rows){
	int **b;
	b = new int *[rows];
	for(int i = 0; i < rows; i++)
		b[i] = new int [3];
	return b;
}

void tower(int disk, int **b, int from, int to, int spare, int height){
	if(disk >= 1){
		tower (disk - 1, b, from, spare, to, height);
		move(height, b, from - 1, to - 1);
		print(height, b);
		tower(disk - 1, b, spare, to, from, height);
	}
	//print_board();
}

void move(int height, int **b, int from, int to){
	int start_pos = height - 1, end_pos = height - 1;
	for(int i = 0; i < height; i++){
		if(b[i][from] != 0){
			start_pos = i;
			break;
		}
	}
	for(int i = 0; i < height; i++){
		if(b[i][to] != 0){
			end_pos = i - 1;
			break;
		}
	}
	//cout << b[end_pos][to] << b[start_pos][from] << endl;
	b[end_pos][to] = b[start_pos][from];
	b[start_pos][from] = 0;
}
void print(int height, int **b){
	for(int i = 0; i < height; i++){
		cout << " " << b[i][0] << " " << b[i][1] << " " << b[i][2] <<endl;
	}
	cout << "-------" << endl;
}