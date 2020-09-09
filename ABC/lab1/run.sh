#!/bin/bash

echo -n 'Дата : '; date +%d-%m-%Y
echo -n 'Имя учетной записи: '; whoami
echo -n 'Доменное имя ПК: '; hostname
echo 'Процессор:'
echo -n -e ' * Модель - '; lscpu | grep "Model name" | cut -d: -f2 
echo -n ' * Архитектура - '; lscpu | grep "Architecture" | cut -d: -f2 
echo -n ' * Архитектура - '; lscpu | grep "Architecture" | cut -d: -f2 
echo -n ' * Архитектура - '; lscpu | grep "Architecture" | cut -d: -f2 
echo -n ' * Архитектура - '; lscpu | grep "Architecture" | cut -d: -f2 
# infocmp
# df
# free
# lscpu
# ifconfig
# lshw
# cat /proc/cpuinfo
# ethtool
# cut
# grep
# sed
# awk
# head, tail
# lcpci
# lsblk
# pydf
