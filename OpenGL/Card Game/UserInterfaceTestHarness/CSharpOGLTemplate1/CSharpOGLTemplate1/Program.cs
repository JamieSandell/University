/////////////////////////////////////////////////
////////Author: Jamie Sandell
////////Signed On: 27th November 2008 - 3:52pm
////////Work done: Created the test harness
////////Signed Off: 27th November 2008 - 5:03pm
/////////////////////////////////////////////////

using System.Windows.Forms;
using System;
using System.Drawing;
using Tao.OpenGl;
using Tao.FreeGlut;

namespace CardGame
{
    /// <summary>
    /// Summary description for UserInterfaceTestHarness
    /// </summary>

    public class UserInterfaceTestHarness
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
        private static string _title = "08343 - ACW - Team09 - UserInterfaceTestHarness";

        private static int[] _MTexture = new int[2];
        private static int currentState = 0; // The current state to draw

        // Class instances
        private static UserInterface myUI = new UserInterface();
        #endregion

        private UserInterfaceTestHarness()
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

            // Start main loop
            Glut.glutMainLoop();
        }
        #endregion Main(string[] args)


        #region MainDisplay
        private static void Display()
        {
            // Depth buffer will clear the bitmap text
            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT | Gl.GL_DEPTH_BUFFER_BIT);

            ///////////////////////////////////////////////
            // START YOUR DRAWING CODE HERE

            RenderString((float)-15, (float)10, "Press Spacebar to change scenes");

            if(currentState==0) // Intro state
            {
                myUI.SetState(0); // so the right drawing code is called
                Gl.glBindTexture(Gl.GL_TEXTURE_2D, _MTexture[currentState]);
                Gl.glEnable(Gl.GL_TEXTURE_2D);
                Gl.glBegin(Gl.GL_QUADS);
                myUI.Draw(_winL, _winR, _winT, _winB, _winWidth, _winHeight);
                Gl.glEnd();
                Gl.glDisable(Gl.GL_TEXTURE_2D);
                RenderString((float)-10, (float)13, "Intro Screen Loaded");
            }
            if(currentState==1) // Game playing state
            {
                myUI.SetState(1);
                Gl.glBindTexture(Gl.GL_TEXTURE_2D, _MTexture[currentState]);
                Gl.glEnable(Gl.GL_TEXTURE_2D);
                myUI.Draw(_winL, _winR, _winT, _winB, _winWidth, _winHeight);
                Gl.glDisable(Gl.GL_TEXTURE_2D);
                RenderString((float)-10, (float)13, "Playing Screen Loaded");
            }

            // END OF DRAWING CODE
            ///////////////////////////////////////////////

            Glut.glutSwapBuffers();
            System.Threading.Thread.Sleep(10);

        }
        #endregion MainDisplay


        #region ReshapeInitIdle


        private static void myGLInit()
        {

            Gl.glShadeModel(Gl.GL_SMOOTH);								// enable smooth shading
            Gl.glClearColor(0.0f, 0.0f, 0.0f, 0.5f);					// black background
            Gl.glClearDepth(1.0f);										// depth buffer setup
            Gl.glEnable(Gl.GL_DEPTH_TEST);								// enables depth testing
            Gl.glDepthFunc(Gl.GL_LEQUAL);								// type of depth testing
            Gl.glHint(Gl.GL_PERSPECTIVE_CORRECTION_HINT, Gl.GL_NICEST);	// nice perspective calculations
            // rquad = 150.0f;		defines the rotation anGle in the start position of the quad
            // select modulate to mix texture with color for shading
            Gl.glTexEnvf(Gl.GL_TEXTURE_ENV, Gl.GL_TEXTURE_ENV_MODE, Gl.GL_REPLACE); // replace colour
            // with texture

            Bitmap image = new Bitmap("Loading Screen.bmp"); // TODO: Add error handling code
            image.RotateFlip(RotateFlipType.RotateNoneFlipY);
            System.Drawing.Imaging.BitmapData bitmapdata;
            Rectangle rect = new Rectangle(0, 0, image.Width, image.Height);

            bitmapdata = image.LockBits(rect, System.Drawing.Imaging.ImageLockMode.ReadOnly,
                System.Drawing.Imaging.PixelFormat.Format24bppRgb);

            Gl.glGenTextures(2, _MTexture);
            Gl.glBindTexture(Gl.GL_TEXTURE_2D, _MTexture[0]);
            Gl.glTexImage2D(Gl.GL_TEXTURE_2D, 0, (int)Gl.GL_RGB8, image.Width, image.Height,
                0, Gl.GL_BGR_EXT, Gl.GL_UNSIGNED_BYTE, bitmapdata.Scan0);
            Gl.glTexParameteri(Gl.GL_TEXTURE_2D, Gl.GL_TEXTURE_MIN_FILTER, Gl.GL_LINEAR);		// Linear Filtering
            Gl.glTexParameteri(Gl.GL_TEXTURE_2D, Gl.GL_TEXTURE_MAG_FILTER, Gl.GL_LINEAR);		// Linear Filtering

            image.UnlockBits(bitmapdata);
            image.Dispose();

            //

            Bitmap image2 = new Bitmap("cloth texture.bmp"); // TODO: Add error handling code
            image2.RotateFlip(RotateFlipType.RotateNoneFlipY);
            System.Drawing.Imaging.BitmapData bitmapdata2;
            Rectangle rect2 = new Rectangle(0, 0, image2.Width, image2.Height);

            bitmapdata2 = image2.LockBits(rect2, System.Drawing.Imaging.ImageLockMode.ReadOnly,
                System.Drawing.Imaging.PixelFormat.Format24bppRgb);

            //Gl.glGenTextures(2, texture);
            Gl.glBindTexture(Gl.GL_TEXTURE_2D, _MTexture[1]);
            Gl.glTexImage2D(Gl.GL_TEXTURE_2D, 0, (int)Gl.GL_RGB8, image2.Width, image2.Height,
                0, Gl.GL_BGR_EXT, Gl.GL_UNSIGNED_BYTE, bitmapdata2.Scan0);
            Gl.glTexParameteri(Gl.GL_TEXTURE_2D, Gl.GL_TEXTURE_MIN_FILTER, Gl.GL_LINEAR);		// Linear Filtering
            Gl.glTexParameteri(Gl.GL_TEXTURE_2D, Gl.GL_TEXTURE_MAG_FILTER, Gl.GL_LINEAR);		// Linear Filtering

            image2.UnlockBits(bitmapdata2);
            image2.Dispose();

            // Setup our UI
            myUI.SetState(0); // Intro state
            myUI.SetTexture(_MTexture);

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
                case 32: // Spacebar
                    if(currentState==0)
                    {
                        currentState = 1;
                    }
                    else
                    {
                        currentState = 0;
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
