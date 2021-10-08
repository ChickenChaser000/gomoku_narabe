#include <iostream>
#include <windows.h>

using namespace std;

const int BOARD_SIZE = 9;
//�Ֆ�
int board[BOARD_SIZE+1][BOARD_SIZE+1];

//�^�[��
int turn;

//���݂̃v���C���[�̐�
int player_stone;

//�I���t���O
int end_flug;

/**
@fn
�Q�[���X�^�[�g�֐�
@brief �^�C�g���̕\���ƔՖʂ����������s���܂��B
*/
void game_start();

/**
@fn
�Ֆʏ������֐�
@brief �Ֆʂ����������s���܂��B
*/
void board_init();

/**
@fn
�����Ί֐�
@brief �Ֆʂɍŏ��̍��΂�u���܂��B
*/
void first_place();

/**
@fn
�Ֆʕ`�ʊ֐�
@brief �Ֆʂ̏󋵂�`�ʂ��܂��B
*/
void board_draw();

/**
@fn
�Βu���֐�
@brief �Ֆʂɐ΂�u�����������܂��B
*/
void stone_put();

/**
@fn
�ܖڊ֐�
@brief �΂��܌���ł邩�m���߁A����ł�����end_flug�𗧂Ă܂��B
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
	cout << "======�ܖڕ���======" << endl;
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
	cout << "�ŏ��ɍ��΂������ɒu����܂�" << endl;
	board[4][4] = 1;
}

void board_draw() {
	cout << "�@";
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << " ";
	}
	cout << endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << i + 1;
		for (int j = 0; j < BOARD_SIZE; j++) {
			switch (board[i][j]) {
			case 0:
				cout << "�E";
				break;
			case 1:
				cout << "��";
				break;
			case 2:
				cout << "�Z";
				break;
			}
		}
		cout << endl;
	}
}

void stone_put() {
	int stone_place_x = 0;//�u���΂�x��
	int stone_place_y = 0;//�u���΂�y��
	turn++;//�^�[�������Z
	player_stone = turn % 2 + 1;//���݂̃v���C���[�𔻕�
	board_draw();
	switch (player_stone) {
	case 1:
		cout << "��";
		break;
	case 2:
		cout << "��";
		break;
	}
	cout << "�̃^�[���ł�" << endl;
	for (;;) {
		cout << "�΂�u���ʒu����͂��Ă��������B" << endl;
		for (;;) {//�ȉ��œ��͒l��1�`9������
			cout << "�������̈ʒu����͂��Ă�������" << endl;
			cin >> stone_place_x;
			if (stone_place_x < 1 || stone_place_x > 9) {
				cout << "1�`9�̐�������͂��Ă�������" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}
			else {
				break;
			}
		}
		for (;;) {//�ȉ��œ��͒l��1�`9������
			cout << "�c�����̈ʒu����͂��Ă�������" << endl;
			cin >> stone_place_y;
			if (stone_place_y < 1 || stone_place_y > 9) {
				cout << "1�`9�̐�������͂��Ă�������" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}
			else {
				break;
			}
		}
		if (board[stone_place_y - 1][stone_place_x - 1] != 0) {//���͂����ʒu�ɐ΂��u���ĂȂ�������
			cout << "���łɑ��̐΂������Ă���܂�\n������x���͂��Ă��������B\n" << endl;
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
				cout << "���̐΂Ɨאڂ����ꏊ�ɐ΂�u���ĉ������B" << endl;
			}
			else {
				board[stone_place_y - 1][stone_place_x - 1] = player_stone;
				break;
			}
		}
	}
}

void is_five_stones() {
	for (int i = 0; i < 9; i++) {//�Ֆʂ��T�[�`
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != 0) {//�����΂���������ȉ��̏���������
				for (int k = 0; k < 4; k++) {//�E�A�E���A��,�����̎l�����ňȉ��̏���������
					int direction = k;//���ݒ��ׂĂ�������̕ϐ�
					for (int n = 0; n < 5; n++) {//�܌��J��Ԃ��B
						int five_stone = 4;//�N�_�ȊO�ɉ��΂�����ł���΂������̕ϐ�
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
		cout << "��";
		break;
	case 2:
		cout << "��";
		break;
	}
	cout << "�̏����ł��I" << endl;
	board_draw();
	Sleep(3 * 1000);
}