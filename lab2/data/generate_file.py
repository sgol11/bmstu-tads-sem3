import random

cars = {'Ford' : 'USA',
        'Chevrolet' : 'USA',
        'Cadillac' : 'USA',
        'Jeep' : 'USA',
        'Audi' : 'Germany',
        'Porsche' : 'Germany',
        'BMW' : 'Germany',
        'Lexus' : 'Japan',
        'Nissan' : 'Japan',
        'Toyota' : 'Japan',
        'Mazda' : 'Japan',
        'Citroen' : 'France',
        'Peugeot' : 'France',
        'Renault' : 'France',
        'Volvo' : 'Sweden',
        'Hyundai' : 'Korea',
        'Ferrari' : 'Italy' }

price = [i for i in range(40000, 100000, 1000)]

color = ['red', 'green', 'blue', 'black', 'white', 'brown',
          'yellow', 'pink', 'gray']

warranty = [i for i in range(20)]
year = [i for i in range(1980, 2015)]
mileage = [i for i in range(20000, 200000, 1000)]
repairs = [i for i in range(4)]
owners = [i for i in range(4)]

f = open('cars_table.txt', 'w')

for i in range(100):
    car_brand = random.choice(list(cars.keys()))
    car_country = cars[car_brand]

    f.write('{}\n'.format(car_brand))
    f.write('{}\n'.format(car_country))
    f.write('{}\n'.format(random.choice(price)))
    f.write('{}\n'.format(random.choice(color)))

    is_new = random.randint(0, 1)

    if is_new:
        f.write('{}\n'.format(random.choice(warranty)))
    else:
        f.write('{}\n'.format(random.choice(year)))
        f.write('{}\n'.format(random.choice(mileage)))
        f.write('{}\n'.format(random.choice(repairs)))
        f.write('{}\n'.format(random.choice(owners)))

    f.write('\n')

for i in range(20):
    car_brand = random.choice(list(cars.keys()))
    car_country = cars[car_brand]

    f.write('{}\n'.format(car_brand))
    f.write('{}\n'.format(car_country))
    f.write('{}\n'.format(random.choice(price)))
    f.write('{}\n'.format(random.choice(color)))

    f.write('{}\n'.format(random.choice(year)))
    f.write('{}\n'.format(random.choice(mileage)))
    f.write('0\n')
    f.write('1\n')

    f.write('\n')

f.close()

