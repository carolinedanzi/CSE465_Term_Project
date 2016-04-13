% Caroline Danzi
% Dr. Zmuda
% CSE 465
% Great Uncle Problem

% male1 and female1 are married
married(male1, female1).
married(female1, male1).
% male1 is the father of male2
father(male1, male2).
% female1 is the mother to male2
mother(female1, male2).
father(male1, male3).
mother(female1, male3).
father(male1, female2).
mother(female1, female2).

married(male2, female3).
married(female3, male2).
father(male2, male4).
mother(female3, male4).
father(male2, male8).
mother(female3, male8).


married(male3, female4).
married(female4, male3).
father(male3, female5).
mother(female4, female5).
father(male3, male5).
mother(female4, male5).

married(male6, female2).
married(female2, male6).

married(male4, female6).
married(female6, male4).
father(male4, female9).
mother(female6, female9).
father(male4, male7).
mother(female6, male7).


married(male8, female7).
married(female7, male8).
father(male8, female8).
mother(female7, female8).


parent(X, Y) :- father(X, Y).
parent(X, Y) :- mother(X, Y).

sibling(X, Y) :- parent(Z, X), parent(Z, Y), not(X = Y).

% A person is your uncle if your parent's parent is their parent
uncleaunt(X, Y) :- parent(Z, Y), sibling(X, Z).
uncleaunt(X, Y) :- parent(Z, Y), sibling(W, Z), married(X, W).

% A person is your great uncle or aunt if they are the uncle (or aunt) to your parent
greatuncleaunt(X, Y) :- parent(Z, Y), uncleaunt(X, Z).