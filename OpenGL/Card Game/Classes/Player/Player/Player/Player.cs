////////////////////////////////////
////////// Created: 20 November 2008
////////// Author: Jason Carby
////////// Work done: Created and Implemented Interface
////////// Signed off: 22 November 2008
////
//////////
////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;

namespace Player
{
    public interface IPlayer
    {
        ///<summary>
        /// Validates the players name
        ///</summary>
        ///<returns>Returns empty string if succesful or error message 
        ///if unsucesful</returns>
        string validateName(string inName);

        ///<summary>
        /// Sets the players name
        ///</summary>
        ///<returns>Returns empty string if succesful or error message 
        ///if unsucesful</returns>
        void setName(string inName);

        ///<summary>
        /// Sets the players name
        ///</summary>
        ///<returns></returns>
        string getName();

        ///<summary>
        /// Sets the players score
        ///</summary>
        ///<returns></returns>
        void setScore(int inScore);

        ///<summary>
        /// Returns the players current score
        ///</summary>
        ///<returns>The players current score</returns>
        int getScore();
    }

    public class Player:IPlayer
    {
        private string _MName;// The name of the player
        private int _MScore;// The player’s current score

        //Constructor 
        //Validates parameter
        //If validation positive sets _MName to parameter inName
        //and sets _MScore to 0
        public Player(string inName)
        {
            inName = inName.Replace(" ", "");
            validateName(inName);

            if (validateName(inName) == "")
            {
                setName(inName);
                setScore(0);
            }
        }

        public void setName(string inName)
        {
            _MName = inName;
        }

        public string getName()
        {
            return _MName;
        }

        public void setScore(int inScore)
        {
            _MScore = _MScore + inScore;
        }

        public int getScore()
        {
            return _MScore;
        }

        public string validateName(string inName)
        {
            //TO DO: ADD VALIDATION LOGIC

            return "";
        }

 
    }
}
