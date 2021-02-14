////////////////////////////////////
////////// Created: 
////////// Author: Jason Carby
////////// Work done: 
////////// Signed off: 
////
//////////
////////////////////////////////////

using System;
using System.Collections;
using System.IO;

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
        ///Draws the high score table on screen
        ///</summary>
        ///<returns>Returns empty string if succesful or error message 
        ///if unsucesful</returns>
        string drawHighScoreTable();
    }

    public class ScoringSystem:IScoringSystem
    {
        //The filename of the high score table
        private string _mHighScoreTableFile = "highScoreTable.txt";

        //The ArrayList used to store the high score table
        private ArrayList _mHighScoreArrayList = new ArrayList();

        //Constructor
        public ScoringSystem()
        {
        }

        public struct ScoreEntry : System.IComparable
        {
            public string playersName;
            public int playersScore;

            public ScoreEntry(string inPlayersName, int inPlayersScore)
            {
                playersName = inPlayersName;
                playersScore = inPlayersScore;
            }

            public int CompareTo(object obj)
            {
                ScoreEntry e = (ScoreEntry)obj;
                return playersScore.CompareTo(e.playersScore);
            }
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
                    for (int i = 0; i < count; i++)
                    {
                        string playersName = textIn.ReadLine();
                        int playersScore = int.Parse(textIn.ReadLine());

                        _mHighScoreArrayList.Add(new ScoreEntry(playersName, playersScore));
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
                return "Unable to load high score table";
            }
        }

        public string saveHighScoreTable()
        {
            TextWriter textOut = new StreamWriter(_mHighScoreTableFile);

            _mHighScoreArrayList.Sort();
            _mHighScoreArrayList.Reverse();

            // cut the table down to the required size, mine being 5
            if (_mHighScoreArrayList.Count > 10)
            {
                _mHighScoreArrayList.RemoveAt(10);
            }

            textOut.WriteLine(_mHighScoreArrayList.Count);

            foreach (ScoreEntry i in _mHighScoreArrayList)
            {
                textOut.WriteLine(i.playersScore);
                textOut.WriteLine(i.playersName);
            }

            textOut.Close();

            return "";
        }

        public string drawHighScoreTable()
        {
            //TO DO: Draw High Score Table

            return "";
        }

    }
}
