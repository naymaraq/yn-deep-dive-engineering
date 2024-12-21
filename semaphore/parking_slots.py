from threading import *  
from time import sleep
import random

# there are N parking slots
# with a two input gates and two output gates
# design a system to manage the parking slots

N_PARKING_SLOTS = 10
N_INPUT_GATES = 2
N_OUTPUT_GATES = 2
N_CARS = 20

parking_slots = Semaphore(N_PARKING_SLOTS)
input_gates = Semaphore(N_INPUT_GATES)
output_gates = Semaphore(N_OUTPUT_GATES)


class Parking:
    def park(self, car):
        print(f"Car {car} parked")
        sleep(random.randint(1, 3))
    
    def leave(self, car):
        print(f"Car {car} left")
        sleep(random.randint(1, 3))

        
def park_car(parking, car):
    print(f"Car {car} is trying to park")
    parking_slots.acquire()

    input_gates.acquire()
    parking.park(car)
    input_gates.release()

    output_gates.acquire()
    parking.leave(car)
    output_gates.release()

    parking_slots.release()

parking = Parking()
threads = []

for i in range(N_CARS):
    t = Thread(target=park_car, args=(parking, f"car{i}"))
    t.start()
    threads.append(t)

for i in range(N_CARS):
    threads[i].join()

