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
        private string _MPlayersName;// The name of the player
        private int _MPlayersScore;// The player’s current score

        //Constructor 
        //Validates parameter
        //If validation positive sets _MName to parameter inName
        //and sets _MScore to 0
        public Player(string inName)
        {
            if (validateName(inName) == "")
            {
                setName(inName);
                setScore(0);
            }
        }

        public void setName(string inName)
        {
            _MPlayersName = inName;
        }

        public string getName()
        {
            return _MPlayersName;
        }

        public void setScore(int inScore)
        {
            _MPlayersScore = _MPlayersScore + inScore;
        }

        public int getScore()
        {
            return _MPlayersScore;
        }

        public string validateName(string inName)
        {
            for (int i = 0; i < inName.Length; i++)
            {
                if (char.IsWhiteSpace(inName[i]) || char.IsNumber(inName[i]))
                {
                    return "Invalid name";
                }
            }

            return "";
        }

        public void test(string inName)
        {
            Console.WriteLine("Players Name: " + this.getName());

            inName = "invalid name";

            if (this.validateName(inName) == "")
            {
                this.setName(inName);
            }
            Console.WriteLine("Players Name: " + this.getName());

            this.setScore(100);
            Console.WriteLine("Players Score: " + this.getScore());

            Console.WriteLine();
        }
 
    }
}
