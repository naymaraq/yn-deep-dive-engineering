import random
from threading import *  
from time import sleep
N_WORKER = 10

semaphore = Semaphore(2)

class Server:
    def login(self, username):
        print(f"User {username} logged in")
        self.work(username)
        print(f"User {username} finished")
    
    def work(self, username):
        print(f"User {username} is working")
        sleep(random.randint(1, 3))


# open threads
def login_and_work(server, username):
    print(f"User {username} is trying to login")
    semaphore.acquire()
    server.login(username)
    semaphore.release()


server = Server()
threads = []
for i in range(N_WORKER):
    t = Thread(target=login_and_work, args=(server, f"user{i}"))
    t.start()
    threads.append(t)

# close threads
for i in range(N_WORKER):
    threads[i].join()

