from random import randint

class Color():
    def __init__(self, r, g, b):
        r = min(255, r)
        g = min(255, g)
        b = min(255, b)
        self.r = r
        self.g = g
        self.b = b
    
    def __str__(self):
        r = hex(min(255, self.r))[2:]
        g = hex(min(255, self.g))[2:]
        b = hex(min(255, self.b))[2:]
        return '#{:0>2}{:0>2}{:0>2}'.format(r, g, b)
    
    def __add__(self, other):
        r = self.r + other.r
        g = self.g + other.g
        b = self.b + other.b
        return Color(r, g, b)
    
    def __sub__(self, other):
        return self + (other * -1)
    
    def __mul__(self, coef):
        r = int(self.r * coef)
        g = int(self.g * coef)
        b = int(self.b * coef)
        return Color(r, g, b)
    
    def __eq__(self, other):
        return self.r == other.r and self.g == other.g and self.b == other.b
    
    def to_rgb(self):
        return [self.r, self.g, self.b]

    def mean(self, other):
        return mean_color(self, other)
    
    def cp(self):
        return Color(self.r, self.g, self.b)


def color_from_rgb(rgb):
    return Color(rgb[0], rgb[1], rgb[2])


def random_color():
    r = randint(0, 255)
    g = randint(0, 255)
    b = randint(0, 255)
    return Color(r, g, b)


def color_from_limit(first, second):
    rgb_first = first.to_rgb()
    rgb_second = second.to_rgb()
    
    rgb_output = []
    for i in range(3):
        lim_1 = rgb_first[i]
        lim_2 = rgb_second[i]
        if lim_1 > lim_2:
            lim_1, lim_2 = lim_2, lim_1
        rgb_output.append(randint(lim_1, lim_2))
        
    return color_from_rgb(rgb_output)


def mean_color(first, second):
    rgb_first = first.to_rgb()
    rgb_second = second.to_rgb()
    
    rgb_mean = []
    for i in range(3):
        rgb_mean.append((rgb_first[i] + rgb_second[i]) // 2)

    return color_from_rgb(rgb_mean)


def modify_color(color, delta, coef):
    rgb  = color.to_rgb()
    for i in range(2):
        rgb[i] = int(rgb[i] * coef) + delta
    return color_from_rgb(rgb)


def colors_delta(first, second):
    rgb_first = first.to_rgb()
    rgb_second = second.to_rgb()
    delta = 0
    for i in range(3):
        delta += abs(rgb_first[i] - rgb_second[i])
    return delta


def colors_are_equal(first, second):
    delta = colors_delta(first, second)
    if delta <= 6:
        return True
    else:
        return False


def randstr(length, lvl=3):
    s = ""
    for i in range(length):
        roll = randint(1, lvl)
        if roll == 1:
            c = chr(randint(48, 57))
        elif roll == 2:
            c = chr(randint(65, 90))
        elif roll == 3:
            c = chr(randint(97, 122))
        elif roll == 4:
            c = choice(SYMBS)
        s = s + c
    return s


def randstrchoice(length, chars):
    s = []
    for i in range(length):
        s.append(choice(chars))
    return ''.join(s)


