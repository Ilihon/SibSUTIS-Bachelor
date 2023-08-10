read_from_old_and_write_to_new(_):-
at_end_of_stream,!.
read_from_old_and_write_to_new(FR):-
read_line_to_codes(FR,L),
string_to_list(S,L),
split_string(S, " ", "", NL),
reverse(NL,R),
atomics_to_string(R, ' ', NS),
writeln(NS),
read_from_old_and_write_to_new(FR).

second:-
write("Write path to file = "),
read(Filename),
open(Filename,read,FR),
set_input(FR),
tell('D:/new.txt'),
read_from_old_and_write_to_new(FR),
told,
close(FR),
nl,
write("Check D:/new.txt").
