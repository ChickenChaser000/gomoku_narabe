#include <iostream>
#include <windows.h>

using namespace std;

const int BOARD_SIZE = 9;
//盤面
int board[BOARD_SIZE+1][BOARD_SIZE+1];

//ターン
int turn;

//現在のプレイヤーの石
int player_stone;

//終了フラグ
int end_flug;

/**
@fn
ゲームスタート関数
@brief タイトルの表示と盤面を初期化を行います。
*/
void game_start();

/**
@fn
盤面初期化関数
@brief 盤面を初期化を行います。
*/
void board_init();

/**
@fn
初期石関数
@brief 盤面に最初の黒石を置きます。
*/
void first_place();

/**
@fn
盤面描写関数
@brief 盤面の状況を描写します。
*/
void board_draw();

/**
@fn
石置き関数
@brief 盤面に石を置く処理をします。
*/
void stone_put();

/**
@fn
五目関数
@brief 石が五個並んでるか確かめ、並んでいたらend_flugを立てます。
*/
void is_five_stones();

void end_game();

int main() {
	game_start();
	first_place();
	for (;;) {
		end_flug = 0;
		stone_put();
		is_five_stones();
		if (end_flug == 1) {
			break;
		}
	}
	end_game();
	return 0;
}

void game_start() {
	cout << "======五目並べ======" << endl;
	Sleep(3 * 1000);
	board_init();
}

void board_init() {
	for (int i = 0; i < BOARD_SIZE+1; i++) {
		for (int j = 0; j < BOARD_SIZE+1; j++) {
			board[i][j] = 0;
		}
	}
}

void first_place() {
	cout << "最初に黒石が中央に置かれます" << endl;
	board[4][4] = 1;
}

void board_draw() {
	cout << "　";
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << " ";
	}
	cout << endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << i + 1;
		for (int j = 0; j < BOARD_SIZE; j++) {
			switch (board[i][j]) {
			case 0:
				cout << "・";
				break;
			case 1:
				cout << "●";
				break;
			case 2:
				cout << "〇";
				break;
			}
		}
		cout << endl;
	}
}

void stone_put() {
	int stone_place_x = 0;//置く石のx軸
	int stone_place_y = 0;//置く石のy軸
	turn++;//ターンを加算
	player_stone = turn % 2 + 1;//現在のプレイヤーを判別
	board_draw();
	switch (player_stone) {
	case 1:
		cout << "黒";
		break;
	case 2:
		cout << "白";
		break;
	}
	cout << "のターンです" << endl;
	for (;;) {
		cout << "石を置く位置を入力してください。" << endl;
		for (;;) {//以下で入力値が1～9か判別
			cout << "横方向の位置を入力してください" << endl;
			cin >> stone_place_x;
			if (stone_place_x < 1 || stone_place_x > 9) {
				cout << "1～9の数字を入力してください" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}
			else {
				break;
			}
		}
		for (;;) {//以下で入力値が1～9か判別
			cout << "縦方向の位置を入力してください" << endl;
			cin >> stone_place_y;
			if (stone_place_y < 1 || stone_place_y > 9) {
				cout << "1～9の数字を入力してください" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}
			else {
				break;
			}
		}
		if (board[stone_place_y - 1][stone_place_x - 1] != 0) {//入力した位置に石が置いてないか判別
			cout << "すでに他の石がおいてあります\nもう一度入力してください。\n" << endl;
			continue;
		}else{
			int no_stone_flug = 1;
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					if (board[stone_place_y - i][stone_place_x - k] != 0){
						no_stone_flug = 0;
						break;
					}
				}
				if (no_stone_flug == 0) {
					break;
				}
			}
			if (no_stone_flug == 1) {
				cout << "他の石と隣接した場所に石を置いて下さい。" << endl;
			}
			else {
				board[stone_place_y - 1][stone_place_x - 1] = player_stone;
				break;
			}
		}
	}
}

void is_five_stones() {
	for (int i = 0; i < 9; i++) {//盤面をサーチ
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != 0) {//もし石があったら以下の処理をする
				for (int k = 0; k < 4; k++) {//右、右下、下,左下の四方向で以下の処理をする
					int direction = k;//現在調べている方向の変数
					for (int n = 0; n < 5; n++) {//五個分繰り返す。
						int five_stone = 4;//起点以外に何個石が並んでいればいいかの変数
						if (direction == 0) {
							if (board[i][j] == board[i][j + n]) {
								if (n == five_stone) {
									end_flug = 1;
								}
								continue;
							}
							else {
								break;
							}
						}
						else if (direction == 1) {
							if (board[i][j] == board[i + n][j + n]) {
								if (n == five_stone) {
									end_flug = 1;
								}
								continue;
							}
							else {
								break;
							}
						}
						else if (direction == 2) {
							if (board[i][j] == board[i + n][j]) {
								if (n == five_stone) {
									end_flug = 1;
								}
								continue;
							}
							else {
								break;

							}
						}
						else if (direction == 3) {
							if (board[i][j] == board[i + n][j - n]) {
								if (n == five_stone) {
									end_flug = 1;
								}
								continue;
							}
							else {
								break;
							}
						}
					}
				}
			}
		}
	}
}

void end_game() {
	switch (player_stone) {
	case 1:
		cout << "黒";
		break;
	case 2:
		cout << "白";
		break;
	}
	cout << "の勝ちです！" << endl;
	board_draw();
	Sleep(3 * 1000);
}