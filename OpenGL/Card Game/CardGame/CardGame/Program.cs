//////////////////////////////////////////////////////////
///////////Author: Jamie Sandell
///////////Signed On: 11:28am - Tuesday 2nd December 2008
///////////Work Done: Created and worked on the game
///////////Signed Off: 2:00pm - Tuesday 2nd December 2008
////
///////////Signed On: 10:40am - Wednesday 3rd December 2008
///////////Work Done: Worked on the update and draw methods, and general game logic
///////////Signed Off: 3:15pm - Wednesday 3rd December 2008
////
///////////Signed On: 6:48pm - Wednesday 3rd December 2008
///////////Work Done: Worked on the logic
///////////Signed Off: 9:00pm - Wednesday 3rd December 2008
////
///////////Signed On: 9:30am - Thursday 4th December 2008
///////////Work Done: Worked on the logic. The game now plays on Easy
///////////             but no sound, score, highscore table, or
///////////             replayability is available
///////////Signed Off: 4:15pm - Thursday 4th December 2008
////
///////////Signed On: 1:30pm - Saturday 6th December 2008
///////////Work Done: Added music/sounds and worked on game logic.
///////////Signed Off: 5:06pm - Saturday 6th December 2008
////
///////////Signed On: 10:19am - Sunday 7th December 2008
///////////Work Done:
///////////Signed Off:
//////////////////////////////////////////////////////////



///////////////TODO:
////////////// Bonus Card code needs adding
////////////// Medium and Hard mode needs implementing
////////////// Scoring needs implementing for Easy, Medium, and Hard modes
////////////// Game over state needs adding
////////////// Loading and displaying of the highscore table in the GameOver state
////////////// Player can enter their name if they get on the high score table
////////////// Loading/Saving the highscore table
////////////// Adding methods to remove any duplicate code
//Bonus Card
//The player can score a bonus 20 points by correctly matching the bonus pair as indicated on the User
//Interface. The Bonus pair will be a randomly selected pair from the selection of cards and will only be
//available to the player once for 10 seconds and will appear at a random time during the game.
//Power Up
//The player will be able to earn a power up where they will be able to reveal all the cards for a short time
//(1 second). This power up will be earned by matching 4 pairs in a row and will be selectable from the User
//Interface.
//Hint
//The player will be able to get a hint for a point deduction of 7 points * difficulty per hint. The hint 
//will highlight a pair to the player for 1 second.
//Difficulty
//There will be three different levels of difficulty for the game; Easy, Medium and Hard. The differences 
//between them shall be as follows:
//Easy – 12 pairs of cards to match, descriptions on cards, normal scoring, 1.5 minute time limit.
//Medium – 18 pairs of cards to match, descriptions, double scoring, 1.5 minute time limit.
//Hard – 24 pairs of cards to match, no descriptions, triple scoring, 1.5 minute time limit.
//User Interface
//The main game screen will consist of the following items:
//•	The main play area – the area where the cards are displayed and interacted with
//•	Score – this will be displayed in the top right hand corner of the screen
//•	Time – the remaining time will be displayed in the top right below the score
//•	Bonus indicator – the card worth bonus points will be displayed in the right hand side of the screen in
//the centre for as long as the bonus is active for.
//•	Power-Up – A button for the power up only active when one available.
//•	Hint – A button for the hint.
//•	Menu – A menu bar comprising of new game, high score, help and exit.
//The following screens will be presented to the player when they begin the game:
//•	Title and Description Screen – the title of the game and a short description of what the player has to
//do, including a list of all the cards the player will see in the game
//•	Game play screen – the game
//•	High score table – a chance for the player to enter their score into the table and compare it to other 
//players
//Objectives and Scoring
//The objective of the game is to clear all of the cards from the playing area before the time limit expires.
//Players will score 5 points for every pair of cards they correctly match, 20 bonus points can be scored for
//matching the cards indicated in the user interface. If the player completes the level before the time has 
//run out then they will also score 1 point for every second left on the clock.
//If the player matches more than 1 pair in a row they earn a 2x score multiplier where every matched pair is
//worth double points. If they match 4 in a row they will earn a 3x multiplier and earn a power up.






using System;
using System.Drawing;
using System.Windows.Forms;
using System.Collections;
using Tao.OpenGl;
using Tao.FreeGlut;
using System.Runtime.InteropServices;
using System.Media;

namespace CardGame
{
    /// <summary>
    /// Summary description for CardGame
    /// </summary>

    public class CardGame
    {

        #region Member Variables

        // WINDOW PARAMETERS
        // World window co-ordinates
        private static double _winL = -15;
        private static double _winR = 15;
        private static double _winT = 15;
        private static double _winB = -15;

        // Window dimensions
        private static int _winWidth = 800;
        private static int _winHeight = 600;

        // Window Title
        private static string _title = "08343 - Team09 - Pairs: Radiation";

        private static uint[] _MBackgroundTexture; // Stores the texture ID
        private static string[] _MBackgroundTextureName; // Stores the texture name
        private static uint[] _MCardBacksTexture;
        private static string[] _MCardBacksTextureName;
        private static uint[] _MBonusCardTexture;
        private static string[] _MBonusCardTextureName;
        private static uint[] _MCardEasyTexture;
        private static string[] _MCardEasyTextureName;
        private static uint[] _MCardHardTexture;
        private static string[] _MCardHardTextureName;
        private static uint[] _MCardShieldTexture;
        private static string[] _MCardShieldTextureName;

