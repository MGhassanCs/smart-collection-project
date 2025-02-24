import json
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import argparse

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--town_name', type=str, default="pondicherry_india")
    
    name = parser.parse_args().town_name
    cred = credentials.Certificate("data/firebase_credentials/smart-garbage-monitoring-key.json")

    firebase_admin.initialize_app(cred, {
        'databaseURL': 'https://smart-garbage-monitoring-f4b77-default-rtdb.europe-west1.firebasedatabase.app'
    })

    ref = db.reference("/")

    with open(f'data/maps/{name}/{name}_bin_data.json', "r") as file:
        bin_data = json.load(file)

    ref.set(bin_data)
 
if __name__ == "__main__":
    main()