////////////////////////////////////
////////// Created: 10:00am 7th December 2008
////////// Author: Jason Carby
////////// Work done: Namespace changed from Player to CardGame
////////// Signed off: 10:03am 7th December 2008
////
//////////
////////////////////////////////////

namespace CardGame
{
    public interface IPlayer
    {
        ///<summary>
        /// Validates the players name
        ///</summary>
        ///<param name="inName">A string containing a name</param>
        ///<returns>Returns empty string if succesful or error message 
        ///if unsucesful</returns>
        string validateName(string inName);

        ///<summary>
        /// Sets the players name
        ///</summary>
        ///<param name="inName">A string containing a name</param>
        ///<returns>Nothing</returns>
        void setName(string inName);

        ///<summary>
        /// Gets the players name
        ///</summary>
        ///<returns>Players Name as a string</returns>
        string getName();

        ///<summary>
        /// Sets the players score
        ///</summary>
        ///<param name="inScore">An integer value to add to the current score</param>
        ///<returns>Nothing</returns>
        void setScore(int inScore);

        ///<summary>
        /// Returns the players current score
        ///</summary>
        ///<returns>The players current score as an integer</returns>
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
            if (validateName(inName) == "")//Name is valid
            {
                setName(inName);//Set players name
                setScore(0);//Set score to zero
            }
        }

        public Player()
        {
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
            //Taking each character in turn, check if its either a space
            //or a number
            //If the name contains a space or number, it is invalid
            for (int i = 0; i < inName.Length; i++)
            {
                if (char.IsWhiteSpace(inName[i]) || char.IsNumber(inName[i]))
                {
                    return "Invalid name";
                }
            }

            return "";
        } 
    }
}
