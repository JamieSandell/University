////////////////////////////////////
////////// Created: 19th November 2008 - 20:30
////////// Author: Jamie Sandell
////////// Work done: Interface created and implemented
////////// Signed off: 19th November 2008 - 21:37
////
////////// Author: Jamie Sandell
////////// Signed On: 22nd November 2008 - 12:31pm
////////// Work done: Added the FlipCard method
////////// Signed off: 22nd November 2008 - 14:35
////
////////// Author: Jamie Sandell
////////// Signed On: 24th November 2008 - 08:57pm
////////// Work done: Removed IsTypeValid
//////////              Added strings _MProtection and _MRay, removed ArrayList _MType
//////////              Added the IsPair method
////////// Signed off: 24th November 2008 - 10:03pm
////
////////// Author: Jamie Sandell
////////// Signed On: 25th November 2008 - 3:20pm
////////// Work done: Added _MCurrentTexture
//////////              Added texture code to the Draw function
//////////              Removed the update function
////////// Signed off: 25th November 2008 - 15:48pm
////
////////// Author: Jamie Sandell
////////// Signed On: 25th November 2008 - 4:04pm
////////// Work done: Changed inTexture in the Constructor to an Array type
//////////              Added the methods, SetPosition, SetTexture, SetRay, GetTexture, and SetProtection
//////////              Changed all ArrayList types to Arrays
////////// Signed off: 25th November 2008 - 5:04pm
////
////////// Author: Jamie Sandell
////////// Signed On: 27th November 2008 - 11:18am
////////// Work done: Added the _MColourdID variable
//////////              Added the GetColourID method
//////////              Removed the none-default constructor - will only be using the default
//////////              constructor along with Setters
////////// Signed off: 27th November 2008 - 11:30am
////
////////// Author: Jamie Sandell
////////// Signed On: 27th November 2008 - 2:04pm
////////// Work done: Updated comments, tested compilation in Release Mode
////////// Signed off: 27th November 2008 - 2:09pm
////
////////// Author: Jamie Sandell
////////// Signed On: 3rd December 2008 - 2:15pm
////////// Work done: Added _MFlipped and IsFlipped method.
////////// Signed off: 3rd December 2008 - 2:23pm
////
////////// Author: Jamie Sandell
////////// Signed On: 4th December 2008 - 11:15am
////////// Work done: _MColourID is no longer static, added static _MCardCounter
//////////              Added _MType, and Set/GetType methods
//////////              Added GetProtection method and GetRay method
////////// Signed off: 4th December 2008 - 11:25am
////
////////// Author: Jamie Sandell
////////// Signed On: 7th December 2008 - 4:40pm
////////// Work done: Changed _MCounter to += 1 on every instance
////////// Signed off: 7th December 2008 - 4:42pm
////////////////////////////////////

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using Tao.OpenGl;

namespace CardGame
{
    public interface ICard
    {
        /// <summary>
        /// Checks to see if two cards are a pair
        /// </summary>
        /// <param name="inRay">A ray card</param>
        /// <param name="inProtection">A protection card</param>
        /// <returns>True if they are a pair, else false</returns>
        bool IsPair(string inRay, string inProtection);

        ///<summary>
        /// Returns true or false according to the alive status of the card
        ///</summary>
        ///<returns>Returns _MAlive</returns>
        bool IsAlive();

        /// <summary>
        /// Returns true if the card is flipped (front showing), else false (back showing)
        /// </summary>
        /// <returns>_MFlipped</returns>
        bool IsFlipped();

        ///<summary>
        /// Sets the alive status
        ///</summary>
        ///<returns>Nothing</returns>
        void SetAliveStatus(bool inAlive);

        ///<summary>
        /// Get the position of the card - useful for collision (e.g. mouse-click no card)
        ///</summary>
        ///<returns>An array of floats</returns>
        float[] GetPosition();

        /// <summary>
        /// Set the position of the card.
        /// </summary>
        /// <param name="inPosition">The positions passed in</param>
        /// <returns>Nothing</returns>
        void SetPosition(float[] inPosition);

        /// <summary>
        /// Sets the texture (front and back) of the card.
        /// </summary>
        /// <param name="inTexture">The textures passed in</param>
        /// <returns>Nothing</returns>
        void SetTexture(int[] inTexture);

        /// <summary>
        /// Gets the current texture
        /// </summary>
        /// <returns>An int</returns>
        int GetTexture();

        /// <summary>
        /// Gets the colourID (R,G,B) of the card.
        /// </summary>
        /// <returns>Nothing</returns>
        int[] GetColourID();

        /// <summary>
        /// Sets the ray type of the card
        /// </summary>
        /// <param name="inRay">The type of ray</param>
        /// <returns>Nothing</returns>
        void SetRay(string inRay);

        /// <summary>
        /// Get the ray
        /// </summary>
        /// <returns>Returns the ray of the card</returns>
        string GetRay();

        /// <summary>
        /// Sets the protection type of the card
        /// </summary>
        /// <param name="inProtection">The type of protection</param>
        /// <returns>Nothing</returns>
        void SetProtection(string inProtection);

        /// <summary>
        /// Gets the protection of the card
        /// </summary>
        /// <returns>The protection of the card</returns>
        string GetProtection();

        /// <summary>
        /// Gets the type of the card
        /// </summary>
        /// <returns>Returns the type of the card</returns>
        string GetType();

