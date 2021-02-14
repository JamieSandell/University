/////////////////////////////////////////////////
////////Author: Jamie Sandell
////////Signed On: 27th November 2008 - 2:15pm
////////Work done: Created the class and added relevant methods
////////Signed Off: 27th November 2008 - 3:52pm
////
////////Author: Jamie Sandell
////////Signed On: 3rd December 2008 - 10:40am
////////Work done: Removed bindTexture code from the draw method
////////Signed Off: 3rd December 2008 - 10:43am
////
////////Author: Jamie Sandell
////////Signed On: 7th December - 10:21am
////////Work done: Added member variables _MTimeRemaining, _MScore, _MRenderText
////////            Added methods SetScore and SetTimeRemaining, replaced
////////                RenderString with Text.RenderString
////////Signed Off: 7th December - 10:27am
/////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using Tao.OpenGl;
using Tao.FreeGlut;

namespace CardGame
{
    public interface IUserInterface
    {
        /// <summary>
        /// Draw the UserInterface
        /// </summary>
        /// <param name="inWinL">Left World Window</param>
        /// <param name="inWinR">Right World Window</param>
        /// <param name="inWinT">Top World Window</param>
        /// <param name="inWinB">Bottom World Window</param>
        /// <param name="inWinWidth">Window Dimension</param>
        /// <param name="inWinHeight">Window Dimension</param>
        /// <returns>Nothing</returns>
        void Draw(double inWinL, double inWinR, double inWinT, double inWinB,
            int inWinWidth, int inWinHeight);

        /// <summary>
        /// Sets the current state, e.g. 0 = IntroScreen state
        /// </summary>
        /// <param name="inState">The state passed in</param>
        /// <returns>Returns an empty string if OK else error message</returns>
        string SetState(int inState);

        /// <summary>
        /// Sets the current textures
        /// </summary>
        /// <param name="inTextures">An array of textures</param>
        void SetTexture(int[] inTextures);

        /// <summary>
        /// Set's the time left
        /// </summary>
        /// <param name="inTimeLeft">The game-time remaining</param>
        void SetTimeLeft(int inTimeLeft);

        /// <summary>
        /// Set the score to draw
        /// </summary>
        /// <param name="inScore">The score</param>
        void SetScore(int inScore);
    }

    public class UserInterface
    {
        private int _MCurrentState; // This will be used to determine what is drawn on the screen
                            // e.g. Intro screen, playing screen
        private int[] _MTexture; // Stores the different textures, texture order should match the
                                    // _MCurrentState ordering
        private int _MTimeRemaining;
        private int _MScore;
        private static Text _MRenderText = new Text();

        public UserInterface()
        {
            _MCurrentState = 0;
            _MTexture = null;
            _MScore = 0;
        }

        public void Draw(double inWinL, double inWinR, double inWinT, double inWinB,
            int inWinWidth, int inWinHeight)
        {
            if (_MCurrentState==0) // Draw the IntroScene
            {
                //Gl.glBegin(Gl.GL_QUADS);
                Gl.glTexCoord2f(0.0f, 0.0f);
                Gl.glVertex3f((float)inWinL, (float)inWinB, 0.0f); // Bottom Left

                Gl.glTexCoord2f(1.0f, 0.0f);
                Gl.glVertex3f((float)inWinR, (float)inWinB, 0.0f);// Bottom right

                Gl.glTexCoord2f(1.0f, 1.0f);
                Gl.glVertex3f((float)inWinR, (float)inWinT, 0.0f);// Top right

                Gl.glTexCoord2f(0.0f, 1.0f);
                Gl.glVertex3f((float)inWinL, (float)inWinT, 0.0f);// Top left
                //Gl.glEnd();
            }
            if (_MCurrentState==1) // Draw the playing scene
            {
                //Gl.glBindTexture(Gl.GL_TEXTURE_2D, _MTexture[_MCurrentState]);
                //Gl.glEnable(Gl.GL_TEXTURE_2D);
                Gl.glBegin(Gl.GL_QUADS);
                    Gl.glTexCoord2f(0.0f, 0.0f);
                    Gl.glVertex3f((float)inWinL, (float)inWinB, 0.0f); // Bottom Left

                    Gl.glTexCoord2f(1.0f, 0.0f);
                    Gl.glVertex3f((float)inWinR, (float)inWinB, 0.0f);// Bottom right

                    Gl.glTexCoord2f(1.0f, 1.0f);
                    Gl.glVertex3f((float)inWinR, (float)inWinT, 0.0f);// Top right

                    Gl.glTexCoord2f(0.0f, 1.0f);
                    Gl.glVertex3f((float)inWinL, (float)inWinT, 0.0f);// Top left
                Gl.glEnd();

                Gl.glDisable(Gl.GL_TEXTURE_2D);
                Gl.glColor3f(0.0f, 0.0f, 0.0f);
                Gl.glLineWidth(3.0f);
                Gl.glBegin(Gl.GL_LINES);
                    Gl.glVertex3f((float)inWinR - 5, (float)inWinT, 0.0f); // Right Vertical Line
                    Gl.glVertex3f((float)inWinR - 5, (float)inWinB, 0.0f);
                    Gl.glVertex3f((float)inWinL, (float)(inWinT + inWinB) / 2, 0.0f); // Middle Horizontal line
                    Gl.glVertex3f((float)inWinR - 5, (float)(inWinT + inWinB) / 2, 0.0f);
                Gl.glEnd();

                Gl.glDisable(Gl.GL_TEXTURE_2D);
                Gl.glColor3f(1.0f, 1.0f, 1.0f);
                _MRenderText.RenderString((float)inWinR - 4.9f, (float)inWinT - 2, "SCORE: " +
                    _MScore.ToString());
                _MRenderText.RenderString((float)inWinR - 4.9f, (float)inWinT - 3.5f, "TIME: " +
                    _MTimeRemaining.ToString());
            }
        }

        public string SetState(int inState)
        {
            ///TODO:
            ///Add validation
            _MCurrentState = inState;
            return ""; // If here everything went OK
        }

        public void SetTexture(int[] inTexture)
        {
            _MTexture = new int[inTexture.Length];
            inTexture.CopyTo(_MTexture, 0);
        }

        public void SetTimeLeft(int inTime)
        {
            _MTimeRemaining = inTime;
        }

        public void SetScore(int inScore)
        {
            _MScore = inScore;
        }
    }
}
