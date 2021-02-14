////////////////////////////////////
////////// Created: 20 November 2008
////////// Author: Jason Carby
////////// Work done: Created and Implemented Interface
////////// Signed off: 22 November 2008
////
////////// Author: Jamie Sandell
////////// Signed On: 11:01am - 7th December 2008
////////// Work done: Changed the namespace name so it differs from the Class name
//////////              Added a default (empty) constructor
////////// Signed off: 11:02am - 7th December 2008
////////////////////////////////////

namespace CardGame
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

        public Player()
        {

        }

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

        public void test(string inName)
        {
            System.Console.WriteLine("Players Name: " + this.getName());

            System.Console.WriteLine();
            System.Console.WriteLine("Attempt to change players name to n4me,this should fail");

            inName = "n4me";

            if (this.validateName(inName) == "")
            {
                this.setName(inName);
            }

            System.Console.WriteLine("Players Name: " + this.getName());
            System.Console.WriteLine();

            System.Console.WriteLine("Players Score: " + this.getScore());

            System.Console.WriteLine("Increase Players score by 50");
            this.setScore(50);
            System.Console.WriteLine("Players Score: " + this.getScore());

            System.Console.WriteLine();
        }
 
    }
}