        /// <summary>
        /// Sets the type to either "Ray" or "Protection"
        /// </summary>
        /// <param name="inType">The type passed in</param>
        void SetType(string inType);

        ///<summary>
        /// Draws the card, GlBegin is not used within the instance, too inefficient
        ///</summary>
        ///<returns>Nothing</returns>
        void Draw();

        ///<summary>
        /// Flips the card, i.e. changes the texture from the back to the front and vice versa
        ///</summary>
        ///<returns>Nothing</returns>
        void FlipCard();
    }

    public class Card:ICard
    {
        private bool _MAlive; // if true the card is alive, else it isn't and therefore
                              // no actions should be taken on it (e.g. discard mouseclicks)
        private float [] _MPosition = new float [12]; // it is size 12 because we will be drawing the
                                                        // cards using gl_quads and as such there will be
                                                        // 12 vertices in total
        private string _MRay; // The type of ray, used for finding a correct pair, e.g. "UltraViolet"
        // pairs with "Sun glasses" protection
        private string _MProtection; // see _MRay
        private int [] _MTexture = new int[2]; // First element is the back texture, 2nd element is the
                                            // front element
        private int _MCurrentTexture; // used in conjunction with _MTexture, 0 = back, 1 = front
        private bool _MFlipped; // If true show front else texture, else show back texture
        private int[] _MColourID = new int[]{0,0,0}; // e.g. each value between 0 and 255(RGB)
                                        // used for colour coding for identifying a clicked card
                                        //(i.e. readpixels)
        private static int _MCardCounter = 0; // Used for creating unique _MColourID values
        private string _MType; // Either Protection or Ray

        public Card()
        {
            _MAlive = true;
            _MPosition[0] = -1.0f; // bottom left x
            _MPosition[1] = -0.5f; // bottom left y
            _MPosition[2] = 0.0f; // bottom left z
            _MPosition[3] = 1.0f; // bottom right x
            _MPosition[4] = -0.5f; // bottom right y
            _MPosition[5] = 0.0f; // bottom right z
            _MPosition[5] = 1.0f; // top right x
            _MPosition[6] = 0.5f; // top right y
            _MPosition[7] = 0.0f; // top right z
            _MPosition[8] = -1.0f; // top left x
            _MPosition[9] = 0.5f; // top left y
            _MPosition[11] = 0.0f; // top left z
            _MRay = "UltraViolet";
            _MProtection = "SunGlasses";
            _MCurrentTexture = 0;
            _MFlipped = false;
            _MCardCounter += 1;
            _MColourID[0] = _MCardCounter;
        }

        public bool IsPair(string inRay, string inProtection)
        {
            if (inRay==_MRay && (inProtection == _MProtection)) // found a matching pair
            {
                return true;
            }
            return false; // No match was found
        }

        public bool IsAlive()
        {
            return _MAlive;
        }

        public bool IsFlipped()
        {
            return _MFlipped;
        }

        public void SetAliveStatus(bool inAlive)
        {
            _MAlive = inAlive;
        }

        public float[] GetPosition()
        {
            return _MPosition;
        }

        public void SetPosition(float[] inPosition)
        {
            /// TODO:
            /// Add validation
            
            for (int i = 0; i < inPosition.Length; i++)
            {
                _MPosition[i] = inPosition[i];
            }
        }

        public void SetTexture(int[] inTexture)
        {
            /// TODO:
            /// Add validation
            /// 

            for (int i = 0; i < inTexture.Length; i++)
            {
                _MTexture[i] = inTexture[i];
            }
        }

        public int GetTexture()
        {
            return _MTexture[_MCurrentTexture];
        }

        public int[] GetColourID()
        {
            return _MColourID;
        }

        public void SetRay(string inRay)
        {
            /// TODO:
            /// Add validation
            /// 

            _MRay = inRay;
        }

        public string GetRay()
        {
            return _MRay;
        }

        public void SetProtection(string inProtection)
        {
            /// TODO:
            /// Add validation
            /// 

            _MProtection = inProtection;
        }

        public string GetProtection()
        {
            return _MProtection;
        }

        public void SetType(string inType)
        {
            /// TODO:
            /// Add validation
            /// 

            _MType = inType;
        }

        public string GetType()
        {
            return _MType;
        }

        public void Draw()
        {

            Gl.glTexCoord2f(0.0f, 0.0f);
            Gl.glVertex3f(_MPosition[0], _MPosition[1],
                _MPosition[2]); // x,y,z - BottomLeft

            Gl.glTexCoord2f(1.0f, 0.0f);
            Gl.glVertex3f(_MPosition[3], _MPosition[4],
                _MPosition[5]); // x,y,z - BottomRight

            Gl.glTexCoord2f(1.0f, 1.0f);
            Gl.glVertex3f(_MPosition[6], _MPosition[7],
                _MPosition[8]); // x,y,z - TopRight

            Gl.glTexCoord2f(0.0f, 1.0f);
            Gl.glVertex3f(_MPosition[9], _MPosition[10],
                _MPosition[11]); // x,y,z - TopLeft

        }

        public void FlipCard()
        {
            if (_MCurrentTexture==0) // back is showing
            {
                _MCurrentTexture = 1; // flip it so the front is showing
                _MFlipped = true;
            }
            else // front is showing
            {
                _MCurrentTexture = 0; // flip it so the back is showing
                _MFlipped = false;
            }           
        }
    }
}
