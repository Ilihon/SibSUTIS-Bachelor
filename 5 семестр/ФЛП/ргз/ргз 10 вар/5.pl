% Автор:
% Дата: 09.11.2020

z1:-
 write('[List]. X.'), nl,
 read(List), read(X),
 add_element_in_list(List, X, List1, List2),
 apend(List1, List2, List3, X),
 writeln(List3).

apend([], [], List3, X):-
 !,
 append([], [X], List3).

apend(List1, [], List3, X):-
 !,
 append(List1, [X], List3).
 
apend(List1, List2, List3, X):-
 !,
 append(List1, List2, List3).

add_element_in_list([], _X, [], []).

add_element_in_list([H|T], X, [H|List1], List2):-
 H < X,
 !,
 add_element_in_list(T, X, List1, List2).

add_element_in_list([H|T], X, [X|List1], [H|T]):-
 add_element_in_list([], X, List1, List2).