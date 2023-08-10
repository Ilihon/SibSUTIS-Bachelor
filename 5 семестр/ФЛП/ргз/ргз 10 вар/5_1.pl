% Автор:
% Дата: 17.11.2020

z2:-
 open('123.txt', read, T),
 set_input(T),
 walk(T, L, W),
 min(W, Min),
 list_make(L, W, L1, Min),
 close(T),
 (exists_file('out.txt'), delete_file('out.txt'), ! ; true),
 open('out.txt', write, OUT),
 set_output(OUT),
 out(OUT, L1),
 close(OUT),
 write(L), nl, write(W), nl, write(L1), nl.

walk(_, [], []):-
 at_end_of_stream,
 !.
 
walk(F, [H|T], [O|P]):-
 read_string(F, " \n", "-,.!", End, H),
 string_length(H, O),
 walk(F, T, P ).
 
min([], 10000).

min([H|T], Min) :-
 min(T, TMin),
 H < TMin,
 Min = H.
 
min([H|T], Min) :-
 min(T, TMin),
 H >= TMin,
 Min = TMin.
 
out(_, []):-
 !.
 
out(R, [H|T]):-
 writeln(H),
 out(R, T).
 
list_make([], [], [], _):-
 !.
 
list_make([O|P], [F|S], [O|T], Min):-
 list_make(P, S, T, Min),
 F == Min.
 
list_make([O|P], [F|S], T, Min):-
 list_make(P, S, T, Min),
 F =\= Min.