from dataclasses import dataclass
from typing import Dict, List
from tkinter import *
from tkinter import filedialog
from os import path
from functools import partial
from colorama import Fore, init
import json

nomachine = 0;
window = Tk()
txt = Entry(window, width=60)
text = Text(master=window, width=60, height=10)


@dataclass
class Machine:
    Q: List[str]
    V: List[str]
    Rules: List[List[str]]
    Start_state: str
    Current_state: str
    Start_stack: str
    Stack: str
    Transform_stack: str
    End: List[str]


def machine_input(filename):
    try:
        with open(filename, "r") as json_file:
            data = json.load(json_file)
    except FileNotFoundError:
        print(Fore.RED + "Файл с данными не найден.")
        exit(-1)
    states = data["states"]
    alphabet = data["alphabet"]
    in_stack = data["in_stack"]
    in_transform = data["in_transform"]
    rules = data["rules"]
    start = data["start"]
    stack = data["start_stack"]
    end = data["end"]
    lbl_machine = Label(window, text=f"P({states}, {alphabet}, {in_stack}, {in_transform}, δ, {start}, {stack}, {end})",
                        font=("Arial", 15), padx=5, pady=10)
    lbl_machine.grid(row=1, column=0, sticky="w")
    print(f"P({states}, {alphabet}, {in_stack}, {in_transform}, δ, {start}, {stack}, {end})")
    for i in rules:
        if i[1] == "EPS":
            i[1] = "ε";
        if i[4] == "EPS":
            i[4] = "ε";
        if i[5] == "EPS":
            i[5] = "ε";
        print(f"({i[0]}, {i[1]}, {i[2]}) -> ({i[3]}, {i[4]}, {i[5]})")
    machine = Machine(states, alphabet, rules, start, start, stack, stack, "", end)
    return machine


# Отрисовывает таблицу переходов
def generate_func_tab(machine, frame):
    lbl_sigma = Label(frame, text=f"δ", font=("Arial", 15), padx=-15, pady=5)
    lbl_sigma.grid(row=0, column=0)
    # for i in range(len(machine.V)):
    #     lbl_alphabet = Label(frame, text=f"'{list(machine.V)[i]}'", font=("Arial", 15), padx=5, pady=5)
    #     lbl_alphabet.grid(row=0, column=1 + i)
    for i in range(len(machine.Rules)):
        rule = machine.Rules[i]
        # print(list(machine.Func)[0])
        lbl_current = Label(frame, text=f"({rule[0]}, {rule[1]}, {rule[2]})", font=("Arial", 15), padx=5, pady=5)
        lbl_current.grid(row=1 + i, column=0)
        lbl_arrow = Label(frame, text=f"→", font=("Arial", 15), padx=5, pady=5)
        lbl_arrow.grid(row=1 + i, column=1)
        lbl_next = Label(frame, text=f"({rule[3]}, {rule[4]}, {rule[5]})", font=("Arial", 15), padx=5, pady=5)
        lbl_next.grid(row=1 + i, column=2)


def clicked():
    file = filedialog.askopenfilename(filetypes=[("Json Files", "*.json"), ("All Files", "*.*")],
                                      initialdir=path.dirname(__file__))
    if not file:
        return
    result = machine_input(file)
    frame = Frame(master=window, padx=10, pady=15)
    generate_func_tab(result, frame)
    frame.grid(row=2, column=0, sticky="w")
    lbl_check_word = Label(window, text=f" Введите цепочку для проверки: ", font=("Arial", 15), padx=5, pady=10)
    lbl_check_word.grid(row=3, column=0, sticky="w")
    txt.grid(row=4, column=0)
    btn_check_word = Button(window, text="Проверить", command=partial(check_button, result), padx=10, pady=10)
    btn_check_word.grid(row=4, column=1, sticky="e")

    text.grid(row=5, column=0, columnspan=2, sticky="w", padx=10)
    scroll = Scrollbar(command=text.yview)
    scroll.grid(row=5, column=1, sticky="n"+"s"+"w")
    text.config(yscrollcommand=scroll.set)


def check_button(machine):
    chain = txt.get()
    if chain == 'quit':
        return 0
    machine.Current_state = machine.Start_state
    machine.Stack = machine.Start_stack
    machine.Transform_stack = ""
    if all([c in machine.V for c in chain]):
        print(Fore.GREEN + "Цепочка состоит только из символов алфавита, начинаю проверку..." + Fore.RESET)
        check_word(chain, machine)
    else:
        print(Fore.RED + "\nОшибка. Слово состоит из символов, которых нет в алфавите.\n" + Fore.RESET)


