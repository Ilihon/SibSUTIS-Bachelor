%1.14. ��������� � ������� ������ ������ ������� ������.
one:-
    write('������� ������: '),
    read(List), nl,
    one(List,Res),
    write('���������: '),writeln(Res).
one([X,Y,Z|T],[X,Y,ZZ|TT]):-
    !,
    ZZ is Z*Z,
    one(T, TT).
one(X,X).


% 2.14. �������� ��� ����� � ��������� �����, �������� ������� ���� � �����. ����������� ����� ����

two(_):-
    at_end_of_stream,!.
two(File):-
    read_line_to_codes(File,Line),
    reverse(Line,Enil),
    string_to_list(Str,Enil),
    split_string(Str, " ", "", List),
    reverse(List,Tsil),
    atomics_to_string(Tsil, ' ', Newstring),
    writeln(Newstring),
    two(File).

two:-
    write("������� ���� � �����: "),
    read(Name),
    open(Name,read,File),
    set_input(File),
    tell('D:/otvet.txt'),
    two(File),
    told,
    close(File),
    nl,
    write("Check D:/otvet.txt").

