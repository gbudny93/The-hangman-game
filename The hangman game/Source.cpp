#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
/*functions*/
/*function printing logo of the game*/
void logo();
/*function getting a word to guess*/
void getWord();
/*function guessing a word for multiplayer mode*/
void multiGuess();
/*function printig a hangman*/
void printHangManEasy();
/*function printing a hangman*/
void printHangManHard();
/*function writing a random word from a file*/
void singleGetWord();
/*function guessing a word for single player mode*/
void singleGuess();

/*global variables*/
char arr[100]; /*Array for '_'*/
char arrToGuess[100]; /*Array for inputing word*/
int level; /*level variable*/
int c, i, j, ins, countLetters, countCorrect, countMistakes;
FILE *getword;



int main(){

	/*variables*/
	int option;
	logo();
	while (1){
		/*MENU*/
		printf("\nPlease choose the game mode or the other option: \n");
		printf("1. Single Player\n");
		printf("2. Multiplayer\n");
		printf("3. Instructions\n");
		printf("4. Exit game\n");
		scanf_s("%d", &option);

		switch (option){

		case 1:
		{
				  printf("You have chosen a single player mode! \n");
				  printf("Please choose difficulty level: \n1. Easy\n2. Hard\n");
				  scanf_s("%d", &option);
				  switch (option){
				  case 1:
				  {

							printf("You have chosen an easy mode !\n");
							level = 16;
							singleGetWord();
							singleGuess();
							break;
				  }
				  case 2:
				  {
							printf("You have chosen a hard mode !\n");
							level = 10;
							singleGetWord();
							singleGuess();
							break;
							
				  }
				  }
				  break;

		}
		case 2:
		{
				  printf("You have chosen a multiplayer mode !\n");
				  printf("Please choose difficulty level: \n1. Easy\n2. Hard\n");
				  scanf_s("%d", &option);
				  switch (option){
				  case 1:
				  {
							printf("You have chosen an easy mode !\n");
							level = 16;
							getWord();
							multiGuess();

							break;
				  }
				  case 2:
				  {
							printf("You have chosen a hard mode !\n");
							level = 10;
							getWord();
							multiGuess();
							break;
				  }
				  }

				  break;
		}
		case 3:
		{
				  system("cls");
				  logo();
				  /*Reading instructions from text file*/
				  FILE *fp;
				  errno_t file;
				  file = fopen_s(&fp, "\instructions.txt", "r");

				  while (ins != EOF){
					  ins = fgetc(fp);
					  printf("%c", ins);
				  }
				  fclose(fp);
				  break;
		}
		case 4:
		{
				  exit(0);
				  break;
		}
		default:
		{
				   printf("An error occured! Wrong value! Please insert a number from 1 to 4!\n");

		}
		}


	}
	getchar();
	getchar();
	return 0;
}
void logo(){
	printf(" @   @       @       @@     @  @@@@@@@  @@   @@      @      @@     @     \n");
	printf(" @   @      @ @      @ @    @  @        @ @ @ @     @ @     @ @    @     \n");
	printf(" @   @     @   @     @  @   @  @        @  @  @    @   @    @  @   @     \n");
	printf(" @@@@@    @@@@@@@    @   @  @  @  @@@@  @     @   @@@@@@@   @   @  @     \n");
	printf(" @   @   @       @   @    @ @  @     @  @     @  @       @  @    @ @     \n");
	printf(" @   @  @         @  @     @@  @@@@@@@  @     @ @         @ @     @@     \n");
	printf("                                           FoCP Project January 2014  \n");
	printf("                                                      Grzegorz Budny   \n");
}
void getWord(){

	i = 0;
	countLetters = 0;
	printf("\nPlease enter the word for your opponent:\n");
	c = getchar();
	while (c != EOF){
		arrToGuess[i] = c;
		i++;
		c = getchar();
		countLetters++;
		if (c == '\n'){
			goto nextStep;
		}
	}
nextStep:
	;
	system("cls");
}
void multiGuess(){

	logo();
	printf("\n");
	
	countCorrect = 1;
	countMistakes = 0;
	for (i = 0; i < 100; i++){
		arr[i] = '_';
	}
	for (i = 0; i < countLetters-1 ; i++){
		printf("%c ", arr[i]);
	}
	printf("\n");

	while(1){

		c = getchar();
		for (i = 0; i < countLetters; i++){
			if (arrToGuess[i] == c){
				arr[i] = arrToGuess[i];
				countCorrect++;
				Beep(3000, 300);
			}
			
	}
		
		for (i = 0; i < countLetters; i++){
			if (arrToGuess[i] == c){
				countMistakes--;
				break;
			}

		}
		countMistakes++;
		if (c == '\n'){
			if (level == 16){
				printHangManEasy();
				if (countMistakes == 10)break;
					
			}
			if (level == 10){
				printHangManHard();
				if (countMistakes == 6)break;
			}
			countCorrect--;
			printf("\n");
			for (i = 0; i < countLetters; i++)printf("%c ", arr[i]);
		}
		
		if (countLetters == countCorrect){
			Beep(2500, 2000);
			printf("CONGRATULATIONS! YOU WON");
			break;
		}	
	}
	
	for (i = 0; i < countLetters; i++)printf("%c ", arr[i]);
		
}
void singleGetWord()
{
	int choice;
	int i = 0;
	int count = -1;
	char ch;
	errno_t gw;
	countLetters = -1;

	for (int i = 0; i < 100; i++)
	{
		arrToGuess[i] = NULL;
	}
	srand((time(NULL)));
	choice = rand() % 30;
	rand();
	gw = fopen_s(&getword, "input.txt", "r");
	rewind(getword);
	while (1)
	{
		ch = fgetc(getword);
		if (ch == '|')
			count++;
		if (count == choice)
		{

			for (int i = 0;; i++)
			{
				arrToGuess[i] = fgetc(getword);
				countLetters++;
				if (arrToGuess[i] == '|')
				{
					arrToGuess[i] = NULL;
					break;
				}
			}
			break;
		}
	} 


}
void singleGuess(){

	system("cls");
	logo();
	printf("\n");
	countMistakes = -1;;
	countCorrect = 0;

	for (i = 0; i < countLetters; i++){
		arr[i] = '_';
	}
	
	printf("\n");
	while (1){

		c = getchar();
		for (i = 0; i < countLetters; i++){
			if (c == arrToGuess[i]){
				arr[i] = arrToGuess[i];
				countCorrect++;
				Beep(3000, 300);
				
			}
		}
		for (i = 0; i < countLetters; i++){
			if (c == arrToGuess[i]){
				countMistakes--;
				break;
			}
		}
		countMistakes++;
		if (c == '\n')
		{
			if (level == 16){
				printHangManEasy();
				if (countMistakes == 10)break;
			}
			if (level == 10){
				printHangManHard();
				if (countMistakes == 6)break;
			}
			countMistakes--;
			printf("\n");
			for (i = 0; i < countLetters; i++)printf("%c ", arr[i]);
			if (countCorrect == countLetters){
				Beep(2500, 2000);
				printf("\nCONGRATULATIONS! YOU WON!");
				break;
			}
		}
	}
}
/*Print for easy mode*/
void printHangManEasy(){

	switch (countMistakes){

	case 1:
	{
			 
		printf("                                                  __");
		
		break;
	}
	case 2:
	{
			 
		
		printf("                                                  |\n");
		printf("                                                  |\n");
		printf("                                                  |\n");
		printf("                                                  |\n");
		printf("                                                  |\n");
		printf("                                                  __");
	
		break;
	}
	case 3:
	{
		printf("                                                   __________\n");
		printf("                                                  |          \n");
		printf("                                                  |          \n");
		printf("                                                  |          \n");
		printf("                                                  |          \n");
		printf("                                                  |          \n");
		printf("                                                  __           ");
	
		break;
	}
	case 4:
	{
			  printf("                                              __________   \n");
			  printf("                                             |          |  \n");
			  printf("                                             |          O  \n");
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             __           ");
			
			  break;
	}

	case 5:
	{
			  printf("                                              __________   \n");
			  printf("                                             |          |  \n");
			  printf("                                             |          O  \n");
			  printf("                                             |          |   \n");
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             __           ");
			 
			  break;
	}
	case 6:
	{
			  printf("                                              __________   \n");
			  printf("                                             |          |  \n");
			  printf("                                             |          O  \n");
			  printf("                                             |          |\\\n");
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             __           ");
			 
			  break;
	}
	case 7:
	{
			  printf("                                              __________   \n");
			  printf("                                             |          |  \n");
			  printf("                                             |          O  \n");
			  printf("                                             |         /|\\\n");
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             __           ");
			 
			  break;
	}
	case 8:
	{
			  printf("                                              __________   \n");
			  printf("                                             |          |  \n");
			  printf("                                             |          O  \n");
			  printf("                                             |         /|\\\n");
			  printf("                                             |         /  \n");
			  printf("                                             |             \n");
			  printf("                                             __           ");
			  
			  break;
	}
	case 9:
	{
			  printf("                                              __________   \n");
			  printf("                                             |          |  \n");
			  printf("                                             |          O  \n");
			  printf("                                             |         /|\\\n");
			  printf("                                             |         /\\  \n");
			  printf("                                             |             \n");
			  printf("                                             __           ");
			  
			  break;
	}
	case 10:
	{
			  printf("                                              __________   \n");
			  printf("                                             |          |  \n");
			  printf("                                             |          O I'M DEAD GAME OVER! \n");
			  printf("                                             |         /|\\\n");
			  printf("                                             |         /\\  \n");
			  printf("                                             |             \n");
			  printf("                                             __           ");
			  
			  break;
	}
	}

}
void printHangManHard(){
	switch (countMistakes){

	case 1:
	{
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             __              ");
			 
			  break;
	}
	
	case 2:
	{

			  printf("                                              __________   \n");
			  printf("                                             |          |  \n");
			  printf("                                             |          O  \n");
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             __           ");
			 
			  break;
	}
	case 3:
	{

			  printf("                                              __________   \n");
			  printf("                                             |          |  \n");
			  printf("                                             |          O  \n");
			  printf("                                             |          |  \n");
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             __           ");
			
			  break;
	}
	case 4:
	{

			  printf("                                              __________   \n");
			  printf("                                             |          |  \n");
			  printf("                                             |          O  \n");
			  printf("                                             |         /|\\\n");
			  printf("                                             |             \n");
			  printf("                                             |             \n");
			  printf("                                             __           ");
			
			  break;
	}
	case 5:
	{

			  printf("                                              __________       \n");
			  printf("                                             |          |      \n");
			  printf("                                             |          O      \n");
			  printf("                                             |         /|\\    \n");
			  printf("                                             |         /       \n");
			  printf("                                             |                 \n");
			  printf("                                             __                  ");
			
			  break;
	}
	case 6:
	{
			  printf("                                              __________   \n");
			  printf("                                             |          |  \n");
			  printf("                                             |          O I'M DEAD GAME OVER! \n");
			  printf("                                             |         /|\\\n");
			  printf("                                             |         /\\  \n");
			  printf("                                             |             \n");
			  printf("                                             __           ");
			
			  break;
			
	}
	}
}



















