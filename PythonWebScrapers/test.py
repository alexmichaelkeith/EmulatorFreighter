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
def scrapeRom(roms):

    chrome_options = Options()
    #chrome_options.add_argument("--headless")
    driver = webdriver.Chrome(service=Service(ChromeDriverManager(chrome_type=ChromeType.CHROMIUM).install()),options=chrome_options)


    for rom in roms:
        try:
            IGDBSearchQuery = rom["filename"]

            IGDBSearchQuery = IGDBSearchQuery.replace("-", " ")
            IGDBSearchQuery = IGDBSearchQuery.replace("(USA)", " ")
            IGDBSearchQuery = IGDBSearchQuery.replace(".", " ")

            try:
                driver.get("https://www.igdb.com/search?type=1&q=" + IGDBSearchQuery)
                time.sleep(2)
                firstResult = driver.find_element_by_css_selector('div.game-result:nth-child(1) > div:nth-child(1) > '
                                                           'div:nth-child(2) > '
                                                           'h4:nth-child(1) > a:nth-child(1)').get_attribute('href')
                driver.get(firstResult)
                time.sleep(2)
                src = driver.find_element_by_css_selector('.gamepage-cover > img:nth-child(1)').get_attribute('src')
                nameIGDB = unidecode.unidecode(driver.find_element_by_css_selector('.banner-title').text[:-4])
            except:
                driver.get("https://www.igdb.com/search?type=1&q=" + IGDBSearchQuery)
                time.sleep(5)
                firstResult = driver.find_element_by_css_selector(
                    'div.game-result:nth-child(1) > div:nth-child(1) > div:nth-child(2) > '
                    'h4:nth-child(1) > a:nth-child(1)').get_attribute('href')
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
        driver.delete_all_cookies()
    driver.quit()
    return nameIGDB, fileName



def metadata(test):


    # Open metadata queue json
    f = open('C:\EmulatorFreighter\config\paths/temp.json')
    queueRoms = json.load(f)
    f.close()


    # Open roms json
    f = open('C:\EmulatorFreighter\config\paths/roms.json')
    roms = json.load(f)
    f.close()


    # Loop to search for matching paths and search for metadata
    for replaced in roms:
        for replacer in queueRoms:
            if replaced["path"] == replacer["path"]:
                # Scrape rom and update metadata
                replaced["nameIGDB"], replaced["imagePathIGDB"] = scrapeRom(replaced)



    # Serializing json 
    json_object = json.dumps(roms, indent = 4)
  
    # Writing to roms.json
    with open("C:\EmulatorFreighter\config\paths/roms.json", "w") as outfile:
        outfile.write(json_object)

    return("Youre gay")