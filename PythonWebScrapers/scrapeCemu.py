from importlib.resources import path
import os
import requests
from bs4 import BeautifulSoup
from lxml import html
from zipfile import ZipFile
from urllib.request import urlopen
from io import BytesIO


# Function to scrape Cemu
def __main__():
    page = requests.get("https://cemu.info/#download")
    soup = BeautifulSoup(page.content, "html.parser")
    zipurl = soup.select_one(".btn").get('href')
    zipPath = os.path.dirname(os.getcwd()) + "\emulators"
    with urlopen(zipurl) as zipresp:
        with ZipFile(BytesIO(zipresp.read())) as zfile:
            zfile.extractall(zipPath)
            print(zfile)


if __name__ == '__main__':
    __main__()