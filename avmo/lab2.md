# Лабораторная работа №2. Моделирование матричной игры 2x2
- Решите аналитически матричную игру 2x2, заданную платежной матрицей (найдите оптимальные стратегии игроков и цену игры)
- Напишите программу, моделирующую результат игры, разыграв 100 партий. Программа должна выводить:
-- Результаты моделирования в виде таблицы с заголовками
-- относительные чистоты использования чистых стратегий каждым игроком.
```
5. (9  17)
   (12 8 )
```
# Поиск нижней и верхней цены игры

9  17    9
12 8     8

12 17

b = 12, a = 8

player A
9p1 + 12p2 = v
17p1 + 8p2 = v
p1+p2 = 1


8p1 - 4p2 = 0
8p1=4p2
p1 = 1/2p2

p2 + 1/2p2  = 1
3/2p2 = 1
p2 = 2/3;
p1 = 1/3;
v=3+8 = 11

p = (1/3 ; 2/3)

player B

9q1 + 17q2 = v
12q1 + 8q2 = v
q1+q2 = 1

3q1 - 9q2 = 0
q1 = 3q2
q2 = 0.25
q1 = 0.75
v = 9+2 = 11

p = (1/3 ; 2/3) q = (3/4 ; 1/4); v = 11
