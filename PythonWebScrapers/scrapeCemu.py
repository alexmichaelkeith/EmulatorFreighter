import os
import platform
import requests
from zipfile import ZipFile
from io import BytesIO
from bs4 import BeautifulSoup
from urllib.request import urlopen
from lxml import html


# Function to scrape Cemu
def main():
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

if __name__ == "__main__":
    main()