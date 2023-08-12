import requests
from bs4 import BeautifulSoup


def Search_Crypt(search, Tab):
    try:
        i = Tab.index(search)
        return i
    except:
        print("Криптовалюта с этим названием не найдена")
        return -1

def main():
    page = requests.get('https://coinmarketcap.com/ru/all/views/all/')
    soup = BeautifulSoup(page.text, 'html.parser')
    Tbody = soup.find('tbody')
    Names = [element.text for element in Tbody.find_all(class_='cmc-table__column-name--name cmc-link')]
    Market_cap = [element.text for element in Tbody.find_all(class_='ggzdxp-0 hWIeFI')]
    Price = [element.text for element in Tbody.find_all(class_='cmc-table__cell--sort-by__price')]
    Tab = []
    for i in range(len(Names)):
        Tab.append({'Name': Names[i], 'Market_cap': Market_cap[i], 'Price': Price[i]})
    f = open('Crypt.txt', 'w', encoding="utf-8")
    for i in range(len(Tab)):
        f.write('{:<33}'.format(Tab[i]['Name'])+'{:<20}'.format(Tab[i]['Market_cap'])+Tab[i]['Price']+'\n')
    f.close()
    print("Найдено", len(Tab), "криптовалют\n")
    while True:
        print("Введите название искомой криптовалюты: ")
        search = input()
        if len(search) != search.count(' '):
            search = search.strip()
        Found_index = Search_Crypt(search, Names)
        if Found_index != -1:
            print('{:<4}'.format(Found_index + 1), '{:<33}'.format(Tab[Found_index]['Name']),
                  '{:<20}'.format(Tab[Found_index]['Market_cap']), Tab[Found_index]['Price'])
        print("Продолжить? (y/n)")
        contin = input()
        if contin != "y" and contin != "yes":
            break

    print("Вывести весь список? (y/n)")
    contin = input()
    if contin == "y" or contin == "yes":
        for i in range(len(Tab)):
            print('{:<4}'.format(i + 1), '{:<33}'.format(Tab[i]['Name']), '{:<20}'.format(Tab[i]['Market_cap']),
                  Tab[i]['Price'])
        
if __name__ == '__main__':
    main()
    input("Нажмите что-нибудь чтобы выйти")