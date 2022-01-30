import time
import unidecode
from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager
from webdriver_manager.utils import ChromeType
from selenium.webdriver.chrome.options import Options
import requests
import threading

chrome_options = Options()
chrome_options.add_argument("--headless")


def scrapeRom(namesString):
    names = namesString.split(',')
    finalstring = ""
    driver = webdriver.Chrome(ChromeDriverManager(chrome_type=ChromeType.CHROMIUM).install())
    # , options=chrome_options
    for name in names:
        try:
            romNumber = name.split(';')[0]
            name = name.split(';')[1]
            name = name.replace("-", " ")
            name = name.replace("(USA)", " ")
            name = name.replace(".", " ")

            try:
                driver.get("https://www.igdb.com/search?type=1&q=" + name)
                time.sleep(2)
                test = driver.find_element_by_css_selector('div.game-result:nth-child(1) > div:nth-child(1) > '
                                                           'div:nth-child(2) > '
                                                           'h4:nth-child(1) > a:nth-child(1)').get_attribute('href')
                driver.get(test)
                time.sleep(2)
                src = driver.find_element_by_css_selector('.gamepage-cover > img:nth-child(1)').get_attribute('src')
                name = unidecode.unidecode(driver.find_element_by_css_selector('.banner-title').text[:-4])
            except:
                driver.get("https://www.igdb.com/search?type=1&q=" + name)
                time.sleep(5)
                test = driver.find_element_by_css_selector(
                    'div.game-result:nth-child(1) > div:nth-child(1) > div:nth-child(2) > '
                    'h4:nth-child(1) > a:nth-child(1)').get_attribute('href')
                driver.get(test)
                time.sleep(5)
                src = driver.find_element_by_css_selector('.gamepage-cover > img:nth-child(1)').get_attribute('src')
                name = unidecode.unidecode(driver.find_element_by_css_selector('.banner-title').text[:-4])
            response = requests.get(src)
            fileName = "metadata/" + name + ".png"
            file = open(fileName, "wb")
            file.write(response.content)
            file.close()
        except:
            src = "No Match Found"
            name = "No Match Found"
            fileName = "metadata/covermissing.png"
        driver.delete_all_cookies()
        finalstring = finalstring + romNumber + ',' + name + ',' + fileName + ','
    driver.quit()
    return finalstring[:-1]
