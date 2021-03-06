from importlib.metadata import MetadataPathFinder
import time
import unidecode
from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager
from webdriver_manager.utils import ChromeType
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
import requests
import json
import os

def metadata(test):


    #find_element(by=By.CSS_SELECTOR, value=css_selector)

    curDir = os.getcwd()



    # Open roms json
    f = open(curDir + '/config/paths/roms.json')
    roms = json.load(f)
    f.close()


    needed = []

    for rom in roms:

        if rom["imagePathIGDB"] == "" or not os.path.exists(rom["imagePathIGDB"]):
            needed.append(rom)



    chrome_options = Options()
    #chrome_options.add_argument("--headless")
    driver = webdriver.Chrome(service=Service(ChromeDriverManager(chrome_type=ChromeType.CHROMIUM).install()),options=chrome_options)


    for i in range(len(needed)):
        try:
            IGDBSearchQuery = needed[i]["filename"]

            IGDBSearchQuery = IGDBSearchQuery.replace("-", " ")
            IGDBSearchQuery = IGDBSearchQuery.replace("(USA)", " ")
            IGDBSearchQuery = IGDBSearchQuery.replace(".", " ")

            try:
                driver.get("https://www.igdb.com/search?type=1&q=" + IGDBSearchQuery)
                time.sleep(2)
                #firstResult = driver.find_element_by_css_selector('div.game-result:nth-child(1) > div:nth-child(1) > ''div:nth-child(2) > ''h4:nth-child(1) > a:nth-child(1)').get_attribute('href')
                firstResult = driver.find_element_by_css_selector('div.media:nth-child(1) > div:nth-child(2) > a:nth-child(1)').get_attribute('href')
                driver.get(firstResult)
                time.sleep(2)
                src = driver.find_element_by_css_selector('.gamepage-cover > img:nth-child(1)').get_attribute('src')
                nameIGDB = unidecode.unidecode(driver.find_element_by_css_selector('.banner-title').text[:-4])
            except:
                driver.get("https://www.igdb.com/search?type=1&q=" + IGDBSearchQuery)
                time.sleep(5)
                firstResult = driver.find_element_by_css_selector('div.media:nth-child(1) > div:nth-child(2) > a:nth-child(1)').get_attribute('href')
                driver.get(firstResult)
                time.sleep(5)
                src = driver.find_element_by_css_selector('.gamepage-cover > img:nth-child(1)').get_attribute('src')
                IGDBSearchQuery = unidecode.unidecode(driver.find_element_by_css_selector('.banner-title').text[:-4])
            response = requests.get(src)
            fileName = "metadata/" + nameIGDB + ".png"
            file = open(fileName, "wb")
            file.write(response.content)
            file.close()
        except:
            src = "No Match Found"
            nameIGDB = "No Match Found"
            fileName = "metadata/covermissing.png"


        needed[i]["nameIGDB"] = nameIGDB
        needed[i]["imagePathIGDB"] = fileName

        for rom in roms:
            if rom['filename'] == needed[i]['filename']:
                rom = needed[i]
            

    driver.delete_all_cookies()
    driver.quit()



    # Serializing json 
    json_object = json.dumps(roms, indent = 4)
  
    # Writing to roms.json
    with open(curDir + '/config/paths/roms.json', "w") as outfile:
        outfile.write(json_object)
    return("test")

#if __name__ == "__main__":
    #metadata("test")