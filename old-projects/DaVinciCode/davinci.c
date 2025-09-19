#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#pragma warning(disable:4996)


struct code
{
	int number;
	int count;
};

typedef struct code code;

int sort_ascending_order(code arr[6]); //sort in ascending order
int display(code arr_user[6], code arr_computer[6]); //display screen

int main() {
	code block[11] = { {1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2},{9,2},{10,2},{11,2} };
	code computer_code[6] = { {0,0},{0,0},{0,0},{0,0},{0,0},{0,0} };
	code user_code[6] = { {0,0},{0,0},{0,0},{0,0},{0,0},{0,0} };

	int a = 0; int b = 0; int i;
	int right_answer_user = 0; int right_answer_computer = 0; //count of user's and computer's right answer
	int answer_user = 0; int answer_computer = 0; //anwer of user and computer
	int storage[10] = { 0,0,0,0,0,0,0,0,0,0 }; int block_computer; //for computer's answer making
	int n;

	int min; int max; int temp; int x = 0; int test = 0;
	int condition1, condition2;//conditon for computer to make answer 0: disavailable / 1: available
	int balance = 100; // 컴퓨터가 정답을 더 맞추도록 유도


	//ramdomly making code blocks of computer and user
	srand((unsigned int)time(NULL));
	while (a < 6) {
		b = (rand() % 11);
		if (block[b].count != 0) {
			computer_code[a].number = block[b].number;
			a++;
			block[b].count--;
		}
	}

	a = 0; b = 0;
	while (a < 6) {
		b = (rand() % 11);
		if (block[b].count != 0) {
			user_code[a].number = block[b].number;
			a++;
			block[b].count--;
		}
	}


	//sort in ascending order
	sort_ascending_order(computer_code);
	sort_ascending_order(user_code);


	//display screen
	display(user_code, computer_code);


	//playing
	block_computer = rand() % 6 + 1;//최초 컴퓨터 선택 블록 설정
	while ((right_answer_user != 6) && (right_answer_computer != 6)) {
		//user's turn
		printf("\n[Your turn]\n");
		printf("which block? ");
		scanf("%d", &n);
		if (computer_code[n - 1].count != 0) {
			printf("This block is already disclosed.\nTry next turn!");
			goto next_turn;
		}
		printf("what is block %d's number? ", n);
		scanf("%d", &answer_user);

		if (computer_code[n - 1].number == answer_user) {
			printf("\nYOU'RE RIGHT!\n\n");
			computer_code[n - 1].count = 1;
			right_answer_user++;
		}
		else
			printf("\nYOU'RE WRONG!\n\n");
	next_turn:
		Sleep(3000);
		system("cls");
		display(user_code, computer_code);

		//computer's turn
		//test++;
		printf("\n[Computer's turn]\n");
		printf("which block? ");
		while (user_code[block_computer - 1].count == 1) { //정답을 맞추지 못한 코드를 고를 때까지 반복
			block_computer = (rand() % 6) + 1;
		}
		Sleep(1500);
		printf("%d\n", block_computer);
		printf("what is block %d's number? ", block_computer);

		balance = rand() % 4; // 25% 확률로 컴퓨터의 무조건 정답
		if (balance == 3)
			goto balance_;

		temp = 0;
		while (user_code[block_computer - temp - 1].count == 0) { //왼쪽으로 이동하며 맞춘 코드를 고를 때까지 반복
			if (block_computer - temp - 1 < 0)
				goto out_min;
			temp++;
		}
	out_min:
		if (block_computer - temp - 1 < 0) //랜덤값의 최소 설정
			switch (block_computer) {
			case 1:
				min = 1;
				break;
			case 2:
				min = 1;
				break;
			case 3:
				min = 2;
				break;
			case 4:
				min = 2;
				break;
			case 5:
				min = 3;
				break;
			case 6:
				min = 3;
			}
		else min = user_code[block_computer - temp - 1].number;

		temp = 0;
		while (user_code[block_computer + temp - 1].count == 0) { //오른쪽으로 이동하며 맞춘 코드를 고를 때까지 반복
			if (block_computer + temp - 1 > 5)
				goto out_max;
			temp++;
		}
	out_max:
		if (block_computer + temp - 1 > 5) //랜덤값의 최대 설정
			switch (block_computer) {
			case 1:
				max = 9;
				break;
			case 2:
				max = 9;
				break;
			case 3:
				max = 10;
				break;
			case 4:
				max = 10;
				break;
			case 5:
				max = 11;
				break;
			case 6:
				max = 11;
			}
		else max = user_code[block_computer + temp - 1].number;

		//printf("\ntest// 최소: %d   최대: %d\n", min, max); //test code

		condition1 = 0; condition2 = 0; test = 0;
		while ((condition1 == 0) || (condition2 == 0)) {
			condition1 = 0; condition2 = 0;
			if (min == max) //컴퓨터 답안 생성
				answer_computer = min;
			else
				answer_computer = rand() % (max - min) + min;

			temp = 0; //중복 답안 제거
			for (i = 0; i < 10; i++) {
				if (answer_computer == storage[i])
					temp++;
			}
			if (temp == 0)
				condition1 = 1;

			temp = 0; // 공개된 답안 및 컴퓨터 코드 제거
			for (i = 0; i < 6; i++) {
				if ((answer_computer == user_code[i].number) && (user_code[i].count == 1))
					temp++;
				if (answer_computer == computer_code[i].number)
					temp++;
			}
			if (temp < 2)
				condition2 = 1;
			//test++; //test code
			Sleep(200);
			//printf("test// %d) 답안후보: %d, 조건1: %d, 조건2: %d\n", test, answer_computer, condition1, condition2); //test code

		}

	balance_: // 20% 확률로 컴퓨터의 무조건 정답
		if (balance == 3) {
			//printf("\ntest// balance!\n"); //test code
			answer_computer = user_code[block_computer - 1].number;
		}

		Sleep(1000);
		printf("%d", answer_computer);

		if (user_code[block_computer - 1].number == answer_computer) {
			printf("\n\nCOMPUTER IS RIGHT!\n\n");
			user_code[block_computer - 1].count = 1;
			right_answer_computer++;
			for (x = 0; x < 10; x++)
				storage[x] = 0;
			x = 0;
		}
		else {
			printf("\n\nCOMPUTER IS WRONG!\n\n");
			storage[x] = answer_computer;
			x++;
		}
		//printf("test// 답안 기록: "); //test code
		//for (i = 0; i < 10; i++)
			//printf("%3d", storage[i]);
		//printf("\ntest// 시도: %d", test); //test code
		//printf("\ntest// 정답: %d", right_answer_computer); //test code

		Sleep(3000);
		system("cls");
		display(user_code, computer_code);
	}

	Sleep(1000);
	system("cls");
	display(user_code, computer_code);

	if (right_answer_user > right_answer_computer)
		printf("\nYou win!!\n");
	else {
		printf("\nYou lose...\n\n");
		printf("Computer's code is this!\n");
		for (i = 0; i < 6; i++)
			printf("%5d", computer_code[i].number);
	}

}