        private static int[] cardRow;
        private static int[] cardCol;
        private static bool mouseClicked = false; // used for deciding to render to the back
                                                    // buffer, picking based on colour coding
        private static int cursorX;
        private static int cursorY;
        private static int _MCurrentSceneToDraw = 0;
        private static bool easyMode = true;
        private static bool mediumMode = false;
        private static bool hardMode = false;
        private static bool firstRun = true; // Used for initialisations
        private static string[] protections = new string[6];
        private static int[] chosenEasy = new int[12]; // Use this to check easyCards
        private static int[] chosenMedium = new int[18]; // Medium
        private static int[] chosenHard = new int[24]; // Hard
        private static string[] rays = new string[6];
        private static bool alreadyChosenThatCard = true;
        private static ArrayList noneFlippedRayCards = new ArrayList();
        private static ArrayList flippedRayCards = new ArrayList(); // Remember to skip 'dead' cards
        private static ArrayList noneFlippedProtectionCards = new ArrayList();
        private static ArrayList flippedProtectionCards = new ArrayList(); // Remember to skip 'dead' cards
        private static bool flippedRayCard = false; // Keep track of what is flipped, don't want the user
                                                        // flipping two ray cards
        private static bool flippedProtectionCard = false;
        private static int timeSinceFlipped; // don't want to turn the cards back over too soon
        private static bool stopMusic = true;
        private static int score = 0;
        private static int pairsInARow = 0;
        // Class instances
        private static Card[] cardRay;
        private static Card[] cardProtection;
        private static Player myPlayer = new Player();
        private static ScoringSystem myScoringSystem = new ScoringSystem();
        private static Texture[] myTexture;
        private static Timer cardFlippedTimer = new Timer(); // Control how long cards remain flipped for
        private static Timer timeRemainingTimer = new Timer();
        private static UserInterface myUI = new UserInterface();
        private static Text myText = new Text();
        // Music and Sounds
        private static SoundPlayer backgroundMusic = new SoundPlayer();
        private static SoundPlayer cardFlip = new SoundPlayer();
        private static SoundPlayer incorrectMatch = new SoundPlayer();
        private static SoundPlayer correctMatch = new SoundPlayer();
        #endregion

        private CardGame()
        {
        }

        #region Main(string[] args)
        [STAThread]
        public static void Main(string[] args)
        {

            Glut.glutInit();
            Glut.glutInitDisplayMode(Glut.GLUT_RGBA | Glut.GLUT_DOUBLE | Glut.GLUT_DEPTH);
            Glut.glutInitWindowSize(_winWidth, _winHeight);
            Glut.glutInitWindowPosition(0, 0);
            Glut.glutCreateWindow(_title);
            Glut.glutSetWindowTitle(_title);
            Glut.glutDisplayFunc(new Glut.DisplayCallback(Display));
            Glut.glutReshapeFunc(new Glut.ReshapeCallback(Reshape));

            // Interface callbacks
            Glut.glutKeyboardFunc(new Glut.KeyboardCallback(Keyboard));
            Glut.glutPassiveMotionFunc(new Glut.PassiveMotionCallback(PassiveMouse));
            Glut.glutMouseFunc(new Glut.MouseCallback(MouseCallback));

            // Idle function for animation
            Glut.glutIdleFunc(new Glut.IdleCallback(Idle));

            //Glut.GlutFullScreen(); // Full screen option.

            // Start main loop
            Glut.glutMainLoop();
        }
        #endregion Main(string[] args)

        #region CustomMethods

        public static void ProcessPick(Card[] inCard)
        {
            int[] viewport = new int[4];
            byte[] pixel = new byte[3];


            Gl.glGetIntegerv(Gl.GL_VIEWPORT, viewport);
            Gl.glReadPixels(cursorX, viewport[3] - cursorY, 1, 1, Gl.GL_RGB, Gl.GL_UNSIGNED_BYTE, pixel);

            if (pixel[1]!=255) // Don't check clicks against the background
            {
                // Find out which card was clicked
                int[] colourId = new int[3];
                for (int i = 0; i < inCard.Length; i++)
                {
                    colourId = inCard[i].GetColourID();
                    if (colourId[0]==pixel[0]) // found the card that was clicked
                    {
                        bool result = inCard[i].IsFlipped(); // If it's already been clicked/flipped
                                                                // don't flip it again
                        if (!result)
                        {
                            // If a ray card has been flipped
                            if ((!flippedRayCard)&& (inCard[i].GetType()=="Ray"))
                            {
                                inCard[i].FlipCard();
                                flippedRayCard = true;
                                cardFlip.Play();
                            }
                            // If a protection card has been flipped
                            if ((!flippedProtectionCard) && (inCard[i].GetType() == "Protection"))
                            {
                                inCard[i].FlipCard();
                                cardFlip.Play();
                                flippedProtectionCard = true;
                            }
                            //// If both a protection and ray card have been flipped
                            if ((flippedRayCard) && (flippedProtectionCard)) // have we got a match?
                            {
                                // start the timer
                                cardFlippedTimer.StopTimer();
                                cardFlippedTimer.ResetTimer();
                                cardFlippedTimer.StartTimer();
                            //}
                            //{
                                int rayIndex = 0;
                                int protectionIndex = 0;
                                foreach (Card ray in cardRay)
                                {
                                    if (ray.IsFlipped())
                                    {
                                        break;
                                    }
                                    rayIndex++;
                                    if (rayIndex==12)
                                    {
                                        rayIndex = 11;
                                    }
                                }
                                foreach (Card protection in cardProtection)
                                {
                                    if (protection.IsFlipped())
                                    {
                                        break;
                                    }
                                    protectionIndex++;
                                    if(protectionIndex==12)
                                    {
                                        protectionIndex = 11;
                                    }
                                }
                            }
                        }
                        break; // Found the card that was clicked, no need to check the rest
                    }
                }
            }
        }

