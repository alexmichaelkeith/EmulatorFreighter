import time
import unidecode
from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager
from webdriver_manager.utils import ChromeType
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
import requests
import json

# Function to scrape the IGDG using rom names for metadata
    #chrome_options.add_argument("--headless")






# Open metadata queue json
f = open('C:\EmulatorFreighter\config\paths/temp.json')
queueRoms = json.load(f)
for rom in queueRoms:
    rom['nameIGDB'] = "cats"
    rom['imagePathIGDB'] = "dogs"
f.close()

# Open roms json
f = open('C:\EmulatorFreighter\config\paths/roms.json')
roms = json.load(f)
f.close()


# Loop to search for matching paths and replace metadata
for replaced in roms:
    for replacer in queueRoms:
        if replaced["path"] == replacer["path"]:
            replaced["nameIGDB"] = replacer["nameIGDB"]
            replaced["imagePathIGDB"] = replacer["imagePathIGDB"]

# Serializing json 
json_object = json.dumps(roms, indent = 4)
  
# Writing to sample.json
with open("C:\EmulatorFreighter\config\paths/test.json", "w") as outfile:
    outfile.write(json_object)
