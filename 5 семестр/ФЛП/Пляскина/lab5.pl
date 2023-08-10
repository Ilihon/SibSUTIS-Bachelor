% �����: �
% ����: 18.11.2020
% -----1------
task1:-write('print X:'),read(X),write('print Y:'),read(Y),task1(X,Y).
task1(X, Y):-(Y >= X ->(((Y mod 2) =:= 1) -> write(Y); write(' ')),
Z is (Y - 1),task1(X, Z); true).

% -----2------
task2:-repeat,writeln('Enter number'),read(N),fib(N),!.
f(0,1):-!.
f(1,1):-!.
f(I,F):-I1 is I-1,I2 is I-2,f(I1,F1),f(I2,F2),F is F1+F2.
fib(N):-N<0,!.
fib(N):-f(N, F),writeln(F),fail.

% -----3------
task3:-writeln('Enter numbers'),read(A),read(B),
   writeln('Enter list'),read(L),
   compare_AB(A,B,L,L1,L2,L3),writeln(L1),writeln(L2),writeln(L3).
compare_AB(A,B,L,L1,L2,L3):-(A<B ->split_1(A,B,L,L1,L2,L3); split_1(B,A,L,L1,L2,L3)).
split_1(A,B,[H|T],[H|T1],L2,L3):-(H<A ->split_1(A,B,T,T1,L2,L3)).
split_1(A,B,[H|T],L1,L2,[H|T3]):-(H>B ->split_1(A,B,T,L1,L2,T3)).
split_1(A,B,[H|T],L1,[H|T2],L3):-split_1(A,B,T,L1,T2,L3).
split_1(_,_,[],[],[],[]).


% -----4------
move_max_to_end([], []):-!.
move_max_to_end([Head], [Head]):-!.
move_max_to_end([First, Second|Tail],
    [Second|ListWithMaxEnd]):-First > Second, !,
    move_max_to_end([First|Tail], ListWithMaxEnd).
move_max_to_end([First, Second|Tail],
    [First|ListWithMaxEnd]):- move_max_to_end([Second|Tail], ListWithMaxEnd).

sorting(SortedList, SortedList):- move_max_to_end(SortedList, DoubleSortedList),
    SortedList = DoubleSortedList, !.
sorting(List, SortedList):- move_max_to_end(List, SortedPart),
    sorting(SortedPart, SortedList).

task4:-write("������:"), nl, read(ListA),
   % ListA = [0,3,5,7,1,5,3,0,3,3,5,7,0,5,0],nl,
    sorting(ListA, Y),task4(Y, Z), write(Z).
    
task4([], []).
task4([H|T], Res):-task4([H|T], _, Res, _).

task4([], 0, [], 0).
task4([H], 1, [H], 1).
task4([H, H1|T], Count, Res, Max):-task4([H1|T], Count1, Res1, Max1),
    Count2 is Count1 + 1,
    ((H =:= H1)->
         (Count = Count2, ((Count2 > Max1)->
           Max = Count2,Res = [H];
          (Max = Max1,((Count2 =:= Max1)->append([H], Res1, Res);Res = Res1)))
          );
    Count = 1,Max = Max1,Res = Res1).