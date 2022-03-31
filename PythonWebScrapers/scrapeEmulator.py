import os
import platform
import requests
from zipfile import ZipFile
from io import BytesIO
from bs4 import BeautifulSoup
from urllib.request import urlopen
from lxml import html


# Function to scrape Cemu
def Cemu():
    if platform.system() == "Windows":
        try:
            page = requests.get("https://cemu.info/#download")
            soup = BeautifulSoup(page.content, "html.parser")
            zipurl = soup.select_one(".btn").get('href')
            zipPath = os.path.dirname(os.getcwd()) + "\emulators"
            with urlopen(zipurl) as zipresp:
                with ZipFile(BytesIO(zipresp.read())) as zfile:
                    zfile.extractall(zipPath)
        except:
            return "Download failed"
    else:
        return "Cemu " + "is not available on " + platform.system()
    

# Function to scrape mGBA
def mGBA():
    if platform.system() == "Windows":
        try:
            zipurl = "https://github.com/mgba-emu/mgba/releases/download/0.9.3/mGBA-0.9.3-win64.7z"
            zipPath = os.path.dirname(os.getcwd()) + "\emulators"
            with urlopen(zipurl) as zipresp:
                with ZipFile(BytesIO(zipresp.read())) as zfile:
                    zfile.extractall(zipPath)
            
        except:
            return "Download failed"
    else:
        return "mGBA " + "is not available on " + platform.system()



def DeSmuME():
    if platform.system() == "Windows":
        try:
            zipurl = "https://nightly.link/TASEmulators/desmume/workflows/build_win/master/desmume-win-x64.zip"
            zipPath = os.path.dirname(os.getcwd()) + "\emulators/DeSmuME"
            with urlopen(zipurl) as zipresp:
                with ZipFile(BytesIO(zipresp.read())) as zfile:
                    zfile.extractall(zipPath)
        except:
            return "Download failed"
    else:
        return "DeSmuME " + "is not available on " + platform.system()




if __name__ == "__main__":
    DeSmuME()