int sort_ascending_order(code arr[6])
{
	int num = 6; int temp;
	for (int e = num - 1; e > 0; e--)
	{
		for (int s = 0; s < e; s++)
		{
			if (arr[s].number > arr[s + 1].number)
			{
				temp = arr[s].number;
				arr[s].number = arr[s + 1].number;
				arr[s + 1].number = temp;
			}
		}
	}
	return 0;
}

int display(code arr_user[6], code arr_computer[6]) {
	int i;
	printf("《Da Vinci Code》\n");
	printf("----------------------------\n\n");
	printf("computer : ");
	for (i = 0; i < 6; i++) {
		if (arr_computer[i].count == 0)
			printf("  ■");
		else
			printf("%3d", arr_computer[i].number);
	}
	printf("\n");
	printf("you      : ");
	for (i = 0; i < 6; i++) {
		if (arr_user[i].count == 0)
			printf("  ■");
		else
			printf("%3d", arr_user[i].number);
	}
	printf("\n\n");
	printf("----------------------------\n\n");
	printf("your blocks : ");
	for (i = 0; i < 6; i++)
		printf("%5d", arr_user[i].number);
	printf("\n");
	//printf("test// computer's blocks : ");
	//for (i = 0; i < 6; i++)
		//printf("%5d", arr_computer[i].number);
	printf("\n\n");

	return 0;
}
