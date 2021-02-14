/*
Author  - Jamie Sandell
Program - Snake Game
Version - 1.0
Date Created - 15/11/06
Best Viewed - Notepad, maximised, word-wrap disabled, resolution 1280x1024, font Courier, Regular, pt 10

TODO
-----
Possibly later make random walls around the screen

Add a demonstration

Add a health bar maybe

Might have to adjust how the difficulty affects the score, multiplying by the difficulty modifier seems a bit extreme
*/


using System;
using System.Threading;
using System.IO;
class Snake
{

	struct food
	{
		public int foodX;
		public int foodY;
		public int foodLifeLength;
		public int foodLifeLengthTime;
		public int foodColor;
	}

	struct snakeBodySegment
	{
		public int x;
		public int y;
	}

	struct player
	{
		public string name;
		public int score;
	}

	static void Main()
	{
try
{


		int initialSnakeX = 40, initialSnakeY = 12;	// Snake Position
		int xSpeed = 0, ySpeed = 0;	// Snake direction
		int score = 0;
		int counter = 0;	// counter for foodInfo
		int maxFood = 2;
		int snakeLength = 1; // how snake segments
		int gameBeginBorderX = 0; // These variables are used for drawing the game border
		int gameEndBorderX = 79;
		int gameBeginBorderY = 1;
		int gameEndBorderY = 25;
		int validInput = 0;
		int difficulty = 1; // Difficulty level affects snake movement speed and food value
				    // Cannot be less than 1 or greater then 3.
		int maxNames = 11;
		int arrayLength = 10;
		int rightEdge = arrayLength - 1;

		string gameStatusPaused = "Paused";
		string gameStatusRunning = "Running";
		string gameStatusGameOver = "GameOver";
		string fileNamePlayed = "Played.txt";
		string fileNameNames = "Names.txt";
		string fileNameScores = "Scores.txt";
		string readIn;

		bool pause = false;
		bool gameRunning = true;
		bool inputCheck = false;
		bool playedBefore = false;
		bool playAgain = true;
		bool quit = false;
		bool updateHighScores = false;

		food[] foodInfo = new food [maxFood];
		snakeBodySegment[] snake = new snakeBodySegment[25*80];
		player[] playerInfo = new player [maxNames];
		int[] initialScores = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }; // If there is no current high scores use these
		string[] initialNames = { "Held", "Up", "Without", "A", "Gun", "I'm", "Pulling", "Out", "Of", "Here", "To" };
			

		// Try to read in the various needed game files, if it can't be done then try to create them
		try
		{
			TextReader textIn = new StreamReader(fileNamePlayed);
			readIn = textIn.ReadToEnd();
			textIn.Close();
			Console.Write(readIn);
			playedBefore = true;
		}
		catch
		{
			// File couldn't be open so try to create it
			try
			{
				TextWriter textOut = new StreamWriter(fileNamePlayed);
				textOut.Close();
			}
			catch
			{
				// If the file couldn't be created then ask if they would like play instructions
			}
		}

		try
		{
			TextReader textInScores = new StreamReader(fileNameScores);
			for ( int i = 0; i < maxNames; i++ )
			{
				playerInfo[i].score = Int32.Parse(textInScores.ReadLine());
			}
			textInScores.Close();
		}

		catch
		{
			// If the file couldn't be read try to create it
			try
			{
				TextWriter textOutScores = new StreamWriter(fileNameScores);
				for ( int i = 0; i < maxNames; i++ )
				{
					textOutScores.WriteLine(initialScores[i]);
				}
				textOutScores.Close();
			}
			
			catch
			{
				Console.WriteLine(fileNameScores + " could not be created.");
			}
		}

		try
		{
			TextReader textInNames = new StreamReader(fileNameNames);
			for ( int i = 0; i < maxNames; i++ )
			{
				playerInfo[i].name = textInNames.ReadLine();
			}
			textInNames.Close();
		}

		catch
		{
			// If the file couldn't be read try to create it
			try
			{
				TextWriter textOutNames = new StreamWriter(fileNameNames);
				for ( int i = 0; i < maxNames; i++ )
				{
					textOutNames.WriteLine(initialNames[i]);
				}
				textOutNames.Close();
			}
			
			catch
			{
				Console.Write(fileNameNames + " could not be created");
			}
		}
		
		Console.ForegroundColor = ConsoleColor.Green;
		// If they haven't played before allow them the choice of play instructions
		if ( playedBefore == false )
		{
			do{
				Console.Write ("Would you like to learn how to play? y/n : ");
				getInputCheckInput(ref validInput);
				if ( validInput == 1 ) // Chose yes
				{
					inputCheck = true;
					showGameInstructions(ref inputCheck, ref validInput); // bool, int
				}
				if ( validInput == 0 ) // Chose no
				{
					inputCheck = true;
				}
			}while ( inputCheck == false );
			inputCheck = false; // We put it back to this because it could be used again.
		}

		// Here we will display the menu, wait for input, validate input. If correct input quit loop (inside method)
		displayMenu();
		executeMenu(ref playAgain, ref difficulty, ref inputCheck, ref validInput, ref quit,
			ref updateHighScores, ref playerInfo[10].score, ref playerInfo[10].name);

		if ( quit ) // If the user chose to quit in the executeMenu method
		{
			return;
		}

while (playAgain)
{
		
		// Initialise game screen, border, food, snake, game status, reset varaiables etc
		Console.Clear();
		Console.ForegroundColor = ConsoleColor.Blue;
		snakeLength = 1;
		score = 0;
		xSpeed = 0;
		ySpeed = 0;
		// Draw the X game border
		for ( int i = 0; i < gameEndBorderX; i++ )
		{
			// Draw the top border
			Console.SetCursorPosition(i, gameBeginBorderY);
			Console.Write("*");
			// Draw the bottom border
			Console.SetCursorPosition(i, gameEndBorderY-1);
			Console.Write("*");
		}
		// Draw the Y game border
		for ( int i = 1; i < gameEndBorderY; i++ )
		{
			// Draw the left border
			Console.SetCursorPosition(gameBeginBorderX, i);
			Console.Write("*");
			// Draw the right border
			Console.SetCursorPosition(gameEndBorderX, i);
			Console.Write("*");
		}

		Console.ForegroundColor = ConsoleColor.Green;
		// draw first food/(s)
		for ( counter = 0; counter < maxFood; counter++)
		{
			drawFoodDrawScore(ref foodInfo[counter].foodX, ref foodInfo[counter].foodY,
				ref foodInfo[counter].foodLifeLength, ref foodInfo[counter].foodColor, ref score);
		}
		// Set the first game status
		Console.ForegroundColor = ConsoleColor.Green;
		showGameStatus(ref gameStatusRunning);
		// Set the initial snake position
		snake[0].x = initialSnakeX;
		snake[0].y = initialSnakeY;

		// Now start the game running loop
		while(gameRunning)
		{
			if (Console.KeyAvailable)
			{
				ConsoleKeyInfo keyInfo = Console.ReadKey(true);
				switch (keyInfo.Key)
				{
					case ConsoleKey.UpArrow:
						ySpeed = -1;
						xSpeed = 0;
						break;
					case ConsoleKey.DownArrow:
						ySpeed = 1;
						xSpeed = 0;
						break;
					case ConsoleKey.LeftArrow:
						ySpeed = 0;
						xSpeed = -1;
						break;
					case ConsoleKey.RightArrow:
						ySpeed = 0;
						xSpeed = 1;
						break;
					case ConsoleKey.P:
						pause = true;
						Console.ForegroundColor = ConsoleColor.Yellow;
						showGameStatus(ref gameStatusPaused);
						break;
				}

			}

			do
			{
				if (Console.KeyAvailable)
				{
					ConsoleKeyInfo keyInfo = Console.ReadKey(true);
					if ( keyInfo.Key == ConsoleKey.P )
					{
						pause = false;
						Console.ForegroundColor = ConsoleColor.Green;
						showGameStatus(ref gameStatusRunning);
					}
				}
			} while(pause);

			
			// Within the boundaries so erase, update, draw the snake
			// Erase snake
			for ( int i = 0; i < snakeLength; i++ )
			{
				Console.SetCursorPosition(snake[i].x, snake[i].y);
				Console.Write(" ");
			}


			// Shuffle the snake segments
			for ( int i = snakeLength; i > 0; i-- )
			{
				snake[i] = snake[i-1];
			}	

			// Update the snake position
			snake[0].x = snake[0].x + xSpeed;
			snake[0].y = snake[0].y + ySpeed;

			// Check to see if the snake has run into itself
			for ( int i = 1; i < snakeLength; i++ )
			{
				if (( snake[0].x == snake[i].x ) && ( snake[0].y == snake[i].y ))
				{
					gameRunning = false;
					break;
				}
			}

			// Check to see if the snake (head) has crashed into a wall
			if ( gameRunning == true ) // If it's already false no need to do further checks
			{
				if ((( (snake[0].x<1 ) || (snake[0].x>78) || (snake[0].y<2) || (snake[0].y>23) )))
				{
					gameRunning = false;
				}
			}
					
			// We still draw the snake even if it has crashed, so the player can see where they went wrong
			// Draw the new snake
			for ( int i = 0; i < snakeLength; i++ )
			{
				Console.SetCursorPosition(snake[i].x, snake[i].y);
            			Console.Write("*");
			}

			if ( gameRunning == true ) // No need to do this if the game should be over.
			{
				for (counter = 0; counter < maxFood; counter++)
				{
	
					// Increase the variable until it reaches the foodLifeLength
					foodInfo[counter].foodLifeLengthTime++;			
		
                			// Need to detect snake and food collision then update score and add new food in a new place
                			if ((snake[0].x == foodInfo[counter].foodX) && (snake[0].y == foodInfo[counter].foodY)) // Collision
                			{
						calculateScore(foodInfo[counter].foodColor, ref score, difficulty, ref playerInfo[10].score);
                    				//score = score + 50;
                    				drawFoodDrawScore(ref foodInfo[counter].foodX, ref foodInfo[counter].foodY,
							ref foodInfo[counter].foodLifeLength, ref foodInfo[counter].foodColor, ref score);
						snakeLength++;
                			}

	                		// Has the food expired?
        	        		if (foodInfo[counter].foodLifeLength == foodInfo[counter].foodLifeLengthTime)
                			{
                   		 		Console.SetCursorPosition(foodInfo[counter].foodX, foodInfo[counter].foodY);
                   	 			Console.Write(" "); // Delete the food

	                   	 		// Have to reset the time length check because it will never be met again otherwise
        	           	 		foodInfo[counter].foodLifeLengthTime = 0;

	                   	 		// Have to draw some more food because there is none now
        	            			drawFoodDrawScore(ref foodInfo[counter].foodX, ref foodInfo[counter].foodY,
							ref foodInfo[counter].foodLifeLength, ref foodInfo[counter].foodColor, ref score);
	
        	        		}
				}
			}
			Thread.Sleep(200 / difficulty); // Have a brief pause, this uses the difficulty modifier to determine the snake speed
		}// End of while loop closing bracket

		// If the player arrived at this point then it must be GAMEOVER!
		Console.ForegroundColor = ConsoleColor.Red;
		showGameStatus(ref gameStatusGameOver); // Change the game status accordingly
		Console.Beep(30000, 300); // (frequency, duration)
		Console.ReadLine(); // Not necessary but maybe later add a flashing effect of the game area
		Console.Clear();

		// Ask the player if they want to play again
		Console.SetCursorPosition(0, 0);
		//Console.Write ("Do you wish to play again? y/n : ");
		do{
			Console.Write ("Do you wish to play again? y/n : ");
			getInputCheckInput(ref validInput); // call the input validation method
			if ( validInput == 1 ) // Chose yes
			{
				inputCheck = true;
				gameRunning = true;
				playAgain = true;
				getPlayerName(ref playerInfo[10].name); // Incase a new player is playing
				setDifficulty(ref difficulty);	// Player may want to change the difficulty			
			}
			if ( validInput == 0 ) // Chose no
			{
				inputCheck = true;
				gameRunning = true;
				updateHighScores = true;
				displayHighScores(ref updateHighScores, ref playerInfo[10].score, ref playerInfo[10].name);
				displayMenu();
				executeMenu(ref playAgain, ref difficulty, ref inputCheck, ref validInput, ref quit,
					ref updateHighScores, ref playerInfo[10].score, ref playerInfo[10].name);
				if ( quit )
				{
					return;
				}
			}
		}while ( inputCheck == false );
		inputCheck = false; // We put it back to this because it could be used again.
		
};
Console.ForegroundColor = ConsoleColor.Gray; // Set the original console colour back to what it was
		
}
catch
{
	Console.Clear();
	Console.Write("An unexpected error occurred; please contact the software author.");
	Console.ForegroundColor = ConsoleColor.Gray;
}
	}


	static void drawFoodDrawScore(ref int randX, ref int randY, ref int foodLifeLength, ref int foodColor, ref int score)
	{
		Random rand = new Random(); // Used for random placing of food
		
		Console.SetCursorPosition(0, 0);
		Console.Write("Score : " + score);

		randX = rand.Next(2, 79); // Random will never reach our boundary, goes up to but not including the number.
		randY = rand.Next(2, 24);

		foodColor = rand.Next(1, 4); // Number between 1 and 3, 3 different colours.

		// Determine the colour of the food
		switch(foodColor)
		{
			case 1:
			Console.ForegroundColor = ConsoleColor.DarkRed;
			break;
			
			case 2:
			Console.ForegroundColor = ConsoleColor.Magenta;
			break;
	
			case 3:
			Console.ForegroundColor = ConsoleColor.Gray;
			break;
		}		

		Console.SetCursorPosition(randX, randY); // Set food co-ords up
		Console.Write("."); // Draw the food
		Console.ForegroundColor = ConsoleColor.Green;

		// Set up the timer for how long the food is displayed for
		foodLifeLength = 50 + rand.Next(20); // This needs to be dependant on the value, call a method within a method for readability
		Thread.Sleep(20); // Needed, otherwise not all food is shown, .NET bug?
	}

	static void showGameStatus(ref string gameStatus)
	{
		string gameStatusText = "Game status : ";
		int gameStatusX = 50;
		
		Console.SetCursorPosition(gameStatusX, 0);
		Console.Write(gameStatusText + gameStatus + " "); // We add a space so we don't have to clear screen from "running" to "paused"
		Console.ForegroundColor = ConsoleColor.Green;
	}

	static void getInputCheckInput(ref int validInput)
	{
		string userInput;
		bool inputCheck = false;

		while (inputCheck == false)
		{
			userInput = Console.ReadLine();
			userInput = userInput.ToUpper();

			Console.Clear();
			if ( userInput == "Y" )
			{
				inputCheck = true; // Set the flag so we will quit the loop
				validInput = 1; // This way the method can be called by other game aspects
				break; // Can't be anything else no need to continue
			}
			if ( userInput == "N" )
			{
				inputCheck = true; // Set the flag so we will quit the loop
				validInput = 0; // This way the method can be called by other game aspects
				break; // Can't be anything else no need to continue
			}
			if (( userInput != "Y" ) || ( userInput != "N" ))
			{
				Console.Write("That was not a valid form of input, you must enter \"y\" or \"n\". \nPlease try again. : ");
			}
		};
	}

	static void showGameInstructions(ref bool inputCheck, ref int validInput)
	{
		bool showAgain = true;
		int yPos = 0;	

		do{
			yPos = 0;
			Console.Clear();
			Console.SetCursorPosition(30, yPos);
			Console.Write("Snake - How to play");
			yPos++;
			for ( int i = 30; i < 49; i++ )
			{
				Console.SetCursorPosition(i, yPos);
				Console.Write("-");
			}
			yPos++;
			Console.SetCursorPosition(0, yPos);
			Console.Write("Game Background");
			yPos++;
			for ( int i = 0; i < 15; i++ )
			{
				Console.SetCursorPosition(i, yPos);
				Console.Write("-");
			}
			yPos++;
			Console.SetCursorPosition(0, yPos);
			Console.WriteLine("You are a snake on an island called Black Forest.");
			yPos++;
			Console.WriteLine("As you know an island is surrounded by water.");
			yPos++;
			Console.WriteLine("This is very bad for you as you are a snake who cannot tolerate water.");
			yPos++;
			Console.WriteLine("In other words if you touch any water you will be instantly killed!");
			yPos++;
			Console.WriteLine("You are not the smartest snake out there either, if you accidentally bump");
			yPos++;
			Console.WriteLine("into yourself you will eat yourself and die!");
			yPos = yPos + 2;
			showMoreText(ref yPos);

			Console.SetCursorPosition(0, yPos);
			Console.Write("Game Mechanics");
			yPos++;
			for ( int i = 0; i < 14; i++ )
			{
				Console.SetCursorPosition(i, yPos);
				Console.Write("-");
			}
			yPos++;
			Console.SetCursorPosition(0, yPos);
			Console.WriteLine("The aim of the game is to get the highest score.");
			yPos++;
			Console.WriteLine("You do this by steering your snake around the screen,");
			yPos++;
			Console.WriteLine("and collecting as much food as possible before it disappears.");
			yPos++;
			Console.WriteLine("Whilst all the time avoiding water, as this will kill you.");
			yPos = yPos + 2;
			showMoreText(ref yPos);
			
			Console.SetCursorPosition(0, yPos);
			Console.Write("Game Controls");
			yPos++;
			for ( int i = 0; i < 13; i++ )
			{
				Console.SetCursorPosition(i, yPos);
				Console.Write("-");
			}
			yPos++;
			Console.SetCursorPosition(0, yPos);
			Console.WriteLine("UpArrow    - Move the snake up");
			yPos++;
			Console.WriteLine("DownArrow  - Move the snake down");
			yPos++;
			Console.WriteLine("LeftArrow  - Move the snake left");
			yPos++;
			Console.WriteLine("RightArrow - Move the snake right");
			yPos++;
			Console.WriteLine("P          - Pause the game");
			yPos = yPos + 2;
			showMoreText(ref yPos);

			Console.SetCursorPosition(0, yPos);
			Console.Write("Game Legend");
			yPos++;
			for ( int i = 0; i < 11; i++ )
			{
				Console.SetCursorPosition(i, yPos);
				Console.Write("-");
			}
			yPos++;
			Console.SetCursorPosition(0, yPos);
			Console.WriteLine("The snake            -            *");
			yPos++;
			Console.ForegroundColor = ConsoleColor.Blue;
			Console.WriteLine("Water                -            *");
			yPos++;
			Console.ForegroundColor = ConsoleColor.DarkRed;
			Console.WriteLine("Lowest value food    -            .");
			yPos++;
			Console.ForegroundColor = ConsoleColor.Magenta;
			Console.WriteLine("Middle value food    -            .");
			yPos++;
			Console.ForegroundColor = ConsoleColor.Gray;
			Console.WriteLine("Highest value food   -            .");
			yPos = yPos + 2;

			Console.ForegroundColor = ConsoleColor.Green;
			Console.SetCursorPosition(0, yPos);
			do{
				Console.Write("Would you like to view this information again? : y/n ");
				getInputCheckInput(ref validInput);
				if ( validInput == 1 ) // Chose yes
				{
					inputCheck = true;
				}
				if ( validInput == 0 ) // Chose no
				{
					inputCheck = true;
					showAgain = false;
				}
			}while (inputCheck == false);
		}while (showAgain);
		
	}

	static void showMoreText(ref int yPos)
	{
		Console.SetCursorPosition(0, yPos);
		Console.Write("Please press 'Enter' for more game instructions.");
		Console.ReadLine();
		yPos = 0; // Set it to 0 for new text
		Console.Clear(); // Clear the screen for next instructions
		// Write the title so it appears on every appropriate page
		Console.SetCursorPosition(30, yPos);
		Console.Write("Snake - How to play");
		yPos++;
		for ( int i = 30; i < 49; i++ )
		{
			Console.SetCursorPosition(i, yPos);
			Console.Write("-");
		}
		yPos++;
	}

	static void calculateScore(int foodInfo, ref int score, int difficulty, ref int playerScore)
	{
		switch (foodInfo)
		{
			case 1: // Lowest score
			score = ( score + 25 ) * difficulty;
			playerScore = score;
			break;
			
			case 2: // Middle score
			score = ( score + 50 ) * difficulty;
			playerScore = score;
			break;

			case 3:	// Highest score
			score = ( score + 75 ) * difficulty;
			playerScore = score;
			break;
		}
	}

	static void displayMenu()
	{
		int yPos = 0;
		int xPos = 35;
		int menuConnect = 6;

		Console.Clear();
		// Incase of been called more then once reset vars
		yPos = 0;
		xPos = 35;
		menuConnect = 5;

		// Draw top part of "Snake Menu"
		Console.ForegroundColor = ConsoleColor.Blue;
		Console.SetCursorPosition(xPos, yPos);
		for ( int i = 35; i < 47; i++ )
		{
			Console.SetCursorPosition(i, yPos);
			Console.Write("*");
		}
		yPos++;
		
		// Draw bottom part of "Snake Menu"
		for ( int i = 35; i < 47; i++ )
		{
			Console.SetCursorPosition(i, yPos + 1);
			Console.Write("*");
		}

		// Draw left part of "Snake Menu"
		for ( int i = 1; i < 2; i++ )
		{
			Console.SetCursorPosition(xPos, i);
			Console.Write("*");
		}
		
		// Draw the right part of the "Snake Menu"
		for ( int i = 1; i < 2; i++ )
		{
			Console.SetCursorPosition(xPos + 11, i);
			Console.Write("*");
		}

		Console.SetCursorPosition(xPos + 1, yPos);
		Console.ForegroundColor = ConsoleColor.Green;
		Console.Write("Snake Menu");

		//yPos = 3;
		// Draw the line from "Snake Menu title" to the menu
		Console.ForegroundColor = ConsoleColor.Blue;
		for( int i = 3; i < menuConnect; i++ )
		{
			Console.SetCursorPosition(xPos + 5, i);
			Console.Write("*");
		}

		// Write the menu contents
		Console.ForegroundColor = ConsoleColor.Green;
		Console.SetCursorPosition(xPos - 2, yPos + 5);
		Console.Write("1 - New Game");
		Console.SetCursorPosition(xPos - 2, yPos + 6);
		Console.Write("2 - Difficulty");
		Console.SetCursorPosition(xPos - 2, yPos + 7);
		Console.Write("3 - High Scores");
		Console.SetCursorPosition(xPos - 2, yPos + 8);
		Console.Write("4 - Quit");
		
		yPos = 5;
		// Draw top part of "Menu contents"
		Console.ForegroundColor = ConsoleColor.Blue;
		Console.SetCursorPosition(xPos + 4, yPos);
		for ( int i = 31; i < 51; i++ )
		{
			Console.SetCursorPosition(i, yPos);
			Console.Write("*");
		}
		yPos++;
		
		// Draw bottom part of "Menu contents"
		for ( int i = 31; i < 51; i++ )
		{
			Console.SetCursorPosition(i, yPos + 4);
			Console.Write("*");
		}

		// Draw left part of "Menu contents"
		for ( int i = 6; i < 10; i++ )
		{
			Console.SetCursorPosition(xPos - 4, i);
			Console.Write("*");
		}
		
		// Draw the right part of the "Menu contents"
		for ( int i = 6; i < 10; i++ )
		{
			Console.SetCursorPosition(xPos + 15, i);
			Console.Write("*");
		}

		// Draw the line from "Snake Menu Contents" to input box
		for( int i = 11; i < 13; i++ )
		{
			Console.SetCursorPosition(xPos + 5, i);
			Console.Write("*");
		}

		// Draw the top part of the "Input Box"
		for ( int i = 0; i < 80; i++ )
		{
			Console.SetCursorPosition(i, 13);
			Console.Write("*");
		}

		// Draw the left part of the "Input Box"
		for ( int i = 13; i < 18; i++ )
		{
			Console.SetCursorPosition(0, i);
			Console.Write("*");
		}

		// Draw the bottom part of the "Input Box"
		for ( int i = 0; i < 80; i++ )
		{
			Console.SetCursorPosition(i, 18);
			Console.Write("*");
		}

		// Draw the right part of the "Input Box"
		for ( int i = 13; i < 18; i++ )
		{
			Console.SetCursorPosition(79, i);
			Console.Write("*");
		}

		Console.ForegroundColor = ConsoleColor.Green;
		
	}

	static void getMenuInputCheckInput(ref int validInput, ref bool inputCheck)
	{
		string userInput;

		inputCheck = false;

		while(inputCheck == false)
		{
			userInput = Console.ReadLine();
			switch(userInput)
			{
				case "1": // New game
				inputCheck = true; // So we break the loop
				validInput = 1; // number determines next actions
				Console.Clear();
				break;

				case "2": // Difficulty
				inputCheck = true;
				validInput = 2;
				Console.Clear();
				break;

				case "3": // High Scores
				inputCheck = true;
				validInput = 3;
				Console.Clear();
				break;

				case "4": // Quit
				inputCheck = true;
				validInput = 4;
				Console.Clear();
				break;
			}

			if ( inputCheck == false )
			{
				Console.Clear();
				displayMenu();
				//Console.SetCursorPosition(1, 14);
				//Console.WriteLine("Please choose an option (1/2/3/4) from the menu : ");
				Console.SetCursorPosition(1, 14);
				Console.Write("That was not a valid input, enter \"1\",\"2\",\"3\", or \"4\" : ");
			}
		}
	}

	static void getPlayerName(ref string playerName)
	{
		bool inputCheck = false;		

		Console.ForegroundColor = ConsoleColor.Green;
		Console.Clear();
		Console.Write("Please enter your name : ");

		while(inputCheck == false)
		{
			playerName = Console.ReadLine();
			if ( playerName == "" ) // No input
			{
				Console.Clear();
				Console.Write("You must enter a name, please try again : ");
			}
			else
			{
				inputCheck = true; // Set the flag so we quit the loop and return from the method
				Console.Clear();
			}
		}	
	}
	static void setDifficulty(ref int difficulty)
	{
		string userInput;
		bool inputCheck = false;

		// Show the default/current difficulty level
		switch(difficulty)
		{
			case 1: // Easy
			Console.WriteLine("Current difficulty level is : Easy");
			break;

			case 2: // Medium
			Console.WriteLine("Current difficulty level is : Medium");
			break;

			case 3: // Hard
			Console.WriteLine("Current difficulty level is : Hard");
			break;
		}

		Console.ForegroundColor = ConsoleColor.Green;
		Console.Clear();
		Console.WriteLine("1.) - Easy\n2.) - Medium\n3.) - Hard");
		Console.Write("Please choose a difficulty level : ");

		// Validate the input
		while (inputCheck == false)
		{
			try // Incase a non-numerical value is entered we must catch the exception
			{
				userInput = Console.ReadLine();
				difficulty = Int32.Parse(userInput);
			}
			catch
			{
				Console.Clear();
				Console.WriteLine("1.) - Easy\n2.) - Medium\n3.) - Hard");
				Console.Write("That was not a valid choice, please enter \"1\", \"2\", or \"3\" : ");
			}
			if (( difficulty < 1 ) || ( difficulty > 3 )) // Didn't choose a valid difficulty
			{
				Console.Clear();
				Console.WriteLine("1.) - Easy\n2.) - Medium\n3.) - Hard");
				Console.Write("That was not a valid choice, please enter \"1\", \"2\", or \"3\" : ");	
			}
			else
			{
				inputCheck = true; // Set the flag to quit the loop and return from the method
			}
		}
	}

	static void executeMenu(ref bool playAgain, ref int difficulty, ref bool inputCheck,
		ref int validInput, ref bool quit, ref bool updateHighScores, ref int playerTempScore, ref string playerTempName)
	{
		Console.SetCursorPosition(1, 14);
		Console.Write("Please choose an option (1/2/3/4) from the menu : ");
		getMenuInputCheckInput(ref validInput, ref inputCheck); // Method keeps looping until it has correct input
		inputCheck = false; // We put it back to this because flag could be used again.

		// Now we determine what to do next from menu input
		switch(validInput)
		{
			case 1:
			inputCheck = true;
			playAgain = true; // Flag to start the game/play again
			getPlayerName(ref playerTempName); // Get the player's name, method loops until get's a valid input
			break;

			case 2:
			inputCheck = true;
			playAgain = true;
			setDifficulty(ref difficulty);
			// Set the Difficulty so now need to go back to the main menu
			displayMenu();
			executeMenu(ref playAgain, ref difficulty, ref inputCheck, ref validInput, ref quit,
				ref updateHighScores, ref playerTempScore, ref playerTempName);
			break;

			case 3:
			inputCheck = true;
			updateHighScores = true;
			displayHighScores(ref updateHighScores, ref playerTempScore, ref playerTempName);
			displayMenu();
			executeMenu(ref playAgain, ref difficulty, ref inputCheck, ref validInput, ref quit,
				ref updateHighScores, ref playerTempScore, ref playerTempName);
			break;

			case 4:
			Console.ForegroundColor = ConsoleColor.Gray;
			// can't use return as we will just return from the method
			// so check for case 4 outside of the method
			quit = true;
			break;
		}
	}

	static void displayHighScores(ref bool updateHighScores, ref int tempPlayerScore, ref string tempPlayerName)
	{
		int maxNames = 11;
		int arrayLength = 10;
		int rightEdge = arrayLength - 1;

		string fileNameNames = "Names.txt";
		string fileNameScores = "Scores.txt";

		player[] playerInfo = new player [maxNames];


		TextReader textInScores = new StreamReader(fileNameScores);
		for ( int i = 0; i < maxNames; i++ )
		{
			playerInfo[i].score = Int32.Parse(textInScores.ReadLine());
		}
		textInScores.Close();

		TextReader textInNames = new StreamReader(fileNameNames);
		for ( int i = 0; i < maxNames; i++ )
		{
			playerInfo[i].name = textInNames.ReadLine();
		}
		textInNames.Close();

		playerInfo[10].score = tempPlayerScore;
		playerInfo[10].name = tempPlayerName;

		if ( updateHighScores == true )
		{
			updateHighScores = false;
			updateHighScoreTable(ref playerInfo[10].score, ref playerInfo[10].name);
		}

		TextReader textInScores2 = new StreamReader(fileNameScores);
		for ( int i = 0; i < maxNames; i++ )
		{
			playerInfo[i].score = Int32.Parse(textInScores2.ReadLine());
		}
		textInScores2.Close();

		TextReader textInNames2 = new StreamReader(fileNameNames);
		for ( int i = 0; i < maxNames; i++ )
		{
			playerInfo[i].name = textInNames2.ReadLine();
		}
		textInNames2.Close();

		// Write the title and add a blue underline
		Console.WriteLine("High Scores Table");
		Console.ForegroundColor = ConsoleColor.Blue;
		for ( int i = 0; i < 17; i++ )
		{
			Console.SetCursorPosition(i, 1);
			Console.Write("*");
		}
		// Write the high scores
		Console.SetCursorPosition(0,2);
		Console.WriteLine("");
		Console.ForegroundColor = ConsoleColor.Green;
		for ( int i = 0; i < maxNames - 1; i++ )
		{
			Console.WriteLine(playerInfo[i].score + "  -  " + playerInfo[i].name);
		}
		Console.WriteLine("");
		Console.Write("Please press enter to continue.");
		Console.ReadLine();
	}

	static void updateHighScoreTable(ref int tempPlayerScore, ref string tempPlayerName)
	{
		int maxNames = 11;
		int arrayLength = 10;
		int rightEdge = arrayLength - 1;
		int temp;

		string fileNameNames = "Names.txt";
		string fileNameScores = "Scores.txt";
		string tempName;

		player[] playerInfo = new player [maxNames];

		TextReader textInScores = new StreamReader(fileNameScores);
		for ( int i = 0; i < maxNames; i++ )
		{
			playerInfo[i].score = Int32.Parse(textInScores.ReadLine());
		}
		textInScores.Close();

		TextReader textInNames = new StreamReader(fileNameNames);
		for ( int i = 0; i < maxNames; i++ )
		{
			playerInfo[i].name = textInNames.ReadLine();
		}
		textInNames.Close();

		playerInfo[10].name = tempPlayerName;
		playerInfo[10].score = tempPlayerScore;

		for ( int j = rightEdge; j >= 0; j-- )
		{
			for ( int i = 0; i <= j; i++ )
			{
				if ( playerInfo[i].score < playerInfo[i + 1].score )
				{
					temp = playerInfo[i].score;
					playerInfo[i].score = playerInfo[i + 1].score;
					playerInfo[i + 1].score = temp;

					tempName = playerInfo[i].name;
					playerInfo[i].name = playerInfo[i + 1].name;
					playerInfo[i + 1].name = tempName;
				}
			}
		}

		TextWriter textOutScores = new StreamWriter(fileNameScores);
		for ( int i = 0; i < maxNames; i++ )
		{
			textOutScores.WriteLine(playerInfo[i].score);
		}
		textOutScores.Close();
		TextWriter textOutNames = new StreamWriter(fileNameNames);
		for ( int i = 0; i < maxNames; i++ )
		{
			textOutNames.WriteLine(playerInfo[i].name);
		}
		textOutNames.Close();
	}
}