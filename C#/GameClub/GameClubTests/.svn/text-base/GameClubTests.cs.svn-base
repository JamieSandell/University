using System;
using System.Windows.Forms;
using GameClubBusinessObjects;
using GameClubControlClasses;
using GameClubWindowsGUI;

namespace GameClubTests
{

	class GameClubTester 
	{
		private string [] testMemberNames = new string [] { "Rob", "Jim", "Ethel" } ;
		private string [] testTitles = new string [] { "Doom 3", "Half Life 2", "PacMan"  };

		private GameClub MakeTestGameClub () 
		{
			GameClub result = new GameClub( "Test Gameclub" ) ;

			//add the members
			foreach ( string name in testMemberNames ) 
			{
				ClubMember c = new ClubMember( name, name + "'s House" );
				result.AddMember(c);
			}

			//add the titles

			// counter for unique ID
			long id = 0 ;

			foreach ( string title in testTitles ) 
			{
				Title t = new Title (title);
				for ( int i=0 ; i < 3 ; i++ ) 
				{
					LendableItem l = new LendableItem( t, id ) ;
					id++;
					result.AddLendableItem(l);
					t.AddLendableItem(l);
				}
				result.AddTitle(t);
			}
			return result;
		}

		private void TestMakeReservation () 
		{
			Console.WriteLine ( "Testing MakeReservation control class");

			GameClub test = MakeTestGameClub();
			MakeTitleReservation reserveMaker = new MakeTitleReservation ( test ) ;

			if ( !reserveMaker.SelectTitleByName("Doom 3") ) 
			{
				Console.WriteLine ( "Reservation maker failed to find game");
			}

			if ( !reserveMaker.SelectMemberByName("Rob") ) 
			{
				Console.WriteLine ( "Reservation maker failed to find member" ) ;
			}

			if ( !reserveMaker.ReserveTitle() ) 
			{
				Console.WriteLine ( "Reservation maker failed to make reservation");
			}

			TitleReservation reservation = reserveMaker.Result;

			if ( reservation == null ) 
			{
				Console.WriteLine ( "Reservation maker null result");
			}
			else 
			{
				Console.WriteLine ( reservation );
			}
		}

		private void TestGUIMakeReservation () 
		{
			Console.WriteLine ( "Testing MakeReservationForm GUI control");
			GameClub test = MakeTestGameClub();
			MakeTitleReservation reserveMaker = new MakeTitleReservation ( test ) ;

			TitleReservationForm form = new TitleReservationForm (reserveMaker);
			form.ShowDialog();
			
			TitleReservation reservation = reserveMaker.Result;

			if ( reservation == null ) 
			{
				Console.WriteLine ( "GUI Reservation maker null result");
			}
			else 
			{
				Console.WriteLine ( reservation );
			}

		}

		public void RunTests () 
		{
			GameClub test = MakeTestGameClub();
			Console.WriteLine ( test );
			TestMakeReservation();
			TestGUIMakeReservation();
		}
	}

	/// <summary>
	/// Runs tests on the business objects
	/// </summary>
	class RunTests
	{

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			GameClubTester tester = new GameClubTester();
			tester.RunTests();
			Console.ReadLine();
		}
	}
}
