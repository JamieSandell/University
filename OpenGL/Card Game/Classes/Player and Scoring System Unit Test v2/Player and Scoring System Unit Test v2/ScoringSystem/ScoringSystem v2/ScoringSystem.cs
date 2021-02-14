////////////////////////////////////
////////// Created: 
////////// Author: Jason Carby
////////// Work done: 
////////// Signed off: 
////
//////////
////////////////////////////////////

using System.Collections.Generic; //For _mHighScoreTable list data structure
using System.IO; //For Loading and Saving _mHighScoreTable from/to a txt file

namespace ScoringSystem
{
    public interface IScoringSystem
    {
        ///<summary>
        /// Loads the high score table from a text file
        ///</summary>
        ///<returns>Returns empty string if succesful or error message 
        ///if unsucesful</returns>
        string loadHighScoreTable();

        ///<summary>
        /// Saves the high score table to a text file
        ///</summary>
        ///<returns>Returns empty string if succesful or error message 
        ///if unsucesful</returns>
        string saveHighScoreTable();

        ///<summary>
        ///Adds a new entry to the high score table
        ///</summary>
        ///<returns>Nothing</returns>
        void addToHighScoreTable(string inPlayersName, int inPlayersScore);

        ///<summary>
        ///Draws the high score table on screen
        ///</summary>
        ///<returns>Nothing</returns>
        void drawHighScoreTable();

        ///<summary>
        ///Sorts the high score table into descending order
        ///</summary>
        ///<returns>Nothing</returns>
        void sortHighScoreTable();

        ///<summary>
        ///Removes the lowest score from the high score table
        ///</summary>
        ///<returns>Nothing</returns>
        void removeLowestScore();
    }

    public class ScoringSystem:IScoringSystem
    {
        //The filename of the high score table txt file
        private string _mHighScoreTableFile = "highScoreTable.txt";

        //The list data structure used to store the high score table
        private List<ScoreEntry> _mHighScoreTable = new List<ScoreEntry>();

        //The struct used to hold the players name and score
        //before it is added to the high score table
        private struct ScoreEntry : System.IComparable
        {
            public string _mPlayersName;//The players name
            public int _mPlayersScore;//The players score

            //A constructor for the struct
            public ScoreEntry(string inName, int inScore)
            {
                _mPlayersName = inName;
                _mPlayersScore = inScore;
            }

            //This method takes two scores and compares them to
            //each other and sorts them into ascending order
            public int CompareTo(object obj)
            {
                ScoreEntry e = (ScoreEntry)obj;
                return _mPlayersScore.CompareTo(e._mPlayersScore);
            }
        }

        //Constructor
        public ScoringSystem()
        {
        }

        public string loadHighScoreTable()
        {
            TextReader textIn = null;

            if (File.Exists(_mHighScoreTableFile))
            {
                try
                {
                    textIn = new StreamReader(_mHighScoreTableFile);

                    int count = int.Parse(textIn.ReadLine());

                    //If for any reason there are more than 10 entries
                    //in the high score table, only load in the first 10
                    if (count > 10)
                    {
                        count = 10;
                    }

                    for (int i = 0; i < count; i++)
                    {
                        string playersName = textIn.ReadLine();
                        int playersScore = int.Parse(textIn.ReadLine());

                        this.addToHighScoreTable(playersName, playersScore);
                    }

                    textIn.Close();

                    return "";
                }

                catch
                {
                    textIn.Close();
                    return "Unable to load high score table";
                }

            }

            else
            {
                return "High score table could not be found";
            }
        }

        public string saveHighScoreTable()
        {
            TextWriter textOut = null;

            try
            {
                textOut = new StreamWriter(_mHighScoreTableFile);

                this.sortHighScoreTable();
                this.removeLowestScore();

                textOut.WriteLine(_mHighScoreTable.Count);

                foreach (ScoreEntry i in _mHighScoreTable)
                {
                    textOut.WriteLine(i._mPlayersName);
                    textOut.WriteLine(i._mPlayersScore);
                }

                textOut.Close();

                return "";
            }

            catch
            {
                textOut.Close();
                return "Unable to save high score table";
            }
        }

        public void addToHighScoreTable(string inPlayersName, int inPlayersScore)
        {
            _mHighScoreTable.Add(new ScoreEntry(inPlayersName, inPlayersScore));
        }

        public void drawHighScoreTable()
        {
            //TO DO: Add Draw Code

            this.sortHighScoreTable();//Sort the high score table before drawing
        }

        public void sortHighScoreTable()
        {
            //Sort the high score table and then reverse it
            //so its in descending order
            _mHighScoreTable.Sort();
            _mHighScoreTable.Reverse();
        }

        public void removeLowestScore()
        {
            //If the high score table has more than 10 entries, remove the
            //lowest score
            if (_mHighScoreTable.Count > 10)
            {
                _mHighScoreTable.RemoveAt(10);
            }
        }

        //This method is for testing purposes only
        public void test()
        {
            if (this.loadHighScoreTable() == "")
            {
                System.Console.WriteLine("Load high score table Succesful");
            }

            else
            {
                System.Console.WriteLine("Load high score table unsucessful");
            }

            this.sortHighScoreTable();

            System.Console.WriteLine();
            System.Console.WriteLine("High Score Table:");
            System.Console.WriteLine();

            foreach (ScoreEntry i in _mHighScoreTable)
            {
                System.Console.WriteLine(i._mPlayersName);
                System.Console.WriteLine(i._mPlayersScore);
            }
            System.Console.WriteLine();

            System.Console.WriteLine("Add to high score table: Player - 200 ");
            this.addToHighScoreTable("Player", 200);

            System.Console.WriteLine();
            System.Console.WriteLine("High Score Table:");
            System.Console.WriteLine();

            foreach (ScoreEntry i in _mHighScoreTable)
            {
                System.Console.WriteLine(i._mPlayersName);
                System.Console.WriteLine(i._mPlayersScore);
            }
            System.Console.WriteLine();

            if (this.saveHighScoreTable() == "")
            {
                System.Console.WriteLine("Save high score table Succesful");
            }

            else
            {
                System.Console.WriteLine("Save high score table unsucesful");
            }
        }
    }
}