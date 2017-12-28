#!/usr/bin/env python3
'''
Рисование фигур из символов на текстовом экране
'''

def init(width, height, paper="."):
    """Создаёт пустой экран (список строк) размером width×height,
    в качестве пустых элементов использовать строку paper.
    Возвращает экран.
    """
    return([paper*width for i in range(height)])

def str(screen):
    """Преобразует экран в строку"""
    sep = "+"+"-"*len(screen[0])+"+"
    return(sep+"\n"+"\n".join("|"+s+"|" for s in screen)+"\n"+sep)

def dot(screen, x, y, ink="*"):
    """Ставит точку (первый символ строки ink) нв экран screen по координатам x:y
    Выход за границы экрана обрезается по модулю
    """
    x = x % len(screen[0])
    y = y % len(screen)
    screen[y] = screen[y][:x]+ink[0]+screen[y][x+1:]

def get(screen, x, y):
    """Возвращает символ экрана screen по координатам x,y
    Выход за границы экрана обрезается по модулю
    """
    x = x % len(screen[0])
    y = y % len(screen)
    return screen[y][x]

def hline(screen, x, y, x1, ink="*"):
    """Проводит горизонтальный отрезок из символов ink на экране screen
    начиная с точки x:y и заканчивая точкой x1:y (координаты неотрицательные)"""
    for x0 in range(x,x1+1) if x<x1 else range(x1,x+1):
        dot(screen,x0,y,ink)

def vline(screen, x, y, y1, ink="*"):
    """Проводит вертикальный отрезок из символов ink на экране screen
    начиная с точки x:y и заканчивая точкой x:y1 (координаты неотрицательные)"""
    for y0 in range(y,y1+1) if y<y1 else range(y1,y+1):
        dot(screen,x,y0,ink)

def line(screen, x0, y0, x1, y1, ink="*"):
    """Проводит произвольный отрезок из символов ink на экране screen 
    начиная с точки x0:y0 и заканчивая точкой x0:y1 (координаты неотрицательные)"""
    x, y = x0, y0
    if x0 == x1:
        return vline(screen, x, y0, y1, ink)
    if y0 == y1:
        return hline(screen, x, y0, x1, ink)
    dx, dy = -1 if x1<x0 else 1, -1 if y1<y0 else 1
    dot(screen, x, y, ink)
    n = max(abs(x0-x1),abs(y0-y1))
    for i in range(n):
        x, y = x0+(x1-x0)*i//n, y0+(y1-y0)*i//n
        dot(screen, x, y, ink)

def fill(screen, x, y, ink="#", paper="."):
    """Закрашивает связную область экрана screen из символов paper
    символами ink
    """
    turn = (0,1), (1,0), (0,-1), (-1,0)
    todo = [(x,y)]
    while todo:
        x,y = todo.pop()
        dot(screen,x,y,ink)
        for dx, dy in turn:
            if get(screen,x+dx,y+dy)==paper:
                todo.append((x+dx,y+dy))

if __name__ == "__main__":
    scr = init(60,20)
    print(str(scr))
    vline(scr,4,2,18,"+")
    print(str(scr))
    hline(scr,2,4,55,"@")
    print(str(scr))
    line(scr, 0,12,57,38)
    print(str(scr))
    line(scr, 10,19,58,7,"%")
    print(str(scr))
    fill(scr, 20, 10)
    print(str(scr))
