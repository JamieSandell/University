:-dynamic
	frame/3.

frame(band,_,[has(songs)]).

frame(electric, subclass_of(band), [instruments([guitar])]).
frame(blues, subclass_of(electric), [instruments([saxophone])]).
frame(chicago, subclass_of(blues), [popular(['Chicago'])]).
frame(muddy, instance_of(chicago), [songs(['All Night Long'])]).

frame(elmore, instance_of(chicago), [songs(['Dust My Broom'])]).


frame(delta, subclass_of(blues), [popular(['1920'])]).
frame(robert, instance_of(delta), [songs(['Sweet Homes Chicago'])]).

frame(punk, subclass_of(electric), [popular(['1970'])]).
frame(british, subclass_of(punk), [popular(['UK 1970'])]).
frame(theclash, instance_of(british), [songs(['London Calling'])]).

frame(new_york, subclass_of(punk), [popular(['USA 1970'])]).
frame(ramones, instance_of(punk), [songs(['I wanna be sedated'])]).

frame(acoustic, subclass_of(band), [instruments([guitar])]).
frame(rock, subclass_of(acoustic), [instruments([guitar, drums])]).
frame(soft, subclass_of(rock), [popular(['Everywhere'])]).
frame(nora, instance_of(soft), [songs(['Kill You For A Dollar'])]).
frame(ry, instance_of(soft), [songs(['Dark End Of The Street'])]).

frame(hard, subclass_of(rock), [popular(['Everywhere'])]).
frame(john, instance_of(hard), [songs(['Crocodile Rock'])]).
frame(richard, instance_of(hard), [songs(['Do You Love Me?'])]).

frame(folk, subclass_of(acoustic), [instruments([violin, fiddle, viola, melodeon, piano, tenorguitar])]).
frame(trad, subclass_of(folk), [popular(['Everywhere'])]).
frame(ewan, instance_of(trad), [songs(['Dirty Old Town'])]).
frame(eliza, instance_of(trad), [songs(['My Old Man'])]).

frame(commercial, subclass_of(folk), [popular(['Everywhere'])]).
frame(roger, instance_of(commercial), [songs(['Every woman'])]).

fadd(FrameName, Item, ItemValue):-
	frame(FrameName, Y, X), % Find the frame
	retract(frame(FrameName, Y, X)), % Delete the frame
	NewItem=..[Item,ItemValue], % extract the data
	append(X, [NewItem], NewList), % Append the old with the new
	assert(frame(FrameName, Y, NewList)), % Create the frame
	write(FrameName),write(' frame has been added to. The frame now is:'),nl,write(frame(FrameName, Y, NewList)). % write out to the user

fchange(FrameName, Type, ValueToChange):- % change this
	frame(FrameName, Inheritance, List), % Does the frame exist
	Target=..[Type, _], % extract the relevant data
	member(Target, List), % is our target part of the frame
	my_delete(Target, List, NewList), % delete it from the list
	NewValue=..[Type, ValueToChange], % extract data
	append(NewList, [NewValue], FinalList), % append it into the new list
	retract(frame(FrameName, Inheritance, List)), % remove the frame
	assert(frame(FrameName, Inheritance, FinalList)), % add the frame
	write('The frame '),write('"'),write(FrameName),write('"'),write(' has been changed. The frame is now:'),nl,write(frame(FrameName, Inheritance, FinalList)). %write out to the user

fchange(FrameName, Type, ValueToChange):- % If at this predicate then Type did not exist
	frame(FrameName, Inheritance, List), % Store the frame info
	write('The slot '),write('"'),write(Type),write('"'),write(' does not exist for the frame '),write('"'),write(FrameName),write('"'),write('. The frame is as follows:'),nl,
	write(frame(FrameName, Inheritance, List)).

fdelete(FrameName):-
	frame(FrameName, Y, X), % Find the frame by its name
	Y=..ValueToCheck, % extract the data into ValueToCheck
	member(instance_of, ValueToCheck), % if an instance/leaf delete
	retract(frame(FrameName, Y, X)), % delete the instance/leaf
	write('The frame '),write('"'),write(FrameName),write('"'),write(' has been deleted.').

fremove(FrameName, ToRemove):-
	frame(FrameName, Inheritance, List), % Does the frame exist
	Target=..[ToRemove, _], % Get the relevant info
	member(Target, List), % Is our target in the frame
	my_delete(Target, List, NewList), % Delete it from the list
	retract(frame(FrameName, Inheritance, List)), % remove the frame
	assert(frame(FrameName, Inheritance, NewList)), % add the new frame
	write(FrameName),write(' has had an item removed. The frame now is:'),nl,write(frame(FrameName, Inheritance, NewList)). % write out to the user

fremove(FrameName, ToRemove):- % If here then fremove failed
	frame(FrameName, Inheritance, List), % Get the frame info
	write('The slot '),write('),write(ToRemove),write('),write(' does not exist for the frame '),write(FrameName),write('. The frame is as follows:'),nl,
	write(frame(FrameName, Inheritance, List)).

fask(FrameName, Value):-
	frame(FrameName,_, X), % Does frame exist? Get the relevant frame info
	X=..List, % Exract X into list
	member(Value, List), % is the Value in that list?
	write( 'which '),write(Value).

fask(FrameName, Value):-
	frame(FrameName, instance_of(Type),_), % get's the name of the instance and then use the first fask on that
	write(FrameName),write(' instance_of '),write(Type),write(' '),
	fask(Type, Value).

fask(FrameName, Value):-
	frame(FrameName, subclass_of(Type),_), % get's the name of the subclass and then use the first fask on that
	write(FrameName),write(' subclass_of '),write(Type),write(' '),
	fask(Type, Value).

my_delete(_,[],[]). my_delete(Target,[Target|Rest],Rest).
my_delete(Target,[Head|Rest],[Head|List]):-
	my_delete(Target,Rest,List).