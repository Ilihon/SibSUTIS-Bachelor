#!/bin/bash
echo "Дата: $(date +"%d-%m-%Y")"
echo "Имя пользователя $(whoami)"
echo "Доменнон имя ПК: $(hostname)"
echo "Процессор:"
echo "     Модель -           $(lscpu | sed -n 's!Имя модели: *\(.*\) ! \1 !p')"
echo "     Архитектура -      $(lscpu | sed -n 's!Архитектура: *\(.*\) ! \1 !p')"
echo "     Тактовая частота - $(lscpu | sed -n 's!CPU МГц: *\(.*\) ! \1 !p')"
echo "     Количество ядер - $(lscpu | sed -n 's!^CPU(s): *\(.*\) ! \1 !p')"
echo "     Количество потоков на одно ядро - $(lscpu | sed -n 's!Потоков на ядро: *\(.*\) ! \1 !p')"
echo "Оперативная память:"
echo "     Всего - $(free -h | awk '/^Память:/ {print $2}')"
echo "     Доступно - $(free -h | sed -n 's!Память *\(.*\) !!p')"
echo "Жёсткий диск:"
echo "     Всего - $(df -h | grep '/$' | awk '{print $2}')"
echo "     Доступно - $(df -h | grep '/$' | awk '{print $4}')"
echo "     Смонтировано в корневую директорию / - $(df -h | grep '/$' | awk '{print $1}')"
echo "     SWAP всего - $(free -h | awk '/^Подкачка:/ {print $2}')"
echo "     SWAP доступно - $(free -h | awk '/^Подкачка:/ {print $4}')"
echo "Сетевые интерфейсы:"
echo "     Количество сетевых интерфейсов - $(ifconfig |awk '/flags/ {print $1}' | wc -l)"
echo "| № |  Имя сетевого интерфейса | MAC адрес | IP адрес |"
NAMES=$(echo "$(ifconfig)" | awk '/flags/ {print $1}')
NUM=$((0))
for NAME in $NAMES
do
  NUM=$(($NUM+1))
  NAME=${NAME/:/}
  MAC=$(ifconfig $NAME | grep ether | gawk '{print $2}')
  IP=$(ifconfig $NAME | awk '/inet / {print $2}')
  if [ -z $MAC ]
  then
  echo -e "  $NUM \t $NAME \t\t\t\t\t $IP"
  else
  echo -e "  $NUM \t $NAME \t $MAC \t $IP"
fi
done
speed-test
