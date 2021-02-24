# This will publish tests to the broker.
from fastapi import FastAPI
import test_publisher as test_pub

app = FastAPI()

@app.get("/runall")
def run_all_tests():
    return test_pub.publish('run all')