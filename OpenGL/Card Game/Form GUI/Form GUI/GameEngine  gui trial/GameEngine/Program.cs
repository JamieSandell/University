//// PMC C#OGL Template Ver 1.1; Last update 5.7.07 ///
///////////////////////////////////////////////////////
//// NAME:
//// EXERCISE: 
//// NOTES:
////
////
////////////////////////////////////////////////////////
// http://atlas.net.dcs.hull.ac.uk/sites/modules/08240 /
////////////////////////////////////////////////////////


using System;
using Tao.OpenGl;
using Tao.Glut;

namespace CardGame
{
    /// <summary>
    /// Summary description for GameEngine
    /// </summary>

    public class Program
    {

        #region Member Variables

        //Initalise Classes
        private static Text text = new Text();
        private static Timer timer = new Timer();
        private static ScoringSystem scoringSystem = new ScoringSystem();
        //private static Player player = new Player("playersName");

        private static Player player;

        private static bool gameOver = false;
        private static bool pointsScored = true;
        private static bool gamePaused = false;

        private static int scoreMultiplier;
        private static int cardPointsValue = 1;

        private static string playersName;

        enum difficultySettings
        {
            easy,
            medium,
            hard
        };

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
        private static string _title = "Pairs: Radiation";
        #endregion

        private Program()
        {
        }

        #region Main()
        [STAThread]
        public static void runGame(string inName)
        {
            playersName = inName;

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

            //Glut.glutFullScreen(); // Full screen option.

            player = new Player(playersName);

            scoringSystem.loadHighScoreTable();

            difficultySettings selectedDifficulty = difficultySettings.hard;

            switch (selectedDifficulty)
            {
                case difficultySettings.easy:
                    Program.scoreMultiplier = 1;
                    break;
                case difficultySettings.medium:
                    Program.scoreMultiplier = 2;
                    break;
                case difficultySettings.hard:
                    Program.scoreMultiplier = 3;
                    break;
                default:
                    break;
            }

            timer.StartTimer();

            // Start main loop
            Glut.glutMainLoop();
        }
        #endregion Main(string[] args)


        #region MainDisplay
        private static void Display()
        {
            if (timer.GetTimeElapsed() / 1000 == 90)
            {
                Program.gameOver = true;
            }

            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT);

            text.RenderString((float)Program._winR - 4, (float)Program._winT - 2, "Score " + player.getScore().ToString());
            text.RenderString((float)Program._winR - 4, (float)Program._winT - 4, "Time " + (90 - timer.GetTimeElapsed() / 1000));

            if (!Program.gamePaused & Program.pointsScored)
            {
                Program.pointsScored = false;
                player.setScore(Program.scoreMultiplier*Program.cardPointsValue);
            }

            if (!Program.gamePaused & Program.gameOver)
            {
                Gl.glClear(Gl.GL_COLOR_BUFFER_BIT);

                //scoringSystem.addToHighScoreTable(player.getName(), player.getScore());

                scoringSystem.sortHighScoreTable();

                scoringSystem.removeLowestScore();

                scoringSystem.drawHighScoreTable(text);

                scoringSystem.saveHighScoreTable();
            
            }

            if (Program.gamePaused)
            {
                Gl.glClear(Gl.GL_COLOR_BUFFER_BIT);
                text.RenderString(0, 0, "Game Paused");
            }

            Glut.glutSwapBuffers();

        }
        #endregion MainDisplay


        #region ReshapeInitIdle


        private static void myGLInit()
        {

            Gl.glMatrixMode(Gl.GL_PROJECTION);
            Gl.glLoadIdentity();
            Gl.glOrtho(_winL, _winR, _winB, _winT, -1, 1);

            Gl.glMatrixMode(Gl.GL_MODELVIEW);

        }


        private static void Reshape(int width, int height)
        {
            Gl.glViewport(0, 0, width, height);
            _winWidth = width;
            _winHeight = height;

            myGLInit();
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
                case 27: // Escape Exit the game
                    Environment.Exit(0);
                    break;

                case 112: //p Pause the game
                    if (!Program.gamePaused) // If the game isn`t paused pause it
                    {
                        Program.gamePaused = true;
                        timer.StopTimer();
                    }

                    else //Otherwise if the game is paused, unpause it
                    {
                        Program.gamePaused = false;
                        timer.StartTimer();
                    }
                    break;

                default:
                    break;
            }
        }


        #endregion KeyboardInterface

        #endregion KeybAndMouseInterface

        #region OtherUtils

        // Note x and y are in world co-ordinates, not screen.
        private static void RenderString(float x, float y, string str)
        {
            Gl.glRasterPos2f(x, y);
            int len = str.Length;
            for (int i = 0; i < len; i++)
            {
                Glut.glutBitmapCharacter(Glut.GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
            }
        }
        #endregion

    }
}
