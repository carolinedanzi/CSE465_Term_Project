query(greatuncleaunt(b, c)).
query(greatuncleaunt(a, c)).
query(greatuncleaunt(b, b)).
query(greatuncleaunt(b, a)).
query(greatuncleaunt(c, e)).
query(greatuncleaunt(d, e)).

writeln(T) :- write(T), nl.

main :- consult(uncle),
	forall(query(Q), (Q->writeln(yes:Q) ; writeln(no:Q))),
	halt.
:- initialization(main).
