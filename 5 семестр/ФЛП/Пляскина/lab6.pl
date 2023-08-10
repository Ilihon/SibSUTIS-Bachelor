%Написать предикат, который разбивает числовой список по двум числам,
% вводимым с клавиатуры на три списка: меньше меньшего введенного% числа,
% от меньшего введенного числа до большего введенного числа, больше
% большего введенного числа. Список и два числа вводятся с клавиатуры в
% процессе работы предиката.
%Например: [3,7,1,-3,5,8,0,9,2], 8, 3 –> [1,-3,0,2], [3,7,5,8], [9].
one:-
    write('Список:'), nl,
    read(ListA),
    %ListA = [3,7,1,-3,5,8,0,9,2],nl,
    write('Первое число:'), nl,
    read(N1),
    write('Second number:'), nl,
    read(N2),
    one(ListA, T1, T2, T3, N1, N2),
    write(T1),
    write(T2),
    write(T3).

one([], [], [], [], _, _):-!.

one(ListA, T1, T2, T3, S1, S2):-
    S1 > S2 ->
    !,
    one(ListA, T1, T2, T3, S2, S1).

one([Hs|Ts], T1, T2, T3, S1, S2):-
    (Hs > S2)->
    one(Ts, T1, T2, T3d, S1, S2),
    append([Hs], T3d, T3);
    (Hs >= S1)->
    one(Ts, T1, T2d, T3, S1, S2),
    append([Hs], T2d, T2);
    (Hs < S1)->
    one(Ts, T1d, T2, T3, S1, S2),
    append([Hs], T1d, T1).


% Написать предикат, который формирует список из номеров максимальных
% элементов числового списка. Список вводится с клавиатуры в процессе
% работы предиката. Встроенный предикат поиска максимума не использовать!
%Например: [3,5,4,2,5,5,0] –> [2,5,6].
max([X], X).
max([X|T], X):-
    max(T, M),
    X > M,
    !.
max([_|T], X):-
    max(T, X).

two:-
    write("Список:"), nl,
    read(ListA),
    %ListA =  [3,5,4,2,5,5,0],
    max(ListA, Y),
    two(ListA, Y, -1, Z),
    write(Z).

two([],_,_,[]):-!.
two([H|T], Max, Count, Tr):-
    Count1 is Count + 1,
    ((H =:= Max) ->
    two(T, Max, Count1, Tr1),
    append([Count1], Tr1, Tr);
    two(T, Max, Count1, Tr)).


% Написать предикат, который формирует список из наиболее часто
% встречающихся элементов списка. Список вводится с клавиатуры в процессе
% работы предиката. Встроенные предикаты поиска максимума и сортировки не
% использовть!
%Например: [0,3,5,7,1,5,3,0,3,3,5,7,0,5,0] –> [0,3,5].

move_max_to_end([], []):-!.
move_max_to_end([Head], [Head]):-!.
move_max_to_end([First, Second|Tail], [Second|ListWithMaxEnd]):-
    First > Second, !,
    move_max_to_end([First|Tail], ListWithMaxEnd).
move_max_to_end([First, Second|Tail], [First|ListWithMaxEnd]):-
    move_max_to_end([Second|Tail], ListWithMaxEnd).

sorting(SortedList, SortedList):-
    move_max_to_end(SortedList, DoubleSortedList),
    SortedList = DoubleSortedList, !.
sorting(List, SortedList):-
    move_max_to_end(List, SortedPart),
    sorting(SortedPart, SortedList).

three:-
    write("Список:"), nl,
    read(ListA),
   % ListA = [0,3,5,7,1,5,3,0,3,3,5,7,0,5,0],nl,
    sorting(ListA, Y),
    three(Y, Z),
    write(Z).
three([], []).
three([H|T], Res):-
    three([H|T], _, Res, _).

three([], 0, [], 0).
three([H], 1, [H], 1).
three([H, H1|T], Count, Res, Max):-
    three([H1|T], Count1, Res1, Max1),
    Count2 is Count1 + 1,
    ((H =:= H1)->
         (Count = Count2,
         ((Count2 > Max1)->
          Max = Count2,
          Res = [H];
          (Max = Max1,
          ((Count2 =:= Max1)->
              append([H], Res1, Res);
          Res = Res1
          ))));
    Count = 1,
    Max = Max1,
    Res = Res1).

