% Автор: Я
% Дата: 02.12.2020

%------1-------
member(H,[H|_]).
member(X,[_|Tail]):-member(X,Tail).

pool([],B,B).
pool([H|Tail],B,NewTail):-member(H, B),!,pool(Tail,B,NewTail).
pool([H|Tail],B,[H|NewTail]):-pool(Tail,B,NewTail).
 
remove_duplicates([], []):-!.
remove_duplicates([H|Tail], NewTail):-member(H, Tail),!, remove_duplicates(Tail, NewTail).
remove_duplicates([H|Tail], [H|NewTail]):-remove_duplicates(Tail, NewTail).

rgr1():-
  read(List1),
  read(List2),
  remove_duplicates(List1,List1r),
  remove_duplicates(List2,List2r),
  pool(List1r,List2r,List),
  write(List).
  

%------2-------
check_exist(Fname):-exists_file(Fname),!.
check_exist(_):-writeln('File not found!'),fail.

rgr2:-
  writeln('Введите имя входного файла:'),
  read(Fname1),
  check_exist(Fname1),
  writeln('Введите имя выходного файла:'),
  read(Fname2),
  open(Fname1,read,F1),
  open(Fname2,write,F2),
  repeat,
    read_line_to_codes(F1,C),
    atom_chars(F,C),
    %writeln(F),
    atomic_list_concat(L,' ',F),
    writestr(F2,L),
    at_end_of_stream(F1),
  close(F1),
  close(F2).

empty([]).
empty(_):-fail.

writeword(F2,W):-
  sub_string(W,Before,_,0,'ing'),
  sub_string(W,0,Before,_,Wed),
  write(F2,Wed),
  write(F2,'ed').
writeword(F2,W):-
  not(sub_string(W,_,_,0,'ing')),
  write(F2,W).

writestr(F2,[H|T]):-
  writeword(F2,H),
  not(empty(T)),
  writeword(F2, " "),
  writestr(F2,T).
writestr(F2,[_|T]):-
  empty(T),
  nl(F2).