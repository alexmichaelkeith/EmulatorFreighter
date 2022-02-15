import time
import unidecode
from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager
from webdriver_manager.utils import ChromeType
from selenium.webdriver.chrome.options import Options
import requests
from lxml import html

# Function to scrape Cemu

page = requests.get("https://cemu.info/#download")
    

tree = html.fromstring(page)

test = tree.xpath('/html/body/div/div[7]/div/a/@href')


print(tree)
