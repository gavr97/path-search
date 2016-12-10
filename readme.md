﻿# Tема проекта: Автоматическое планирование траектории
## Выполняет: Гавриков Алексей Владимирович, группа 152


## Актуальность решаемой задачи

Планирование - одна из основополагающих способностей любого интеллектуального агента. Они встречаются повсеместно и в разных формах. Например, робот, который должен самостоятельно обходить препятствия, персонаж компьютерной игры, беспилотник или даже просто механическая рука, задача которой схватить какой-либо предмет. Очевидно, люди не могут управлять всеми ими от пульта. Людей и времени не хватит. Поэтому создание эффективных алгоритмов планирования очень важно в век современных технологий.
Автоматическое планирование – широкое понятие, которое включает в себя множество частных задач. Одна из них, рассматриваемая в этом проекте, - планирование траектории.  В этом случае задача интеллектуального агента, находясь в начальном состоянии, - достичь целевое состояние, обходя препятствия, располагая информацией о среде, в которой он находится. И согласно этой информации агент должен спланировать оптимальную траекторию. Часто алгоритмически можно точно найти наилучшее решение, но ценой этому может стать долгий поиск  и объем затрачиваемых ресурсов.  Естественно, хочется, чтобы интеллектуальный агент действовал оптимально, быстро, используя как можно меньший объем ресурсов.  Таким образом, задача современных исследователей в этой области состоит в разработке и усовершенствовании алгоритмов, которые сочетают в себе три свойства: оптимальность, эффективность по времени, а также эффективность по памяти.



## Обзор существующих решений

Часто используемое представлениее экземпляра задачи, отражающее особенности среды, в которой действует агент, -  метрический топологический граф. Неформально, это матрица из 0 и 1, являющаяся картой, где 0 и 1 означает, что ячейка проходима и нет соответсвенно.
Такое представлнение среды, используется в этом проекте. На таких графах есть разные алгоритмы планирования траектории. Одним из прародителем очень важнго класса ялвяется такой базовый алгоритм как A\*.
Главная его парадигма – искать путь по наиболее перспективным направлениям. Понятие перспективности вершины графа определяется эвристикой, которую закладывает программист. Суть алгоритма А\*: последовательно рассматриваются вершины графа по определенному порядку, где в приоритете те вершины, до которых расстояние от вершины-старта(пути найденного до настоящего момента) в сумме с предположительным расстоянием от этой вершины до финиша наименьшее.

Есть немало усовершенствований A\*. В этом проекте будут рассматриваться, например, JPS и Theta. Особенность JPS по сравнению с классическим A\* в том, что при поиске делаются не единичные шаги, а “прыжжки” до видимых вершин по определенному правилу.


## Используемые технологические решения
1)Язык программирования С++, т.к. он эффективен и удобен для ООП.
2)Среда разработки Qt creator, т.к. в ней удобно программировать на C++, а также   она свободно распространяется.
3)Формат входных данных XML, т.к. он хорошо подходит для хранения карт, к тому же разумно иметь определенный стандарт входных данных.
4)Библиотека TinyXML для обработки XML-файлов.

## План работы

1)КТ2: Функционал A\* реализован в программном коде, проект компилируется и корректно работает на корректных входных данных.

2)КТ3: Функционал A\*, JPS и Theta\* реализован в программном коде с использованием грамотной иерархии классов (наследование, не дублирование основного функционала и пр.). Проект компилируется и корректно работает на корректных входных данных, а на некорректных сообщает пользователю об ошибке.


