from fastapi import FastAPI
import web_publisher as wp

app = FastAPI()

# a dict to contain the MAC ids of registered devices
registered_devices = {}
# a dict that maps ids, issued by this server, to raspberry pi objects 
registered_pis = {}

@app.get("/get_pi_info/all")
def see_all_devices():
    return registered_devices

@app.get("/get_pi_info/{pi_id}")
def read(pi_id: str):
    # return information stored for the raspberry pi with the given id
    if pi_id in registered_pis:
        all_info = registered_pis[pi_id].information
        return f"rPi{pi_id}\n {all_info}"
    return "id " + pi_id

# register with server
@app.get("/register/{mac_address}")
def register_device(mac_address: str):
    pi = raspberry_pi(mac_address, len(registered_devices))
    registered_devices[mac_address] = pi
    registered_pis[pi.app_id] = pi
    return pi.app_id

# recieve data from pi:
@app.put("/give_pi_info/{pi_info}")
def store_pi_info(pi_info):
    pi_id = pi_info.pi_id
    