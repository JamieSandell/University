using System;
using Tao.OpenGl;
using Tao.Glut;
using Player;

namespace Game_Skeleton
{
    /// <summary>
    /// Summary description for Game_Skeleton
    /// </summary>

    public class Program
    {

        static void runPlayerTest()
        {
            string inName = "originalname";

            Player.Player player = new Player.Player(inName);

            player.test(inName);
        }

        static void runScoringSystemTest()
        {
            ScoringSystem.ScoringSystem scoringSystem = new ScoringSystem.ScoringSystem();

            scoringSystem.test();
        }

        #region Member Variables

        // WINDOW PARAMETERS
        // World window co-ordinates
        private static double _winL = -10;
        private static double _winR = 10;
        private static double _winT = 10;
        private static double _winB = -10;

        // Window dimensions
        private static int _winWidth = 500;
        private static int _winHeight = 500;

        // Window Title
        private static string _title = "08240 Computer Graphics Programming";
        #endregion

        private Program()
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

            //Glut.glutFullScreen(); // Full screen option.

            runPlayerTest();
            runScoringSystemTest();

            // Start main loop
            Glut.glutMainLoop();
        }
        #endregion Main(string[] args)


        #region MainDisplay
        private static void Display()
        {

            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT);


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
                case 27: // Escape
                    Environment.Exit(0);
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
