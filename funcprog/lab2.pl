split([], _, [], []):-!.
split([H|T], X, [H|LL1], LL2) :- H=<X, split(T, X, LL1, LL2),!.
split([H|T], X, LL1, [H|LL2]) :- H>X, split(T, X, LL1, LL2),!.

run:-
    split([1, 2, 3, 4, 5], 3, L1, L2),
    print(L1), nl, print(L2).
