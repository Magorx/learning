from random import randint, choice

LOWEST_ITEMS = ["rope", "square", "triangle", "circle", "box"]
LOWEST_MATERIALS = ["wooden", "stone", "paper", "plastic"]
LOWEST_CONDTS = ["brown", "painted", "cool", "good", "nice"]

class thing():
    price = -999
    name = "ERROR"
    material = "TITANIT"
    condt = "BUGGED"
    lvl = -999
    def gen_lowest(self, price = randint(3, 8)):
        self.nullify()
        if randint(0, 30):
            self.lvl = 1
        else:
            self.lvl = 2
        self.name = choice(LOWEST_ITEMS)
        roll = randint(2, 4)
        self.price += roll
        price -= roll
        if price <= 0:
            return 0
        if randint(0, 1):
            self.material = choice(LOWEST_MATERIALS)
            roll = randint(2, 4)
            self.price += roll
            price -= roll
            if price <= 0:
                return 0
            self.condt = choice(LOWEST_CONDTS)
            roll = randint(2, 4)
            self.price += roll
        else:
            self.condt = choice(LOWEST_CONDTS)
            roll = randint(2, 4)
            self.price += roll
            price -= roll
            if price <= 0:
                return 0
            self.material = choice(LOWEST_MATERIALS)
            roll = randint(2, 4)
            self.price += roll
    def mix(self, other):
        if randint(0, 1):
            self.name = other.name
        if randint(0, 1):
            self.material = other.material
        if randint(0, 1):
            self.condt = other.condt
        other.nullify()
        del inv[inv.index(other)]
    def nullify(self):
        if not self.name:
            return 1
        self.price = 0
        self.lvl = 0
        self.name = ""
        self.material = ""
        self.condt = ""
        return 0
    def tell(self):
        if self.condt:
            print(self.condt, end=' ')
        if self.material:
            print(self.material, end=' ')
        if self.name:
            print(self.name, end=' ')
        print()


obj = thing()
c1 = 0
c2 = 0
inventory = [thing() for i in range(10)]
inv = inventory
for i in range(len(inv)):
    inv[i].gen_lowest()
for i in range(len(inv)):
    inv[i].tell()
for i in range(5):
    print(i)
    inv[randint(0, len(inv))].mix(inv[randint(0, len(inv))])
print("=====")
for i in range(len(inv)):
    inv[i].tell()
