using System;

namespace GameClubBusinessObjects
{

	/// <summary>
	/// The entire GameClub - contains all the members and the game titles
	/// </summary>
	public class GameClub 
	{
		#region Club Member management

		System.Collections.ArrayList clubMembers = new System.Collections.ArrayList();

		public void AddMember ( ClubMember newMember ) 
		{
			clubMembers.Add(newMember);
		}

		public ClubMember FindMemberByName ( string memberName ) 
		{
			foreach ( ClubMember member in clubMembers ) 
			{
				if ( member.MemberName == memberName ) 
				{
					return member;
				}
			}
			return null;
		}

		public string GetMemberList () 
		{
			System.Text.StringBuilder buffer = new System.Text.StringBuilder();

			foreach ( ClubMember member in clubMembers ) 
			{
				buffer.Append (member.ToString());
				buffer.Append ("\n");
			}
			return buffer.ToString();
		}

		#endregion

		#region Club Title management

		System.Collections.ArrayList titles = new System.Collections.ArrayList();

		public void AddTitle ( Title newTitle ) 
		{
			titles.Add ( newTitle );
		}

		public Title FindTitleByName ( string titleName ) 
		{
			foreach ( Title title in titles ) 
			{
				if ( title.TitleName == titleName ) 
				{
					return title;
				}
			}
			return null;
		}

		public string GetTitleList () 
		{
			System.Text.StringBuilder buffer = new System.Text.StringBuilder();

			foreach ( Title title in titles ) 
			{
				buffer.Append (title.ToString());
				buffer.Append ("\n");
			}
			return buffer.ToString();
		}

		#endregion

		#region Lendable Items management

		System.Collections.ArrayList lendableItems = new System.Collections.ArrayList();

		public void AddLendableItem ( LendableItem newItem ) 
		{
			lendableItems.Add ( newItem );
		}

		public LendableItem FindLendableItemByID ( long id ) 
		{
			foreach ( LendableItem item in lendableItems ) 
			{
				if ( item.ID == id ) 
				{
					return item;
				}
			}
			return null;
		}

		public string GetLendableItemList () 
		{
			System.Text.StringBuilder buffer = new System.Text.StringBuilder();

			foreach ( LendableItem item in lendableItems ) 
			{
				buffer.Append (item.ToString());
				buffer.Append ("\n");
			}
			return buffer.ToString();
		}

		#endregion		
		
		#region Reservation Management

		System.Collections.ArrayList reservations = new System.Collections.ArrayList();

		public void AddReservation ( TitleReservation newReservation ) 
		{
			reservations.Add ( newReservation );
		}

		public string GetReservationList () 
		{
			System.Text.StringBuilder buffer = new System.Text.StringBuilder();

			foreach ( TitleReservation reservation in reservations ) 
			{
				buffer.Append (reservation.ToString());
				buffer.Append ("\n");
			}
			return buffer.ToString();
		}

		#endregion
		

		private string clubName;

		public string ClubName 
		{
			get 
			{
				return clubName;
			}
		}
		#region Constructors

		public GameClub ( string inName ) 
		{
			clubName = inName;
		}

		#endregion

		#region Overriden methods

		public override string ToString()
		{
			System.Text.StringBuilder buffer = new System.Text.StringBuilder();
			buffer.Append ( ClubName ) ;
			buffer.Append ( "\n" ) ;
			buffer.Append ( "Members\n" );
			buffer.Append ( this.GetMemberList() );
			buffer.Append ( "Titles\n" );
			buffer.Append ( this.GetTitleList() );
			buffer.Append ( "Lendable Items\n" );
			buffer.Append ( this.GetLendableItemList() );
			buffer.Append ( "Reservations\n" );
			buffer.Append ( this.GetReservationList() ) ;
			return buffer.ToString();
		}
		
		#endregion

	}

	/// <summary>
	/// Represents a member of the club
	/// </summary>
	public class ClubMember
	{
		private string memberName ;
		public string MemberName 
		{
			get 
			{
				return memberName;
			}
		}

		private string memberAddress ;
		public string MemberAddress 
		{
			get 
			{
				return memberAddress;
			}
		}

		public ClubMember( string inName, string inAddress)
		{
			memberName = inName;
			memberAddress = inAddress;
		}

		#region Overridden Methods

		public override string ToString()
		{
			return "Name : " + memberName + " Address : " + memberAddress;
		}

		public override bool Equals(object obj)
		{
			ClubMember test = obj as ClubMember;

			if ( test.MemberName != MemberName ) 
			{
				return false;
			}

			if ( test.MemberAddress != MemberAddress ) 
			{
				return false;
			}
			return true;
		}

		#endregion 
	}

	/// <summary>
	/// A particular game title that the club will have one or more lendable instances of
	/// </summary>
	public class Title 
	{
		private string titleName;

		public string TitleName 
		{
			get 
			{
				return titleName;
			}
		}

		public Title ( string inName ) 
		{
			titleName = inName;
		}

		System.Collections.ArrayList lendableItems = new System.Collections.ArrayList();

		public void AddLendableItem ( LendableItem item ) 
		{
			lendableItems.Add(item);
		}

		#region Overriden Methods

		public override string ToString()
		{
			System.Text.StringBuilder buffer = new System.Text.StringBuilder();
			buffer.Append ( "Title : " );
			buffer.Append ( TitleName );
			buffer.Append ( "\n" );
			foreach ( LendableItem item in lendableItems ) 
			{
				buffer.Append ( "    ID: " );
				buffer.Append ( item.ID );
				buffer.Append ( "\n" );
			}
			return buffer.ToString();
		}

		public override bool Equals(object obj)
		{
			Title test = obj as Title;

			if ( test.TitleName != TitleName ) 
			{
				return false;
			}

			return true;
		}

		#endregion

	}

	/// <summary>
	/// Something that can be lent - an instance of a title
	/// </summary>
	public class LendableItem 
	{
		private Title itemTitle;

		public Title ItemTitle 
		{
			get 
			{
				return itemTitle;
			}
		}

		private long id;

		public long ID 
		{
			get 
			{
				return id;
			}
		}

		public LendableItem ( Title inTitle, long inID ) 
		{
			itemTitle = inTitle;
			id = inID;
		}

		#region Overridden Methods

		public override string ToString()
		{
			return "Title : " + itemTitle.TitleName + " ID : " + ID;
		}

		public override bool Equals(object obj)
		{
			LendableItem test = obj as LendableItem;

			if ( test.ID != ID ) 
			{
				return false;
			}
			return true;
		}

		#endregion
	}

	public class TitleReservation 
	{
		private ClubMember reservationOwner;

		public ClubMember ReservationOwner
		{
			get 
			{
				return reservationOwner;
			}
		}

		private Title reservedTitle ;

		public Title ReservedTitle 
		{
			get 
			{
				return reservedTitle;
			}
		}

		public TitleReservation ( ClubMember inReservationOwner, Title inReservedTitle ) 
		{
			reservationOwner = inReservationOwner;
			reservedTitle = inReservedTitle;
		}
		#region Overridden Methods

		public override string ToString()
		{
			return "Title : " + reservedTitle.TitleName + " Reserved by : " + reservationOwner.MemberName ;
		}

		#endregion
	}
}
