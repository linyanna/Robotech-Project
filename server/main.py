from dotenv import load_dotenv
import os
import base64
from requests import post, get
import json

load_dotenv()

client_id = os.getenv("CLIENT_ID")
client_secret = os.getenv("CLIENT_SECRET")

# Request and gets access token
def get_token():
    # Create auth string from base64 encoding of client id and secret
    auth_string = client_id + ":" + client_secret
    auth_bytes = auth_string.encode("utf-8")
    auth_base64 = str(base64.b64encode(auth_bytes), "utf-8")

    # Setting up Post request to url, following Spotify Client Credentials page
    url = "https://accounts.spotify.com/api/token"
    headers = { "Authorization": "Basic " + auth_base64, 
               "Content-Type": "application/x-www-form-urlencoded"
               }
    data = {"grant_type": "client_credentials"}

    # Making the Post request and converting json content string to Python dict to be able to access it
    result = post(url, headers=headers, data=data)
    json_result = json.loads(result.content)
    token = json_result["access_token"]
    return token

# Help us construct rest of headers
def get_auth_header(token):
    return {"Authorization": "Bearer " + token}

# Construct query to search for artist
def search_for_artist(token, artist_name):
    url = "https://api.spotify.com/v1/search"
    headers = get_auth_header(token)
    # "?q (query string) = {[whatever text value being searched for]}&type="[list of things being looked for, ie. "artist,track"]&limit (quantity to grab)"
    query = f"?q={artist_name}&type=artist&limit=1"

    query_url = url + query
    result = get(query_url, headers=headers)
    json_result = json.loads(result.content)["artists"]["items"]
    if len(json_result) == 0:
      print("No artist with this name exists")
      return None
    return json_result[0]

def get_songs_by_artist(token, artist_id):
    url = f"https://api.spotify.com/v1/artists/{artist_id}/top-tracks?country=US"
    headers = get_auth_header(token)
    result = get(url, headers=headers)
    json_result = json.loads(result.content)["tracks"]
    return json_result

# Construct query to search for track
def get_track_genre(token, track_name):
    url = "https://api.spotify.com/v1/search"
    headers = get_auth_header(token)
    # "?q (query string) = {[whatever text value being searched for]}&type="[list of things being looked for, ie. "artist,track"]&limit (quantity to grab)"
    query = f"?q={track_name}&type=track&limit=1"

    query_url = url + query
    result = get(query_url, headers=headers)
    json_result = json.loads(result.content)["artists"]["items"]
    if len(json_result) == 0:
      print("No artist with this name exists")
      return None
    return json_result[0]
  
token = get_token()
result = search_for_artist(token, "BTS")
artist_id = result["id"]
songs = get_songs_by_artist(token, artist_id)

for index, song in enumerate(songs):
  print(f"{index + 1}. {song['name']}")    
