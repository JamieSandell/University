///////////////////////////////////////
///////// Author: Jamie Sandell
///////// Created: 10:30am 26th November 2008
///////// Work: Created and completed the Non-Functional Prototype
///////// Signed Off: 2:00pm 26th November 2008
////
///////// Author: Jamie Sandell
///////// Signed On: 1:45pm 27th November 2008
///////// Work: Made somethings more efficient, removed glBegin/glEnd from within the forLoop and added
/////////           Sleep(10) - because no deltaTime is been used yet, this got the CPU usgae (on my PC)
/////////           down from ~55% to ~20%
///////// Signed Off: 2:02pm 27th November 2008
//////////////////////////////////////

using System;
using System.Drawing;
using System.Windows.Forms;
using Tao.OpenGl;
using Tao.FreeGlut;
using System.Runtime.InteropServices;

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
        private static string _title = "08343 - Team09 - Non-Functional Prototype";

        private static uint[] texture;
        private static int[] cardRow;
        private static int[] cardCol;
        private static int cardRowGap; // use for positioning the rows of cards
        private static bool mouseClicked = false; // used for deciding to render to the back
                                                    // buffer, picking based on colour coding
        private static int cursorX;
        private static int cursorY;
        private static int colourCounter = 0; // colour counter, used for picking a unique colour
                                            // for each card
        private static bool flipFirstCard = false;
        private static int firstCardCurrentTexture = 0;
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

        public static void ProcessPick()
        {
            //ByteBuffer pixelsRGB = new ByteBuffer();
            int[] viewport = new int[4];
            byte[] pixel = new byte[3];
            //IntPtr data_pointer = Marshal.AllocHGlobal(4); // Allocate 4 bytes


            Gl.glGetIntegerv(Gl.GL_VIEWPORT, viewport);

            //Gl.glReadPixels(cursorX, viewport[3] - cursorY, 1, 1,
                //Gl.GL_RGB, Gl.GL_UNSIGNED_BYTE, data_pointer);
            //Color color = Color.FromArgb(Marshal.ReadInt32(data_pointer));

            Gl.glReadPixels(cursorX, viewport[3] - cursorY, 1, 1, Gl.GL_RGB, Gl.GL_UNSIGNED_BYTE, pixel);



            if ((pixel[0]==0)&&(pixel[1]!=255)) // first card was selected because first card red is set to 0
            {
                flipFirstCard = true;
            }
           // Marshal.FreeHGlobal(data_pointer);
            RenderString((float)_winR - 5.9f, (float)_winT - 2, pixel[0].ToString());

        }

        #endregion CustomMethods


        #region MainDisplay
        private static void Display()
        {

            //Gl.glClear(Gl.GL_COLOR_BUFFER_BIT);
            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT | Gl.GL_DEPTH_BUFFER_BIT);

            Gl.glLoadIdentity();
            Gl.glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
            Gl.glBindTexture(Gl.GL_TEXTURE_2D, texture[0]);					// defines the texture

            ///////////////////////////////////////////////
            // START YOUR DRAWING CODE HERE

            // Draw the cards
            //Gl.glDisable(Gl.GL_TEXTURE_2D);
            //Gl.glBegin(Gl.GL_QUADS); // Potentially more efficient than Gl_QUADS

                Gl.glDisable(Gl.GL_DITHER);
                Gl.glDisable(Gl.GL_TEXTURE_2D);
                Gl.glColor3f(1.0f, 1.0f, 1.0f);
                //Gl.glDisable(Gl.GL_DITHER);
                RenderString((float)_winR - 4.9f, (float)_winT - 2, cursorX.ToString());
                RenderString((float)_winR - 4.9f, (float)_winT - 10, cursorY.ToString());
                if (mouseClicked)
                {
                Gl.glBegin(Gl.GL_QUADS);
                //Gl.glColor3f(1.0f, 0.0f, 0.0f);
                for (int i = 0; i < cardRow.Length; i++)
                {
                    for (int j = 0; j < cardCol.Length; j++)
                    {
                        if (i == 2) // Onto the 3rd row, 3rd row needs to alter the row gap
                        {
                            cardRowGap = 8;
                        }
                        if (i == 3)
                        {
                            cardRowGap = 7; // Onto the 4th row, 4th row needs to alter the row gap
                        }
                        if (i == 1)
                        {
                            cardRowGap = 5;
                        }

                        Gl.glColor3ub((byte)(colourCounter*10), 0, 0);
                        //Gl.glTexCoord2f(0.0f, 0.0f);			// bottom left of texture
                        Gl.glVertex3f((float)_winL + 1 + 3 * j, (float)_winT - 5 - cardRowGap * i, 0.0f); // Bottom Left

                        Gl.glColor3ub((byte)(colourCounter * 10), 0, 0);
                        //Gl.glTexCoord2f(1.0f, 0.0f);			// bottom right of texture
                        Gl.glVertex3f((float)_winL + 3 + 3 * j, (float)_winT - 5 - cardRowGap * i, 0.0f); // Bottom Right

                        Gl.glColor3ub((byte)(colourCounter * 10), 0, 0);
                        //Gl.glTexCoord2f(1.0f, 1.0f);			// top right of texture
                        Gl.glVertex3f((float)_winL + 3 + 3 * j, (float)_winT - 1 - cardRowGap * i, 0.0f);// Top Right

                        Gl.glColor3ub((byte)(colourCounter * 10), 0, 0);
                        //Gl.glTexCoord2f(0.0f, 1.0f);			// top left of texture
                        Gl.glVertex3f((float)_winL + 1 + 3 * j, (float)_winT - 1 - cardRowGap * i, 0.0f);// Top Left
                        colourCounter++;
                    }
                }
                Gl.glEnd();
                colourCounter = 0;
                    ProcessPick();
                    mouseClicked = false;
               }
            Gl.glEnable(Gl.GL_DITHER);
            Gl.glEnable(Gl.GL_TEXTURE_2D);
            Gl.glBegin(Gl.GL_QUADS);
            for (int i = 0; i < cardRow.Length; i++)
            {
                for (int j = 0; j < cardCol.Length; j++)
                {
                    if (i == 2) // Onto the 3rd row, 3rd row needs to alter the row gap
                    {
                        cardRowGap = 8;
                    }
                    if (i == 3)
                    {
                        cardRowGap = 7; // Onto the 4th row, 4th row needs to alter the row gap
                    }
                    if (i == 1)
                    {
                        cardRowGap = 5;
                    }
                    Gl.glBindTexture(Gl.GL_TEXTURE_2D, texture[0]);
                    Gl.glTexCoord2f(0.0f, 0.0f);			// bottom left of texture
                    Gl.glVertex3f((float)_winL + 1 + 3 * j, (float)_winT - 5 - cardRowGap * i, 0.0f); // Bottom Left

                    Gl.glTexCoord2f(1.0f, 0.0f);			// bottom right of texture
                    Gl.glVertex3f((float)_winL + 3 + 3 * j, (float)_winT - 5 - cardRowGap * i, 0.0f); // Bottom Right

                    Gl.glTexCoord2f(1.0f, 1.0f);			// top right of texture
                    Gl.glVertex3f((float)_winL + 3 + 3 * j, (float)_winT - 1 - cardRowGap * i, 0.0f);// Top Right

                    Gl.glTexCoord2f(0.0f, 1.0f);			// top left of texture
                    Gl.glVertex3f((float)_winL + 1 + 3 * j, (float)_winT - 1 - cardRowGap * i, 0.0f);// Top Left

                }
            }
            Gl.glEnd();

            if (flipFirstCard)
            {
                if (firstCardCurrentTexture==0)
                {
                    firstCardCurrentTexture = 1;
                }
                else
                {
                    firstCardCurrentTexture = 0;
                }
                flipFirstCard = false;
            }
            Gl.glBindTexture(Gl.GL_TEXTURE_2D, texture[firstCardCurrentTexture]);
            Gl.glEnable(Gl.GL_TEXTURE_2D);
            Gl.glBegin(Gl.GL_QUADS);
                Gl.glTexCoord2f(0.0f, 0.0f);			// bottom left of texture
                Gl.glVertex3f((float)_winL + 1, (float)_winT - 5, 0.0f); // Bottom Left

                Gl.glTexCoord2f(1.0f, 0.0f);			// bottom right of texture
                Gl.glVertex3f((float)_winL + 3, (float)_winT - 5, 0.0f); // Bottom Right

                Gl.glTexCoord2f(1.0f, 1.0f);			// top right of texture
                Gl.glVertex3f((float)_winL + 3, (float)_winT - 1, 0.0f);// Top Right

                Gl.glTexCoord2f(0.0f, 1.0f);			// top left of texture
                Gl.glVertex3f((float)_winL + 1, (float)_winT - 1, 0.0f);// Top Left
            Gl.glEnd();

             //Draw the bonus card
            Gl.glBindTexture(Gl.GL_TEXTURE_2D, texture[1]);					// defines the texture
            Gl.glEnable(Gl.GL_TEXTURE_2D);
            Gl.glBegin(Gl.GL_QUADS);
                Gl.glTexCoord2f(0.0f, 0.0f);			// bottom left of texture
                Gl.glVertex3f((float)_winR - 4, (float)_winT - 13, 0.0f); // Bottom Left

                Gl.glTexCoord2f(1.0f, 0.0f);			// bottom right of texture
                Gl.glVertex3f((float)_winR - 2, (float)_winT - 13, 0.0f); // Bottom Right

                Gl.glTexCoord2f(1.0f, 1.0f);			// top right of texture
                Gl.glVertex3f((float)_winR - 2, (float)_winT - 9, 0.0f);// Top Right

                Gl.glTexCoord2f(0.0f, 1.0f);			// top left of texture
                Gl.glVertex3f((float)_winR - 4, (float)_winT - 9, 0.0f);// Top Left
            Gl.glEnd();

            // Draw the playing area
            Gl.glDisable(Gl.GL_TEXTURE_2D);
            Gl.glColor3f(0.0f, 0.0f, 0.0f);
            Gl.glLineWidth(3.0f);
            Gl.glBegin(Gl.GL_LINES);
                Gl.glVertex3f((float)_winR - 5, (float)_winT, 0.0f); // Right Vertical Line
                Gl.glVertex3f((float)_winR - 5, (float)_winB, 0.0f);
                Gl.glVertex3f((float)_winL, (float)(_winT+_winB)/2, 0.0f); // Middle Horizontal line
                Gl.glVertex3f((float)_winR - 5, (float)(_winT + _winB) / 2, 0.0f);
            Gl.glEnd();

            Gl.glDisable(Gl.GL_TEXTURE_2D);
            Gl.glColor3f(1.0f, 1.0f, 1.0f);
            //RenderString((float)_winR - 4.9f, (float)_winT - 2, "SCORE: ");
            RenderString((float)_winR - 4.9f, (float)_winT - 3.5f, "TIME: ");
            RenderString((float)_winR - 4.9f, (float)_winT - 8, "BONUS");

            // END OF DRAWING CODE
            ///////////////////////////////////////////////
            System.Threading.Thread.Sleep(10); // because no deltaTime used yet

            Glut.glutSwapBuffers();

        }
        #endregion MainDisplay


        #region ReshapeInitIdle


        private static void myGlInit()
        {
            texture = new uint[2];
            cardRow = new int[4];
            cardCol = new int[6];
            cardRowGap = 5;

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