        private static void IsPairFound()
        {
            // If both a protection and ray card have been flipped
            if ((flippedRayCard) && (flippedProtectionCard)) // have we got a match?
            {
                // Do not process any of this until the timer has exceeded it's designated time
                // This way two turned over cards stay turned over
                int timeElapsed = cardFlippedTimer.GetTimeElapsed();
                if (timeElapsed >= 1000)
                {
                    cardFlippedTimer.ResetTimer();
                    cardFlippedTimer.StopTimer();
                    int rayIndex = 0;
                    int protectionIndex = 0;
                    foreach (Card ray in cardRay)
                    {
                        if (ray.IsFlipped())
                        {
                            break;
                        }
                        rayIndex++;
                    }
                    foreach (Card protection in cardProtection)
                    {
                        if (protection.IsFlipped())
                        {
                            break;
                        }
                        protectionIndex++;
                    }
                    // Now got the Index of the cards flipped
                    bool result = cardRay[rayIndex].IsPair(cardRay[rayIndex].GetRay(),
                        cardProtection[protectionIndex].GetProtection());
                    if (result) // found a match
                    {
                        cardRay[rayIndex].SetAliveStatus(false);
                        cardProtection[protectionIndex].SetAliveStatus(false);
                        flippedProtectionCard = false;
                        flippedRayCard = false;
                        cardRay[rayIndex].FlipCard();
                        cardProtection[protectionIndex].FlipCard();
                        correctMatch.Play();
                        pairsInARow++; // used as a score multiplier
                        if (easyMode)
                        {
                            if ((pairsInARow > 0) && (pairsInARow < 4)) // if 4 multiplier = x3
                            {
                                score += 5 * 2; // 2x multiplier
                            }
                            if (pairsInARow >= 4)
                            {
                                ///TODO:
                                ///Bonus code needs adding
                                score += 5 * 3; // 3x multiplier
                            }
                            if (pairsInARow==0)
                            {
                                score += 5;
                            }
                            myUI.SetScore(score);
                        }
                        if (mediumMode)
                        {
                            if ((pairsInARow > 0) && (pairsInARow < 4)) // if 4 multiplier = x3
                            {
                                score += 10 * 2; // 2x multiplier
                            }
                            if (pairsInARow >= 4)
                            {
                                score += 10 * 3; // 3x multiplier
                            }
                            if (pairsInARow == 0)
                            {
                                score += 10; // double scoring
                            }
                            myUI.SetScore(score);
                        }
                        if (hardMode)
                        {
                            if ((pairsInARow > 0) && (pairsInARow < 4)) // if 4 multiplier = x3
                            {
                                score += 15 * 2; // 2x multiplier
                            }
                            if (pairsInARow >= 4)
                            {
                                score += 15 * 3; // 3x multiplier
                            }
                            if (pairsInARow == 0)
                            {
                                score += 15; // triple scoring
                            }
                            myUI.SetScore(score);
                        }
                    }
                    else // flip them back
                    {
                        flippedProtectionCard = false;
                        flippedRayCard = false;
                        cardRay[rayIndex].FlipCard();
                        cardProtection[protectionIndex].FlipCard();
                        incorrectMatch.Play();
                        pairsInARow = 0;
                    }
                }
            }
        }

        #endregion CustomMethods


        #region MainDisplay

