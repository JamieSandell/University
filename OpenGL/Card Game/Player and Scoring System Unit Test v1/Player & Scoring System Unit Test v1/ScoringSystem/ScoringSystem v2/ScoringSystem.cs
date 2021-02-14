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
using System.Collections.Generic;
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
        ///
        ///</summary>
        ///<returns></returns>
        void addToHighScoreTable(string inPlayersName, int inPlayersScore);

        ///<summary>
        ///
        ///</summary>
        ///<returns></returns>
        void drawHighScoreTable();

        ///<summary>
        ///Sorts the high score table into descending order
        ///</summary>
        ///<returns></returns>
        void sortHighScoreTable();

        ///<summary>
        ///
        ///</summary>
        ///<returns></returns>
        void removeLowestScore();
    }

    public class ScoringSystem:IScoringSystem
    {
        //The filename of the high score table
        private string _mHighScoreTableFile = "highScoreTable.txt";

        private List<ScoreEntry> _mHighScoreTable = new List<ScoreEntry>();

        private struct ScoreEntry : System.IComparable
        {
            public int score;
            public string name;

            public ScoreEntry(string n, int s)
            {
                name = n;
                score = s;
            }

            public int CompareTo(object obj)
            {
                ScoreEntry e = (ScoreEntry)obj;
                return score.CompareTo(e.score);
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
                return "high score table could not be found";
            }



        }

        public string saveHighScoreTable()
        {

            TextWriter textOut = new StreamWriter(_mHighScoreTableFile);

            this.sortHighScoreTable();
            this.removeLowestScore();

            textOut.WriteLine(_mHighScoreTable.Count);

            foreach (ScoreEntry i in _mHighScoreTable)
            {
                textOut.WriteLine(i.name);
                textOut.WriteLine(i.score);
            }

            textOut.Close();

            return "";
        }

        public void addToHighScoreTable(string inPlayersName, int inPlayersScore)
        {
            _mHighScoreTable.Add(new ScoreEntry(inPlayersName, inPlayersScore));
        }

        public void drawHighScoreTable()
        {
            this.sortHighScoreTable();

            foreach (ScoreEntry i in _mHighScoreTable)
            {
                Console.WriteLine(i.name);
                Console.WriteLine(i.score);
            }
         
        }

        public void sortHighScoreTable()
        {
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

        public void test()
        {
            if (this.loadHighScoreTable() == "")
            {
                Console.WriteLine("Load high score table Succesful");
            }

            else
            {
                Console.WriteLine("load high score table unsucessful");
            }

            Console.WriteLine();
            this.drawHighScoreTable();
            Console.WriteLine();

            this.addToHighScoreTable("Player", 100);

            if (this.saveHighScoreTable() == "")
            {
                Console.WriteLine("Save high score table Succesful");
            }

            else
            {
                Console.WriteLine("save high score table unsucesful");
            }
        }
    }
}