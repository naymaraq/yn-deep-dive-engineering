import asyncio
import requests
import aiohttp
import aiofiles
import os
import threading

from time import time

async def download_image_async(url, filename="image.jpg"):
    async with aiohttp.ClientSession() as session:
        async with session.get(url) as response:
            image = await response.read()  # Download image data
            
            if response.status != 200:
                print(f"Failed to download image: {response.status}")
                return

            print("Image downloaded")  # This will now run

            # Save image to file
            async with aiofiles.open(filename, "wb") as file:
                await file.write(image)
            print(f"Image saved as {filename}")


def download_image_sync(url, filename="image.jpg"):
    response = requests.get(url)
    image = response.content

    if response.status_code != 200:
        print(f"Failed to download image: {response.status_code}")
        return

    print("Image downloaded")

    with open(filename, "wb") as file:
        file.write(image)
    print(f"Image saved as {filename}")



N_REQUESTS = 100

def download_files_sync(folder):
    URL  = "https://loremflickr.com/cache/resized/defaultImage.small_1000_1000_nofilter.jpg"
    os.makedirs(folder, exist_ok=True)
    for i in range(N_REQUESTS):
        filename =  os.path.join(folder, f"image_{i}.jpg")  
        download_image_sync(URL, filename)
    print("All images downloaded successfully")


def download_files_threads(folder):
    URL  = "https://loremflickr.com/cache/resized/defaultImage.small_1000_1000_nofilter.jpg"
    os.makedirs(folder, exist_ok=True)
    
    threads = []
    for i in range(N_REQUESTS):
        filename =  os.path.join(folder, f"image_{i}.jpg")  
        thread = threading.Thread(target=download_image_sync, args=(URL, filename))
        thread.start()
        threads.append(thread)
    
    # Wait for all threads to finish
    for thread in threads:
        thread.join()
    print("All images downloaded successfully")


async def download_files_async(folder):
    URL  = "https://loremflickr.com/cache/resized/defaultImage.small_1000_1000_nofilter.jpg"
    os.makedirs(folder, exist_ok=True)
    tasks = []
    for i in range(N_REQUESTS):
        filename =  os.path.join(folder, f"image_{i}.jpg")  
        tasks.append(download_image_async(URL, filename))
    await asyncio.gather(*tasks)
    print("All images downloaded successfully")


if __name__ == "__main__":

    # Synchronous download
    start = time()
    download_files_sync("images_sync")
    exec_time = time() - start
    print(f"Execution time for synchronous download: {exec_time:.2f} seconds")

    # Threaded download
    start = time()
    download_files_threads("images_threads")
    exec_time = time() - start
    print(f"Execution time for threaded download: {exec_time:.2f} seconds")

    # Asynchronous download
    start = time()
    asyncio.run(download_files_async("images_async"))
    exec_time = time() - start
    print(f"Execution time for asynchronous download: {exec_time:.2f} seconds")