        private static void Update()
        {
            // Initilise the cards
            if (easyMode) // initialise the easyMode parts
            {
                if (firstRun) // set up initial cards
                {
                    cardRay = new Card[12];
                    cardProtection = new Card[12];
                    for (int i = 0; i < cardRay.Length; i++)
                    {
                        cardRay[i] = new Card();
                        cardProtection[i] = new Card();
                    }
                    Random rand = new Random(DateTime.Now.Millisecond);
                    int number; // holds random number
                    int chosenCounter = 0; // So we know what card we're upto
                    for (int i = 0; i < cardRay.Length; i++)
                    {
                        alreadyChosenThatCard = true;
                        while (alreadyChosenThatCard) // need to pick another
                        {
                            number = rand.Next(0, 12);
                            chosenEasy[chosenCounter] = number;
                            for (int j = 0; j <= chosenCounter; j++)
                            {
                                if ((chosenEasy[j] == number) && (j != chosenCounter)) // already been chosen - don't
                                // check current card
                                {
                                    alreadyChosenThatCard = true;
                                    j = 0; // need to check the next new number against all others again
                                    break; // break from the loop and set a new number
                                }
                                if(j == chosenCounter) // If here then a number that hasn't been chosen has been found
                                {
                                    alreadyChosenThatCard = false;
                                    // Not init the card's values
                                    int[] textureArray = new int[2]; // back and front
                                    switch (number) // only breaking 6 times (should do) but not on the same
                                            // number, case 0
                                    {
                                        case 0:
                                            textureArray[0] = (int)_MCardBacksTexture[0];
                                            textureArray[1] = (int)_MCardEasyTexture[0]; // Beta
                                            cardRay[i].SetProtection("Plastic Sheet");
                                            cardRay[i].SetRay("Beta");
                                            cardRay[i].SetTexture(textureArray);
                                            cardRay[i].SetType("Ray");
                                            break;
                                        case 1:
                                            textureArray[0] = (int)_MCardBacksTexture[0];
                                            textureArray[1] = (int)_MCardEasyTexture[1]; // Gamma
                                            cardRay[i].SetProtection("Metal Sheet");
                                            cardRay[i].SetRay("Gamma");
                                            cardRay[i].SetTexture(textureArray);
                                            cardRay[i].SetType("Ray");
                                            break;
                                        case 2:
                                            textureArray[0] = (int)_MCardBacksTexture[0];
                                            textureArray[1] = (int)_MCardEasyTexture[2]; // Infrared
                                            cardRay[i].SetProtection("Tinfoil");
                                            cardRay[i].SetRay("Infrared");
                                            cardRay[i].SetTexture(textureArray);
                                            cardRay[i].SetType("Ray");
                                            break;
                                        case 3:
                                            textureArray[0] = (int)_MCardBacksTexture[0];
                                            textureArray[1] = (int)_MCardEasyTexture[3]; // Laser
                                            cardRay[i].SetProtection("Mirror");
                                            cardRay[i].SetRay("Laser");
                                            cardRay[i].SetTexture(textureArray);
                                            cardRay[i].SetType("Ray");
                                            break;
                                        case 4:
                                            textureArray[0] = (int)_MCardBacksTexture[0];
                                            textureArray[1] = (int)_MCardEasyTexture[4]; // Ultraviolet
                                            cardRay[i].SetProtection("Sunglasses");
                                            cardRay[i].SetRay("Ultraviolet");
                                            cardRay[i].SetTexture(textureArray);
                                            cardRay[i].SetType("Ray");
                                            break;
                                        case 5:
                                            textureArray[0] = (int)_MCardBacksTexture[0];
                                            textureArray[1] = (int)_MCardEasyTexture[5]; // X-Ray
                                            cardRay[i].SetProtection("Lead");
                                            cardRay[i].SetRay("X-Ray");
                                            cardRay[i].SetTexture(textureArray);
                                            cardRay[i].SetType("Ray");
                                            break;
                                        case 6:
                                            textureArray[0] = (int)_MCardBacksTexture[0];
                                            textureArray[1] = (int)_MCardEasyTexture[0]; // Beta
                                            cardRay[i].SetProtection("Plastic Sheet");
                                            cardRay[i].SetRay("Beta");
                                            cardRay[i].SetTexture(textureArray);
                                            cardRay[i].SetType("Ray");
                                            break;
                                        case 7:
                                            textureArray[0] = (int)_MCardBacksTexture[0];
                                            textureArray[1] = (int)_MCardEasyTexture[1]; // Gamma
                                            cardRay[i].SetProtection("Metal Sheet");
                                            cardRay[i].SetRay("Gamma");
                                            cardRay[i].SetTexture(textureArray);
                                            cardRay[i].SetType("Ray");
                                            break;
                                        case 8:
                                            textureArray[0] = (int)_MCardBacksTexture[0];
                                            textureArray[1] = (int)_MCardEasyTexture[2]; // Infrared
                                            cardRay[i].SetProtection("Tinfoil");
                                            cardRay[i].SetRay("Infrared");
                                            cardRay[i].SetTexture(textureArray);
                                            cardRay[i].SetType("Ray");
                                            break;
                                        case 9:
                                            textureArray[0] = (int)_MCardBacksTexture[0];
                                            textureArray[1] = (int)_MCardEasyTexture[3]; // Laser
                                            cardRay[i].SetProtection("Mirror");
                                            cardRay[i].SetRay("Laser");
                                            cardRay[i].SetTexture(textureArray);
                                            cardRay[i].SetType("Ray");
                                            break;
                                        case 10:
                                            textureArray[0] = (int)_MCardBacksTexture[0];
                                            textureArray[1] = (int)_MCardEasyTexture[4]; // UltraViolet
                                            cardRay[i].SetProtection("Sunglasses");
                                            cardRay[i].SetRay("Ultraviolet");
                                            cardRay[i].SetTexture(textureArray);
                                            cardRay[i].SetType("Ray");
                                            break;
                                        case 11:
                                            textureArray[0] = (int)_MCardBacksTexture[0];
                                            textureArray[1] = (int)_MCardEasyTexture[5]; // X-Ray
                                            cardRay[i].SetProtection("Lead");
                                            cardRay[i].SetRay("X-Ray");
                                            cardRay[i].SetTexture(textureArray);
                                            cardRay[i].SetType("Ray");
                                            break;
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        chosenCounter++;
                    }
                    chosenCounter = 0;
                    for (int i = 0; i < chosenEasy.Length; i++)
                    {
                        chosenEasy[i] = 7; // reset all of the chosen values to their original ones
                    }
                    // Set each card into a random position
                    Card[] cardRaySorting = new Card[cardRay.Length];
                    for (int i = 0; i < cardRay.Length; i++)
                    {
                        cardRaySorting[i] = new Card();
                    }
                    float[] rayPosition = new float[12];
                    alreadyChosenThatCard = true;
                    int y = 0; // used for positioning cards correctly
                    for (int i = 0; i < cardRay.Length; i++)
                    {
                        alreadyChosenThatCard = true;
                        while (alreadyChosenThatCard) // need to pick another
                        {
                            number = rand.Next(0, 12);
                            chosenEasy[chosenCounter] = number;
                            for (int j = 0; j <= chosenCounter; j++)
                            {
                                if ((chosenEasy[j] == number) && (j != chosenCounter)) // already been chosen - don't
                                // check first card
                                {
                                    alreadyChosenThatCard = true;
                                    j = 0;
                                    break; // break from the loop and set a new number
                                }
                                if (j == chosenCounter) // If here then a number that hasn't been chosen has been found
                                {
                                    int x;
                                    float topY = 1.0f;
                                    float bottomY = 5.0f;
                                    if (chosenCounter>5) //next row down
                                    {
                                        topY = 7.0f;
                                        bottomY = 11.0f;
                                        x = y;
                                        y++;
                                    }
                                    else
                                    {
                                        x = i;
                                    }
                                    // Will be in a muddled order need to reorder the cardRay array
                                    alreadyChosenThatCard = false;
                                    rayPosition[0] = (float)_winL + 1 + 3 * x; // BottomLeft x
                                    rayPosition[1] = (float)_winT - bottomY; // BottomLeft y
                                    rayPosition[2] = 0.0f; // BottomLeft z
                                    rayPosition[3] = (float)_winL + 3 + 3 * x; // BottomRight x
                                    rayPosition[4] = rayPosition[1]; // BottomRight y
                                    rayPosition[5] = 0.0f; // BottomRight z
                                    rayPosition[6] = rayPosition[3]; // TopRight x
                                    rayPosition[7] = (float)_winT - topY; // TopRight y
                                    rayPosition[8] = 0.0f; // TopRight z
                                    rayPosition[9] = rayPosition[0]; // TopLeft x
                                    rayPosition[10] = rayPosition[7]; // TopLeft y
                                    rayPosition[11] = 0.0f; // TopLeft z
                                    cardRay[number].SetPosition(rayPosition);
                                    break;
                                }
                            }
                        }
                        chosenCounter++;
                    }

                    /////////////////// Shield cards ///////////////////
                    ////////////////////////////////////////////////////
                    for (int i = 0; i < cardProtection.Length; i++) // Construct the card objects
                    {
                        number = rand.Next(0, 12);
                    }
                    chosenCounter = 0; // So we know what card we're upto
                    for (int i = 0; i < cardProtection.Length; i++)
                    {
                        alreadyChosenThatCard = true;
                        while (alreadyChosenThatCard) // need to pick another
                        {
                            number = rand.Next(0, 12);
                            chosenEasy[chosenCounter] = number;
                            for (int j = 0; j <= chosenCounter; j++)
                            {
                                if ((chosenEasy[j] == number) && (j != chosenCounter)) // already been chosen - don't
                                // check current card
                                {
                                    alreadyChosenThatCard = true;
                                    j = 0; // need to check the next new number against all others again
                                    break; // break from the loop and set a new number
                                }
                                if (j == chosenCounter) // If here then a number that hasn't been chosen has been found
                                {
                                    alreadyChosenThatCard = false;
                                    // Not init the card's values
                                    int[] textureArray = new int[2]; // back and front
                                    switch (number) // only breaking 6 times (should do) but not on the same
                                    // number, case 0
                                    {
                                        case 0:
                                            textureArray[0] = (int)_MCardBacksTexture[1];
                                            textureArray[1] = (int)_MCardShieldTexture[3]; // Plastic Sheet
                                            cardProtection[i].SetProtection("Plastic Sheet");
                                            cardProtection[i].SetRay("Beta");
                                            cardProtection[i].SetTexture(textureArray);
                                            cardProtection[i].SetType("Protection");
                                            break;
                                        case 1:
                                            textureArray[0] = (int)_MCardBacksTexture[1];
                                            textureArray[1] = (int)_MCardShieldTexture[1]; // Metal Sheet
                                            cardProtection[i].SetProtection("Metal Sheet");
                                            cardProtection[i].SetRay("Gamma");
                                            cardProtection[i].SetTexture(textureArray);
                                            cardProtection[i].SetType("Protection");
                                            break;
                                        case 2:
                                            textureArray[0] = (int)_MCardBacksTexture[1];
                                            textureArray[1] = (int)_MCardShieldTexture[5]; // Tinfoil
                                            cardProtection[i].SetProtection("Tinfoil");
                                            cardProtection[i].SetRay("Infrared");
                                            cardProtection[i].SetTexture(textureArray);
                                            cardProtection[i].SetType("Protection");
                                            break;
                                        case 3:
                                            textureArray[0] = (int)_MCardBacksTexture[1];
                                            textureArray[1] = (int)_MCardShieldTexture[2]; // Mirror
                                            cardProtection[i].SetProtection("Mirror");
                                            cardProtection[i].SetRay("Laser");
                                            cardProtection[i].SetTexture(textureArray);
                                            cardProtection[i].SetType("Protection");
                                            break;
                                        case 4:
                                            textureArray[0] = (int)_MCardBacksTexture[1];
                                            textureArray[1] = (int)_MCardShieldTexture[4]; // Sunglasses
                                            cardProtection[i].SetProtection("Sunglasses");
                                            cardProtection[i].SetRay("Ultraviolet");
                                            cardProtection[i].SetTexture(textureArray);
                                            cardProtection[i].SetType("Protection");
                                            break;
                                        case 5:
                                            textureArray[0] = (int)_MCardBacksTexture[1];
                                            textureArray[1] = (int)_MCardShieldTexture[0]; // Lead
                                            cardProtection[i].SetProtection("Lead");
                                            cardProtection[i].SetRay("X-Ray");
                                            cardProtection[i].SetTexture(textureArray);
                                            cardProtection[i].SetType("Protection");
                                            break;
                                        case 6:
                                            textureArray[0] = (int)_MCardBacksTexture[1];
                                            textureArray[1] = (int)_MCardShieldTexture[3]; // Plastic Sheet
                                            cardProtection[i].SetProtection("Plastic Sheet");
                                            cardProtection[i].SetRay("Beta");
                                            cardProtection[i].SetTexture(textureArray);
                                            cardProtection[i].SetType("Protection");
                                            break;
                                        case 7:
                                            textureArray[0] = (int)_MCardBacksTexture[1];
                                            textureArray[1] = (int)_MCardShieldTexture[1]; // Metal Sheet
                                            cardProtection[i].SetProtection("Metal Sheet");
                                            cardProtection[i].SetRay("Gamma");
                                            cardProtection[i].SetTexture(textureArray);
                                            cardProtection[i].SetType("Protection");
                                            break;
                                        case 8:
                                            textureArray[0] = (int)_MCardBacksTexture[1];
                                            textureArray[1] = (int)_MCardShieldTexture[5]; // TinFoil
                                            cardProtection[i].SetProtection("Tinfoil");
                                            cardProtection[i].SetRay("Infrared");
                                            cardProtection[i].SetTexture(textureArray);
                                            cardProtection[i].SetType("Protection");
                                            break;
                                        case 9:
                                            textureArray[0] = (int)_MCardBacksTexture[1];
                                            textureArray[1] = (int)_MCardShieldTexture[2]; // Mirror
                                            cardProtection[i].SetProtection("Mirror");
                                            cardProtection[i].SetRay("Laser");
                                            cardProtection[i].SetTexture(textureArray);
                                            cardProtection[i].SetType("Protection");
                                            break;
                                        case 10:
                                            textureArray[0] = (int)_MCardBacksTexture[1];
                                            textureArray[1] = (int)_MCardShieldTexture[4]; // Sunglasses
                                            cardProtection[i].SetProtection("Sunglasses");
                                            cardProtection[i].SetRay("Ultraviolet");
                                            cardProtection[i].SetTexture(textureArray);
                                            cardProtection[i].SetType("Protection");
                                            break;
                                        case 11:
                                            textureArray[0] = (int)_MCardBacksTexture[1];
                                            textureArray[1] = (int)_MCardShieldTexture[0]; // Lead
                                            cardProtection[i].SetProtection("Lead");
                                            cardProtection[i].SetRay("X-Ray");
                                            cardProtection[i].SetTexture(textureArray);
                                            cardProtection[i].SetType("Protection");
                                            break;
                                        default:
                                            break;
                                    }
                                    //continue;
                                }
                            }
                        }
                        chosenCounter++;
                    }
                    for (int i = 0; i < chosenEasy.Length; i++)
                    {
                        chosenEasy[i] = 7; // reset all of the chosen values to their original ones
                    }
                    // Set each card into a random position
                    chosenCounter = 0; // So we know what card we're upto
                    float[] protectionPosition = new float[12];
                    alreadyChosenThatCard = true;
                    y = 0; // used for positioning cards correctly
                    for (int i = 0; i < cardProtection.Length; i++)
                    {
                        alreadyChosenThatCard = true;
                        while (alreadyChosenThatCard) // need to pick another
                        {
                            number = rand.Next(0, 12);
                            chosenEasy[chosenCounter] = number;
                            for (int j = 0; j <= chosenCounter; j++)
                            {
                                if ((chosenEasy[j] == number) && (j != chosenCounter)) // already been chosen - don't
                                // check first card
                                {
                                    alreadyChosenThatCard = true;
                                    j = 0;
                                    break; // break from the loop and set a new number
                                }
                                if (j == chosenCounter) // If here then a number that hasn't been chosen has been found
                                {
                                    int x;
                                    float topY = 1.0f;
                                    float bottomY = 5.0f;
                                    if (chosenCounter > 5) //next row down
                                    {
                                        topY = 23.0f;
                                        bottomY = 27.0f;
                                        x = y;
                                        y++;
                                    }
                                    else
                                    {
                                        x = i;
                                        topY = 17.0f;
                                        bottomY = 21.0f;
                                    }
                                    alreadyChosenThatCard = false;
                                    protectionPosition[0] = (float)_winL + 1 + 3 * x; // BottomLeft x
                                    protectionPosition[1] = (float)_winT - bottomY; // BottomLeft y
                                    protectionPosition[2] = 0.0f; // BottomLeft z
                                    protectionPosition[3] = (float)_winL + 3 + 3 * x; // BottomRight x
                                    protectionPosition[4] = protectionPosition[1]; // BottomRight y
                                    protectionPosition[5] = 0.0f; // BottomRight z
                                    protectionPosition[6] = protectionPosition[3]; // TopRight x
                                    protectionPosition[7] = (float)_winT - topY; // TopRight y
                                    protectionPosition[8] = 0.0f; // TopRight z
                                    protectionPosition[9] = protectionPosition[0]; // TopLeft x
                                    protectionPosition[10] = protectionPosition[7]; // TopLeft y
                                    protectionPosition[11] = 0.0f; // TopLeft z
                                    cardProtection[number].SetPosition(protectionPosition);
                                    break;
                                }
                            }
                        }
                        chosenCounter++;
                    }
                    firstRun = false;
                }
            }
            if (mediumMode) // initialise the mediumMode parts
            {
                if (firstRun) // set up initial cards
                {
                    firstRun = false;
                }
            }
            if (hardMode)// initialise the hardMode parts
            {
                if (firstRun) // set up initial cards
                {
                    firstRun = false;
                }
            }

            // Get time passed
            timeSinceFlipped = cardFlippedTimer.GetTimeElapsed();

            flippedRayCards.Clear(); // Should be emptied on every update and recalculated
            noneFlippedRayCards.Clear();
            foreach (Card rayCard in cardRay)
            {
                if ((rayCard.IsAlive()) && (rayCard.IsFlipped()))
                {
                    flippedRayCards.Add(rayCard); // These will get drawn
                    continue;
                }
                if (rayCard.IsAlive())
                {
                    noneFlippedRayCards.Add(rayCard); // These will get drawn
                }
            }

            flippedProtectionCards.Clear();
            noneFlippedProtectionCards.Clear();
            foreach (Card protectionCard in cardProtection)
            {
                if ((protectionCard.IsAlive()) && (protectionCard.IsFlipped()))
                {
                    flippedProtectionCards.Add(protectionCard); // These will get drawn
                    continue;
                }
                if (protectionCard.IsAlive())
                {
                    noneFlippedProtectionCards.Add(protectionCard); // These will get drawn
                }
            }

            IsPairFound();
        }

        private static void Display()
        {
            //// Update the scene first
            Update();
            ////

            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT | Gl.GL_DEPTH_BUFFER_BIT);
            Gl.glLoadIdentity();
            Gl.glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

            if (_MCurrentSceneToDraw==0) // Draw the intro scene
            {
                Gl.glEnable(Gl.GL_TEXTURE_2D);
                Gl.glBindTexture(Gl.GL_TEXTURE_2D, _MBackgroundTexture[0]);
                myUI.SetState(0); // So it draws correctly
                Gl.glBegin(Gl.GL_QUADS);
                myUI.Draw(_winL, _winR, _winT, _winB, _winWidth, _winHeight);
                Gl.glEnd();
            }
            if (_MCurrentSceneToDraw==1) // Draw the playing scene
            {
                if (stopMusic)
                {
                    backgroundMusic.Stop();
                    stopMusic = false;
                }
                if(mouseClicked) // Have they clicked a card?
                {
                    Gl.glDisable(Gl.GL_TEXTURE_2D);
                    Gl.glBegin(Gl.GL_QUADS);
                    for (int i = 0; i < cardRay.Length; i++)
                    {
                        float[] tempPos = new float[12];
                        int[] tempCol = new int[3];
                        tempPos = cardRay[i].GetPosition();
                        tempCol = cardRay[i].GetColourID();

                        Gl.glColor3ub((byte)(tempCol[0]), 0, 0);
                        //Gl.glTexCoord2f(0.0f, 0.0f);			// bottom left of texture
                        Gl.glVertex3f(tempPos[0], tempPos[1], tempPos[2]); // Bottom Left

                        Gl.glColor3ub((byte)(tempCol[0]), 0, 0);
                        //Gl.glTexCoord2f(1.0f, 0.0f);			// bottom right of texture
                        Gl.glVertex3f(tempPos[3], tempPos[4], tempPos[5]); // Bottom Right

                        Gl.glColor3ub((byte)(tempCol[0]), 0, 0);
                        //Gl.glTexCoord2f(1.0f, 1.0f);			// top right of texture
                        Gl.glVertex3f(tempPos[6], tempPos[7], tempPos[8]);// Top Right

                        Gl.glColor3ub((byte)(tempCol[0]), 0, 0);
                        //Gl.glTexCoord2f(0.0f, 1.0f);			// top left of texture
                        Gl.glVertex3f(tempPos[9], tempPos[10], tempPos[11]);// Top Left
                    }
                    Gl.glEnd();
                    if ((flippedRayCard) && (flippedProtectionCard))
                    {
                        // Don't process any more clicks whilst two cards are turned over
                    }
                    else
                    {
                        ProcessPick(cardRay);
                    }
                    mouseClicked = false;
                    ///////////////////// Shield Cards /////////////////////////
                    ////////////////////////////////////////////////////////////
                    Gl.glDisable(Gl.GL_TEXTURE_2D);
                    Gl.glBegin(Gl.GL_QUADS);
                    for (int i = 0; i < cardProtection.Length; i++)
                    {
                        float[] tempPos = new float[12];
                        int[] tempCol = new int[3];
                        tempPos = cardProtection[i].GetPosition();
                        tempCol = cardProtection[i].GetColourID();

                        Gl.glColor3ub((byte)(tempCol[0]), 0, 0);
                        //Gl.glTexCoord2f(0.0f, 0.0f);			// bottom left of texture
                        Gl.glVertex3f(tempPos[0], tempPos[1], tempPos[2]); // Bottom Left

                        Gl.glColor3ub((byte)(tempCol[0]), 0, 0);
                        //Gl.glTexCoord2f(1.0f, 0.0f);			// bottom right of texture
                        Gl.glVertex3f(tempPos[3], tempPos[4], tempPos[5]); // Bottom Right

                        Gl.glColor3ub((byte)(tempCol[0]), 0, 0);
                        //Gl.glTexCoord2f(1.0f, 1.0f);			// top right of texture
                        Gl.glVertex3f(tempPos[6], tempPos[7], tempPos[8]);// Top Right

                        Gl.glColor3ub((byte)(tempCol[0]), 0, 0);
                        //Gl.glTexCoord2f(0.0f, 1.0f);			// top left of texture
                        Gl.glVertex3f(tempPos[9], tempPos[10], tempPos[11]);// Top Left
                    }
                    Gl.glEnd();
                    if ((flippedRayCard) && (flippedProtectionCard))
                    {
                        // Don't process any more clicks whilst two cards are turned over
                    }
                    else
                    {
                        ProcessPick(cardProtection);
                    }
                    mouseClicked = false;
                }

                Gl.glEnable(Gl.GL_TEXTURE_2D);
                Gl.glBindTexture(Gl.GL_TEXTURE_2D, _MBackgroundTexture[1]);
                myUI.SetState(1); // So it draws correctly
                Gl.glBegin(Gl.GL_QUADS); // Draw the playing area
                myUI.Draw(_winL, _winR, _winT, _winB, _winWidth, _winHeight);
                Gl.glEnd();

                //Gl.glDisable(Gl.GL_DITHER); // Enable to be able to use 32bit colouring                
                //Gl.glEnable(Gl.GL_DITHER);
                if(easyMode) // Draw the easyMode version of the Scene
                {
                    ///////////////// Ray Cards ///////////////////
                    ///////////////////////////////////////////////
                    // Draw the none flipped cards
                    Gl.glEnable(Gl.GL_TEXTURE_2D);
                    Gl.glBindTexture(Gl.GL_TEXTURE_2D, _MCardBacksTexture[0]);
                    Gl.glBegin(Gl.GL_QUADS);
                    foreach(Card myCard in noneFlippedRayCards)
                    {
                        myCard.Draw();
                    }
                    Gl.glEnd();
                    // Draw the flipped cards
                    int texture;
                    Gl.glEnable(Gl.GL_TEXTURE_2D);
                    foreach (Card myCard in flippedRayCards)
                    {
                        texture = myCard.GetTexture();
                        for (int i = 0; i < _MCardEasyTexture.Length; i++)
                        {
                            // Find where the texture id is in the texture array
                            if (texture==_MCardEasyTexture[i]) // found it
                            {
                                texture = i;
                                break; // No need to search anymore
                            }
                        }
                        Gl.glBindTexture(Gl.GL_TEXTURE_2D, _MCardEasyTexture[texture]);
                        Gl.glBegin(Gl.GL_QUADS);
                        myCard.Draw();
                        Gl.glEnd();
                    }
                    /////////////////////// Shield Cards /////////////////////////
                    //////////////////////////////////////////////////////////////
                    // Draw the none flipped cards
                    Gl.glEnable(Gl.GL_TEXTURE_2D);
                    Gl.glBindTexture(Gl.GL_TEXTURE_2D, _MCardBacksTexture[1]);
                    Gl.glBegin(Gl.GL_QUADS);
                    foreach (Card myCard in noneFlippedProtectionCards)
                    {
                        myCard.Draw();
                    }
                    Gl.glEnd();
                    // Draw the flipped cards
                    Gl.glEnable(Gl.GL_TEXTURE_2D);
                    foreach (Card myCard in flippedProtectionCards)
                    {
                        texture = myCard.GetTexture();
                        for (int i = 0; i < _MCardShieldTexture.Length; i++)
                        {
                            // Find where the texture id is in the texture array
                            if (texture == _MCardShieldTexture[i]) // found it
                            {
                                texture = i;
                                break; // No need to search anymore
                            }
                        }
                        Gl.glBindTexture(Gl.GL_TEXTURE_2D, _MCardShieldTexture[texture]);
                        Gl.glBegin(Gl.GL_QUADS);
                        myCard.Draw();
                        Gl.glEnd();
                    }
                }
                if(mediumMode) // Draw the mediumMode version of the Scene
                {

                }
                else // Draw the hardMode version of the scene
                {

                }
            }

            // END OF DRAWING CODE
            ///////////////////////////////////////////////
            System.Threading.Thread.Sleep(10); // because no deltaTime used yet

            Glut.glutSwapBuffers();

        }
        #endregion MainDisplay


        #region ReshapeInitIdle


        private static void myGlInit()
        {
            //music
            incorrectMatch.SoundLocation = "Wave sounds\\Incorrect match wav.wav";
            correctMatch.SoundLocation = "Wave sounds\\Matched cards wav.wav";
            cardFlip.SoundLocation = "Wave sounds\\card flip wav.wav";
            backgroundMusic.SoundLocation = "Wave sounds\\backing track wav.wav";
            backgroundMusic.PlayLooping();

            cardRow = new int[4];
            cardCol = new int[6];

            cardFlippedTimer.StartTimer();

            _MBackgroundTexture = new uint[2]; // Set the sizes for the texture ids and names
            _MBackgroundTextureName = new string[2];
            _MCardBacksTexture = new uint[2];
            _MCardBacksTextureName = new string[2];
            _MBonusCardTexture = new uint[1];
            _MBonusCardTextureName = new string[1];
            _MCardEasyTexture = new uint[6];
            _MCardEasyTextureName = new string[6];
            _MCardHardTexture = new uint[6];
            _MCardHardTextureName = new string[6];
            _MCardShieldTexture = new uint[6];
            _MCardShieldTextureName = new string[6];

            myTexture = new Texture[_MBackgroundTexture.Length + _MCardBacksTexture.Length+
                _MBonusCardTexture.Length+_MCardEasyTexture.Length+_MCardHardTexture.Length+
                _MCardShieldTexture.Length]; // Array constructed but no Texture constructed yet
            for (int i = 0; i < myTexture.Length; i++ ) // Construct the Texture objects
            {
                myTexture[i] = new Texture();
            }

            _MBackgroundTextureName[0] = "images\\MISC\\Loading Screen.bmp"; // Load in all texture names
            _MBackgroundTextureName[1] = "images\\MISC\\cloth tecture.bmp";
            _MCardBacksTextureName[0] = "images\\Backs\\Radioactive tri boarder.bmp";
            _MCardBacksTextureName[1] = "images\\Backs\\Sheild back black.bmp";
            _MBonusCardTextureName[0] = "images\\MISC\\Bonus FLIP.bmp";
            _MCardEasyTextureName[0] = "images\\Radiation Cards (Easy)\\Beta.bmp";
            _MCardEasyTextureName[1] = "images\\Radiation Cards (Easy)\\Gamma.bmp";
            _MCardEasyTextureName[2] = "images\\Radiation Cards (Easy)\\Infrared.bmp";
            _MCardEasyTextureName[3] = "images\\Radiation Cards (Easy)\\Laser.bmp";
            _MCardEasyTextureName[4] = "images\\Radiation Cards (Easy)\\ultraviolet.bmp";
            _MCardEasyTextureName[5] = "images\\Radiation Cards (Easy)\\X-Ray.bmp";
            _MCardHardTextureName[0] = "images\\Radiation Cards (Hard)\\Beta hard.bmp";
            _MCardHardTextureName[1] = "images\\Radiation Cards (Hard)\\Gamma hard.bmp";
            _MCardHardTextureName[2] = "images\\Radiation Cards (Hard)\\Infrared hard.bmp";
            _MCardHardTextureName[3] = "images\\Radiation Cards (Hard)\\Laser hard.bmp";
            _MCardHardTextureName[4] = "images\\Radiation Cards (Hard)\\ultraviolet hard.bmp";
            _MCardHardTextureName[5] = "images\\Radiation Cards (Hard)\\X-Ray Hard.bmp";
            _MCardShieldTextureName[0] = "images\\Shield Cards\\Lead.bmp";
            _MCardShieldTextureName[1] = "images\\Shield Cards\\Metal sheet.bmp";
            _MCardShieldTextureName[2] = "images\\Shield Cards\\Mirror.bmp";
            _MCardShieldTextureName[3] = "images\\Shield Cards\\plastic sheet.bmp";
            _MCardShieldTextureName[4] = "images\\Shield Cards\\Sunglasses.bmp";
            _MCardShieldTextureName[5] = "images\\Shield Cards\\Tin Foil.bmp";

            myTexture[0].LoadTexture(_MBackgroundTextureName, ref _MBackgroundTexture); // []=+2
            myTexture[2].LoadTexture(_MCardBacksTextureName, ref _MCardBacksTexture); // []=+2
            myTexture[4].LoadTexture(_MBonusCardTextureName, ref _MBonusCardTexture); // []=+1
            myTexture[5].LoadTexture(_MCardEasyTextureName, ref _MCardEasyTexture); // []=+6
            myTexture[11].LoadTexture(_MCardHardTextureName, ref _MCardHardTexture); // []=+6
            myTexture[17].LoadTexture(_MCardShieldTextureName, ref _MCardShieldTexture); // []=+6

            for (int i = 0; i < chosenEasy.Length; i++)
            {
                chosenEasy[i] = 7; // We set every value to 7 initially because 7 will never be a valid
                                    // chosen number, whereas 0 is so that cannot be present
                                    // initially
                chosenMedium[i] = 7;
                chosenHard[i] = 7;
            }

            rays[0] = "Beta";
            rays[1] = "Gamma";
            rays[0] = "Infrared";
            rays[3] = "Laser";
            rays[4] = "Ultraviolet";
            rays[5] = "X-Ray";
            protections[0] = "Plastic Sheet";
            protections[1] = "Metal Sheet";
            protections[2] = "Tin Foil";
            protections[3] = "Mirror";
            protections[4] = "Sunglasses";
            protections[5] = "Lead";

            Gl.glShadeModel(Gl.GL_SMOOTH);								// enable smooth shading
            Gl.glClearColor(0.0f, 0.0f, 0.0f, 0.5f);					// black background
            Gl.glClearDepth(1.0f);										// depth buffer setup
            Gl.glEnable(Gl.GL_DEPTH_TEST);								// enables depth testing
            Gl.glDepthFunc(Gl.GL_LEQUAL);								// type of depth testing
            Gl.glHint(Gl.GL_PERSPECTIVE_CORRECTION_HINT, Gl.GL_NICEST);	// nice perspective calculations
            Gl.glTexEnvf(Gl.GL_TEXTURE_ENV, Gl.GL_TEXTURE_ENV_MODE, Gl.GL_REPLACE); // replace colour
            // with texture

            Gl.glMatrixMode(Gl.GL_PROJECTION);
            Gl.glLoadIdentity();
            //Gl.glOrtho(_winL, _winR, _winB, _winT, -1, 1);
            Gl.glOrtho(_winL, _winR, _winB, _winT, 0, 1);

            Gl.glMatrixMode(Gl.GL_MODELVIEW);

        }


        private static void Reshape(int width, int height)
        {
            Gl.glViewport(0, 0, width, height);
            _winWidth = width;
            _winHeight = height;

            myGlInit();
        }

        // Force the program to constantly redraw
        private static void Idle()
        {
            Glut.glutPostRedisplay();
        }

        #endregion ReshapeInitIdle


        #region KeybAndMouseInterface

        #region MouseInterface
        private static void MouseCallback(int button, int state, int x, int y)
        {
            if (state == Glut.GLUT_DOWN) // i.e. the mouse is down
            {
                switch (button)
                {
                    case Glut.GLUT_LEFT_BUTTON:
                        cursorX = x;
                        cursorY = y;
                        mouseClicked = true;
                        break;
                    case Glut.GLUT_MIDDLE_BUTTON:
                        break;
                    case Glut.GLUT_RIGHT_BUTTON:
                        break;
                    default:
                        break;
                }
            }

        }

        private static void PassiveMouse(int x, int y)
        {

        }
        #endregion MouseInterface

        #region KeyboardInterface

        private static void Keyboard(byte key, int x, int y)
        {
            switch (key)
            {
                case 27: // Escape
                    Environment.Exit(0);
                    break;
                case 49: // '1'
                    if (_MCurrentSceneToDraw==0) // Selected to play Easy Mode
                    {
                        _MCurrentSceneToDraw = 1;
                        easyMode = true;
                        mediumMode = false;
                        hardMode = false;
                    }
                    break;
                /*For example, trapping a 'P' keypress
                case (byte)'P':
                    break;*/
                default:
                    break;
            }
        }


        #endregion KeyboardInterface

        #endregion KeybAndMouseInterface

        #region OtherUtils
        #endregion

    }
}