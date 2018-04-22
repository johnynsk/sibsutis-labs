run:-
    retractall(product/3),
    ['./db.txt'],
    menu.

menu:-
    repeat, nl,
    write('Select menu item'),nl,
    write('\t1: Show stored products'),nl,
    write('\t2: Insert product item'),nl,
    write('\t3: Remove product item'),nl,
    write('\t4: Show all minimal cost for products'),nl,
    write('\t5: Halt'),nl,
    write('Your\'s choice #: '),
    read(X),
    X < 6,
    choice(X),
    X = 5,!.

choice(1):-show_all.
choice(2):-add.
choice(3):-remove.
choice(4):-show_minimal.
choice(5):-db_save,retractall(product/3).
add:-
    write('Adding new product:'),nl,nl,
    repeat,
    write('Product name: '),
    read(Name),
    write('Quantity: '),
    read(Quantity),
    write('Price: '),
    read(Price),
    assertz(product(Name, Quantity, Price)),
    add_another,!.

db_save:-
    tell('db.txt'),
    listing(product),
    told,
    write('database to db.txt saved').

remove:-
    write('Removing product:'),nl,
    repeat,
    write('Enter product name: '),
    read(Name),
    (retract(product(Name,_,_)) -> (
        write('Product removed successfuly'),nl,nl,
        remove_another);
        remove_another
    ),!.

answer(_):-fail.
answer(y):-fail.
answer(n).


remove_another:- write('Should we continue removinng items? (y/n)'), read(A), answer(A).
add_another:- write('Add another product? (y/n) '), read(A), answer(A).

min(X,Y,X):-X=<Y,!.
min(_,Y,Y).
minl([X],X):-!.
minl([X|T],R):-minl(T,R1),min(X,R1,R).
del(X,[X|T],T):-!.
del(X,[Y|T],[Y|L]):-del(X,T,L).
sort_([],[]):-!.
sort_(L,[El|R2]):-minl(L,El),del(El,L,R1),sort_(R1,R2).
sorted_min([H|_], H).

show_all:-
    nl,write('Stored products: '),nl,nl,
    product(Name,Quantity,Price),
    write('Product name: '), write(Name), write(', '), write(Quantity), write('pcs costs $'), write(Price),nl.

find_minimum(MinPrice):-
    findall(Price, product(_Name, _Quantity, Price), AllPrices),
    print(AllPrices),
    sort_(AllPrices, SortedPrices),
    sorted_min(SortedPrices, MinPrice).

show_minimal:-
    find_minimum(MinPrice),
    product(Name, Quantity, Price),
    Price == MinPrice,
    write('Product name: '), write(Name), write(', '), write(Quantity), write('pcs costs $'), write(MinPrice), nl.

