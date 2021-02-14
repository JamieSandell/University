using System;
using GameClubBusinessObjects;

namespace GameClubControlClasses
{

    /// <summary>
    /// Messages which are sent to an instance of the control object to set up 
    /// a reservation.
    /// </summary>
	public interface ITitleReservationMessages 
	{
        /// <summary>
        /// Selects the member for whom the reservation is being made.
        /// </summary>
        /// <param name="name">The name of the member</param>
        /// <returns>true if the member has been found and selected</returns>
		bool SelectMemberByName ( string name ) ;
        /// <summary>
        /// Selects the title for whom the reservation is being made.
        /// </summary>
        /// <param name="name">The name of the game title</param>
        /// <returns>true if the title has been found and selected</returns>
		bool SelectTitleByName ( string name ) ;
        /// <summary>
        /// Reserve the title
        /// </summary>
        /// <returns>true if the title has been reserved</returns>
		bool ReserveTitle () ;
        /// <summary>
        /// Abort the reservation and deselect any items
        /// </summary>
        void AbortReservation();

        /// <summary>
        /// The reservation instance that has been created. Null if 
        /// one has not been made yet.
        /// </summary>
        TitleReservation Result
        {
            get;
        }
	}

	/// <summary>
	/// Makes a reservation for a game for a particular member
	/// </summary>
	public class MakeTitleReservation : ITitleReservationMessages 
	{
		GameClub club;
		ClubMember member = null;
		Title title = null;
		TitleReservation result = null;

        /// <summary>
        /// Gets the created reservation, or null if one is not present
        /// </summary>
		public TitleReservation Result 
		{
			get 
			{
				return result;
			}
		}

        /// <summary>
        /// Selects the member by name
        /// </summary>
        /// <param name="name">the name of the member to search for</param>
        /// <returns>true if the member has been found and selected</returns>
		public bool SelectMemberByName ( string name ) 
		{
			member = club.FindMemberByName(name);
			if ( member == null ) 
			{
				return false;
			}
			return true;
		}

        /// <summary>
        /// Selects the game title by name
        /// </summary>
        /// <param name="name">the name of the game to search for</param>
        /// <returns>true if the game has been found and selected</returns>
		public bool SelectTitleByName ( string name ) 
		{
			title = club.FindTitleByName ( name ) ;
			if ( title == null ) 
			{
				return false;
			}
			return true;
		}

        /// <summary>
        /// Perform the reservation action and create an reservation instance
        /// Precondition : the member must have been selected
        /// Precondition : the title must have been selected
        /// </summary>
        /// <returns>true if the reservation has been selected.</returns>
		public bool ReserveTitle () 
		{
			if ( member == null ) 
			{
				return false;
			}
			if ( title == null ) 
			{
				return false;
			}

			result = new TitleReservation ( member, title ) ;

			if ( result == null ) 
			{
				return false;
			}
			
			return true;
		}

        /// <summary>
        /// Creates an istance of the control class to manage one use 
        /// of the reservation action
        /// </summary>
        /// <param name="inClub">The game club containing the member
        ///  and the title to be reserved</param>
		public MakeTitleReservation( GameClub inClub )
		{
			club = inClub;
		}

        /// <summary>
        /// Aborts the reservation. 
        /// </summary>
        public void AbortReservation()
        {
            result = null;
        }
	}
}
