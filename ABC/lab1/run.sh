#!/bin/bash

echo
echo -n 'Дата : '; date +%d-%m-%Y
echo -n 'Имя учетной записи: '; whoami
echo -n 'Доменное имя ПК: '; hostname
echo 'Процессор:'
echo -n -e ' * Модель - '; lscpu | grep "Model name" | cut -d: -f2 
echo -n ' * Архитектура - '; lscpu | grep "Architecture" | cut -d: -f2 
echo -n ' * Тактовая частота - '; lscpu | grep "CPU MHz" | cut -d: -f2 
echo -n ' * Количество ядер - '; lscpu | grep "Core(s) per socket"  | cut -d: -f2 
echo -n ' * Количество потоков на одно ядро - '; lscpu | grep "Thread(s) per core" | cut -d: -f2 
echo 'Оперативная память:'
echo -n -e ' * Всего - '; free -h | grep "Mem" | awk '{print $2}'
echo -n -e ' * Доступно - '; free -h | grep "Mem" | awk '{ print $4 }'
echo 'Жесткий диск:' 
echo -n -e ' * Всего - '; lsblk /dev/sda | grep "sda " | awk '{ print $4 }'
echo -n -e ' * Доступно - '; lsblk /dev/sda | grep "sda4" | awk '{ print $4 }'
echo -n -e ' * Смонтировано в корневую директорию / - '; df -h | grep '/$' | awk '{print $1}'
echo -n -e ' * SWAP Всего - '; free -h | grep "Swap" | awk '{ print $2 }'
echo -n -e ' * SWAP Доступно - '; free -h | grep "Swap" | awk '{ print $4 }'
echo 'Сетевые интерфейсы:'
echo -n -e ' * Количество сетевых интерфейсов - '; ip a |awk '/state/' | wc -l
echo "Имя              ipv4                  mac                 speed"
info=$(ifconfig)
names=$(echo "$info" | awk '$1~/[^:]*?:/ {print $1}')
temp=$(mktemp)
for NAME in $names; do
    NAME=${NAME/:/}
    intInfo=$(ifconfig $NAME)
    IP=$(echo "$intInfo" | sed -n 's|inet \([0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\).*$|\1|p')
    MAC=$(echo "$intInfo" | sed -n -E 's|ether ([[:alnum:]]{2}:[[:alnum:]]{2}:[[:alnum:]]{2}:[[:alnum:]]{2}:[[:alnum:]]{2}:[[:alnum:]]{2}).*$|\1|p')
    SPEED=$(sudo ethtool $NAME | grep "Speed:" | cut -d: -f2 )
    echo "$NAME, $IP, $MAC", $SPEED >> $temp
done
column -t -s, $temp
rm $temp
echo

