////////////////////////////////////
////////// Created: 25th November 2008 - 3:50pm
////////// Author: Jamie Sandell
////////// Work done: Created and developed the harness
////////// Signed off: 25th November 2008 - 5:12pm
////
////////// Created: 27th November 2008 - 2:10pm
////////// Author: Jamie Sandell
////////// Work done: Tested compilation and execution in Release mode. Used updated Card.dll
////////// Signed off: 27th November 2008 2:12pm
////////////////////////////////////

using System;
using System.Collections;
using System.Drawing;
using System.Windows.Forms;
using Tao.OpenGl;
using Tao.Glut;
using CardGame;

namespace CardGame
{
    /// <summary>
    /// Summary description for CardGame
    /// </summary>

    public class Program
    {

        #region Member Variables

        // Class members
        public static bool alive = true;
        public static float[] position = new float[12];
        public static string ray = "UltraViolet";
        public static string protection = "SunGlasses";
        public static int[] texture = new int[2];
        public static Card myCard = new Card();

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
        private static string _title = "08343 - ACW - Team09 - Card Class Test Harness";
        #endregion

        private Program()
        {
            
        }

        #region Main(string[] args)
        [STAThread]
        public static void Main(string[] args)
        {
            // Bottom Left
            position[0] = 0.0f; // x
            position[1] = 0.0f; // y
            position[2] = 0.0f; // z
            // Bottom Right
            position[3] = 2.0f;
            position[4] = 0.0f;
            position[5] = 0.0f;
            // Top Right
            position[6] = 2.0f;
            position[7] = 2.0f;
            position[8] = 0.0f;
            // Top Left
            position[9] = 0.0f;
            position[10] = 2.0f;
            position[11] = 0.0f;

            ArrayList textureList = new ArrayList();
            textureList.Add(texture[0]);
            textureList.Add(texture[1]);


            //Card myCard = new Card(alive, position, ray, protection, texture);
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

            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT);

            ///////////////////////////////////////////////
            // START YOUR DRAWING CODE HERE

            myCard.FlipCard();
            System.Threading.Thread.Sleep(500);
            Gl.glDisable(Gl.GL_TEXTURE_2D);
            RenderString(-8, 9, "FlipCard - Successfull");
            Gl.glBindTexture(Gl.GL_TEXTURE_2D, texture[myCard.GetTexture()]);
            Gl.glEnable(Gl.GL_TEXTURE_2D);
            Gl.glBegin(Gl.GL_QUADS);
            myCard.Draw();
            Gl.glEnd();
            Gl.glDisable(Gl.GL_TEXTURE_2D);
            RenderString(-8, 8, "SetAlive - Successfull");
            RenderString(-8, 7, "GetTexture - Successfull");
            RenderString(-8, 6, "SetTexture - Successfull");
            RenderString(-8, 5, "SetAlive - Successfull");

            // END OF DRAWING CODE
            ///////////////////////////////////////////////

            Glut.glutSwapBuffers();

        }
        #endregion MainDisplay


        #region ReshapeInitIdle


        private static void myGLInit()
        {
            //texture = new uint[2];
            //cardRow = new int[4];
            //cardCol = new int[6];
            //cardRowGap = 5;



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

            Bitmap image = new Bitmap("Radioactive no border.bmp"); // TODO: Add error handling code
            image.RotateFlip(RotateFlipType.RotateNoneFlipY);
            System.Drawing.Imaging.BitmapData bitmapdata;
            Rectangle rect = new Rectangle(0, 0, image.Width, image.Height);

            bitmapdata = image.LockBits(rect, System.Drawing.Imaging.ImageLockMode.ReadOnly,
                System.Drawing.Imaging.PixelFormat.Format24bppRgb);

            Gl.glGenTextures(2, texture);
            Gl.glBindTexture(Gl.GL_TEXTURE_2D, texture[0]);
            Gl.glTexImage2D(Gl.GL_TEXTURE_2D, 0, (int)Gl.GL_RGB8, image.Width, image.Height,
                0, Gl.GL_BGR_EXT, Gl.GL_UNSIGNED_BYTE, bitmapdata.Scan0);
            Gl.glTexParameteri(Gl.GL_TEXTURE_2D, Gl.GL_TEXTURE_MIN_FILTER, Gl.GL_LINEAR);		// Linear Filtering
            Gl.glTexParameteri(Gl.GL_TEXTURE_2D, Gl.GL_TEXTURE_MAG_FILTER, Gl.GL_LINEAR);		// Linear Filtering

            image.UnlockBits(bitmapdata);
            image.Dispose();

            //

            Bitmap image2 = new Bitmap("Bonus FLIP.bmp"); // TODO: Add error handling code
            image2.RotateFlip(RotateFlipType.RotateNoneFlipY);
            System.Drawing.Imaging.BitmapData bitmapdata2;
            Rectangle rect2 = new Rectangle(0, 0, image2.Width, image2.Height);

            bitmapdata2 = image2.LockBits(rect2, System.Drawing.Imaging.ImageLockMode.ReadOnly,
                System.Drawing.Imaging.PixelFormat.Format24bppRgb);

            //Gl.glGenTextures(2, texture);
            Gl.glBindTexture(Gl.GL_TEXTURE_2D, texture[1]);
            Gl.glTexImage2D(Gl.GL_TEXTURE_2D, 0, (int)Gl.GL_RGB8, image2.Width, image2.Height,
                0, Gl.GL_BGR_EXT, Gl.GL_UNSIGNED_BYTE, bitmapdata2.Scan0);
            Gl.glTexParameteri(Gl.GL_TEXTURE_2D, Gl.GL_TEXTURE_MIN_FILTER, Gl.GL_LINEAR);		// Linear Filtering
            Gl.glTexParameteri(Gl.GL_TEXTURE_2D, Gl.GL_TEXTURE_MAG_FILTER, Gl.GL_LINEAR);		// Linear Filtering

            image2.UnlockBits(bitmapdata2);
            image2.Dispose();

            myCard.SetAliveStatus(alive);
            myCard.SetPosition(position);
            myCard.SetProtection(protection);
            myCard.SetRay(ray);
            myCard.SetTexture(texture);

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