def check_word(chain, machine):
    # print("Stack:", machine.Stack, "\n")
    text.insert(END, f"Stack: {machine.Stack}\n")
    step = 1
    for i in chain:
        # print(Fore.CYAN + "Step" + Fore.RESET, step)
        text.insert(END, f"Step {step}\n")
        rule_skip = 0
        # print("Chain:", i)
        # print("Current stack:", machine.Stack)
        text.insert(END, f"Chain {i}\n")
        text.insert(END, f"Current stack: {machine.Stack}\n")
        text.insert(END, f"Current transform: {machine.Transform_stack}\n")
        for j in machine.Rules:
            # print(machine.Current_state, j[0])
            if machine.Current_state != j[0]:
                rule_skip += 1
                continue
            # print(i, j[1])
            if i != j[1]:
                rule_skip += 1
                continue
            # print(machine.Stack[0], j[2])
            if machine.Stack[0] != j[2]:
                rule_skip += 1
                continue

            # print(f"Rule: ({j[0]}, {j[1]}, {j[2]}) -> ({j[3]}, {j[4]}, {j[5]})\n")
            text.insert(END, f"Rule: ({j[0]}, {j[1]}, {j[2]}) -> ({j[3]}, {j[4]}, {j[5]})\n\n")
            machine.Current_state = j[3]
            if j[4] != "ε":
                machine.Stack = j[4] + machine.Stack[1:]
            elif j[4] == "ε":
                machine.Stack = machine.Stack[1:]

            if j[5] != "ε":
                machine.Transform_stack = machine.Transform_stack + j[5]
            break
        step += 1
        if rule_skip == len(machine.Rules):
            # print(Fore.RED + "Ошибка. Отсутсвует переход для данного состояния.\n" + Fore.RESET)
            text.insert(END, f"Ошибка. Отсутсвует переход для данного состояния.\n\n")
            return
    while TRUE:
        if len(machine.Stack) == 0 and machine.Current_state in machine.End:
            # print(Fore.GREEN + "Цепочка проходит заданный МП-преобразователь.\n" + Fore.RESET
            text.insert(END, f"Цепочка проходит заданный МП-преобразователь.\n"
                             f"Полученный перевод: {machine.Transform_stack}\n\n")
            return
        # print(Fore.CYAN + "Step" + Fore.RESET, step)
        text.insert(END, f"Step {step}\n")
        rule_skip = 0
        # print("Chain: ε")
        # print("Current stack:", machine.Stack)
        text.insert(END, f"Chain: ε\n")
        text.insert(END, f"Current stack: {machine.Stack}\n")
        text.insert(END, f"Current transform: {machine.Transform_stack}\n")
        for j in machine.Rules:
            if machine.Current_state != j[0]:
                rule_skip += 1
                continue
            if "ε" != j[1]:
                rule_skip += 1
                continue
            if machine.Stack[0] != j[2]:
                rule_skip += 1
                continue

            # print(f"Rule: ({j[0]}, {j[1]}, {j[2]}) -> ({j[3]}, {j[4]}, {j[5]})\n")
            text.insert(END, f"Rule: ({j[0]}, {j[1]}, {j[2]}) -> ({j[3]}, {j[4]}, {j[5]})\n\n")
            machine.Current_state = j[3]
            if j[4] == "ε":
                machine.Stack = machine.Stack[1:]
            if j[5] != "ε":
                machine.Transform_stack = machine.Transform_stack + j[5]
            break
        step += 1
        if rule_skip == len(machine.Rules):
            # print(Fore.RED + "Ошибка. Отсутсвует переход для данного состояния.\n" + Fore.RESET)
            text.insert(END, f"Ошибка. Отсутсвует переход для данного состояния.\n\n")
            return


# ζ δ ε
if __name__ == '__main__':
    ls = list()
    ls.append("Z")
    ls = ls[1:]
    # window.columnconfigure(1, minsize=400, weight=1)
    # window.rowconfigure(0, minsize=250, weight=1)
    window.title("Добро пожаловать на сервер ТЯПофриния")
    # window.geometry('400x250')
    lbl = Label(window, text="ДМПА:", font=("Arial Bold", 20))
    lbl.grid(row=0, column=0, sticky="nw")
    # lbl.place(x=0, y=0)
    btn = Button(window, text="Загрузить ДМПА!", command=clicked, padx=10, pady=10)
    btn.grid(row=0, column=1, sticky="e")
    # btn.place(x=290, y=220)
    window.mainloop()
