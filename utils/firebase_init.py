import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

class FirebaseReader:
    def __init__(self):
        cred = credentials.Certificate("data/firebase_credentials/smart-garbage-monitoring-key.json")

        firebase_admin.initialize_app(cred, {
         'databaseURL': 'https://junior-817bf-default-rtdb.asia-southeast1.firebasedatabase.app/'
            })

        

        self.ref = db.reference('/')

    def get_active_bins(self):
        active_bins = []
        data = self.ref.get()

        for node in data:
            if data[node]['state'] == 1:
                active_bins.append(node)

        return active_bins
