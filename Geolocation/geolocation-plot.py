# import gmplot package
import gmplot
import requests
import json
import socket
from requests import get
import urllib.request



hostname = socket.gethostname()
print("My Computer Name is:" + hostname)


ip = get('https://api.ipify.org').text
print('My public IP address is:'+ ip)

external_ip = urllib.request.urlopen('https://ident.me').read().decode('utf8')

print("My ipV6 address is "+ external_ip)

response = requests.get("http://ip-api.com/json/"+ip)  #use external_ip if ip not working

data = response.json()

print(data)

lat_client = float(data["lat"])
lon_client = float(data["lon"])

latitude_list = [ lat_client, 26.2585]   #26.2585 and 82.0660 are coordinates of Sultanpur
longitude_list = [ lon_client, 82.0660]  #Sultanpur, Uttar Pradesh

gmap3 = gmplot.GoogleMapPlotter(lat_client,
								lon_client, 13)

# scatter method of map object
# scatter points on the google map
gmap3.scatter( latitude_list, longitude_list, '# FF0000',
							size = 40, marker = False )

# Plot method Draw a line in
# between given coordinates
gmap3.plot(latitude_list, longitude_list,
		'red', edge_width = 2.5)

gmap3.draw( "C:\\Users\\SHIVANG\\Desktopmap11.html") #enter the path where file is to be stored
